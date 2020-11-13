import sys
import random
import math

def readFile():
    nums = open("numbers.txt", "r")
    print ("Name of the file: ", nums.name)
    print ("Closed or not : ", nums.closed)
    print ("Opening mode : ", nums.mode)
    content = nums.read()
    print("File content:\n", content)

def adjProduct():
    ndx = 1 
    curr = 2 #the first known prime number (1 doesn't count)
    while ndx <= MAX:
        curr += 1
        if isPrime(curr) == True:
            ndx += 1
    return curr

if __name__ == '__main__':
    readFile()
   #print("The greatest 4 adjacent number product is " + str(adjProduct()))
