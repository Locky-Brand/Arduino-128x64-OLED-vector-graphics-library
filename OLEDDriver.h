#ifndef OLED_H
#define OLED_H
#include <Wire.h>

#define adr 0x3C
#define WIDTH 128
#define HEIGHT 64
#define BYTE_HEIGHT 8

// data specification codes
#define COMMAND 0x00
#define DATA 0x40

// command codes
#define DISPLAY_ON_FOLLOW_RAM 0xA4
#define DISPLAY_ON_IGNORE_RAM 0xA5
#define DISPLAY_ON 0xAF
#define DISPLAY_SLEEP 0xAE
#define SET_CLOCK_DIVIDE_RATIO 0xD5
#define CHARGE_PUMP_SETTING 0x8D
#define SET_MULTIPLEX_RATIO 0xA8
#define CONTRAST_CONTROL 0x81
#define NORMAL_DISPLAY 0xA6
#define INVERSE_DISPLAY 0xA7
#define SET_DISPLAY_OFFSET 0xD3
#define DISPLAY_EXTERNAL_VCC 0x10
#define SET_MEMORY_ADDRESSING 0x20
#define SET_PRECHARGE_PERIOD 0xD9
#define SET_COM_LOW_THRESHOLD 0xDB
#define NOP 0xE3
#define SET_COLUMN_ADDRESS 0x21
#define SET_PAGE_ADDRESS 0x22

// setting code
#define SUGGESTED_CLOCK_DIVIDE_RATIO 0x80
#define CHARGE_PUMP_ON 0x14

typedef unsigned char Byte;

class OLED {
public:
  OLED();
  ~OLED();

  void init();

  void swapBuffers(Byte* frameBuffer);
  void swapBuffersEx(Byte* frameBuffer);
private:
  void setSetting(Byte setting);
  void setSetting(Byte setting, Byte setTo);
  void setSetting(Byte setting, Byte setToA, Byte setToB);
  void setSetting(Byte* setting, Byte* setToBuf); // hard coded to two instructions both taking two parameters
  void setSetting(Byte* buffer); // hard coded to two instructions both taking two parameters
  void GDDRAMWrite(Byte data);
  void GDDRAMWrite(Byte* frameBuffer);
};

#endif