/*_________________________LIBRARY INCLUDES_________________________*/
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <Adafruit_NeoPixel.h>
#include <RGBWConverter.h>
#include <EEPROM.h>
#include "html_page.h"




/*________________PIN CONFIGURATION & DEFINATIONS__________________*/
/*----------------OUTPUT PINS------------------*/
#define LED_PIN_L 2   // LED Strip LEFT Signal Connection
#define LED_PIN_R 4   // LED Strip RIGHT Signal Connection
#define LED_PIN_3 19  // Extra LEDS
//define LED_PIN_4 13 //Extra LEDS/ABS2

/*-------------- INPUT PINS-----------------*/
#define ParkSignal 15   // Park Signal Connection
#define BrakeSignal 13  // Brake Signal Connection
#define LeftSignal 12   // Left Blinker Signal Connection
#define RightSignal 14  // Right Blinker Signal Connection
#define DRLsignal 26    // DRL Signal Connection
#define ReverseSignal 27  // Reverse Signal Connection
#define Extraleds 32
//define Extraleds2 33 // ExtraLeds/DRL2




/*___________________________________Wifi AP Configuration__________________________*/
#ifndef APSSID
#define APSSID "Richard's Car"
#define APPSK "Color1234"
#endif
/*--------- SSID and password of the access point ------------*/
const char *ssid = APSSID;
const char *password = APPSK;

/*------------------ Server Configuration --------------------*/
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);




//.......................................................................................................................................................
/*_______________________________________STRIP CONFIGURATIIONS_____________________________________________*/
/*_____________________Number of LEDs Setup___________________________*/
uint16_t NUM_LEDS_L = 60;  // default no. of neopixel leds in Left Strip
uint16_t NUM_LEDS_R = 65;  // default no. of neopixel leds in Right Strip
uint16_t NUM_LEDS_3 = 60;  // default extra leds
//uint16_t NUM_LEDS_4 = 60; // default extra leds

/*____________________Frequency of led strip setup_____________________*/
uint8_t freq_L = NEO_KHZ800;  //default frequency for left strip
uint8_t freq_R = NEO_KHZ800;  //default frequency for Right strip
uint8_t freq_3 = NEO_KHZ800;  //default frequency for extra strip
//uint8_t freq_4 = NEO_KHZ800; //default frequency for extra strip

/*___________________Led Strip Color Scheme Setup______________________*/
uint8_t scheme_L = NEO_GRBW;  //default Color Scheme for left strip
uint8_t scheme_R = NEO_GRBW;  //default Color Scheme for right strip
uint8_t scheme_3 = NEO_GRBW;  //default Color Scheme for extra
//uint8_t scheme_4 = NEO_GRBW; //default Color Scheme for extra

/*__________________________________________NEO PIXEL INITIALIZATION_______________________________________*/
Adafruit_NeoPixel *leds_L = new Adafruit_NeoPixel(NUM_LEDS_L, LED_PIN_L, scheme_L + freq_L);
Adafruit_NeoPixel *leds_R = new Adafruit_NeoPixel(NUM_LEDS_R, LED_PIN_R, scheme_R + freq_R);
Adafruit_NeoPixel *leds_3 = new Adafruit_NeoPixel(NUM_LEDS_3, LED_PIN_3, scheme_3 + freq_3);
//Adafruit_NeoPixel *leds_4 = new Adafruit_NeoPixel(NUM_LEDS_4, LED_PIN_4, scheme_4 + freq_4 );


/*__________________________RGBW Converter Config________________________*/
RGBWConverter converter(255, 255, 255, false);
RGBWConverter::RGBW col;



//............................................................................................................................................................
/*____________________________________NEOPIXEL FUNCTION VARIABLES____________________________________*/
uint8_t Strobe = 0;
uint8_t strobePerformed = 0;

uint8_t freq_select;    // temp to get data
uint8_t scheme_select;  // temp to get data

uint32_t leftColor = (224, 34, 0);         // Equivalent to RGB(224, 34, 0)
uint32_t RightColor = (224, 34, 0);        // Equivalent to RGB(224, 34, 0)
uint32_t thrdColor = (255, 0, 0);          // Equivalent to RGB(255, 0, 0)
uint32_t DRLColor = (255, 255, 255);       // Equivalent to RGB(255, 0, 0)
uint32_t DRLColorLeft = (255, 255, 255);   // Equivalent to RGB(255, 255, 255) (white)
uint32_t DRLColorRight = (255, 255, 255);  // Equivalent to RGB(255, 255, 255) (white)
uint32_t BrakeColor = (255, 0, 0);         // Equivalent to RGB(255, 0, 0) (red)
uint32_t rgbColor = (0, 0, 0);             // Equivalent to RGB(0, 0, 0) (black)


uint8_t brightness = 255;
uint32_t duration = 10000;   // (10s) duration of the effect in the loop
uint8_t BlinkerLEDs = 60;    // No of LEDs for Left/Right Blinker
uint16_t BlinkerSpeed = 10;  // Turn Signal Running LED Speed. Adjust this to
                             // match with your vehicle turn signal speed.
uint8_t strip_select = 3;

uint8_t BlinkerAnimation = 2;

uint8_t effect = 0;

bool isPlay = false;
bool isLoopEffect = false;
bool isRandom = false;

// effects that will be in the loop
uint8_t favEffects[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
                         12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
                         23, 24, 25, 26, 27, 28, 29, 30, 31, 32 };
uint8_t numFavEffects = sizeof(favEffects);

uint32_t lastChange;
uint8_t currentEffect = 0;

// variables for basic effects settings
uint8_t _delay = 20;
uint8_t _step = 10;
uint8_t _sat = 255;
uint16_t hue = 10000;
uint8_t Red = 0;
uint8_t Green = 0;
uint8_t Blue = 0;

int BlinkerOffDelay = 250;  // Turn Signal Off time. Adjust this to match with
                            // your vehicle turn signal speed.

int StartupSpeed = 25;
int ParkDetect = 0;
int effectState = 0;


uint32_t lastTime = millis();

//.................................................................................................................................................
/*________________________ USED FUNCTIONS DECLARATIONS __________________________*/
//Main page setup and loop Functions
void WI_FI_Init();
void NeoPixel_Init();
void Initialize_Inputs();
void EEPROM_Init();
void Server_Init();
void Handle_Inputs();

//car call functions
void Reverse();
void BrakeFull();
void ParkON();
void ParkOFF();
void AllOff();
void DRLRightFull();
void DRLLeftFull();
void RightOff();
void LeftDim();
void RightOff();
void LeftOff();
void RightDim();
void LeftFull();
void RightFull();
void MiddleOff();
void DualBlinker();
void BrakeMiddle();
void RightLit();
void LeftLit();
void ParkMiddle();
void DRLRightOff();
void DRLLeftOff();
void DRLON();
void updateConfig_L();
void updateConfig_R();
void playEffects();
void fadeall();
void LoadConfig();
void SaveConfig();



void setup() {
  //Begin Serial-UART for debugging baudrate 115200
  Serial.begin(115200);

  //Initialize and Connect to WI-FI
  WI_FI_Init();

  //Initialize NeoPixel Instance and Output Pins
  NeoPixel_Init();

  //Initialize Input Pins
  Initialize_Inputs();

  //EEPROM Setup
  EEPROM_Init();

  //Server Initialize
  Server_Init();

  //White over rainbow time init
  lastTime = millis();
}

void loop() {
  server.handleClient();
  webSocket.loop();

  //Handle Sensed Inputs and call relevant LED display functions
  Handle_Inputs();
}
