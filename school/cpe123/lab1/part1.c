//CPE123 - Fall 2012
//Lab 1 - part 1
//Jared Spadaro and Ryan Gelston
//Write a program which makes the on-board LED blink 5 times. 
//Each blink should turn the LED on for .4 seconds and then turn the LED off for .4 seconds.
//The on-board LED is connected to PB5 (PortB, pin #5).
#include <avr/io.h>  //Includes compiler into program
#include <util/delay.h> //Includes delay function into program

int main (void) {             //Begins the main program
  
  DDRB = DDRB | (1<<PB5);     //Sets pin 5 as output
  
  PORTB = PORTB | (1<<PB5);   //Sets pin to high for 400 milliseconds
  _delay_ms(400);
  
  PORTB = PORTB & ~(1<<PB5);  //Sets pin to low for 400 milliseconds
  _delay_ms(400);
    
  PORTB = PORTB | (1<<PB5);   //Sets pin to high for 400 milliseconds 
  _delay_ms(400);
  
  PORTB = PORTB & ~(1<<PB5);  //Sets pin to low for 400 milliseconds
  _delay_ms(400);
  
  PORTB = PORTB | (1<<PB5);   //Sets pin to high for 400 milliseconds
  _delay_ms(400);
  
  PORTB = PORTB & ~(1<<PB5);  //Sets pin to low for 400 milliseconds
  _delay_ms(400);  
  
  PORTB = PORTB | (1<<PB5);   //Sets pin to high for 400 milliseconds
  _delay_ms(400);
  
  PORTB = PORTB & ~(1<<PB5);  //Sets pin to low for 400 milliseconds
  _delay_ms(400);  
  
  PORTB = PORTB | (1<<PB5);   //Sets pin to high for 400 milliseconds
  _delay_ms(400);
  
  PORTB = PORTB & ~(1<<PB5);  //Sets pin to low for 400 milliseconds
  _delay_ms(400);
  return 0;                   //Ends the program
}