#include "poly.h"

void poly_add2 (double poly1[], int degree1, double poly2[], int degree2, double result[])
{
   int i;
   int num_terms_1 = degree1 + 1;
   int num_terms_2 = degree2 + 1;
   if (degree1<degree2)
   {
      for(i=0;i<num_terms_1;i++)
      {
         result[i] = poly1[i] + poly2[i];
      }
      for(i=num_terms_1;i<num_terms_2;i++)
      {
         result[i] = poly2[i];
      }
   }
   else if(degree2<degree1)
   {
      for(i=0;i<num_terms_2;i++)
      {
         result[i] = poly1[i] + poly2[i];
      }
      for(i=num_terms_2;i<num_terms_1;i++)
      {
         result[i] = poly1[i];
      }
   }
   else
   {
      for(i=0;i<degree1;i++)
      {
         result[i] = poly1[i] + poly2[i];
      }
   }   
}

void poly_mult2 (double poly1[],int degree1,double poly2[],int degree2,double result[])
{
   int i;
   int j;
   int num_terms_1 = degree1 + 1;
   int num_terms_2 = degree2 + 1;
   
   for(i=0;i<num_terms_1;i++)
   {
      for(j=0;j<num_terms_2;j++)
      {
         result[i+j] = 0;
      }
   }
   
   
   for(i=0;i<num_terms_1;i++)
   {
      for(j=0;j<num_terms_2;j++)
      {
            
         result[i+j] = poly1[i] * poly2[j] + result[i+j];

      }
   }
}
