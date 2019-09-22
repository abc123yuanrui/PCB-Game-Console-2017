/*************************************************************************
Title:    game_console Template
Initial Author:   David Jahshan
Extended by : Wei Li  748080
Software: AVR-GCC 
Hardware: ATMEGA16 @ 8Mhz 

DESCRIPTION:
	Main and functions for Game Console basic sample code

*************************************************************************/

#include "game_console.h" 
#include <util/delay.h>

byte frame_buffer[LCDcolumn][LCDpage-1];
byte i=0;
byte j=0;
int ro=0;
int co=0;
int ro1=0;
int co1=0;
int flag=0;
int shoot=0;
byte threshold[] = {0,50,100,150,200,255};
int condition = 0;//setup initial condition of threshold

//**************************************************************************


//INTERRUPT1 INT1 initialise
void int1_init( void )
	{
		/* Interrupt */
    	sei();//enables global interrupt
     	GICR = 1<< INT0;//INT0 enable
	   	SET(MCUCR,_BV(ISC01),HIGH);
		SET(MCUCR,_BV(ISC00),HIGH);
		
	}
//**************************************************************************


//function of SPI data transmission
byte SPI_MasterTransmit(char cData)
{
	LCD_CS0_INIT(LOW);
	SPDR = cData;// start transmission 
	while(!(SPSR & (1<<SPIF)));// wait for transmission complete
		LCD_CS0_INIT(HIGH);	
	return SPDR;
}
//********************************************************************************


//function of command transmission
void LCD_command_tx(byte cData)
{	
	LCD_CD_INIT(LOW);// set LCD_CD = 0;
	SPI_MasterTransmit(cData);
}
//********************************************************************************


//function of data transmission
void LCD_data_tx(byte cData)
{
	LCD_CD_INIT(HIGH);
	SPI_MasterTransmit(cData);
}
//********************************************************************************


//function of LCD initialisation
void LCDInt(void)
{	
	LCD_RST_INIT(LOW);// rest LCD
	LCD_RST_INIT(HIGH);
	LCD_command_tx(0x40); // display start line 0
	LCD_command_tx(0xA1); // SEG reverse
	LCD_command_tx(0xC0); // normal COM0~COM63
	LCD_command_tx(0xA4); // disable -> Set All Pixel to ON
	LCD_command_tx(0xA6); // display inverse off
	LCD_command_tx(0xA2); // set LCD Bias Ratio A2/A3
	LCD_command_tx(0x2F); // set Power Control 28...2F
	LCD_command_tx(0x27); // set VLCD Resistor Ratio 20...27
	LCD_command_tx(0x81); // set Electronic Volume
	LCD_command_tx(0x10); // set Electronic Volume 00...3F
	LCD_command_tx(0xFA); // set Adv. Program Control
	LCD_command_tx(0x90); // set Adv. Program Control x00100yz yz column wrap x Temp Comp
	LCD_command_tx(0xAF); // display on
}
//********************************************************************************


//function of LCD cursor setting
void select_page(byte page)
{
	LCD_command_tx(0xB0 | page); 
}

void select_column(byte x)
{
	LCD_command_tx(x & 0x0F);      			// set LSB address:  0000 CA[3..0] 
	LCD_command_tx((0x1F & (x>>4))|0x10);  	// set MSB address:  0001 CA[7..4]   
}
//********************************************************************************


//function of clear LCD screen
void LCD_Pixel_Clear(void)
{
	byte x0;
	byte page0;
	for (x0=0; x0<=LCDcolumn-1; x0++)
	{
		for (page0=0;page0<=LCDpage-1;page0++)
		{
			LCD_command_tx(x0 & 0x0F);        
			LCD_command_tx(0x10 | (x0>>4));   
 			LCD_command_tx(0xB0 | page0);     
			LCD_data_tx(0x00);		
		}
	}
}
//********************************************************************************


//function of clear frame_buffer
void clear_frame_buffer(void)
{
	for(i=0;i<=LCDcolumn-1;i++){
		for(j=0;j<=LCDpage-1;j++){
			select_page(j);
			select_column(i);
			frame_buffer[i][j]=0x00;
		}
	}
}
//********************************************************************************



