//test

#include <xc.h>
#include <p18f2553.h>
#include <string.h>

wait00(float k)
{ 	 
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
    wait00(0.1); /* 0.03msec wait */
    PORTC=0x01; /* left motor on */
    wait00(20); /* 0.05msec wait */
    PORTC=0x00; /* both motor off */
    wait00(40); /* 0.79msec wait */
}

int small_right_down(void){
    PORTC=0x03;  /* both motor on */
    wait00(0.1); /* 0.003msec wait */
    PORTC=0x01;  /* left motor on */
    wait00(8);   /* 0.02msec wait */
    PORTC=0x00;  /* both motor off */
    wait00(100);  /* 0.20msec wait */
}

int left_down(void){
    PORTC=0x03; /* both motor on */
    wait00(0.1); /* 0.03msec wait */
    PORTC=0x02; /* right motor on */
    wait00(20); /* 0.05msec wait */
    PORTC=0x00; /* both motor off */
    wait00(40); /* 0.79msec wait */
}

int small_left_down(void){
   PORTC=0x03;  /* both motor on */
   wait00(0.1); /* 0.003msec wait */
   PORTC=0x02;  /* right motor on */
   wait00(8);   /* 0.02sec wait */
   PORTC=0x00;  /* both motor off */
   wait00(100);  /* 0.20msec wait */
}

int straight(void){
    PORTC=0x03; /* both motor on */
    wait00(2); /* 0.08msec wait */
    PORTC=0x00; /* both motor off */
    wait00(40); /* 0.2msec wait */
}

int do_sth(void){
    PORTC=0x03; /* both motor on */
    wait00(2); /* 0.08msec wait */
    PORTC=0x00; /* both motor off */
    wait00(200); /* 0.2msec wait */
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
        
        switch (PORTBbits.RB0) {
            case 0:
                switch (PORTBbits.RB1) {
                    case 0:
                        if (PORTBbits.RB2==0) {
                            if (PORTBbits.RB3==0 && PORTBbits.RB4==0) straight(); /*black black black black black */
                            else if (PORTBbits.RB3==0 && PORTBbits.RB4==1) right_down(); /*black black black black white */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==0) small_right_down(); /*black black black white black */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==1) right_down(); /*black black black white white */
                        } else if (PORTBbits.RB2==1) {
                            if (PORTBbits.RB3==0 && PORTBbits.RB4==0) straight(); /*black black white black black */
                            else if (PORTBbits.RB3==0 && PORTBbits.RB4==1) do_sth(); /*black black white black white */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==0) small_right_down(); /*black black white white black */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==1) left_down(); /*black black white white white */
                        }
                        break;
                    case 1:
                        if (PORTBbits.RB2==0) {
                            if (PORTBbits.RB3==0 && PORTBbits.RB4==0) small_left_down(); /*black white black black black */
                            else if (PORTBbits.RB3==0 && PORTBbits.RB4==1) do_sth(); /*black white black black white */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==0) do_sth(); /*black white black white black */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==1) do_sth(); /*black white black white white */
                        } else if (PORTBbits.RB2==1) {
                            if (PORTBbits.RB3==0 && PORTBbits.RB4==0) small_left_down(); /*black white white black black */
                            else if (PORTBbits.RB3==0 && PORTBbits.RB4==1) do_sth(); /*black white white black white */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==0) straight(); /*black white white white black */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==1) left_down(); /*black white white white white */
                        }
                        break;
                    default: break;
                }
                break;
            case 1:
                switch (PORTBbits.RB1) {
                    case 0:
                        if (PORTBbits.RB2==0) {
                            if (PORTBbits.RB3==0 && PORTBbits.RB4==0) left_down(); /*white black black black black */
                            else if (PORTBbits.RB3==0 && PORTBbits.RB4==1) straight(); /*white black black black white */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==0) do_sth(); /*white black black white black */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==1) small_left_down(); /*white black black white white */
                        } else if (PORTBbits.RB2==1) {
                            if (PORTBbits.RB3==0 && PORTBbits.RB4==0) do_sth(); /*white black white black black */
                            else if (PORTBbits.RB3==0 && PORTBbits.RB4==1) do_sth(); /*white black white black white */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==0) do_sth(); /*white black white white black */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==1) small_left_down(); /*white black white white white */
                        }
                        break;
                    case 1:
                        if (PORTBbits.RB2==0) {
                            if (PORTBbits.RB3==0 && PORTBbits.RB4==0) left_down(); /*white white black black black */
                            else if (PORTBbits.RB3==0 && PORTBbits.RB4==1) small_right_down(); /*white white black black white */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==0) do_sth(); /*white white black white black */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==1) straight(); /*white white black white white */
                        } else if (PORTBbits.RB2==1) {
                            if (PORTBbits.RB3==0 && PORTBbits.RB4==0) right_down(); /*white white white black black */
                            else if (PORTBbits.RB3==0 && PORTBbits.RB4==1) small_right_down(); /*white white white black white */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==0) right_down; /*white white white white black */
                            else if (PORTBbits.RB3==1 && PORTBbits.RB4==1) straight(); /*white white white white white */
                        }
                        break;
                    default: break;
                }
                break;
            default: break;
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
