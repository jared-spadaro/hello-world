void OrderThree (float *a, float *b, float *c) {
   float temp;
   if(*a > *b) {   //swap a's target with b's if it is larger
      if(*a > *c) {  //swap a and c
         temp = *a;
         *a = *c;
         *c = temp;
      }
      else {
         temp = *b;
         *b = *a;
         *a = temp;
      }
   }
   if(*a > *c) {
      temp = *a;
      *a = *c;
      *c = temp;
   }
   if(*b > *c) {
      temp = *b;
      *b = *c;
      *c = temp;
   }
}
      
