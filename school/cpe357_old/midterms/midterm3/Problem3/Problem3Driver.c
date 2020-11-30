#include <stdio.h>
#include <string.h>
#include "Problem3.h"

#define MAX_COMMAND_SIZE 20

int main() {
   char command[MAX_COMMAND_SIZE + 1] = {0};
   int index, size;
   float value;
   Node *list;
   
   while (0 != strcmp("done", command)) {
      /* Read a command */
      if (EOF == scanf("%s", command)) {
         printf("End of input, terminating...\n");
         break;
      }

      /* Process the command */
      if (0 == strcmp("newList", command)) {
         list = NULL;
      }
      else if (0 == strcmp("addAtIndex", command)) {
         scanf("%d%f", &index, &value);
         addAtIndex(&list, index, value);
      }
      else if (0 == strcmp("printList", command)) {
         scanf("%d", &size);

         printf("List: ");

         for (index = 0; index < size; index++) {
            printf("%.2f ", getAtIndex(&list, index));
         }

         printf("\n");
      }
      else if (0 == strcmp("removeAtIndex", command)) {
         scanf("%d", &index);
         removeAtIndex(&list, index);
      }
      else if (0 == strcmp("checkSpace", command)) {
         scanf("%d", &size);

         if (report_space() > sizeof(Node) * size)
            printf("checkSpace: Too much memory allocated\n");
         else if (report_space() < sizeof(Node) * size)
            printf("checkSpace: Too little memory allocated\n");
         else
            printf("checkSpace: Expected amount of memory allocated\n");
      }
      else if (0 != strcmp("done", command)) {
         printf("Unknown command\n");
      }
   }

   return 0;
}