//function of LCD background light setting
void LCD_BACKLIGHT(byte threshold)
{   //set threshold
    OCR0 = threshold;
    SET(TCCR0,_BV(COM00),HIGH);
	SET(TCCR0,_BV(COM01),HIGH);
	SET(TCCR0,_BV(WGM01),LOW);
	SET(TCCR0,_BV(WGM00),HIGH);
	SET(TCCR0,_BV(CS02),LOW);
	SET(TCCR0,_BV(CS01),HIGH);
	SET(TCCR0,_BV(CS00),HIGH);

}
//********************************************************************************




//function of data send
void send_data(void)
{
	for(i=0;i<=LCDcolumn-1;i++){
		for(j=0;j<=LCDpage-1;j++){
			select_page(j);
			select_column(i);
			LCD_data_tx(frame_buffer[i][j]);
		}			
	}
}
//********************************************************************************
		

//2 Plot functions
void write_pixel(int c, int r)
{
	frame_buffer[c][(int)r/8]=(_BV((int)r%8)|(frame_buffer[c][(int)r/8]));
}

void write_name(int cc, int rr)
{

    write_pixel(cc+5, rr-3);
	write_pixel(cc+4, rr-4);
    write_pixel(cc+3, rr-4);
	write_pixel(cc+2, rr-4);
	write_pixel(cc+1, rr-4);
    write_pixel(cc+5, rr-2);
    write_pixel(cc+5, rr-1);
    write_pixel(cc+4, rr-1);
    write_pixel(cc+3, rr-1);
    write_pixel(cc+2, rr-1);
    write_pixel(cc+3, rr);
    write_pixel(cc+4, rr+1);
    write_pixel(cc+5, rr+2);
	write_pixel(cc+1, rr-4);
	write_pixel(cc+1, rr-3);
    write_pixel(cc+1, rr-2);
    write_pixel(cc+1, rr-1);
    write_pixel(cc+1, rr);
    write_pixel(cc+1, rr+1);
	write_pixel(cc+1, rr+2);
    write_pixel(cc+1, rr-1);
    write_pixel(cc+1, rr+2);
	write_pixel(cc+1, rr-2);
	write_pixel(cc+1, rr+2);

	write_pixel(cc-2, rr-4);
	write_pixel(cc-3, rr-3);
	write_pixel(cc-4, rr+2);
	write_pixel(cc-4, rr+1);
	write_pixel(cc-4, rr);
	write_pixel(cc-4, rr-1);
	write_pixel(cc-4, rr-2);
	write_pixel(cc-5, rr-3);
	write_pixel(cc-6, rr-4);

}
void write_bullet(int cc, int rr)
{
	write_pixel(cc+2, rr+1);
	_delay_ms(500);
	write_pixel(cc+2, rr);
	_delay_ms(500);
	write_pixel(cc-2, rr);
	_delay_ms(500);
	write_pixel(cc-2, rr-1);
}

void write_heart(int cc, int rr)
{
	write_pixel(cc+1, rr+3);
	write_pixel(cc-1, rr+3);
	write_pixel(cc-2, rr+3);
	write_pixel(cc+2, rr+3);
	write_pixel(cc, rr+2);
	write_pixel(cc+3, rr+2);
	write_pixel(cc-3, rr+2);
	write_pixel(cc+3, rr+1);
	write_pixel(cc-3, rr+1);
	write_pixel(cc+3, rr);
	write_pixel(cc-3, rr);
	write_pixel(cc+2, rr-1);
	write_pixel(cc-2, rr-1);
	write_pixel(cc+1, rr-2);
	write_pixel(cc-1, rr-2);
	write_pixel(cc, rr-3);
}
//********************************************************************************
//********************************************************************************

