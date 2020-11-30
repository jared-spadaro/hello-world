#include <stdlib.h>

int main () {
   int *x = malloc(sizeof(int));
   int *y = calloc(1, sizeof(int));
   free(x);
   y = realloc(y, 0);
}
