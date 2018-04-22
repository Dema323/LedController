
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "xxxxx";

char ssid[] = "xxxxx";
char pass[] = "xxxxx";

// this constant won't change:
const int potPin= A0;  //Declare potPin to be analog pin A0
const int buttonPin = D3;    // the pin that the pushbutton is attached to
const int ledPin1 = D4;       // the pin that the LED is attached to
const int ledPin2 = D5;       // the pin that the LED is attached to
const int ledPin3 = D6;       // the pin that the LED is attached to

// Variables will change:
int readValue;  // Use this variable to read Potentiometer
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int brightness1 = 0; // Start off with LED off
int brightness2 = 0;
int brightness3 = 0;
int potValue;   // Use this variable to read Potentiometer
int writeValue; // Use this variable for writing to LED

void setup() {
  WiFi.mode(WIFI_STA);
  Blynk.begin(auth, ssid, pass);
  while (Blynk.connect() == false) {}  //ArduinoOTA.setHostname("xxxxxxx"); // OPTIONAL
  ArduinoOTA.begin();// initialize the button pin as a input:
  pinMode(buttonPin, INPUT);  // initialize the LED as an output:
  pinMode(ledPin1, OUTPUT);  // initialize serial communication:
    pinMode(ledPin2, OUTPUT);  // initialize serial communication:
      pinMode(ledPin3, OUTPUT);  // initialize serial communication:
  pinMode(potPin, INPUT);  //set potPin to be an input
  potValue = analogRead(potPin);
  Serial.begin(9600);
}

BLYNK_WRITE(V1) // Slider to led
{

  brightness1 = param.asInt(); // Get slider value.
  analogWrite(ledPin1, brightness1); //Send data to LED
}

BLYNK_WRITE(V2) // Slider to led
{

  brightness2 = param.asInt(); // Get slider value.
  analogWrite(ledPin2, brightness2); //Send data to LED
}

BLYNK_WRITE(V3) // Slider to led
{

  brightness3 = param.asInt(); // Get slider value.
  analogWrite(ledPin3, brightness3); //Send data to LED
}


void Button()
{
// read the pushbutton input pin:
buttonState = digitalRead(buttonPin);

// compare the buttonState to its previous state
if (buttonState != lastButtonState) {
  // if the state has changed, increment the counter
  if (buttonState == HIGH) {
    // if the current state is HIGH then the button went from off to on:
    buttonPushCounter++;
    Serial.println("on");
    Serial.print("number of button pushes: ");
    Serial.println(buttonPushCounter);
  } else {
    // if the current state is LOW then the button went from on to off:
    Serial.println("off");
  }
  // Delay a little bit to avoid bouncing
  delay(50);
}
// save the current state as the last state, for next time through the loop
lastButtonState = buttonState;


// turns on the LED every four button pushes by checking the modulo of the
// button push counter. the modulo function gives you the remainder of the
// division of two numbers:
if (buttonPushCounter % 3 == 1) //RED
{readValue = analogRead(potPin);
    if(potValue != readValue){
      brightness1 = (255./1023.) * readValue; //Calculate Write Value for LED
      analogWrite(ledPin1, brightness1); //Send data to LED
      potValue = analogRead(potPin);
      //Blynk.virtualWrite(V1, brightness); //Send feedback to slider Widget
    }
    delay(100);
}

if (buttonPushCounter % 3 == 2) //GREEN
{readValue = analogRead(potPin);
    if(potValue != readValue){
      brightness2 = (255./1023.) * readValue; //Calculate Write Value for LED
      analogWrite(ledPin2, brightness2); //Send data to LED
      potValue = analogRead(potPin);
      //Blynk.virtualWrite(V1, brightness); //Send feedback to slider Widget
    }
    delay(100);
}

if (buttonPushCounter % 3 == 0) //BLUE
{readValue = analogRead(potPin);
    if(potValue != readValue){
      brightness3 = (255./1023.) * readValue; //Calculate Write Value for LED
      analogWrite(ledPin3, brightness3); //Send data to LED
      potValue = analogRead(potPin);
      //Blynk.virtualWrite(V1, brightness); //Send feedback to slider Widget
    }
    delay(100);
}

}


void loop() {
  Blynk.run();
  ArduinoOTA.handle();
  Button();
}
