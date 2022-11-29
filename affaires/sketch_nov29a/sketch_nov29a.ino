#include <LiquidCrystal_I2C.h>



int totalColumns = 16;
int totalRows = 2;
LiquidCrystal_I2C lcd(0x27, totalColumns, totalRows);

String input = "";
String staticMessage = "SMART COURT";

void scrollMessage(int row, String message, int delayTime, int totalColumns) {
  for (int i=0; i < totalColumns; i++) {
    message = " " + message;  
  } 
   message = message + " ";
  for (int position = 0; position < message.length(); position++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(position, position + totalColumns));
    delay(delayTime);
  }
}

void setup()
{
		lcd.init();
	//lcd.begin(20, 4);
  lcd.backlight();
	lcd.setCursor(0, 0);
//	lcd.print("Hello, ");

	Serial.begin(9600);
	//pinMode(13, OUTPUT);
//	Serial.println("Available");
	
  /* add setup code here */
	
}

void loop()
{
	if (Serial.available() > 0){
    String input = Serial.readString();
    if (input == "#") lcd.clear();
    else {
          lcd.setCursor(0, 0);
      lcd.print(staticMessage);
      int i=0;
      do{
        i++;
        scrollMessage(1, input,700, totalColumns);
        
        }while(i!=2);
         
         }
	}

 
 }
	

