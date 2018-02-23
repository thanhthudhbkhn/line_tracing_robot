//test

#include <xc.h>
#include <p18f2553.h>

wait00(short k)
{ 	 
/*Wait time about (k?~0.01 sec.) */ 		 
    short i; 		 
    short j; /* Declaration of 16 bit variables 	*/ 	 
    for(j=0;j<k;j++){ /*(k?~3000) times iteration */ 	 
		for(i=0;i<3000;i++){ 	 
		}	 
	} 		 
} 			 


int left_down(void){
    PORTC=0x03; /* both motor on */
    wait00(3); /* 0.03msec wait */
    PORTC=0x01; /* right motor on */
    wait00(5); /* 0.05msec wait */
    PORTC=0x00; /* both motor off */
    wait00(20); /* 0.2msec wait */
}

int right_down(void){
    PORTC=0x03; /* both motor on */
    wait00(3); /* 0.03msec wait */
    PORTC=0x02; /* left motor on */
    wait00(5); /* 0.05msec wait */
    PORTC=0x00; /* both motor off */
    wait00(20); /* 0.2msec wait */
}

int straight(void){
    PORTC=0x03; /* both motor on */
    wait00(8); /* 0.08msec wait */
    PORTC=0x00; /* both motor off */
    wait00(20); /* 0.2msec wait */
}

int led_sens(void)
{
PORTAbits.RA0 = PORTBbits.RB0;           
PORTAbits.RA1 = PORTBbits.RB1;           
PORTAbits.RA2 = PORTBbits.RB2;           
PORTAbits.RA3 = PORTBbits.RB3;           
PORTAbits.RA4 = PORTBbits.RB4;      
}

main(void)
{
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
            case 0b00000: 
                straight(); /* go to straight */
                break;
            case 0b00001: break;
            case 0b00010: break;
            case 0b00011: break;
            case 0b00100: 
                straight(); /* go to straight */
                break;
            case 0b00101: break;
            case 0b00110: break;
            case 0b00111: break;
            case 0b01000: break;
            case 0b01001: break;
            case 0b01010: break;
            case 0b01011: break;
            case 0b01100: break;
            case 0b01101: break;
            case 0b01110: break;
            case 0b01111: break;
            case 0b10000: break;
            case 0b10001: break;
            case 0b10010: break;
            case 0b10011: break;
            case 0b10100: break;
            case 0b10101: break;
            case 0b10110: break;
            case 0b10111: break;
            case 0b11000: break;
            case 0b11001: break;
            case 0b11010: break;
            case 0b11011: 
                straight(); /* go to straight */
                break;
            case 0b11100: break;
            case 0b11101: break;
            case 0b11110: break;
            case 0b11111: 
                straight(); /* go to straight */
                break;
            default: break;
        }
//        if(PORTBbits.RB0==1  && PORTBbits.RB2==1 && PORTBbits.RB4==0){ 
//            /*White White White White black*/
//            left_down();/* turn left */
//        }
//        else if(PORTBbits.RB0==0 && PORTBbits.RB2==1 && PORTBbits.RB4==1){ 
//            /*Black White White White White*/
//            right_down(); /* turn right */
//        }
//        else{ /* The other case */
//            straight(); /* go to straight */
//        }
    }
            
}
