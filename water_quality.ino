#include <OneWire.h> 
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#define ONE_WIRE_BUS 9
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
LiquidCrystal lcd( A0, A1, A2, A3, A4, 11);
int turbiditySensor = A5;
int red = 2;
int green = 3;
int blue = 4;

void setup(void) 
{ 
   setled(0,0,0);
   pinMode (9, INPUT);//temperature input
   pinMode(2,OUTPUT);//red
   pinMode(3,OUTPUT);//green
   pinMode(4,OUTPUT);//blue
   pinMode(A5,INPUT);//turbidity
   lcd.begin(16, 2);
   lcd.setCursor(0,0);
   sensors.begin();//temp
   lcd.print("Water Quality");
   lcd.setCursor(0,1);
   lcd.print("Monitoring Sys");
   delay(3000);
} 


void loop(void) 
{ 
   lcd.clear();
   sensors.requestTemperatures(); 
   lcd.setCursor(0,0); 
   lcd.print("Temperature:"); 
   lcd.print(sensors.getTempCByIndex(0)); 
   delay(2000);
   lcd.clear();

   
    delay(1000);
    ntu_Value();
  

} 




void setled(int redvalue, int greenvalue ,int bluevalue)
{
    analogWrite(red,255 - redvalue);
    analogWrite(blue,255 - bluevalue);
    analogWrite(green,255 - greenvalue);
    
}





void ntu_Value()
{
   int ntu;
   int sensorValue = analogRead(A5);
   sensorValue =  map(sensorValue, 14,856,  0,1023);
   float volt = sensorValue * (5.0 / 1024.0);

   if(volt<2.5)
   {
      ntu=3000; 
      
   }
   else if (volt>4.1)
   {
      ntu=2;
    
   }
   else
   {
      ntu = -1120.4*square(volt)+ 5742.3*volt - 4352.9; 
   }

    lcd.setCursor(0, 0);
    lcd.print("Turbidity: ");
    lcd.print(ntu);

    delay(2000);
    lcd.setCursor(0, 1);
    
    if (ntu < 20) 
    {
      setled(0,255, 0);
      lcd.print("CLEAR WATER");
    }
   
    if ((ntu > 20) && (ntu < 2000)) 
    {
      setled(255,165, 0);
      lcd.print("CLOUDY WATER");
    }
    
    if (ntu > 2000) 
    {
      setled(255, 0 , 0);
      lcd.print("DIRTY WATER");
    }
    delay(2000);


    
}
