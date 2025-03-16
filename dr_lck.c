#include<reg51.h>



#define DATA P2			//Select port2 as a data output pin for LCD.
#define input P3		//Select port3 as a keypad input pin.
unsigned int i,j,k,l,m,n,x;


sbit rs=P1^0;      //select the pin P1.0 for register select.
sbit rw=P1^1;			 //select the pin P1.1 for read/write.
sbit en=P1^2;			 //select the pin P1.2 for Enable.
sbit Mp=P1^3;		 
sbit Mn=P1^4;

unsigned char val[]={"123A456B789C*0#D"};
//unsigned char setpsw[]={"set password"};
 unsigned char psw[4];
 unsigned char npsw[4];
 code unsigned char pswval[]={"1234"};

void delay_50ms(){      //  Create a delay of 50mS.
  TMOD=0X01;       // Declear TMOD Resister as Timer 0 Mode 1.
	TH0=0x4B;		     // Load 4B to the TH0 resister.
	TL0=0xFD;		     // Load FD to the TL0 resister.
	TR0=1;			     //Start Timer 0 resister.
	 while(TF0==0);  // Check if timer 0 is overflow or not.
	 TR0=0;				 	 //Stop Timer 0 resister.
	 TF0=0;					 //Reset Timer 0 Overflow flag.
 }

void lcddata(unsigned char dat) // Function for LCD data.
{
	DATA=dat;
	rs=1;
	rw=0;
	en=1;
	delay_50ms();
	en=0;	
}

void lcdcmd(unsigned char comnd) // Function for LCD Command.
{
DATA=comnd;
	rs=0;
	rw=0;
	en=1;
	delay_50ms();
	en=0;
}

void lcddisplay(unsigned char *q)
{
    int k;
    for (k = 0; q[k] != '\0'; k++)
    {
        lcddata(q[k]);
    }
    delay_50ms();
}


 char keypad(){

	//while(x==0){
	while(1){
		input=0xFE;    // send 0 to the 1st row of keypad.
		if(input!=0xFE){
				if(input==0x7E){
					lcddata('A');
				//	x=1;
					return 'A';
					break;
				}
				if(input==0xBE){
					lcddata('9');
					return '9';
					break;
				}
				if(input==0xDE){
				lcddata('8');
					return '8';
					break;
				}
				if(input==0xEE){
				lcddata('7');			
					return '7';
					break;
				}
			
		}
				input=0xFD;		// send 0 to the 2nd row of keypad.
		if(input!=0xFD){
				if(input==0x7D){
					lcddata('B');
					return 'B';
					break;
				}
				if(input==0xBD){
				lcddata('6');
					return '6';
					break;
				}
				if(input==0xDD){
					lcddata('5');
					return '5';
					break;
				}
				if(input==0xED){
				lcddata('4');
					return '4';
					break;
				}
			
		}
				input=0xFB;		// send 0 to the 3rd row of keypad.
		if(input!=0xFB){
			if(input==0x7B){
				lcddata('C');
				return 'C';
				break;
				}
				if(input==0xBB){
					lcddata('3');
					return '3';
					break;
				}
				if(input==0xDB){
				lcddata('2');
					return '2';
					break;
				}
				if(input==0xEB){
					lcddata('1');
					return '1';
					break;
				}
			
		}
		input=0xF7;					// send 0 to the 4th row of keypad.
		if(input!=0xF7){
			if(input==0x77){
				lcddata('D');
				return 'D';
				break;
				}
				if(input==0xB7){
					lcddata('#');
					return '#';
					break;
				}
				if(input==0xD7){
					lcddata('0');
					return '0';
					break;
				}
				if(input==0xE7){
					lcddata('|');
					lcdcmd(0x01);
					return 0;
					break;
				}	
		}
	}
}
//}

