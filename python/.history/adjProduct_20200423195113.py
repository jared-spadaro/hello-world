import sys
import random
import math
import array as arr

def readFile():
    nums = open("numbers.txt", "r")
    num = 0
    master = []
    while True:
        a = []
        while "\n" not in num:
            num = nums.read(3)
            a.append(num)
        master.append(a)
    print(master.tostring())


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
