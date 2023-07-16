#include "msp430.h"
//#include <Servo.h>
#define R_F 1
#define L_F 1
#define L_B 0
#define R_B 0
#define DOWN 1500
#define UP 750
#define LEFT 1
#define RIGHT 0
#define FWD 1
#define BAC 0
#define DEG90 2100
#define DEG45 1050
#define DEG30 700
#define DEG15 350

void d(int delay_time){
    int i=0;
    for (i=0; i<delay_time; i++){
        _delay_cycles(100);
    }
}

void run(int r_step, int l_step, int r_dir, int l_dir){
    int on = 0b00000000;
    int off = 0b00000000;
    if(r_step){
        on+= 0b00000001;
    }
    if(l_step){
        on+= 0b00000010;
    }
    if(r_dir!=R_F){
        on+= 0b00000100;
        off+= 0b00000100;
    }
    if(l_dir==L_F){
        on+= 0b00001000;
        off+= 0b00001000;
    }
    d(10);
    P1OUT = on;
    d(10);
    P1OUT = off;
}

void run_time(int r_step, int l_step, int r_dir, int l_dir, int t){
    int count = 0;
    for(count = 0; count<t; count++){
        run(r_step,l_step,r_dir,l_dir);}
    d(500);
}

void turn(int dir, int deg){
    if(dir == LEFT){
        run_time(1,1,R_F,L_B,deg);}
    else{
        run_time(1,1,R_B,L_F,deg);
    }
}

void go(int dir, int duration){
    if(dir == FWD){
        run_time(1,1,R_F,L_F,duration);
    }
    else{
        run_time(1,1,R_B,L_B,duration);
    }
}


void main(void) {

WDTCTL = WDTPW + WDTHOLD; //Stop WDT
// P1.0 to R_STEP
// P1.1 to L_STEP
// P1.2 to R_DIR
// P1.3 to L_DIR
P1DIR = 0b01001111; //Set P1.0 and P1.6 to output; binary 01000001 is 65
P1SEL |= BIT6;      // Add PWM functionality to P1.5
P1OUT = 0b00000000; //Set the output Pin P1.0 to low and P1.6 to high 010000000


// Setting up for Servo:
// if SMCLK is about 1MHz (or 1000000Hz),
// and 1000ms are the equivalent of 1 Hz,
// then, by setting CCR0 to 20000 (1000000 / 1000 * 20)
// we get a period of 20ms
CCR0 = 20000-1;                           // PWM Period TA0.1

// setting 1500 is 1.5ms is 0deg. servo pos
CCR1 = 1500;                            // CCR1 PWM duty cycle

CCTL1 = OUTMOD_7;                       // CCR1 reset/set
TACTL   = TASSEL_2 + MC_1;                // SMCLK, up mode

//int dir = 0;
//while (1) { // Loop forever

// 2100 - 90 degrees
// 1050 - 45 degrees


d(50000);

// Letter M
CCR1 = DOWN;
go(FWD,1200);
CCR1 = UP;
turn(LEFT,DEG15);
CCR1 = DOWN;
go(BAC,900);
turn(RIGHT,DEG30);
go(FWD,900);
turn(LEFT,DEG15);
go(BAC,1200);
CCR1=UP;

turn(RIGHT,DEG90);
go(FWD,300);
turn(LEFT,DEG90);

// Letter (backwards N) (cerilic I)
go(FWD, 1200);
CCR1 = DOWN;
go(BAC, 1200);
turn(RIGHT, DEG15);
go(FWD, 1242);
turn(LEFT, DEG15);
go(BAC, 1200);
CCR1 = UP;

turn(RIGHT,DEG90);
go(FWD,300);
turn(LEFT,DEG90);

// Letter "sh" in cerilic
go(FWD, 1200);
CCR1 = DOWN;
go(BAC, 1200);
turn(RIGHT, DEG90);
go(FWD, 322*2);
turn(LEFT, DEG90);
go(FWD, 1200);
CCR1 = UP;
turn(RIGHT, DEG15);
go(BAC, 1242);
turn(LEFT, DEG15);
CCR1 = DOWN;
go(FWD, 1200);
CCR1 = UP;

turn(LEFT, DEG15);
go(BAC, 1242);
turn(RIGHT, DEG90 + DEG15);

go(FWD, 300);
turn(LEFT, DEG90);

// Letter "A"
turn(RIGHT, DEG15);
CCR1 = DOWN;
go(FWD, 1242);
turn(LEFT, DEG30);
go(BAC, 1242);
CCR1 = UP;
go(FWD, 414);
turn(LEFT, DEG90-DEG15);
CCR1 = DOWN;
go(FWD, 428);
CCR1 = UP;
turn(RIGHT, DEG30);
go(FWD, 2500);
turn(RIGHT, DEG90-DEG30);




//    }
}




//// Letter M
//CCR1 = DOWN;
//run_time(1,1,R_F,L_F,2000);          //          |
//CCR1 = UP;
////run_time(1,1,R_B,L_B,250);
//run_time(1,1,R_B,L_F,DEG90 + DEG45 + DEG30); //          turn
//CCR1 = DOWN;
//run_time(1,1,R_B,L_B,300);
//run_time(1,1,R_F,L_F,1500);          //
////CCR1 = UP;
//run_time(1,1,R_F,L_B,5*DEG30);         //          turn
////CCR1 = DOWN;
//run_time(1,1,R_F,L_F,1500);          //          /
//CCR1 = UP;
//run_time(1,1,R_F,L_B,DEG15);
//CCR1 = DOWN;
//run_time(1,1,R_B,L_B,2000);
//CCR1 = UP;









//
//while (1) { // Loop forever
//    int count;
//
//    for(count = 0; count<5000;count++){
//        if(dir == 0){
//
//            d(1);
//            P1OUT = 0b00000101;
//            d(10);
//            P1OUT = 0b00000100;
//        }
//        else{
//            d(1); //This function introduces 0.5 s delay
//            P1OUT = 0b00000001;
//            d(10);
//            P1OUT = 0b00000000;
//        }
//       }
//    if(dir==0){
//        dir=1;
//    }
//    else{
//        dir = 0;
//    }
//    }








