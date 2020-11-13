import sys
import random

def evenDiv():
   outerloop = True
   innerloop = True
   num = 2520
   div = 2
   while outerloop:
      innerloop = True
      div = 2
      while innerloop:
         if num % div == 0:
            div += 1
         else:
            innerloop = False
         if div == 20:
            innerloop = False
            outerloop = False
      num += 1

   print(num)
 
         
         


if __name__ == '__main__':
   evenDiv()
