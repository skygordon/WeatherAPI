#include <WiFi.h> //Connect to WiFi Network
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h> //Used in support of TFT Display
#include <string.h>  //used for some string handling and processing.
#include <stdio.h>
#include <list>

char network[] = "MIT";  //SSID for 6.08 Lab
char password[] = ""; //Password for 6.08 Lab
//Some constants and some resources:
const int RESPONSE_TIMEOUT = 6000; //ms to wait for response from host
const int POSTING_PERIOD = 6000; //periodicity of getting a number fact.
const uint16_t IN_BUFFER_SIZE = 1000; //size of buffer to hold HTTP request
const uint16_t OUT_BUFFER_SIZE = 400; //size of buffer to hold HTTP response
char request_buffer[IN_BUFFER_SIZE]; //char array buffer to hold HTTP request
char response_buffer[OUT_BUFFER_SIZE]; //char array buffer to hold HTTP response

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

//input thingsss
const int input_pin = 16; //pin connected to button
uint8_t state;  //system state (feel free to use
uint8_t num_count; //variable for storing the number of times the button has been pressed before timeout
unsigned long timer;  //used for storing millis() readings.
  
  char message6[50]="";
  char message5[50]="";
  char message4[50]="";
  char message3[50]="";
  char message2[50]="";
  char message1[50]="";

  
void setup() {
  Serial.begin(115200);
  delay(10);


WiFi.begin(network,password); //attempt to connect to ESP8266WiFi
  uint8_t count = 0; //count used for ESP8266WiFi check times
  Serial.print("Attempting to connect to ");
  Serial.println(network);
  while (WiFi.status() != WL_CONNECTED && count<12) {
    delay(500);
    Serial.print(".");
    count++;
  }
  delay(3000);
  if (WiFi.isConnected()) { //if we connected then print our IP, Mac, and SSID we're on
    Serial.println("CONNECTED!");
    Serial.println(WiFi.localIP().toString() + " (" + WiFi.macAddress() + ") (" + WiFi.SSID() + ")");
    delay(500);
  } else { //if we failed to connect just Try again.
    Serial.println("Failed to Connect :/  Going to restart");
    Serial.println(WiFi.status());
    ESP.restart(); // restart the ESP (proper way)
  }
  
  tft.init();  //init screen
  startscreen();
  tft.setRotation(3); //adjust rotation
  pinMode(input_pin, INPUT_PULLUP); //set input pin as an input!
  state = 0; //start system in IDLE state!

}

void loop() {
  button(digitalRead(input_pin));
}


void button(uint8_t input){
  switch(state){
    case 0:
      if (input == 0){
      state = 1;
      Serial.println("Start Counting!!");
      }
      break; 
    case 1:
      if (input == 1){
      Serial.println("Counting!");
      state = 2;
      num_count++; // increases num_count
      timer = millis();
      while (millis() - timer < 200) {
        }
      timer = millis();
      } 
      break;
    case 2:
    if ((millis() - timer) > 2500) {
      Serial.println("Done Counting, numcount=");
      Serial.println(num_count);
      Serial.println("calling apireturn");
      Serial.println(apireturn());
      Serial.println(response_buffer);
      strcpy(message1, response_buffer);
      Serial.println(message1);
      changescreen();
      num_count = 0;
      state = 0;
      // checks if done pressing
    } else if (input == 0) {
      Serial.println("Still Counting");
      state = 1;
    }
      break;
  }}

unsigned long changescreen() {
  tft.setCursor(0, 0);
  tft.fillScreen(TFT_BLACK); //fill background
  tft.setRotation(3); //adjust rotation
  tft.setTextSize(1); //default font size
  tft.setTextColor(TFT_CYAN);
/*strcpy(message15, message14);
strcpy(message14, message13);
strcpy(message13, message12);
strcpy(message12, message11);
strcpy(message11, message10);
strcpy(message10, message9);
strcpy(message9, message8);
strcpy(message8, message7);
strcpy(message7, message6);*/
strcpy(message6, message5);
strcpy(message5, message4);
strcpy(message4, message3);
strcpy(message3, message2);
strcpy(message2, message1);
  tft.println("Info:");
  tft.println("");
  tft.println("");
  //tft.println(message1);
  tft.println(message2);
  tft.println("");
  tft.println(message3);
  tft.println("");
  tft.println(message4);
  tft.println("");
  tft.println(message5);
  tft.println("");
  tft.println(message6);
  /*
  tft.println(message7);
  tft.println(message8);
  tft.println(message9);
  tft.println(message10);
  tft.println(message11);
  tft.println(message12);
  tft.println(message13);
  tft.println(message14);*/
  }


  char apireturn () {

      char body[200]; //for body;
      sprintf(body,"numcount=%d",num_count);//generate body, posting to User, 1 step
      int body_len = strlen(body); //calculate body length (for header reporting)
      sprintf(request_buffer,"POST http://608dev.net/sandbox/sc/sfgordon/currentweatherapi.py HTTP/1.1\r\n");
      strcat(request_buffer,"Host: 608dev.net\r\n");
      strcat(request_buffer,"Content-Type: application/x-www-form-urlencoded\r\n");
      sprintf(request_buffer+strlen(request_buffer),"Content-Length: %d\r\n", body_len); //append string formatted to end of request buffer
      strcat(request_buffer,"\r\n"); //new line from header to body
      strcat(request_buffer,body); //body
      strcat(request_buffer,"\r\n"); //header
      Serial.println(request_buffer);
      do_http_request("608dev.net", request_buffer, response_buffer, OUT_BUFFER_SIZE, RESPONSE_TIMEOUT,true);
      tft.fillScreen(TFT_BLACK); //fill background
      tft.setCursor(0,0,1); // set the cursor
      tft.println(response_buffer); //print the result
      }

unsigned long startscreen() {
  tft.setCursor(0, 0);
  tft.fillScreen(TFT_BLACK); //fill background
  tft.setRotation(3); //adjust rotation
  tft.setTextSize(1); //default font size
  tft.setTextColor(TFT_CYAN);  
  tft.println("To Display:");
  tft.println("");
  tft.setTextColor(TFT_GREEN); 
  tft.println("Press button once for");
  tft.println("Current local temperature");
  tft.println("");
  tft.setTextColor(TFT_YELLOW); 
  tft.println("Press button twice for");
  tft.println("Current local time");
  tft.println("");
  tft.setTextColor(TFT_ORANGE); 
  tft.println("Press button 3 times for");
  tft.println("Current date");
  tft.println("");
  tft.setTextColor(TFT_RED); 
  tft.println("Press button 4 times for");
  tft.println("Current local visibility");
  }
