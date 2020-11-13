import sys
import random
import math
import array as arr

def readFile():
    nums = open("numbers.txt", "r")
    master = []
    while True:
        line = nums.readline()
        if line == "":
            break
        master.append(line.split(' '))
    print(master)
    for x in range (len(master)):
        for y in range (len(master[x])):
            print(x[y])


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
