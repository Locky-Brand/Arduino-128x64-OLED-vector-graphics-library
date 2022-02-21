#ifndef UTILITIES_H
#define UTILITIES_H
#include <Arduino.h>

static const float pi = 3.141592653589793;

struct vec2 {
  float x;
  float y;

  vec2 operator + (const vec2& i_other);
  void operator += (const vec2& i_other);
  vec2 operator - (const vec2& i_other);
  vec2 operator - (const int& i_other);
  void operator -= (const vec2& i_other);
  bool operator == (const vec2& i_other);
  bool operator != (const vec2& i_other);
  vec2 operator * (const float& i_scalar);
  void rotateAboutCentre(const float& i_angle, const vec2& i_centre);
  void rotate(const float& i_angle);
  void normalize();
  float getMagnitude() const;
};

struct vec2Ray{
  vec2 direction;
  vec2 point;

  vec2 operator () (const float& t) const;
  void operator = (const vec2Ray& i_other);
  vec2Ray createLine(const vec2& i_direction, const vec2& i_point);
};

struct mat2x2 {
  float matrix[4];

  mat2x2(float v1 ,float v2, float v3, float v4);
  ~mat2x2();

  vec2 operator * (const vec2& i_vec);
};

struct twoVerticies{
  float x1 = 0;
  float y1 = 0;
  float x2 = 0;
  float y2 = 0;
};

static void rndX(float& x){ // rounds a float up or down
  int intX = x;
  float decimalPlace = x - (float)intX;
  if(decimalPlace > 0.5){
    x += 1;
    x -= decimalPlace;
  }
  else{
    x -= decimalPlace;
  }
}
static float assignRndedX(float x){
  int intX = x;
  float decimalPlace = x - intX;
  if(decimalPlace > 0.5){
    x += 1;
    x -= decimalPlace;
  }
  else{
    x -= decimalPlace;
  }
  return x;
}

static twoVerticies greatestDistance(float* i_vertexBuffer, const unsigned int& i_bufferSize, const unsigned int& elementStride){ // returns the verticies that are furthest apart
  twoVerticies currentMax;
  int cmpOffset = 0;
  for(int i = i_bufferSize; i > i_bufferSize; i -= elementStride){
    switch(i){
      case 0:
        cmpOffset = i_bufferSize - elementStride;
      break;
      default:
        cmpOffset = elementStride;
      break;
    }

    if(abs(i_vertexBuffer[i] - i_vertexBuffer[i+cmpOffset]) > abs(currentMax.x1 - currentMax.x2)){
      currentMax.x1 = i_vertexBuffer[i];
      currentMax.x2 = i_vertexBuffer[i+cmpOffset];  
    }
    if(abs(i_vertexBuffer[i+1] - i_vertexBuffer[i+cmpOffset+1]) > abs(currentMax.y1 - currentMax.y2)){
      currentMax.y1 = i_vertexBuffer[i+1];
      currentMax.y2 = i_vertexBuffer[i+cmpOffset+1];
    }
  }
  return currentMax;
}

static vec2 findMean(float* i_vertexBuffer, const unsigned int& i_bufferSize, const unsigned int& i_vertexStride, const unsigned int& i_elementStride, const unsigned int& i_elementAmount){
  float totalX = 0;
  float totalY = 0;
  for(int i = 0; i < i_bufferSize; i+=i_elementStride){
    totalX += i_vertexBuffer[i+i_vertexStride];
    totalY += i_vertexBuffer[i+i_vertexStride+1];
  }
  
  totalX /= i_elementAmount;
  totalY /= i_elementAmount;
  
  return {totalX, totalY};
}

#endif
