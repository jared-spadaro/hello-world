//CPE123 - Fall 2012
//Final Sending Code
//Karthik Jayakumar, Gerik Kubiak, Isaias Diaz, and Jared Spadaro
//
//Send instructions to the robot depending on which buttons are pressed

#include<avr/io.h> 
#include<avr/interrupt.h>
#include<util/delay.h>

#define IR_LED_PORT PD0
#define ONBOARD_SWITCH_PORT	PD1
#define SWITCH_PORT_1 PD2
#define SWITCH_PORT_2 PD3
#define SWITCH_PORT_3 PD4
#define SWITCH_PORT_4 PD5
#define SWITCH_PORT_5 PD6
#define HIGH_US_38KHZ 7
#define LOW_US_38KHZ 20
#define HIGH_US_56KHZ 8
#define LOW_US_56KHZ 10

//Global variables for switching carrier frequencies
//Variables are global for timing correctness
unsigned char loop_count;
char logic_one_delay, logic_zero_delay;
char frequency;

void set_frequency_38(void) {
  frequency = 38;
  loop_count = 89;  //number of periods in 2.4ms
  logic_one_delay = 45;
  logic_zero_delay = 22;
}

void set_frequency_56(void) {
  frequency = 56;
  loop_count = 141;  //number of periods in 2.4ms
  logic_one_delay = 70;
  logic_zero_delay = 35;
}

void send_start_bit() {
  unsigned char i;

  for (i=0;i<loop_count;i++) {
    PORTD |= (1 << IR_LED_PORT);  //turn on the IR LED
    if (frequency == 38) {
      _delay_us(HIGH_US_38KHZ);
    } else {
      _delay_us(HIGH_US_56KHZ);
    }

    PORTD &= ~(1 << IR_LED_PORT);  //turn off the IR LED
    if (frequency == 38) {
      _delay_us(LOW_US_38KHZ);
    } else {
      _delay_us(LOW_US_56KHZ);
    }
  }

  _delay_us(600);
}

void send_command(unsigned char command) {
  char i,j,delay;

  for (i=0;i<7;i++) {  //run 7 times
    if ((command & (1 << i)) != 0) {
      delay = logic_one_delay;
    } else {
      delay = logic_zero_delay;
    }

    for (j=0;j<delay;j++) {
      PORTD |= (1 << IR_LED_PORT); //turn on the IR LED
      if (frequency == 38) {
        _delay_us(HIGH_US_38KHZ);
      } else {
        _delay_us(HIGH_US_56KHZ);
      }

      PORTD &= ~(1 << IR_LED_PORT);  //turn off the IR LED
      if (frequency == 38) {
        _delay_us(LOW_US_38KHZ);
      } else {
        _delay_us(LOW_US_56KHZ);
      }
    }

    _delay_us(600);
  }
}

int detectButtons(){	//Read in which switch is pressed and return the value
	if((PIND&(1<<SWITCH_PORT_1))==0){
		return 1;
	} else if((PIND&(1<<SWITCH_PORT_2))==0){
		return 2;
	} else if((PIND&(1<<SWITCH_PORT_3))==0){
		return 3;
	} else if((PIND&(1<<SWITCH_PORT_4))==0){
		return 4;
	} else if((PIND&(1<<SWITCH_PORT_5))==0){
		return 5;
	}
	return 0;
}

void blinkLED(int num){
	int i;
	for(i=0;i<num;i++){
		PORTD|=(1<<PD7);
		_delay_ms(500);
		PORTD&= ~(1<<PD7);
		_delay_ms(500);
	}
}

int main(void) {
	DDRD |= (1<<PD7)|(1<<IR_LED_PORT);  //set the IR port pin to output
	PORTD |= (1 << SWITCH_PORT_1)|(1 << SWITCH_PORT_2)|(1 << SWITCH_PORT_3)|(1 << SWITCH_PORT_4)|(1 << SWITCH_PORT_5)|(1<<ONBOARD_SWITCH_PORT);
	
	if(PIND&(1<<ONBOARD_SWITCH_PORT)){	//If the onboard switch isn't pressed
		blinkLED(1);
		set_frequency_38();	//Set to 38kHz
	} else {
		blinkLED(2);
		set_frequency_56();	//Set to 56kHz
	}
	
	int buttonPressed;
	
	while(1) {
		buttonPressed = detectButtons();
		if(buttonPressed!=0){
			if(buttonPressed==1){
				send_start_bit();
				send_command(31);
			} else if(buttonPressed==2){
				send_start_bit();
				send_command(32);
			} else if(buttonPressed==3){
				send_start_bit();
				send_command(33);
			} else if(buttonPressed==4){
				send_start_bit();
				send_command(34);
			} else if(buttonPressed==5){
				send_start_bit();
				send_command(35);
			}
			_delay_ms(100);
		}
	}

	return 0;
}