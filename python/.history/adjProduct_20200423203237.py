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
    return master

def adjProduct(master):
    for line in master:
        for num in line:
            print(num)

if __name__ == '__main__':
    adjProduct(readFile())
   #print("The greatest 4 adjacent number product is " + str(adjProduct()))
