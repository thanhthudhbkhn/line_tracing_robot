#include <xc.h>
#include <p18f2553.h>
#define WHITE 1
#define BLACK 0

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
    PORTC=0x03;  /* both motor on */
    wait00(0.3); /* 0.003msec wait */
    PORTC=0x02;  /* right motor on */
    wait00(15);  /* 0.15msec wait */
    PORTC=0x00;  /* both motor off */
    wait00(20);  /* 0.20msec wait */
}

 int small_left_down(void){
    PORTC=0x03;  /* both motor on */
    wait00(0.3); /* 0.003msec wait */
    PORTC=0x02;  /* right motor on */
    wait00(8);   /* 0.12msec wait */
    PORTC=0x00;  /* both motor off */
    wait00(16);  /* 0.15msec wait */
}

int right_down(void){
   PORTC=0x03;  /* both motor on */
   wait00(0.3); /* 0.003msec wait */
   PORTC=0x01;  /* left motor on */
   wait00(15);  /* 0.12sec wait */
   PORTC=0x00;  /* both motor off */
   wait00(20);  /* 0.20msec wait */
}

int small_right_down(void){
   PORTC=0x03;  /* both motor on */
   wait00(0.3); /* 0.003msec wait */
   PORTC=0x01;  /* left motor on */
   wait00(8);   /* 0.12sec wait */
   PORTC=0x00;  /* both motor off */
   wait00(16);  /* 0.15msec wait */
}
 int mini_left_down(void){
   PORTC=0x03;  /* both motor on */
   wait00(0.3); /* 0.003msec wait */
   PORTC=0x02;  /* left motor on */
   wait00(4);   /* 0.06sec wait */
   PORTC=0x00;  /* both motor off */
   wait00(8);  /* both motor off */
 }
 int mini_right_down(void){
   PORTC=0x03;  /* both motor on */
   wait00(0.3); /* 0.003msec wait */
   PORTC=0x01;  /* left motor on */
   wait00(4);   /* 0.06sec wait */
   PORTC=0x00;  /* both motor off */
   wait00(8);  /* both motor off */
 }
 int straight(void){
   PORTC=0x03; /* both motor on */
   wait00(10);  /* 0.09msec wait */
   PORTC=0x00; /* both motor off */
   wait00(10); /* 0.15msec wait */
}
int fast_straight(void){
    PORTC=0x03;
    wait00(20);
    PORTC=0x00;
    wait00(5);
}

int led_sens(void){
   PORTAbits.RA0 = PORTBbits.RB0;
   PORTAbits.RA1 = PORTBbits.RB1;            
   PORTAbits.RA2 = PORTBbits.RB2;           
   PORTAbits.RA3 = PORTBbits.RB3;
   PORTAbits.RA4 = PORTBbits.RB4;       
}

