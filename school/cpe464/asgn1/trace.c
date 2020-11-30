/* CPE464 Asgn 1 
 * Prof Smith
 * written by Jared Spadaro
 * 1/23/17
 */

#include <stdlib.h>
#include <stdio.h>
#include <pcap/pcap.h>
#include <stdint.h>
#include <sys/types.h>
#include "checksum.h"
#include <arpa/inet.h>
#include <string.h>

#define MAC_ADDR_LEN 6
#define ETH_TYPE_LEN 2
#define IP_ADDR_LEN 4
#define IP 0
#define ARP 1
#define UNKNOWN -1
#define UDP 17
#define TCP 6
#define ICMP 1
#define HTTP 80
#define DNS 53
#define TELNET 23
#define FTP 21
#define POP3 110
#define SMTP 25
#define CHECK 0
#define PARSE 1
#define SYN 0x2;
#define RST 0x4;
#define FIN 0x1;
#define ACK 0x10;
#define MAX_PACKET_LEN 65535
#define MAX_TCP_OPTIONS_LEN 40
#define REPLY 0
#define REQUEST 8

/* Data Structures */
typedef struct eth_t {
   uint8_t dest_mac[MAC_ADDR_LEN];
   uint8_t src_mac[MAC_ADDR_LEN];
   uint8_t type[ETH_TYPE_LEN];
} eth_t;

typedef struct arp_t {
   uint8_t hardware[2];
   uint8_t protocol[2];
   uint8_t hardware_addr_len;
   uint8_t protocol_addr_len;
   uint8_t opcode[2];
   uint8_t src_mac[MAC_ADDR_LEN];
   uint8_t src_ip[IP_ADDR_LEN];
   uint8_t dest_mac[MAC_ADDR_LEN];
   uint8_t dest_ip[IP_ADDR_LEN];
} arp_t;

typedef struct ip_t {
   uint8_t ver_and_hdr_len;
   uint8_t TOS;
   uint16_t total_len;
   uint8_t ID[2];
   uint8_t flags_frag_offset[2];
   uint8_t TTL;
   uint8_t protocol;
   uint16_t checksum;
   uint8_t src_ip[4];
   uint8_t dest_ip[4];
} ip_t;
      
typedef struct tcp_t {
   uint16_t src_port;
   uint16_t dest_port;
   uint32_t seq_num;
   uint32_t ack_num;
   uint16_t hdr_len_and_flags;
   uint16_t win_size;
   uint16_t checksum;
   uint16_t urgent_ptr;
} tcp_t;

typedef struct tcp_pseudo_t {
   uint8_t src_ip[4];
   uint8_t dest_ip[4];
   uint8_t padding;
   uint8_t protocol;
   uint16_t hdr_len;
} tcp_pseudo_t;

typedef struct tcp_cksum_t {
   struct tcp_pseudo_t tcp_pseudo_hdr;
   struct tcp_t tcp_hdr;
   uint8_t data[MAX_PACKET_LEN + MAX_TCP_OPTIONS_LEN];
} tcp_cksum_t;
   
typedef struct udp_t {
   uint16_t src_port;
   uint16_t dest_port;
   uint16_t len;
   uint16_t checksum;
} udp_t;

/* Function Prototypes */
int CheckType(uint8_t *);
void Parse_Eth_Hdr(pcap_t *, struct eth_t *, const uint8_t *);
void Sniff(char *);
void Parse_Arp_Hdr(const uint8_t *);
char *CheckOpcode(uint8_t *);
void Print_MAC_Addr(uint8_t *);
void Print_IP_Addr(uint8_t *);
void Parse_IP_Hdr(const uint8_t *);
char *CheckProtocol(uint8_t, int, const uint8_t *, struct ip_t *, 
 uint8_t, uint8_t);
void Parse_TCP_Hdr(const uint8_t *, struct ip_t *, uint8_t);
void CheckFlag(uint16_t, uint16_t);
void CheckPort(uint16_t);
uint16_t TCP_Cksum(struct tcp_t *, struct ip_t *, uint8_t, uint8_t);
void Parse_ICMP_Hdr (const uint8_t *, uint8_t);
void Parse_UDP_Hdr (const uint8_t *);

