import sys
import random
import math

MAX = 10001

def readFile(num):
   div = 2
   for x in range(2, num // 2):
      if num % x == 0:
         return False
   return True      
      

def adjProduct():
   ndx = 1 
   curr = 2 #the first known prime number (1 doesn't count)
   while ndx <= MAX:
      curr += 1
      if isPrime(curr) == True:
         ndx += 1
   return curr

if __name__ == '__main__':
   print("The greatest 4 adjacent number product is " + str(adjProduct()))
