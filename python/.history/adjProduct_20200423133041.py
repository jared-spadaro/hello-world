import sys
import random
import math

def readFile():
    file nums = open("numbers.txt", "r")
    print ("Name of the file: " + fo.name)
    print ("Closed or not : " + fo.closed)
    print ("Opening mode : " + fo.mode)
    print ("Softspace flag : " + fo.softspace)     

def adjProduct():
    ndx = 1 
    curr = 2 #the first known prime number (1 doesn't count)
    while ndx <= MAX:
        curr += 1
        if isPrime(curr) == True:
            ndx += 1
    return curr

if __name__ == '__main__':
    print("File info --> " + readFile())
   #print("The greatest 4 adjacent number product is " + str(adjProduct()))
