import sys
import random
import math
import array as arr

def readFile():
    a = arr.array('i')
    a[0] = 1
    print(a[0])
    nums = open("numbers.txt", "r")
    
    while True:
        num = nums.read(3)
        if num == '':
            break
        print ("Num = ", num)
        if "\n" in num:
            print("Ending number found")


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
