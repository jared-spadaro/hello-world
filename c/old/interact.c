#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 256
#define MAX_NUM_SIDES 10
#define MAX_SHAPE_NAME_LEN 16

void interact() {
   char *name = malloc(sizeof(char) * MAX_NAME_LEN); 
   printf("Enter your name: ");
   scanf("%s", name);
   printf("\nHello %s, welcome to the interact program.\n\n", name);
}

void triangle() {
   printf("triangle\n");
}

void square() {
   printf("square\n");
}

void sphere() {
   printf("sphere\n");
}

void compute() {
   int side_lengths[MAX_NUM_SIDES];
   char *shape = malloc(sizeof(char) * MAX_SHAPE_NAME_LEN);   

   printf("Please type what shape you would like to compute the area of.\n"
          "Your options are:\n"
          "   - Triangle\n"
          "   - Square\n"
          "   - Sphere\n");
   scanf("%s", shape);
   if(strcmp(shape, "Triangle") == 0) {
      triangle();
   }
   else if(strcmp(shape, "Square") == 0) {
      square();
   }
   else if(strcmp(shape, "Sphere") == 0) {
      sphere();
   }
   else {
      printf("Incorrect input. Exiting...\n");
      exit(1);
   }
}

void joke() {
   printf("No jokes entered yet.\n");
}

void choose() {
   char input;
   
   printf("If you want to compute an area, type 'a' and hit enter.\n"
          "If you want to hear a joke, type 'j' and hit enter.\n"
          "If you want to quit, type 'q' and hit enter.\n\n");
   scanf("%c", &input);
   
   if (input == 'a') {
      compute();
   }
   else if (input == 'j') {
      joke();
   }
   else if (input == 'q') {
      exit(0);
   }
   else {
     printf("Incorrect input. Exiting...\n");
     exit(1); 
   }
} 

int main() {
   interact();
   choose();
   return 0;
}
