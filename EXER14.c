#include<LPC214x.H>
#include<STRING.H>

#define  O1  0x00E00000
#define  O2  0x00D00000
#define  O3  0x00B00000
#define  O4  0x00700000
		
#define  I1  0x000E0000
#define  I2  0x000D0000
#define  I3  0x000B0000
#define  I4  0x00070000

#define  CLR  0x00F00000

void DELAY(unsigned int);
void INIT_GPIO(void);
void INIT_PLL(void);
void LCDSTR(unsigned char ADDRESS,char *MSG);
void LCD_DATA(unsigned char);
void LCD_CD(unsigned int);
void LCD_INIT(void);
char scan(int);
void delay(int);

unsigned int E  = 0x00000800;
unsigned int RW  = 0x00000400;
unsigned int RS  = 0x00000200;

int main()
 {
    INIT_PLL();
	INIT_GPIO();
	LCD_INIT();
	      LCDSTR(0x00000080,"Matrix keypad ");
		  LCDSTR(0x000000C0,"key pressed "); 
	 while(1)
	  {
	    IO0CLR =CLR;
		         IO0SET =O1; 
		          delay(10);
		        if(scan(I1))LCDSTR(0x000000CC,"0");
		        if(scan(I2))LCDSTR(0x000000CC,"4");
		        if(scan(I3))LCDSTR(0x000000CC,"8");
		        if(scan(I4))LCDSTR(0x000000CC,"C");
				 IO0CLR = CLR;
				 IO0SET = 02;
				 if(scan(I1))LCDSTR(0x000000CC,"1");
		        if(scan(I2))LCDSTR(0x000000CC,"5");
		        if(scan(I3))LCDSTR(0x000000CC,"9");
		        if(scan(I4))LCDSTR(0x000000CC,"D");
				  IO0CLR = CLR;
				 IO0SET = 03;
				 if(scan(I1))LCDSTR(0x000000CC,"2");
		        if(scan(I2))LCDSTR(0x000000CC,"4");
		        if(scan(I3))LCDSTR(0x000000CC,"A");
		        if(scan(I4))LCDSTR(0x000000CC,"E");
				 IO0CLR = CLR;
				 IO0SET = 04;
				 if(scan(I1))LCDSTR(0x000000CC,"3");
		        if(scan(I2))LCDSTR(0x000000CC,"7");
		        if(scan(I3))LCDSTR(0x000000CC,"B");
		        if(scan(I4))LCDSTR(0x000000CC,"F");
			}
	}
char scan(int keystatus)
 {
   while((IO0PIN & 0x000F0000)==keystatus)
   {
     delay(50);
	   while((IO0PIN & 0x000F0000)==0x000F0000)return 1;
	}
	return(0);
 }

void delay(int n)
 {
   int i,j;
   for(i=1; i<=n; i++)
	for(j=0; i<=1000; j++);
	}
void DELAY(unsigned int VALUE)
  {
 	unsigned int i,j;
	 for(i=0; i<VALUE; i++)
	 {
	   	for(j=1; i<1200; j++);
		}
	}

void INIT_GPIO()
 {
  IO0DIR =0x00F00E00;
  IO1DIR =0x00FF0000;
  }
void INIT_PLL()
 {
   PLL0CFG=0x00000024;
   PLL0CON=0x00000001;
   PLL0FEED=0x000000AA;
   PLL0FEED=0x00000055;
   while(!(PLL0STAT & 0x00000400));
    PLL0CON=0x00000003;
   PLL0FEED=0x000000AA;
   PLL0FEED=0x00000055;
   VPBDIV=0x00000002;
   }
void LCD_DATA(unsigned char value)
{
  unsigned int b,TEMP;
  TEMP = value;
  for(b=0;b<16;b++)
  {
    TEMP = TEMP<<1;
	}
	IO1SET = TEMP;
	IO1CLR = ~TEMP;
	IO0CLR = RW;
	IO0SET = RS;
	IO0SET = E;
	DELAY(50);
	IO0CLR = E;
 }
void LCD_CMD(unsigned int LCMD)
 {
   unsigned int b;
    for(b=0;b<16;b++)
  {
    LCMD = LCMD<<1;
	}
	IO1SET = LCMD;
	IO1CLR = ~LCMD;
	IO0CLR = RW;
	IO0CLR = RS;
	IO0SET = E;
	DELAY(50);
	IO0CLR = E;
 }
void LCDSTR(unsigned char ADDRESS,char *MSG)
 {
   unsigned char COUNT,LENGTH;
        LCD_CMD(ADDRESS);
	LENGTH = strlen(MSG);
	for(COUNT=0;COUNT<LENGTH;COUNT++)
	{
	  LCD_DATA(*MSG);
	  MSG++;
	  }
	}
void LCD_INIT()	
 {
   LCD_CMD(0x00000038);
   LCD_CMD(0x0000000C);
   LCD_CMD(0x00000001);
   LCD_CMD(0x00000006);
   }

