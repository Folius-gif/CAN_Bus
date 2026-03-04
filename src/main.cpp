#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>
#include "Utils.h"

#define CAN_ADDRESS     0xBA
#define NOTAUS_ADDRESS  0xAA

Utils utils(8, 9);

struct can_frame canMsgWrite;
struct can_frame canMsgRead;
MCP2515 mcp2515(10);

void updateCAN();
void readCAN();

void setup()
{  

  while (!Serial)
    ;
  Serial.begin(115200);

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();

  Serial.println("Example: Write to CAN");
}

void loop()
{

  updateCAN();
  readCAN();

  

  delay(100);
}

void updateCAN()
{
  utils.ActionsWrite();
  canMsgWrite.can_id = CAN_ADDRESS;
  canMsgWrite.can_dlc = 8; 

  if (utils.GetNotAus() == 1)
  {
    utils.SetNotAus(0);
  }

  canMsgWrite.data[0] = utils.GetStartStop();
  Serial.println(utils.GetStartStop());

  mcp2515.sendMessage(&canMsgWrite);
}

void readCAN() {
  utils.ActionsRead();
  if (mcp2515.readMessage(&canMsgRead) == MCP2515::ERROR_OK) {
    
    switch(canMsgRead.can_id)
    {
    case (NOTAUS_ADDRESS): {
      utils.SetNotAus(canMsgRead.data[0]);
      break;
    }
    
    default:
      break;
    }     
  }
}

/*
NOAH 0xBA = Start/Stop und Buzzer
LUKA 0xCE = StatusLed und Lichtschranke
DAVE 0xEF = Motor und Temperatur
SPECKI 0xAA = NotAus und Bildschirm 

*/


//This is a test