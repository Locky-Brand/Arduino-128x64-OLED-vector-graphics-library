#ifndef S_TEX
#define S_TEX
#include <Arduino.h>
#include "utilities.h" 
#include "mesh.h"

class static_texture {
public:
  static_texture();
  static_texture(const vec2& i_topLeftCornerPos, const unsigned int& i_width, const unsigned int& i_height);
  static_texture(const vec2& i_topLeftCornerPos, const unsigned int& i_width, const unsigned int& i_height, uint8_t* i_bitMap, const unsigned int& i_bitMapSize);
  ~static_texture();

  void onSelected();
  void onRenderCall();
  void reSize(const unsigned int& i_newX, const unsigned int& i_newY);
  void translateTex(const unsigned int& i_newX, const unsigned int& i_newY);

  vec2 getTopLeftPos() const;
  unsigned int getWidth() const;
  unsigned int getHeight() const;
  uint8_t* getBitMap() const;
  unsigned int getBitWeightX() const;
  unsigned int getBitWeightY() const;
  void translateTex(const vec2& i_translateTo);

  bool operator [] (const vec2& index);
  void operator = (const static_texture& i_other);
  void constructLetterBMP(const static_texture& i_other);
private:
  unsigned int m_bitWeightX;
  unsigned int m_bitWeightY;

  unsigned int m_width;
  unsigned int m_height;
  vec2 m_topLeftCornerPos;
  uint8_t* m_bitMap;
  unsigned int m_bitMapSize;
};

#endif
