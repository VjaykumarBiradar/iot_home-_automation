
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>
#define FIREBASE_HOST "tagglabs-office.firebaseio.com"                     //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "taOeubghZXkNNTyIY4ayxwTzF50wk6dAZIwLbPBa"       //Your Firebase Database Secret goes here
#define WIFI_SSID "tagglabs"                                               //your WiFi SSID for which yout NodeMCU connects
#define WIFI_PASSWORD "12345six"                                      //Password of your wifi network 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


int Relay1= 12; //D6
int val1;

#define Relay2 14 //D2
int val2;

#define Relay3 13  //D7
int val3;

#define Relay4 16 //D0
int val4;

void setup()
{
  Serial.begin(115200);   // Select the same baud rate if you want to see the datas on Serial Monitor
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);

  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, HIGH);
  digitalWrite(Relay4, HIGH);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // display.display();
  delay(1000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE, BLACK);        // Draw white text
  display.setCursor(10,8);            // Start at top-left corner
  display.println(F("Tagglabs"));
  display.setTextSize(1);
  display.setTextColor(WHITE); 
   display.setCursor(20,25);            // Start at top-left corner
 // display.println(F("technologies"));  
  display.display();
  display.startscrollleft(0x00, 0x00);
  delay(1000);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(5, 35);            // Start at top-left corner
  display.println(F("Connecting"));
   display.setTextSize(1);
  display.setTextColor(WHITE); 
   display.setCursor(50,50);            // Start at top-left corner
 // display.println(F("To Server"));  
  
  display.display();
  display.startscrollleft(0x00, 0x00);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");

    display.clearDisplay();
    delay(2000);
  }
  Serial.println();
  Serial.print("connected:");
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE, BLACK);        // Draw white text
  display.setCursor(10, 8);            // Start at top-left corner
  display.println(F("Tagglabs"));
  display.display();
  display.startscrollleft(0x00, 0x00);
  delay(1000);
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(5, 30);            // Start at top-left corner
  display.println(F("Connected"));
  display.setTextSize(1);
  display.setTextColor(WHITE); 
   display.setCursor(50,50);            // Start at top-left corner
  display.println(F("3"));  
  display.display();
  delay(100);
  display.startscrollleft(0x00, 0x00);

  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("S1", 0);                    //Here the varialbe"S1","S2","S3" and "S4" needs to be the one which is used in our Firebase and MIT App Inventor
  Firebase.setInt("S2", 0);
  Firebase.setInt("S3", 0);
  Firebase.setInt("S4", 0);
  Serial.println("Done");

}
void firebasereconnect()
{
  Serial.println("Trying to reconnect");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  if (Firebase.failed())
  {
    Serial.print("setting number failed:");
    Serial.println(Firebase.error());
    firebasereconnect();
    return;
  }

  val1 = Firebase.getString("S1").toInt();                                      //Reading the value of the varialble Status from the firebase

  if (val1 == 1)                                                          // If, the Status is 1, turn on the Relay1
  {
    digitalWrite(Relay1, LOW);
    Serial.println("light 1 ON");
    
  }
  else if (val1 == 0)                                                   // If, the Status is 0, turn Off the Relay1
  {
    digitalWrite(Relay1, HIGH);
    
    Serial.println("light 1 OFF");
   
  }

  val2 = Firebase.getString("S2").toInt();                                      //Reading the value of the varialble Status from the firebase

  if (val2 == 1)                                                          // If, the Status is 1, turn on the Relay2
  {
    digitalWrite(Relay2, LOW);
    Serial.println("light 2 ON");
    
  }
  else if (val2 == 0)                                                   // If, the Status is 0, turn Off the Relay2
  {
    digitalWrite(Relay2, HIGH);
    Serial.println("light 2 OFF");
   
  }

  val3 = Firebase.getString("S3").toInt();                                      //Reading the value of the varialble Status from the firebase

  if (val3 == 1)                                                          // If, the Status is 1, turn on the Relay3
  {
    digitalWrite(Relay3, LOW);
    Serial.println("light 3 ON");
  }
  else if (val3 == 0)                                                   // If, the Status is 0, turn Off the Relay3
  {
    digitalWrite(Relay3, HIGH);
    Serial.println("light 3 OFF");
  }

  val4 = Firebase.getString("S4").toInt();                                      //Reading the value of the varialble Status from the firebase

  if (val4 == 1)                                                          // If, the Status is 1, turn on the Relay4
  {
    digitalWrite(Relay4, LOW);
    Serial.println("light 4 ON");
  }
  else if (val4 == 0)                                                   // If, the Status is 0, turn Off the Relay4
  {
    digitalWrite(Relay4, HIGH);
    Serial.println("light 4 OFF");
  }
  else{}
}
