#include <xc.h>
#include <p18f2553.h>
#include <string.h>

#define BLACK 0
#define WHITE 1
#define STRAIGHT 0
#define LEFT 1
#define RIGHT 2

wait00(float k) { 	 
/*Wait time about (k?~0.01 sec.) */ 		 
    short i; 		 
    short j; /* Declaration of 16 bit variables 	*/ 	 
    for(j=0;j<k;j++){ /*(k?~3000) times iteration */ 	 
		for(i=0;i<3000;i++){ 	 
		}	 
	} 		 
} 			 

int right_down(void){
    PORTC=0x03; /* both motor on */
    wait00(0.3); /* 0.03msec wait */
    PORTC=0x01; /* left motor on */
    wait00(15); /* 0.05msec wait */
    PORTC=0x00; /* both motor off */
    wait00(20); /* 0.2msec wait */
}

int small_right_down(void){
    PORTC=0x03;  /* both motor on */
    wait00(0.3); /* 0.003msec wait */
    PORTC=0x01;  /* left motor on */
    wait00(6);   /* 0.02msec wait */
    PORTC=0x00;  /* both motor off */
    wait00(12);  /* 0.20msec wait */
}

int left_down(void){
    PORTC=0x03; /* both motor on */
    wait00(0.3); /* 0.03msec wait */
    PORTC=0x02; /* right motor on */
    wait00(15); /* 0.05msec wait */
    PORTC=0x00; /* both motor off */
    wait00(20); /* 0.2msec wait */
}

int small_left_down(void){
   PORTC=0x03;  /* both motor on */
   wait00(0.3); /* 0.003msec wait */
   PORTC=0x02;  /* right motor on */
   wait00(6);   /* 0.02sec wait */
   PORTC=0x00;  /* both motor off */
   wait00(12);  /* 0.20msec wait */
}

int straight(void){
    PORTC=0x03; /* both motor on */
    wait00(10); /* 0.08msec wait */
    PORTC=0x00; /* both motor off */
    wait00(10); /* 0.2msec wait */
}

int led_sens(void) {
    PORTAbits.RA0 = PORTBbits.RB0;           
    PORTAbits.RA1 = PORTBbits.RB1;           
    PORTAbits.RA2 = PORTBbits.RB2;           
    PORTAbits.RA3 = PORTBbits.RB3;           
    PORTAbits.RA4 = PORTBbits.RB4;      
}

main(void) {
    
    int background  = -1;
    int status      = -1;
    //setting digital or analog pin
    ADCON1 = 0x0F;

    //setting input or output
    TRISA = 0x20;            //  portA   RA0,1,2,3,4:output, RA5:input   10 0000
    TRISB = 0xFF;            //  portB   RB all input   1111 1111
    TRISC = 0x00;            //  portC   RC all output
    
    //reset to port
    PORTA = 0x00;           //  portA   reset output
    PORTB = 0x00;           //  portB    reset output
    PORTC = 0x00;           //  portC    reset output
    
    //Start SW
    while(PORTAbits.RA5==1){
        led_sens();
    }
    
    //Push Start SW
    //infinit loop
    while(1){/* infinite loop */
        led_sens();
        
        switch (PORTB) {
            case 0b00000:  /*black black black black black */
            case 0b11111: /*white white white white white */
                if (status == RIGHT) {
                    right_down();
                }
                else if (status == LEFT) {
                    left_down();
                }
                else straight();
                break;
            case 0b00001: 
                background = BLACK;
                left_down();/* turn left */
                status = LEFT;
                break;
            case 0b00010: 
                background = BLACK;
                small_left_down();/* turn a little left */
                status = LEFT;
                break;
            case 0b00011: /*white white black black black */
                if (background == WHITE) {
                    small_right_down();
                    status = RIGHT;
                } else {
                    left_down();
                    status = LEFT;
                }
                break;
            case 0b00100: 
                background = BLACK;
                straight(); /* go to straight */
                status = STRAIGHT;
                break;
            case 0b00101: break;
            case 0b00110: 
                background = BLACK;
                small_left_down();
                status = LEFT;
                break;
            case 0b00111: 
                if(background == BLACK) {
                    small_left_down();
                    status = LEFT;
                } else{
                    right_down();/* turn right */
                    status = RIGHT;
                    background=WHITE;
                }
                break;
            case 0b01000: 
                background= BLACK;
                small_right_down();/* turn a little right */
                status = RIGHT;
                break;
            case 0b01001: break;
            case 0b01010: break;
            case 0b01011: break;
            case 0b01100: 
                background = BLACK;
                small_right_down();
                status = RIGHT;
                break;
            case 0b01101: break;
            case 0b01110: 
                background = BLACK;
                straight();
                status = STRAIGHT;
                break;
            case 0b01111: 
                background = WHITE;
                right_down();
                status = RIGHT;
                break;
            case 0b10000: /*black black black black white */
                background = BLACK;
                right_down();
                status = RIGHT;
                break;
            case 0b10001:
                background = WHITE;
                straight();
                status = STRAIGHT;
                break;
            case 0b10010: break;
            case 0b10011: 
                background = WHITE;
                small_right_down();
                status = RIGHT;
                break;
            case 0b10100: break;
            case 0b10101: break;
            case 0b10110: break;
            case 0b10111: 
                background = WHITE;
                small_right_down();
                status = RIGHT;
                break;
            case 0b11000:
                if (background == WHITE) {
                    small_left_down();
                    status = LEFT;
                } else {
                    right_down();
                    status = RIGHT;
                }
                break;
            case 0b11001:
                background = WHITE;
                small_left_down();
                status = LEFT;
                break;
            case 0b11010: break;
            case 0b11011: 
                background = WHITE;
                straight(); /* go to straight */
                status = STRAIGHT;
                break;
            case 0b11100: 
                if (background == BLACK) {
                    small_right_down();
                    status = RIGHT;
                } else {
                    left_down();
                    status = LEFT;
                    background = WHITE;
                }
                break;
            case 0b11101: 
                background = WHITE;
                small_left_down();/* turn a little left */
                status = LEFT;
                break;
            case 0b11110: 
                background = WHITE;
                left_down();/* turn left */
                status = LEFT;
                break;
            default: 
                straight();
                break;
        }

//        if(PORTBbits.RB0==0 && PORTBbits.RB1==0  && PORTBbits.RB2==0 && PORTBbits.RB3==0 && PORTBbits.RB4==0 ){ 
//            straight();
//        }
//        else if(PORTBbits.RB0==0 && PORTBbits.RB2==1 && PORTBbits.RB4==1){ 
//            /*Black White White White White*/
//            right_down(); /* turn right */
//        }
//        else{ /* The other case */
////            straight(); /* go to straight */
//        }
    }
            
}
