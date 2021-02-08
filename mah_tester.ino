//#include <LiquidCrystal.h>  //Default Arduino LCD Librarey is included 
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8; //Mention the pin number for LCD connection
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const float BAT_LOW = 3.3;    //to define the low voltage limit of the Li Ion cell
const float BAT_HIGH = 4.2;   //to define the high voltage limit of the cell
const int MOSFET_Pin=9;
const int PWM_VALUE=50
;
unsigned long previousMillis = 0; // Previous time in ms
unsigned long millisPassed = 0;  // Current time in ms
float Capacity=6260;     //Variable to define the battery Capacity
float Resistor=2.5;   // Load Resistor Value is 2.5ohms
float mA;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  //lcd.begin(16, 2); //Initialise 16*2 LCD
  //lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  //lcd.print("Battery Capacity");
  //lcd.setCursor(0,1);
  //lcd.print("Tester Circuit");
  //delay(3000);
  //lcd.clear();
}
void loop() {
  analogWrite(MOSFET_Pin, PWM_VALUE);
  // read the input on analog pin 0:
  int sensorValue_voltage_Cell = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage =0.3 + sensorValue_voltage_Cell * (5 / 1023.0);
  Serial.print("VOLTAGE: ");
  Serial.println(voltage);      // Here the voltage is being printed on Serial Monitor
  //lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
  //lcd.print("Voltage: "); // Print the voltage reading on the screen
  //lcd.print(voltage);
  delay(100);
  int sensorValue_Shunt_Resistor= analogRead(A1);
  float voltage1= sensorValue_Shunt_Resistor *(5.00 / 1023.0);
  float current= voltage1/Resistor;
  Serial.print("Current: ");
  Serial.println(current);
  //lcd.setCursor(0, 1); //Set the cursor on the first column and the second row (counting starts at 0!).
  //lcd.print("Current: ");
  //lcd.print(current); 
  if ( voltage > BAT_HIGH)
  {
    digitalWrite(MOSFET_Pin, LOW);    // Turned Off the MOSFET , No discharge 
    Serial.println( "Warning High-V! ");
    //lcd.clear();
    //lcd.setCursor(0,0);
    //lcd.print("HIGH VOLTAGE!!");
    delay(2000);
    //lcd.clear();
  }
  else if(voltage < BAT_LOW)
  {
      digitalWrite(MOSFET_Pin, LOW);      // Turned Off the MOSFET , No discharge 
      Serial.println( "Warning Low-V! ");
      //lcd.clear();
      //lcd.setCursor(0,0);
      //lcd.print("Low Voltage!!!");
      delay(2000);
      Serial.print("TOTAL CAPACITY: ");
      Serial.println(Capacity);
      //lcd.clear();
      //lcd.setCursor(0,0);
      //lcd.print("CAPACITY:");
      //lcd.setCursor(0,1);
      //lcd.print(Capacity);
      delay(10000);
  }
  else if(voltage > BAT_LOW && voltage < BAT_HIGH  ) 
  { // Check if the battery voltage is within the safe limit
      millisPassed = millis() - previousMillis;     
      mA = current * 1000.0 ;
      Capacity = Capacity + (mA * (millisPassed / 3600000.0)); // 1 Hour = 3600000ms to convert it into mAh units
      previousMillis = millis();
      Serial.print("CAPACITY:  ");
      Serial.println(Capacity);//uncomment this line to diplay on serial monitor
      delay(1000); 
      //lcd.clear();
     }
}