int CheckType (uint8_t type[ETH_TYPE_LEN]) {
   if (type[0] == 0x08 && type[1] == 0) {
      return IP;
   }
   else if (type[0] == 0x08 && type[1] == 0x06) {
      return ARP;
   } 
   else {
      return UNKNOWN;
   }
}

char *CheckOpcode (uint8_t opcode[2]) {
   if (opcode[1] == 1) {
      return "Request\n";
   }
   else if (opcode[1] == 2) {
      return "Reply\n";
   }
   else {
      return "Unknown ARP type\n";
   }
}

void Print_MAC_Addr (uint8_t MAC_addr[MAC_ADDR_LEN]) {
   int i;
   for (i = 0; i < MAC_ADDR_LEN; i++) {
      printf("%x", MAC_addr[i]);
      if (i != MAC_ADDR_LEN -1) {
         printf(":");
      }
   }
   printf("\n");
}

void Print_IP_Addr (uint8_t IP_addr[IP_ADDR_LEN]) {
   int i;
   for (i = 0; i < IP_ADDR_LEN; i++) {
      printf("%d", IP_addr[i]);
      if (i != IP_ADDR_LEN - 1) {
         printf(".");
      }
   }
   printf("\n");
}

void Parse_ICMP_Hdr (const uint8_t *data, uint8_t ip_ver) {
   data += sizeof(ip_t);
   printf("       ICMP Header\n");
   printf("             Type: ");
   if (ip_ver != 4) {
      printf("109\n");
   }
   else if (*data == REPLY) {
      printf("Reply\n");
   }
   else if (*data == REQUEST) {
      printf("Request\n");
   }
   else {
      printf("Unknown\n");
   }
}

void Parse_UDP_Hdr (const uint8_t *data) {
   struct udp_t *udp_hdr;
   data += sizeof(ip_t);
   udp_hdr = (udp_t *)data;
   
   printf("       UDP Header\n");
   printf("            Source Port: ");             
   CheckPort(htons(udp_hdr->src_port));
   printf("            Dest Port: ");
   CheckPort(htons(udp_hdr->dest_port));
   printf("\n");
}
      
char *CheckProtocol (uint8_t arg, int flag, const uint8_t *data,
struct ip_t *ip_hdr, uint8_t ip_hdr_len, uint8_t ip_ver) {
   char *ret;
   if (arg == UDP) {
      ret = "UDP\n";
      if (flag == PARSE) {
         Parse_UDP_Hdr(data);
      }
   }
   else if (arg == TCP) {
      ret = "TCP\n";
      if (flag == PARSE) {
         Parse_TCP_Hdr(data, ip_hdr, ip_hdr_len);
      }
   }
   else if (arg == ICMP) {
      ret = "ICMP\n";
      if (flag == PARSE) {
         Parse_ICMP_Hdr(data, ip_ver);
      }
   }
   else {
      ret = "Unknown\n";
   }
   return ret;
}

/* Parse Arp header (request or reply) */
void Parse_Arp_Hdr (const uint8_t *data) {
   arp_t *arp_hdr = malloc(sizeof(arp_t)); 
   data += sizeof(eth_t); /* move data pointer to start of ARP hdr */
   arp_hdr = (arp_t *)data; 
   printf("        ARP header\n");
   printf("                Opcode: ");
   printf(CheckOpcode(arp_hdr->opcode));
   printf("                Sender MAC: ");
   Print_MAC_Addr(arp_hdr->src_mac);
   printf("                Sender IP: ");
   Print_IP_Addr(arp_hdr->src_ip);
   printf("                Target MAC: ");
   Print_MAC_Addr(arp_hdr->dest_mac);
   printf("                Target IP: ");
   Print_IP_Addr(arp_hdr->dest_ip);
   printf("\n");
}  
  
