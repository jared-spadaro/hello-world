void TrStr(char *str, char *transTable) {
   char *temp = transTable;
   int found = 0;
   while (*str) {
      while (*transTable && !found) {
         if (*str == *transTable) {
            *str = *(transTable + 1);
            found = 1;
         }
         transTable += 2;
      }
      found = 0;
      transTable = temp;
      str++;
   }
}