void main(){
	P3=0xff;
	lcdcmd(0x38);  //command for 8-Bit,2 line,5x7 Dot.
	delay_50ms();
	while(1){
	lcdcmd(0x0E);  //Command for : Display ON,Cursor ON.
	delay_50ms();
	lcdcmd(0x01);		//Command for : Clear Display Screen.
	delay_50ms();
	lcdcmd(0x80);
	delay_50ms();
	lcddisplay("Initialization");
		lcdcmd(0x01);
	delay_50ms();
	lcdcmd(0x80);
	delay_50ms();
		lcddisplay("key press");
		lcdcmd(0x8a);
	delay_50ms();
	for(i=0;i<4;i++){
//	 x=0;
		psw[i]=keypad();
		delay_50ms();
		delay_50ms();
		delay_50ms();
		delay_50ms();
	}
	lcdcmd(0x01);		
	delay_50ms();
	lcdcmd(0x80);
	delay_50ms();
	for(i=0;i<4;i++){
//	 x=0;
		 lcddata(psw[i]) ;      
		delay_50ms();
		delay_50ms();
		delay_50ms();
		delay_50ms();
	}
	lcdcmd(0x01);		
	delay_50ms();
	lcdcmd(0x80);
	delay_50ms();
		lcddisplay("checking");
	
	
	if(psw[0] == pswval[0] && psw[1] == pswval[1] && psw[2] == pswval[2] && psw[3] == pswval[3]){
	lcdcmd(0x01);		//Command for : Clear Display Screen.
	delay_50ms();
	lcdcmd(0x80);
	delay_50ms();
		lcddisplay("Set Password");
	}
	else{
		lcdcmd(0x01);		//Command for : Clear Display Screen.
	delay_50ms();
			lcdcmd(0x80);
	delay_50ms();
		lcddisplay("Process failed");
		lcdcmd(0x01);		//Command for : Clear Display Screen.
	delay_50ms();
		lcdcmd(0x80);
	delay_50ms();
		lcddisplay("Retry");
		break;
	}
	
//	npsw[4];
  for(k=0;k<4;k++){
	
	npsw[k]=keypad();
		delay_50ms();
		delay_50ms();
		delay_50ms();
		delay_50ms();
	
	}
	//m=0;
	///*********************///
	while(1){
		lcdcmd(0x01);		//Command for : Clear Display Screen.
	delay_50ms();
		lcdcmd(0x80);
	delay_50ms();
		lcddisplay("Enter Password");
		lcdcmd(0x01);		//Command for : Clear Display Screen.
	delay_50ms();
		lcdcmd(0x80);
	delay_50ms();
		lcddisplay("key press");
		lcdcmd(0x8a);
	delay_50ms();
		for(i=0;i<4;i++){
	
		psw[i]=keypad();
			delay_50ms();
		delay_50ms();
		delay_50ms();
		delay_50ms();
	
	}
		
	l=0;
	while(l<4 && npsw[l]==psw[l]){
	
		l++;	
	}
	if(l<4){
		lcdcmd(0x01);		//Command for : Clear Display Screen.
	delay_50ms();
		lcdcmd(0x80);
	delay_50ms();
		lcddisplay("password notmatch");
	}
	else{
		lcdcmd(0x01);		//Command for : Clear Display Screen.
	delay_50ms();
		lcdcmd(0x80);
	delay_50ms();
		lcddisplay("Password math");
		lcdcmd(0x01);		//Command for : Clear Display Screen.
	delay_50ms();
		lcdcmd(0x80);
	delay_50ms();
		lcddisplay("Door Opening");
		
		Mp=1;
		Mn=0;
		
		for(n=0;n<600;n++){
		
				delay_50ms();
		
		}
		lcdcmd(0x01);		//Command for : Clear Display Screen.
	delay_50ms();
		lcdcmd(0x80);
	delay_50ms();
		lcddisplay("Door closing");
		Mp=0;
		Mn=1;
		
		for(n=0;n<600;n++){
		
				delay_50ms();
		
		}
		Mp=0;
		Mn=0;
			lcdcmd(0x01);		//Command for : Clear Display Screen.
	delay_50ms();
		lcdcmd(0x80);
	delay_50ms();
		lcddisplay("Door closed");
	}	
	}
 }
}