/* External interrupt */
//As long as INTERRUPT PORT INT0 at PD2 toggled flag rises
    ISR( INT0_vect )
	{
     
		if (BUTTON_SELECT_PRESSED)
		{
			BAT_LOW_LED_INIT(ON);
				
			if (condition == 5)
			{ 
				condition=(-1);
			}
			condition=condition+1;
			
			LCD_BACKLIGHT(threshold[condition]);
			_delay_ms(300);
			
		} 	
		else
		{
			BAT_LOW_LED_INIT(OFF);
		}
//********************************************************************************
		if (BUTTON_UP_PRESSED)
		{
			BAT_LOW_LED_INIT(ON);
			if(ro==10)
			{
				ro = ro;
				co = co;
			//write_name(co, ro);
				send_data();
				clear_frame_buffer();
			}
			else
			{
				ro = ro-1;
				co = co;
			//	write_name(co, ro);
				send_data();
				clear_frame_buffer();
			}	
		} 	
		else
		{
			BAT_LOW_LED_INIT(OFF);
		}
//********************************************************************************

		if (BUTTON_LEFT_PRESSED)
		{
			BAT_LOW_LED_INIT(ON);
			if(co==5)
			{
				ro = ro;
				co = co;
			//	write_name(co, ro);
				send_data();
				clear_frame_buffer();
			}
			else
			{
				ro = ro;
				co = co-1;
			//	write_name(co, ro);
				send_data();
				clear_frame_buffer();
			}		
		} 	
		else
		{
			BAT_LOW_LED_INIT(OFF);
		}
//********************************************************************************

		if (BUTTON_DOWN_PRESSED)
		{
			BAT_LOW_LED_INIT(ON);
			if(ro==53)
			{
				ro = ro;
				co = co;
				//write_name(co, ro);
				send_data();
				clear_frame_buffer();
			}
			else
			{
				ro = ro+1;
				co = co;
			//	write_name(co, ro);
				send_data();
				clear_frame_buffer();
			}			
		} 	
		else
		{
			BAT_LOW_LED_INIT(OFF);
		}
//********************************************************************************
		if (BUTTON_RIGHT_PRESSED)
		{
			BAT_LOW_LED_INIT(ON);
			if(co==96)
			{
				ro = ro;
				co = co;
				//write_name(co, ro);
				send_data();
				clear_frame_buffer();
			}
			else
			{
				ro = ro;
				co = co+1;
				//write_name(co, ro);
				send_data();
				clear_frame_buffer();
			}		
		} 	
		else
		{
			BAT_LOW_LED_INIT(OFF);
		}
//********************************************************************************
			if (BUTTON_ACTIONA_PRESSED)
			{
			BAT_LOW_LED_INIT(ON);
			flag = !flag;
			send_data();
			clear_frame_buffer();
			}
			else
			{
			BAT_LOW_LED_INIT(OFF);
			}
//********************************************************************************
			if (BUTTON_ACTIONB_PRESSED)
			{
			BAT_LOW_LED_INIT(ON);
			shoot = 1;
			co1=co;
			ro1=ro;
			send_data();
			clear_frame_buffer();	
			} 				
			else
			{
			BAT_LOW_LED_INIT(OFF);
		}	
		}

//MAIN MODULE
int main(void)
{
	BUTTON_UP_DIR(IN);
 	BUTTON_LEFT_DIR(IN);
 	BUTTON_DOWN_DIR(IN);
 	BUTTON_RIGHT_DIR(IN);
 	BUTTON_ACTIONA_DIR(IN);
 	BUTTON_ACTIONB_DIR(IN);
 	BUTTON_SELECT_DIR(IN);

	BUTTON_UP_INIT(HIGH);
 	BUTTON_LEFT_INIT(HIGH);
 	BUTTON_DOWN_INIT(HIGH);
 	BUTTON_RIGHT_INIT(HIGH);
 	BUTTON_ACTIONA_INIT(HIGH);
 	BUTTON_ACTIONB_INIT(HIGH);
 	BUTTON_SELECT_INIT(HIGH);

	BACKLIGHT_DIR(OUT);
	BACKLIGHT_INIT(HIGH);

	BAT_LOW_LED_DIR(OUT);
	BAT_LOW_LED_INIT(OFF); 
	
	SPI_PORTS_DIR(OUT); 
	SPI_MOSI_DIR(OUT);
	SPI_SCK_DIR(OUT);

	LCD_CS0_DIR(OUT);
	LCD_CD_DIR(OUT);
	LCD_RST_DIR(OUT);
	LCD_SS_INIT(HIGH);//PB4

	// enable SPI and Master
	SET(SPCR,_BV(SPE),HIGH);
	SET(SPCR,_BV(MSTR),HIGH);
	SET(SPCR,_BV(SPR0),HIGH);
	//SPI_MASTER_MODE(HIGH);
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
//********************************************************************************
	int1_init();
	LCDInt();
    //byte frame_buffer[101][7];
//********************************************************************************

	LCD_BACKLIGHT(threshold[0]);
	LCD_Pixel_Clear();
	clear_frame_buffer();
	send_data();
	ro = 31;
	co = 50;	
	send_data();
//********************************************************************************


	while (1)
	{
	if (flag==0)
		{write_name(co, ro);}
	else if (flag==1)
		{write_heart(co, ro);}	
	if (shoot==1){
		{
		write_bullet(co1, ro1);
		shoot=0;
			}	
	}	

}
