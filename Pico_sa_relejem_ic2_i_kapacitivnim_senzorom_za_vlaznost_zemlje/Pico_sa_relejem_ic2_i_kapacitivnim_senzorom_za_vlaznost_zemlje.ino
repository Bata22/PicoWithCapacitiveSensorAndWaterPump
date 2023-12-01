 
 #include <Wire.h> 
    
 #include <LiquidCrystal_I2C.h>
 LiquidCrystal_I2C lcd(0x27,16,2); 

  const int DryVal=3120 ;
  const int WetVal= 1550 ;
   int soilMoistureVal;
   int soilMoisturePercent;
   
   bool pump_activation= false;

   #define SENSOR_IN 0
   #define RELEY 16

 void setup()  
  {  
    Serial.begin(6900);
   lcd.begin();    //initialize lcd screen   
   lcd.backlight();  // turn on the backlight
   lcd.setCursor(0,0); 
   analogReadResolution(12);
   pinMode(RELEY, OUTPUT);
   digitalWrite(RELEY, LOW); 
  
  }  
 void loop()   
  {  
    soilMoistureVal=analogRead(SENSOR_IN);
    Serial.print(soilMoistureVal);
    Serial.print(" - ");
    soilMoisturePercent= map(soilMoistureVal, DryVal, WetVal, 0, 100);

    soilMoisturePercent = constrain (soilMoisturePercent, 0, 100);

    Serial.println (soilMoisturePercent);
  lcd.clear();
   lcd.setCursor(0,0);  
   lcd.print("Vlaznost zemlje");  
   lcd.setCursor(0,1);  
   lcd.print(soilMoisturePercent);;  
   lcd.print("%");
   delay(500);  

   lcd.clear();

   if (soilMoisturePercent <=20)
   {
    pumpOn();
    
    } else
    {
      pumpOff();
      
      }


  
    
   
  }  



 void pumpOn()
 {
  digitalWrite(RELEY, HIGH);
   pump_activation= true;
  
  }

  void pumpOff()
 {
  digitalWrite(RELEY, LOW);
   pump_activation= false;
  }
