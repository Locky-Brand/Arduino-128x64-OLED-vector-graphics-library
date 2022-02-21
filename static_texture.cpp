#include "static_texture.h"

static_texture::static_texture(): m_bitMapSize(5), m_bitWeightX(1), m_bitWeightY(1){
  m_bitMap = new uint8_t[5];
}
static_texture::static_texture(const vec2& i_topLeftCornerPos, const unsigned int& i_width, const unsigned int& i_height) : m_bitWeightX(1), m_bitWeightY(1){
  m_bitMap = new uint8_t[5];
  m_topLeftCornerPos = i_topLeftCornerPos;
  m_width = i_width;
  m_height = i_height;
}
static_texture::static_texture(const vec2& i_topLeftCornerPos, const unsigned int& i_width, const unsigned int& i_height, uint8_t* i_bitMap, const unsigned int& i_bitMapSize): m_topLeftCornerPos(i_topLeftCornerPos), m_width(i_width), m_height(i_height), m_bitMapSize(i_bitMapSize), m_bitWeightX(1), m_bitWeightY(1){
  m_bitMap = new uint8_t[i_bitMapSize];
  for(int i = 0; i < i_bitMapSize; ++i){
    m_bitMap[i] = i_bitMap[i]; 
  }
}
static_texture::~static_texture(){
  delete[] m_bitMap;
}

void static_texture::onSelected(){
    
}
void static_texture::onRenderCall(){
  
}

vec2 static_texture::getTopLeftPos() const {
  return m_topLeftCornerPos;
}
unsigned int static_texture::getWidth() const {
  return m_width;
}
unsigned int static_texture::getHeight() const {
  return m_width;
}
uint8_t* static_texture::getBitMap() const {
  return m_bitMap;
}
void static_texture::translateTex(const vec2& i_translateTo){
  m_topLeftCornerPos = i_translateTo;
}

bool static_texture::operator [] (const vec2& index){
  return bitRead(m_bitMap[(int)index.x], (int)index.y);
}
void static_texture::operator = (const static_texture& i_other){
  this->m_topLeftCornerPos = i_other.m_topLeftCornerPos;
  this->m_width = i_other.m_width;
  this->m_height = i_other.m_height;
  for(int i = 0; i < i_other.m_bitMapSize; ++i){
    this->m_bitMap[i] = i_other.m_bitMap[i];
  }
}
void static_texture::constructLetterBMP(const static_texture& i_other){
  this->m_topLeftCornerPos = i_other.m_topLeftCornerPos;
  this->m_width = i_other.m_width;
  this->m_height = i_other.m_height;
}

void static_texture::translateTex(const unsigned int& i_newX, const unsigned int& i_newY){
  if(i_newX != 0){
    m_topLeftCornerPos.x = i_newX;
  }
  if(i_newY != 0){
    m_topLeftCornerPos.y = i_newY;
  }
}

void static_texture::reSize(const unsigned int& i_newX, const unsigned int& i_newY){
  m_bitWeightX = i_newX;
  m_bitWeightY = i_newY;
  m_width *= i_newX;
  m_height *= i_newY;
}

unsigned int static_texture::getBitWeightX() const {
  return m_bitWeightX;
}
unsigned int static_texture::getBitWeightY() const{
  return m_bitWeightY;
}