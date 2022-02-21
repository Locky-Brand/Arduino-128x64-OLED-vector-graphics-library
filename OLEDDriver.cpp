#include "OLEDDriver.h"

// ======public=========
OLED::OLED(){
  
}
OLED::~OLED(){
  Wire.end();
}

void OLED::init(){
  Wire.begin();

  Wire.setClock(400000);

  // diplay off
  setSetting(DISPLAY_SLEEP);

  // sets clock frequency
  setSetting(SET_CLOCK_DIVIDE_RATIO, SUGGESTED_CLOCK_DIVIDE_RATIO);

  // set mux ratio for SSD1306
  setSetting(SET_MULTIPLEX_RATIO, 0x3F);

  // sets contrast control currently maximum
  setSetting(CONTRAST_CONTROL, 0xFF);

  // sets display to normal mode
  setSetting(NORMAL_DISPLAY);

  // set start line to (0,0) in RAM
  setSetting(0x40);
  setSetting(0xA0);
  setSetting(0xC0);
  setSetting(SET_DISPLAY_OFFSET, 0x00);

  // sets display electric characteristics
  setSetting(SET_PRECHARGE_PERIOD, 0x22);
  setSetting(SET_COM_LOW_THRESHOLD, 0x20);

  // turns on charge pump
  setSetting(CHARGE_PUMP_SETTING, CHARGE_PUMP_ON);
  setSetting(DISPLAY_EXTERNAL_VCC);

  // memory addressing
  setSetting(SET_MEMORY_ADDRESSING, 0x00);

  // turns on display
  setSetting(DISPLAY_ON_FOLLOW_RAM);
  setSetting(DISPLAY_ON);
}

void OLED::swapBuffers(Byte *frameBuffer){
  for(int i = 0; i < 1024; ++i){
    GDDRAMWrite(frameBuffer[i]);
  }
}
void OLED::swapBuffersEx(Byte* frameBuffer){
  uint16_t count = 1024;
  uint8_t index = 0;
  Byte addressingCommands[] = {
    SET_COLUMN_ADDRESS, 0x00, 0xFF,
    SET_PAGE_ADDRESS, 0x00, 0xFF
  };

  setSetting(addressingCommands);

  Wire.beginTransmission(adr);
  Wire.write(DATA);
  do{
    if(index >= 31){
      Wire.endTransmission();
      index = 0;
      Wire.beginTransmission(adr);
      Wire.write(DATA);
    }
    Wire.write(frameBuffer[1024-count]);
    ++index;
  } while(--count);
}

// ======private========
void OLED::setSetting(Byte setting){
  Wire.beginTransmission(adr);
  Wire.write(COMMAND);
  Wire.write(setting);
  Wire.endTransmission();
}
void OLED::setSetting(Byte setting, Byte setTo){
  Wire.beginTransmission(adr);
  Wire.write(COMMAND);
  Wire.write(setting);
  Wire.write(setTo);
  Wire.endTransmission();
}
void OLED::setSetting(Byte setting, Byte setToA, Byte setToB){
  Wire.beginTransmission(adr);
  Wire.write(COMMAND);
  Wire.write(setting);
  Wire.write(setToA);
  Wire.write(setToB);
  Wire.endTransmission();
}
void OLED::setSetting(Byte* setting, Byte* setToBuf){
  Wire.beginTransmission(adr);
  Wire.write(COMMAND);
  Wire.write(setting[0]);
  Wire.write(setToBuf[0]);
  Wire.write(setToBuf[1]);
  Wire.write(setting[1]);
  Wire.write(setToBuf[2]);
  Wire.write(setToBuf[3]);
  Wire.endTransmission();
}
void OLED::setSetting(Byte* buffer){
  Wire.beginTransmission(adr);
  Wire.write(COMMAND);
  Wire.write(buffer[0]);
  Wire.write(buffer[1]);
  Wire.write(buffer[2]);
  Wire.write(buffer[3]);
  Wire.write(buffer[4]);
  Wire.write(buffer[5]);
  Wire.endTransmission();
}
void OLED::GDDRAMWrite(Byte data){
  Wire.beginTransmission(adr);
  Wire.write(DATA);
  Wire.write(data);
  Wire.endTransmission();
}
void OLED::GDDRAMWrite(Byte* frameBuffer){
  Wire.beginTransmission(adr);
  Wire.write(DATA);
  Wire.write(frameBuffer, 1024);
  Wire.endTransmission();
}