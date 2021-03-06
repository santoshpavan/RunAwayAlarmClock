#include<LiquidCrystal.h>
#include<Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;

LiquidCrystal lcd(8,9,10,11,12,13);
int t,a,b,s,c,d,e,f,g,k,l,i;
char z,u,p;

void setup()
{  
	Serial.begin(9600);  
	lcd.begin(16,2);  
	Wire.begin();  
	rtc.begin();  

	if(! rtc.isrunning())  
	{    
		lcd.print("no rtc");
	}  
	
	pinMode(5,INPUT); //off  
	pinMode(2,INPUT); //red  
	pinMode(3,INPUT); //green  
	pinMode(4,INPUT); //blue  
	pinMode(6,OUTPUT); //yellow  
	pinMode(7,OUTPUT); //buzzer
  
	lcd.clear();  
	lcd.print("Press red");	
	delay(500);  
	
	while(1)  
	{    
		lcd.setCursor(0,0);    
		lcd.clear();    
		
		if(digitalRead(2)==HIGH) //red    
		{      
			a=getvalue('z');      
			lcd.setCursor(0,0);      
			lcd.print("a= ");      
			lcd.print(a);      
			b=getvalue('y');      
			lcd.setCursor(0,0);      
			lcd.print("b= ");      
			lcd.print(b);      
			c=getvalue('x');      
			lcd.setCursor(0,0);      
			lcd.print("c= ");      
			lcd.print(c);      
			d=getvalue('w');      
			lcd.setCursor(0,0);      
			lcd.print("d= ");      
			lcd.print(d);
      
			digitalWrite(7,HIGH); //red(right)      
			delay(1000);      
			digitalWrite(7,LOW);      
			lcd.print("press green");
      
			delay(500);      
			
			if(digitalRead(3)==HIGH) //green      
			{        
				digitalWrite(7,HIGH); //red(right)        
				delay(1000);        
				digitalWrite(7,LOW);        
				break ;      
			}    
		}  
    
		
		if(digitalRead(3)==HIGH) //green    
		{       
			break;    
		}  
	}
	
	rtc.adjust(DateTime(2015,a,b,c,d,0)); //a-month;b-day;c-hour;d-minute
}

void loop() 
{   
	lcd.setCursor(0,0);   
	DateTime now = rtc.now();   
	int years = now.year();   
	int months = now.month();   	
	int date = now.day();
	int hours = now.hour();   
	int minutes = now.minute();   
	int seconds = now.second();
   
	lcd.print(date);   
	lcd.print("/");   
	lcd.print(months);   
	lcd.print("/");   
	lcd.print(years);   
	lcd.setCursor(0,1);  
	lcd.print(hours);   
	lcd.print(":");   
	lcd.print(minutes);   
	lcd.print(":");   
	lcd.print(seconds);  
	
	if (seconds==59)   
	{
		lcd.clear();
	}   
   //alarm setting   
	
	if(digitalRead(2)==HIGH) //red   
	{     
		lcd.clear();     
		lcd.print("Enter ALARM");     
		k=getalarm('i'); //hours     
		l=getalarm('j'); //mins
     
		while(1)     
		{         
			lcd.setCursor(0,0);       
			lcd.print("ALARM= ");       
			lcd.print(l);       
			lcd.print(":");       
			lcd.print(k);
       
			if(digitalRead(3)==HIGH) //green       
			{         
				delay(1000);         
				break;       
			}     
		}     
		delay(1000);   
	}     
	
	if(hours==k)     
	{       
		if(minutes==l)       
		{         
			while(1)
			{         
				digitalWrite(7,HIGH); //buzzer
				
				if(digitalRead(5)==HIGH)         
				{           
					digitalWrite(7,LOW);           
					break;         
				}         
			}      
		}     
	} 
}

int getvalue(char k)
{  
	digitalWrite(6,HIGH); //yellow  
	delay(1000);  
	digitalWrite(6,LOW);  
	
	if(k=='z') //month  
	{    
		lcd.clear();    
		lcd.print("Enter the month");    
		t=0;    
		s=getit(t);
    
		if(s>12)    
		{
			s=s-12;
		}
		
		lcd.clear();    
		return s;  
	}  
	
	if(k=='y') //dates  
	{    
		lcd.clear();    
		lcd.print("Enter the date");    
		t=0;    
		s=getit(t);    
		
		if(a==2)    
		{      
			if(s>28)      
			{
				s=s-28;
			}    
		}    
		
		if(a==1||a==3||a==5||a==7||a==8||a==10||a==12)    
		{      
			if(s>31)      
			{
				s=s-31;
			}    
		}    
		
		if(a==4||a==6||a==9||a==11)    
		{      
			if(s>30)      
			{
				s=s-30;
			}    
		}
    
		lcd.clear();    
		return s;  
	}
  
	
	if(k=='x') //hour  
	{    
		lcd.clear();    
		lcd.print("Enter the hour");    
		t=0;    
		s=getit(t);    
		
		if(s>24)    
		{
			s=s-24;
		}
    
		lcd.clear();    
		return s;  
	}  
	
	if(k=='w') //minute  
	{    
		lcd.clear();    
		lcd.print("Enter the minute");    
		t=0;    
		s=getit(t);
		
		if(s>60)    
		{
			s=s-60;
		}
		
		lcd.clear();    
		return s;  
	}
}


int getit(int t)
{  
	while(1)  
	{    
		if(digitalRead(3)==HIGH) //green    
		{
			t=t+1;      
			lcd.clear();      
			lcd.print(t);      
			delay(300);    
		}    
		
		if(digitalRead(4)==HIGH) //blue    
		{      
			return t;    
		}  
	}
}

int getalarm(char h)
{
	if(h=='i')         
	{           
		f=getvalue('x');//hour      
		return f;         
	}     
	
	if(h=='j')       
	{           
		g=getvalue('w'); //min       
		return g;       
	}
}