void Parse_IP_Hdr (const uint8_t *data) {
   ip_t *ip_hdr = malloc(sizeof(ip_t));
   uint8_t mask = 0xF0;
   uint8_t len, ver;
   uint16_t src_cksum, my_cksum;
   
   data += sizeof(eth_t);
   ip_hdr = (ip_t *)data;
   ver = (ip_hdr->ver_and_hdr_len & mask) >> 4;
   printf("        IP Header\n");
   printf("                IP Version: ");
   printf("%d\n", ver);
   printf("                Header Len (bytes): ");
   mask = 0xF;
   len = (ip_hdr->ver_and_hdr_len & mask) * 4;
   printf("%d\n", len);
   printf("                TOS subfields:\n");
   mask = 0xFC;
   printf("                   Diffserv bits: %d\n", (ip_hdr->TOS & mask) >> 2);
   mask = 0x3;
   printf("                   ECN bits: %d\n", ip_hdr->TOS & mask);
   printf("                TTL: %d\n", ip_hdr->TTL);
   printf("                Protocol: %s", 
    CheckProtocol(ip_hdr->protocol, CHECK, NULL, NULL, 0, 0));
   printf("                Checksum: ");
  
   src_cksum = ip_hdr->checksum;
   ip_hdr->checksum = 0;
   my_cksum = in_cksum((unsigned short *)ip_hdr, len);
   if (src_cksum == my_cksum) {
      printf("Correct (0x%04x)\n", ntohs(my_cksum));
   }
   else {
     printf("Incorrect (0x%04x)\n", ntohs(src_cksum));  
   }

   printf("                Sender IP: ");
   Print_IP_Addr(ip_hdr->src_ip);
   printf("                Dest IP: ");
   Print_IP_Addr(ip_hdr->dest_ip);
   printf("\n");
   CheckProtocol(ip_hdr->protocol, PARSE, data, ip_hdr, len, ver);
}
 
void CheckPort (uint16_t port) {
   if (port == HTTP) {
      printf("HTTP\n");
   }
   else if (port == DNS) {
      printf("DNS\n");
   }
   else if (port == TELNET) {
      printf("Telnet\n");
   }
   else if (port == FTP) {
      printf("FTP\n");
   }
   else if (port == POP3) {
      printf("POP3\n");
   }
   else if (port == SMTP) {
      printf("SMTP\n");
   }
   else {
      printf("%d\n", port);
   }
}  
 
void CheckFlag (uint16_t arg, uint16_t flag) {
   if (arg & flag) {
      printf("Yes\n");
   }
   else {
      printf("No\n");
   }
}
 
void Parse_TCP_Hdr(const uint8_t *data, struct ip_t *ip_hdr, 
 uint8_t ip_hdr_len) {
   struct tcp_t *tcp_hdr;
   uint8_t mask = 0xF0;
   uint8_t *temp = (uint8_t *)ip_hdr;
   uint16_t flag = SYN; 
   uint16_t hdr_len;
   
   temp += sizeof(ip_t);
   tcp_hdr = (struct tcp_t *)temp;
   hdr_len = (tcp_hdr->hdr_len_and_flags & mask) >> 2;
   
   printf("         TCP Header\n");
   printf("                 Source Port: ");
   CheckPort(ntohs(tcp_hdr->src_port));
   printf("                 Dest Port: ");
   CheckPort(ntohs(tcp_hdr->dest_port));
   printf("                 Sequence Number: %u\n", ntohl(tcp_hdr->seq_num));
   printf("                 ACK Number: %u\n", ntohl(tcp_hdr->ack_num));
   printf("                 Data Offset (bytes): %d\n", hdr_len);  
   printf("                 SYN Flag: "); 
   
   CheckFlag(ntohs(tcp_hdr->hdr_len_and_flags), flag);
   flag = RST;
   printf("                 RST Flag: ");
   CheckFlag(ntohs(tcp_hdr->hdr_len_and_flags), flag);
   flag = FIN;
   printf("                 FIN Flag: ");
   CheckFlag(ntohs(tcp_hdr->hdr_len_and_flags), flag);
   flag = ACK;
   printf("                 ACK Flag: ");
   CheckFlag(ntohs(tcp_hdr->hdr_len_and_flags), flag);
   
   printf("                 Window Size: %d\n", ntohs(tcp_hdr->win_size));   
   printf("                 Checksum: ");
   TCP_Cksum(tcp_hdr, ip_hdr, hdr_len, ip_hdr_len);
}    
 
