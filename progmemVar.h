#ifndef PVAR_H
#define PVAR_H
#include <Arduino.h>
#include <avr/pgmspace.h>
namespace FLASHMEM{
const uint8_t notSelected[] PROGMEM = {
0b11000011,
0b10000001,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b10000001,
0b11000011
};
const uint8_t selected[] PROGMEM = {
0b11011011,
0b10000001,
0b00000000,
0b10000001,
0b10000001,
0b00000000,
0b10000001,
0b11011011
};

enum AlphabetBlockIndex{
  A = 0,
  B = 5,
  C = 10,
  D = 15,
  E = 20,
  F = 25,
  G = 30,
  H = 35,
  I = 40,
  J = 45,
  K = 50,
  L = 55,
  M = 60,
  N = 65,
  O = 70,
  P = 75,
  Q = 80,
  R = 85,
  S = 90,
  T = 95,
  U = 100,
  V = 105,
  W = 110,
  X = 115,
  Y = 120,
  Z = 125,
  DASH = 130
};

const uint8_t Alphabet[160] PROGMEM = {
0b00000100,
0b00001010,
0b00001110,
0b00010001,
0b00010001,

0b00001111,
0b00010001,
0b00001111,
0b00010001,
0b00001111,

0b00011110,
0b00000001,
0b00000001,
0b00000001,
0b00011110,

0b00001111,
0b00010001,
0b00010001,
0b00010001,
0b00001111,

0b00011111,
0b00000001,
0b00011111,
0b00000001,
0b00011111,

0b00011111,
0b00000001,
0b00001111,
0b00000001,
0b00000001,

0b00011111,
0b00000001,
0b00011001,
0b00010001,
0b00011111,

0b00010001,
0b00010001,
0b00011111,
0b00010001,
0b00010001,

0b00011111,
0b00000100,
0b00000100,
0b00000100,
0b00011111,

0b00011111,
0b00000100,
0b00000100,
0b00000100,
0b00011000,

0b00001001,
0b00000101,
0b00000011,
0b00000101,
0b00001001,

0b00000001,
0b00000001,
0b00000001,
0b00000001,
0b00011111,

0b00010001,
0b00011011,
0b00010101,
0b00010001,
0b00010001,

0b00010001,
0b00010011,
0b00010101,
0b00011001,
0b00010001,

0b00001110,
0b00010001,
0b00010001,
0b00010001,
0b00001110,

0b00001111,
0b00010001,
0b00001111,
0b00000001,
0b00000001,

0b00001110,
0b00010001,
0b00010001,
0b00001110,
0b00010000,

0b00001111,
0b00010001,
0b00001111,
0b00001001,
0b00010001,

0b00011110,
0b00000001,
0b00001110,
0b00010000,
0b00001111,

0b00011111,
0b00000100,
0b00000100,
0b00000100,
0b00000100,

0b00010001,
0b00010001,
0b00010001,
0b00010001,
0b00001110,

0b00010001,
0b00010001,
0b00010001,
0b00001010,
0b00000100,

0b00010001,
0b00010001,
0b00010101,
0b00011011,
0b00010001,

0b00010001,
0b00001010,
0b00000100,
0b00001010,
0b00010001,

0b00010001,
0b00001010,
0b00000100,
0b00000010,
0b00000001,

0b00011111,
0b00001100,
0b00000110,
0b00000011,
0b00011111,

0b00000000,
0b00000000,
0b11111111,
0b00000000,
0b00000000
};
}

#endif
