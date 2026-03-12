#include <Arduino.h>
#include <SPI.h>
#include <mcp2515.h>
#include "Utils.h"

#define CAN_ADDRESS 0x01
#define NOTAUS_ADDRESS 0x00

#define Intervall 100

unsigned long Zeit = 0;

Utils utils(8, 9); // StartStop Pin 8, Buzzer Pin 9

struct can_frame canMsgWrite;
struct can_frame canMsgRead;
MCP2515 mcp2515(10);

void updateCAN();
void readCAN();

void setup()
{
  Serial.begin(115200);
  
  // FIX: Initialize hardware here, not globally!
  utils.begin(); 
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();

  Serial.println("Arduino 1 Started");
}

void loop()
{
  utils.ActionsWrite(); // Check buttons
  utils.ActionsRead();  // Update buzzer state
  
  readCAN();

  if (millis() - Zeit >= Intervall)
  {
    updateCAN();  
    Zeit = millis();
  }
}

void updateCAN()
{
  canMsgWrite.can_id = CAN_ADDRESS;
  canMsgWrite.can_dlc = 1;
  canMsgWrite.data[0] = utils.GetStartStop();
  mcp2515.sendMessage(&canMsgWrite);
}

void readCAN()
{
  if (mcp2515.readMessage(&canMsgRead) == MCP2515::ERROR_OK)
  {
    if (canMsgRead.can_id == NOTAUS_ADDRESS)
    {
      utils.SetNotAus(canMsgRead.data[0]);
    }
  }
}