uint16_t TCP_Cksum(struct tcp_t *tcp_hdr, struct ip_t *ip_hdr, 
 uint8_t tcp_hdr_len, uint8_t ip_hdr_len) {
   struct tcp_pseudo_t pseudo_hdr;
   struct tcp_cksum_t cksum_in;
   uint8_t *pseudo_temp = (uint8_t *)&pseudo_hdr, *data_temp, *options_temp;
   uint16_t tcp_total_len, tcp_data_len, cksum, my_cksum;
   
   memmove(pseudo_temp, ip_hdr->src_ip, 4);
   pseudo_temp += 4;
   memmove(pseudo_temp, ip_hdr->dest_ip, 4);
   pseudo_temp += 4;
   memset(pseudo_temp, 0, 1);
   pseudo_temp++;
   memmove(pseudo_temp, &ip_hdr->protocol, 1);
   pseudo_temp++;
   
   /* calculate length of tcp segment (header + data) */
   tcp_total_len = ntohs(ip_hdr->total_len) - ip_hdr_len;
   tcp_data_len = tcp_total_len - tcp_hdr_len;
   tcp_total_len = htons(tcp_total_len); 
   memmove(pseudo_temp, &tcp_total_len, 2);

   data_temp = (uint8_t *)tcp_hdr + tcp_hdr_len;
   
   cksum_in.tcp_pseudo_hdr = pseudo_hdr;
   cksum_in.tcp_hdr = *tcp_hdr;

   options_temp = cksum_in.data;
   memmove(options_temp, data_temp, tcp_data_len);
   
   if (tcp_hdr_len > sizeof(tcp_t)) {
      options_temp += tcp_data_len;
      memmove(options_temp, (uint8_t *)tcp_hdr + sizeof(tcp_t), 
       tcp_hdr_len - sizeof(tcp_t));
   }   

   cksum = cksum_in.tcp_hdr.checksum;
   cksum_in.tcp_hdr.checksum = 0;
   my_cksum = in_cksum((uint16_t *)&cksum_in, 
    sizeof(tcp_pseudo_t) + tcp_hdr_len + tcp_data_len);
   if (cksum == my_cksum) {
      printf("Correct (0x%04x)\n", ntohs(my_cksum));
   }
   else {
      printf("Incorrect (0x%04x)\n", ntohs(cksum));
   } 
   return 0;  
}   

void Parse_Eth_Hdr (pcap_t *stream, struct eth_t *eth_header,
const uint8_t *data) {
   int result;
   
   printf("        Ethernet Header\n");
   eth_header = (eth_t *)data;
   printf("                Dest MAC: ");
   Print_MAC_Addr(eth_header->dest_mac);     
   printf("                Source MAC: ");
   Print_MAC_Addr(eth_header->src_mac);
   printf("                Type: ");
   
   result = CheckType(eth_header->type);
   if (result == IP) {
      printf("IP\n\n");
      Parse_IP_Hdr(data);
   }
   else if (result == ARP) {
     printf("ARP\n\n");
     Parse_Arp_Hdr(data);
   }
   else {
      printf("Unknown\n\n");
   }        
}

void Sniff(char *filename) {
   pcap_t *stream;
   struct pcap_pkthdr *hdr;
   struct eth_t *eth_header;
   const uint8_t *data;
   char *errbuf;
   uint32_t len;   
   int ndx = 1, result;

   eth_header = malloc(sizeof(eth_t));
   errbuf = malloc(PCAP_ERRBUF_SIZE);
   
   stream = pcap_open_offline(filename, errbuf);
   
   if (stream == NULL) {
      fprintf(stderr, "%s\n", errbuf);
      exit(1);
   }

   while (1) {
      result = pcap_next_ex(stream, &hdr, &data);
      if (result == -1) {
         pcap_perror(stream, "pcap_next");
         exit(1);
      }
      else if (result == -2) {
         exit(1);
      }
      else {}
  
      len = hdr->len;
      printf("\nPacket number: %d  Packet Len: %d\n\n", ndx, (int)len);
      Parse_Eth_Hdr(stream, eth_header, data);
      ndx++;
   }
}

int main (int argc, char **argv) {
   if (argc < 2) {
      fprintf(stderr, "Usage: ./trace [pcap filename]\n");
      exit(1);
   }
   char *file = argv[1];
   Sniff(file);
   return 0;
}
