#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>

#define LEN 21

typedef struct coordinates {
   int x;
   int y;
   int id;
   char special[];
} coordinate;

void findPaths() {
   int i, j, id = 0; 
   coordinate points[LEN][LEN];
   for (i = 0; i < LEN; i++) {
      for (j = 0; j < LEN; j++) {
         points[i][j].x = j;
         points[i][j].y = i;
         points[i][j].id = id++;
         printf("coordinates: (%d, %d), id = %d\n", 
          points[i][j].x, points[i][j].y, points[i][j].id); 
      }
   }

   i = 0, j = 0;
   while (not done) {
         coordinate curr = points[i][j];
         // e.g. (20,5)
         if (curr.x == LEN && curr.y != LEN) {}
         // e.g. (5,20)
         else if (curr.x != LEN && curr.y == LEN) {} 
         // (20,20)
         else if (curr.x == LEN && curr.y == LEN) {}
         
}


int main(int argc, char *argv[]) {
   findPaths();
   return 0;
}


