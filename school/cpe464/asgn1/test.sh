#!/bin/bash

./trace pcap/ArpTest.pcap > arp.out
diff -Bw arp.out output/ArpTest.out

./trace pcap/Http.pcap > http.out
diff -Bw http.out output/Http.out

./trace pcap/IP_bad_checksum.pcap > ipbadsum.out
diff -Bw ipbadsum.out output/IP_bad_checksum.out

./trace pcap/largeMix2.pcap > mix2.out
diff -Bw mix2.out output/largeMix2.out

./trace pcap/largeMix.pcap > mix.out
diff -Bw mix.out output/largeMix.out

./trace pcap/PingTest.pcap > ping.out
diff -Bw ping.out output/PingTest.out

./trace pcap/smallTCP.pcap > tcp.out
diff -Bw tcp.out output/smallTCP.out

./trace pcap/TCP_bad_checksum.pcap > tcpbadsum.out
diff -Bw tcpbadsum.out output/TCP_bad_checksum.out

./trace pcap/UDPfile.pcap > udp.out
diff -Bw udp.out output/UDPfile.out

./trace mypcap/mytrace1.pcap > mytrace1.out
./trace mypcap/mytrace2.pcap > mytrace2.out
