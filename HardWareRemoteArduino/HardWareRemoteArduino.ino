

#include "iClickerEmulator.h"
#include <RingBufCPP.h>
#include <string.h>




#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define MALLOC_SCREEN_WIDTH 128 // OLED display width, in pixels
#define MALLOC_SCREEN_HEIGHT 40 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(MALLOC_SCREEN_WIDTH, MALLOC_SCREEN_HEIGHT, &Wire, OLED_RESET);





#define IRQ_PIN 7
#define CSN 8
#define MAX_BUFFERED_PACKETS 10

int A = 0;
int B = 0;
int C = 0;
int D = 0;
int E = 0;

const int buttonPinLeftTop = 9;  
const int buttonPinRightTop = 6;
const int buttonPinBottom = 5;

int buttonStateLeftTop = 0;
int buttonStateRightTop = 0;  
int buttonStateBottom = 0;  

int channelLeft = 0;
int channelRight = 0;
String channelStringLeft = "A";
String channelStringRight = "A";

boolean initialized = false;

boolean firstTimeScreenWriteLetterValues = true;

iClickerEmulator clicker(CSN, IRQ_PIN, digitalPinToInterrupt(IRQ_PIN));
RingBufCPP<iClickerPacket_t, MAX_BUFFERED_PACKETS> recvBuf;

void setup()
{

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation gone WRONG"));
    for(;;); // Don't proceed, loop forever
  }

  pinMode(buttonPinLeftTop, INPUT);
  pinMode(buttonPinRightTop, INPUT);
  pinMode(buttonPinBottom, INPUT);

  delay(1000);
  Serial.begin(9600);
  Serial.println("working");
  //clicker.begin(iClickerChannels::DA);
  //clicker.dumpRegisters();
 // clicker.startPromiscuous(CHANNEL_SEND, recvPacketHandler);
  delay(1000);
  Serial.println("after promiscous");
 // clicker.dumpRegisters();
  
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.println("");
  display.display(); 

}


void loop()
{
  buttonStateLeftTop = digitalRead(buttonPinLeftTop);
  buttonStateRightTop = digitalRead(buttonPinRightTop);
  buttonStateBottom = digitalRead(buttonPinBottom);

  if(!initialized){


    if (buttonStateBottom == LOW) {
      channelSelect(channelStringLeft, channelStringRight);
      initialized = true;
      delay(300);
    }

    if (buttonStateLeftTop == LOW) {
      channelStringLeft = displayChannel(&channelLeft);
      delay(200);
    }

    if (buttonStateRightTop == LOW) {
      channelStringRight = displayChannel(&channelRight);
      delay(200);
    }

    
    display.clearDisplay();
    display.setTextSize(1); // Draw 2X-scale text
    display.setTextColor(WHITE);
    display.setCursor(18, 0);
    display.println("SELECT CHANNHEL:");
    
    display.setTextSize(2);
    display.setCursor(54, 20);
    
    display.print(channelStringLeft);
    display.println(channelStringRight);
    display.display(); 
    
    
    
  } else {

    if(firstTimeScreenWriteLetterValues){
      display.clearDisplay();
      updateValues();
      firstTimeScreenWriteLetterValues = false;
    }
    
    char tmp[30];
    iClickerPacket_t r;
  
    if (buttonStateBottom == LOW) {
      // Reset
      A = 0;B = 0;C = 0;D = 0;E = 0;
      display.clearDisplay();
      display.setCursor(10, 0);
      display.println("RESET");
      updateValues();
    } else {

    }
    
    while (recvBuf.pull(&r)) {
      
      uint8_t *id = r.packet.answerPacket.id;
      char answer = iClickerEmulator::answerChar((iClickerAnswer_t)r.packet.answerPacket.answer);
      snprintf(tmp, sizeof(tmp), "Captured: %c (%02X, %02X, %02X, %02X) \n", answer, id[0], id[1], id[2], id[3]);
      if(answer == 'A'){
        A++;
      }else if(answer == 'B'){
        B++;
      }else if(answer == 'C'){
        C++;
      }else if(answer == 'D'){
        D++;
      }else if(answer == 'E'){
        E++;
      }
      
      display.clearDisplay();
      updateValues();
    }
  }
}

void updateValues(){
    //display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(54, 0);
  
  display.print("A: ");display.println(A);
  display.setCursor(54, 8);
  display.print("B: ");display.println(B);
  display.setCursor(54, 16);
  display.print("C: ");display.println(C);
  display.setCursor(54, 24);
  display.print("D: ");display.println(D);
  display.setCursor(54, 32);
  display.print("E: ");display.println(E);
  
  display.display(); 
}


String displayChannel(int *channelValue){
  (*channelValue)++;

    if ((*channelValue) >= 4){
      *channelValue = 0;
    }
     switch(*channelValue) {
      case 0 :
         return "A";
         break;
      case 1 :
         return "B";
         break;
      case 2 :
         return "C";
         break;
      case 3 :
         return "D";
         break;
      default :
         return "A";
   }
 
}

void recvPacketHandler(iClickerPacket_t *recvd){
 bool ret = recvBuf.add(*recvd);
}


void channelSelect(String left, String right){
  if(left == "A" && right == "A"){
    clicker.begin(iClickerChannels::AA);
  } else if (left == "A" && right == "B") {
    clicker.begin(iClickerChannels::AB);
  } else if (left == "A" && right == "C") {
    clicker.begin(iClickerChannels::AC);
  } else if (left == "A" && right == "D") {
    clicker.begin(iClickerChannels::AD);
  } else if (left == "B" && right == "A") {
    clicker.begin(iClickerChannels::BA);
  } else if (left == "B" && right == "B") {
    clicker.begin(iClickerChannels::BB);
  } else if (left == "B" && right == "C") {
    clicker.begin(iClickerChannels::BC);
  } else if (left == "B" && right == "D") {
    clicker.begin(iClickerChannels::BD);
  } else if (left == "C" && right == "A") {
    clicker.begin(iClickerChannels::CA);
  } else if (left == "C" && right == "B") {
    clicker.begin(iClickerChannels::CB);
  } else if (left == "C" && right == "C") {
    clicker.begin(iClickerChannels::CC);
  } else if (left == "C" && right == "D") {
    clicker.begin(iClickerChannels::CD);
  } else if (left == "D" && right == "A") {
    clicker.begin(iClickerChannels::DA);
  } else if (left == "D" && right == "B") {
    clicker.begin(iClickerChannels::DB);
  } else if (left == "D" && right == "C") {
    clicker.begin(iClickerChannels::DC);
  } else if (left == "D" && right == "D") {
    clicker.begin(iClickerChannels::DD);
  }
  
  clicker.dumpRegisters();
  
  clicker.startPromiscuous(CHANNEL_SEND, recvPacketHandler);
  
}

