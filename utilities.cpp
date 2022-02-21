#include "utilities.h"

vec2 vec2::operator + (const vec2& i_other){
  return {this->x + i_other.x, this->y + i_other.y};
}
void vec2::operator += (const vec2& i_other){
  this->x += i_other.x;
  this->y += i_other.y;
}
vec2 vec2::operator - (const vec2& i_other){
  return {this->x - i_other.x, this->y - i_other.y};
}
vec2 vec2::operator - (const int& i_other){
  return {this->x - i_other, this->y - i_other};
}
void vec2::operator -= (const vec2& i_other){
  this->x -= i_other.x;
  this->y -= i_other.y;
}
bool vec2::operator == (const vec2& i_other){
  return (this->x == i_other.x) && (this->y == i_other.y);
}
bool vec2::operator != (const vec2& i_other){
  return (this->x != i_other.x) || (this->y != i_other.y);
}
vec2 vec2::operator * (const float& i_scalar){
  return {this->x * i_scalar, this->y * i_scalar};
}
void vec2::rotateAboutCentre(const float& i_angle, const vec2& i_centre){
  mat2x2 rotator = {cos(i_angle), -1 * sin(i_angle), sin(i_angle), cos(i_angle)};
  vec2 translatedVertex = {this->x - i_centre.x, this->y - i_centre.y};
  *this = rotator * translatedVertex;
}
void vec2::rotate(const float& i_angle){
  mat2x2 rotator = {cos(i_angle), -1 * sin(i_angle), sin(i_angle), cos(i_angle)};
  *this = rotator * (*this);
}
void vec2::normalize(){
  float size = sqrt(x * x + y * y);
  x /= size;
  y /= size;
}
float vec2::getMagnitude() const{
  return sqrt(x * x + y * y);
}

vec2 vec2Ray::operator () (const float& t) const{
  return (point + direction * t);
}
void vec2Ray::operator = (const vec2Ray& i_other){
  this->direction = i_other.direction;
  this->point = i_other.point;
}
vec2Ray vec2Ray::createLine(const vec2& i_direction, const vec2& i_point){
  direction = i_direction;
  point = i_point;
  return *this;
}

mat2x2::mat2x2(float v1 ,float v2, float v3, float v4){
  matrix[0] = v1;
  matrix[1] = v2;
  matrix[2] = v3;
  matrix[3] = v4;
}
mat2x2::~mat2x2(){
    
}

vec2 mat2x2::operator * (const vec2& i_vec){
  return {matrix[0] * i_vec.x + matrix[1] * i_vec.y, matrix[2] * i_vec.x + matrix[3] * i_vec.y};
}
