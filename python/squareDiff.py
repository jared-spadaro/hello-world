import sys
import random
import math

def squareDiff():
   Curr = 1 
   SquareSum = 0
   Sum = 0
   while Curr <= 100:
      Sum += Curr
      SquareSum += math.pow(Curr, 2)
      Curr += 1
   diff = math.pow(Sum, 2) - SquareSum
   print(diff)    

if __name__ == '__main__':
   squareDiff()
