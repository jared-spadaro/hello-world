import sys
import random

def diceRoll():
   
   num = random.randint(0,100)
   check,counter = 0,0   

   while True:
      counter += 1
      if check == 0:
         userInput = input("Guess the Number! (enter a number from 0 to 100 and hit return) ")
      else:
         userInput = input("Guess Again! ")
      
      
      if not userInput.isnumeric():
         print("You didn't enter a number! Exiting...")
         sys.exit()

      else:
         userNum = int(userInput)
         if userNum < 0 or userNum > 100:
            print("The number must be between 0 and 100! Exiting...")
            sys.exit()
         elif (userNum > num):
            print("Too Large! The actual number is smaller.")
         elif (userNum < num):
            print("Too Small! The actual number is bigger.")
         else:
            print("You got it! It took you", counter, "tries. Good job.")
            sys.exit() 
      check = 1

if __name__ == '__main__':
   diceRoll()