main(void){

   int last, right=1, left=0, strght=2, map=-1;
   //setting digital or analog pin
   ADCON1 = 0x0F;


   //setting input or output
   TRISA = 0x20;            //  portA   RA0,1,2,3,4:output, RA5:input   10 0000
   TRISB = 0xFF;            //  portB   RB all input   1111 1111
   TRISC = 0x00;            //  portC   RC all output

   //reset to port
   PORTA = 0x00;            //  portA   reset output
   PORTB = 0x00;            //  portB    reset output
   PORTC = 0x00;            //  portC    reset output

   //Start SW
   while(PORTAbits.RA5==1){
       led_sens();
   }
   //Push Start SW
   //infinit loop
    while(1){/* infinite loop */
        led_sens();

       /*WHITE SIDE*/
        if(PORTBbits.RB0==1  &&  PORTBbits.RB1==1 &&  PORTBbits.RB2==1 && PORTBbits.RB3==1 && PORTBbits.RB4==0){ 
            /*11110*/
            right_down();/*turn right */
            last=right;
            map=WHITE;
        }
        else if(PORTBbits.RB0==1  &&  PORTBbits.RB1==1 &&  PORTBbits.RB2==1 && PORTBbits.RB3==0 && PORTBbits.RB4==0){ 
            /*11100*/
            if(map == BLACK)
                small_left_down();
            else{
            small_right_down();/* turn right */
            last=right;
            map=WHITE;
            }
        }
        else if(PORTBbits.RB0==1  &&  PORTBbits.RB1==1 &&  PORTBbits.RB2==0 && PORTBbits.RB3==1 && PORTBbits.RB4==1){
            /*11011*/
            fast_straight();/* go straight */
            last=strght; 
            map=WHITE;
        }

        else if(PORTBbits.RB0==0  &&  PORTBbits.RB1==0 &&  PORTBbits.RB2==1 && PORTBbits.RB3==1 && PORTBbits.RB4==1){ 
            /*00111*/
            if(map == BLACK)
               small_right_down();
            else{
            small_left_down();/* turn left */
            last=left;
            map = WHITE;
           }
        }
        else if(PORTBbits.RB0==0  &&  PORTBbits.RB1==1 &&  PORTBbits.RB2==1 && PORTBbits.RB3==1 && PORTBbits.RB4==1){ 
            /*01111*/
           left_down();/* turn left */
           last=left;
           map = WHITE;
             }

        else if(PORTBbits.RB0==1  &&  PORTBbits.RB1==0 &&  PORTBbits.RB2==0 && PORTBbits.RB3==1 && PORTBbits.RB4==1)/*10011*/{mini_left_down();last=left;map = WHITE;}
        else if(PORTBbits.RB0==1  &&  PORTBbits.RB1==1 &&  PORTBbits.RB2==0 && PORTBbits.RB3==0 && PORTBbits.RB4==1)/*11001*/{mini_right_down();last=right; map = WHITE;}
        else if(PORTBbits.RB0==1 && PORTBbits.RB1==1 && PORTBbits.RB2==1 && PORTBbits.RB3==0 && PORTBbits.RB4==1)/*11101*/{mini_right_down();last=right; map = WHITE;}
        else if(PORTBbits.RB0==1 && PORTBbits.RB1==0 && PORTBbits.RB2==1 && PORTBbits.RB3==1 && PORTBbits.RB4==1)/*10111*/{mini_left_down();last=left;map = WHITE;}

        /*BLACK SIDE*/
        else if(PORTBbits.RB0==0  &&  PORTBbits.RB1==0 &&  PORTBbits.RB2==0 && PORTBbits.RB3==0 && PORTBbits.RB4==1){ 
            /*00001*/
           right_down();/* turn right */
           last=right;
           map = BLACK;
        }   

        else if(PORTBbits.RB0==0  &&  PORTBbits.RB1==0 &&  PORTBbits.RB2==0 && PORTBbits.RB3==1 && PORTBbits.RB4==1){ 
            /*00011*/
            if(map == WHITE)
              small_left_down();
            else{
              small_right_down();/* turn right */
              last=right;
              map = BLACK;
            }
        }
        else if(PORTBbits.RB0==0  &&  PORTBbits.RB1==0 &&  PORTBbits.RB2==1 && PORTBbits.RB3==0 && PORTBbits.RB4==0){
            /*00100*/
            fast_straight();/* go straight */last=strght;map = BLACK;}

        else if(PORTBbits.RB0==1  &&  PORTBbits.RB1==1 &&  PORTBbits.RB2==0 && PORTBbits.RB3==0 && PORTBbits.RB4==0){ 
            /*11000*/
            if(map == WHITE) small_right_down();
            else{
                small_left_down();/* turn left */
                last=left;
                map = BLACK;
            }
        }
        else if(PORTBbits.RB0==1  &&  PORTBbits.RB1==0 &&  PORTBbits.RB2==0 && PORTBbits.RB3==0 && PORTBbits.RB4==0){ 
            /*10000*/
            left_down();/* turn left */
            last=left;
            map = BLACK;
       }

        else if(PORTBbits.RB0==0  &&  PORTBbits.RB1==0 &&  PORTBbits.RB2==1 && PORTBbits.RB3==1 && PORTBbits.RB4==0)/*00110*/{mini_right_down();last=right;map = BLACK;}
        else if(PORTBbits.RB0==0  &&  PORTBbits.RB1==1 &&  PORTBbits.RB2==1 && PORTBbits.RB3==0 && PORTBbits.RB4==0)/*01100*/{mini_left_down();last=left;map = BLACK;}
        else if(PORTBbits.RB0==0 && PORTBbits.RB1==0 && PORTBbits.RB2==0 && PORTBbits.RB3==1 && PORTBbits.RB4==0)/*00010*/{mini_right_down();last=left;map = BLACK;}
        else if(PORTBbits.RB0==0 && PORTBbits.RB1==1 && PORTBbits.RB2==0 && PORTBbits.RB3==0 && PORTBbits.RB4==0)/*01000*/{mini_left_down();last=right;map = BLACK;}

        /*OUT LINE*/
        else if((PORTBbits.RB0==0 && PORTBbits.RB1==0 && PORTBbits.RB2==0 && PORTBbits.RB3==0 && PORTBbits.RB4==0)||
                (PORTBbits.RB0==1 && PORTBbits.RB1==1 && PORTBbits.RB2==1 && PORTBbits.RB3==1 && PORTBbits.RB4==1)){
            if(last==right) {
                right_down();              
                last=right;
            } 
            else if (last==left) {
                left_down();
                last=left;
            }
            else if (last==strght) {
                straight();  
                last=strght;
            }
        }
        else {
            straight();
        }
    }          
}
