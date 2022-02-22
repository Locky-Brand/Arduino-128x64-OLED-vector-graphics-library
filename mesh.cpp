#include "mesh.h"

gfxData genCircle(const float& i_radius, const float& i_centrePosX, const float& i_centrePosY, const unsigned int& i_resolution/* = 6 */){
  float* circleVerts = new float[i_resolution * 2];
  float angle = 0;
  for(int i = 1; i < i_resolution * 2; i+=2){
    circleVerts[i - 1] = (i_radius * cos(angle)) + i_centrePosX;
    circleVerts[i] = (i_radius * sin(angle)) + i_centrePosY;
    angle += (2 * pi) / i_resolution;
  }
  return {circleVerts, 0, (i_resolution * 2), 2, i_resolution, {i_centrePosX, i_centrePosY}};
}
gfxData genQuad(const float& i_width, const float& i_height, const float& i_centrePosX, const float& i_centrePosY){
  float* quadVerts = new float[8];
  float halfWidth = i_width/2;
  float halfHeight = i_height/2;

  quadVerts[0] = i_centrePosX + halfWidth;
  quadVerts[1] = i_centrePosY + halfHeight;

  quadVerts[2] = i_centrePosX - halfWidth;
  quadVerts[3] = i_centrePosY + halfHeight;

  quadVerts[4] = i_centrePosX - halfWidth;
  quadVerts[5] = i_centrePosY - halfHeight;

  quadVerts[6] = i_centrePosX + halfWidth;
  quadVerts[7] = i_centrePosY - halfHeight;

  return {quadVerts, 0, 8, 2, 4, {i_centrePosX, i_centrePosY}};
}
gfxData genTri(const float& i_base, const float& i_height, const float& i_centrePosX, const float& i_centrePosY, triType i_type){
  float* triVerts = new float[6];
  float halfBase = i_base/2;
  float halfHeight = i_height/2;

  switch(i_type){
    case ISOSCELES:
      triVerts[0] = i_centrePosX + halfBase;
      triVerts[1] = i_centrePosY - halfHeight;

      triVerts[2] = i_centrePosX - halfBase;
      triVerts[3] = i_centrePosY - halfHeight;

      triVerts[4] = i_centrePosX;
      triVerts[5] = i_centrePosY + halfHeight;
    break;
    case RIGHT:
      triVerts[0] = i_centrePosX + halfBase;
      triVerts[1] = i_centrePosY + halfHeight;

      triVerts[2] = i_centrePosX + halfBase;
      triVerts[3] = i_centrePosY - halfHeight;

      triVerts[4] = i_centrePosX - halfBase;
      triVerts[5] = i_centrePosY - halfHeight;
    break;
  }

  return {triVerts, 0, 6, 2, 3, {i_centrePosX, i_centrePosY}};
}

mesh::mesh(){

}
mesh::mesh(float* i_verticies, const unsigned int& i_vertexStride, const unsigned int& i_verticiesSize, const unsigned int& i_elementStride, const unsigned int& i_elementAmount) : m_verticies(i_verticies), m_bitMap(nullptr), m_vertexStride(i_vertexStride), m_bitMapStride(-1), m_verticiesSize(i_verticiesSize), m_bitMapSize(0), m_elementStride(i_elementStride), m_elementAmount(i_elementAmount){
  m_bitMap = nullptr;
  vec2 centre = findMean(i_verticies, i_verticiesSize, i_vertexStride, i_elementStride, i_elementAmount);
  centreX = centre.x;
  centreY = centre.y; 
}
mesh::mesh(const gfxData& i_data) : m_verticies(i_data.verts), m_bitMap(nullptr), m_vertexStride(i_data.vertexStride), m_bitMapStride(-1), m_verticiesSize(i_data.vertsSize), m_bitMapSize(0), m_elementStride(i_data.elementStride), m_elementAmount(i_data.elementAmount){
  m_bitMap = nullptr;
  setPos(i_data.pos.x, i_data.pos.y);
}
mesh::mesh(float* i_verticies, uint8_t* i_bitMap, const unsigned int& i_vertexStride, const unsigned int& i_bitMapStride, const unsigned int& i_verticiesSize, const unsigned int& i_bitMapSize, const unsigned int& i_elementStride, const unsigned int& i_elementAmount) : m_verticies(i_verticies), m_bitMap(i_bitMap), m_vertexStride(i_vertexStride), m_bitMapStride(i_bitMapStride), m_verticiesSize(i_verticiesSize), m_bitMapSize(i_bitMapSize), m_elementStride(i_elementStride), m_elementAmount(i_elementAmount){
  vec2 centre = findMean(i_verticies, i_verticiesSize, i_vertexStride, i_elementStride, i_elementAmount);
  centreX = centre.x;
  centreY = centre.y; 
}
mesh::mesh(const mesh& i_other) : m_verticiesSize(i_other.m_verticiesSize), m_verticies(new float[i_other.m_verticiesSize]){
  this->centreX = i_other.centreX;
  this->centreY = i_other.centreY;
  for(int i = 0; i < m_verticiesSize; ++i){
    this->m_verticies[i] = i_other.m_verticies[i];
  }
  this->m_vertexStride = i_other.m_vertexStride;
  this->m_elementStride = i_other.m_elementStride;
  this->m_elementAmount = i_other.m_elementAmount;
}
mesh::~mesh(){
  delete[] m_verticies;
  if(m_bitMap != nullptr){
    delete[] m_bitMap;
  }
}

void mesh::rotate(const float& i_rotation){
  mat2x2 rotator = {cos(i_rotation), -1 * sin(i_rotation), sin(i_rotation), cos(i_rotation)};
  vec2 translatedVertex = {0, 0};
  for(int i = 0; i < m_verticiesSize; i += m_elementStride){
    translatedVertex = {m_verticies[i] - centreX, m_verticies[i+1] - centreY};
    
    translatedVertex = rotator * translatedVertex;
    
    m_verticies[i] = (translatedVertex.x + centreX);
    m_verticies[i+1] = (translatedVertex.y + centreY);
  }
  vec2 centre = findMean(m_verticies, m_verticiesSize, m_vertexStride, m_elementStride, m_elementAmount);
  centreX = centre.x;
  centreY = centre.y; 
}
void mesh::translate(const float& i_translateX, const float& i_translateY){
  for(int i = 0; i < m_verticiesSize; i += m_elementStride){
    m_verticies[i] += i_translateX;
    m_verticies[i+1] += i_translateY;
  }
  centreX += i_translateX;
  centreY += i_translateY;
}
void mesh::setPos(const float& i_setX, const float& i_setY){
  centreX = i_setX;
  centreY = i_setY;
}
void mesh::scale(const float& i_scaleFactor){
  for(int i = 0; i < m_verticiesSize; i += m_elementStride){
    m_verticies[i] *= i_scaleFactor;
    m_verticies[i+1] *= i_scaleFactor;
  }
  vec2 centre = findMean(m_verticies, m_verticiesSize, m_vertexStride, m_elementStride, m_elementAmount);
  centreX = centre.x;
  centreY = centre.y;
}

uint8_t* mesh::getBitMap() const {
  return m_bitMap;
}
float* mesh::getVerticies() const {
  return m_verticies;
}
unsigned int mesh::getVertexStride() const {
  return m_vertexStride;
}
unsigned int mesh::getBitMapStride() const {
  return m_bitMapStride;
}
unsigned int mesh::getVerticiesSize() const {
  return m_verticiesSize;
}
unsigned int mesh::getBitMapSize() const {
  return m_bitMapSize;
}
bool mesh::getBitMapCoord(const unsigned int& i_indexByte, const unsigned int& i_indexBit) const{
  return bitRead(m_bitMap[i_indexByte], i_indexBit);
}
vec2 mesh::getCentre() const {
  return {centreX, centreY};
}
float mesh::operator [] (const unsigned int& i_index){
  if(i_index >= m_verticiesSize){
    return m_verticies[i_index - m_verticiesSize];
  }
  else{
    return m_verticies[i_index];
  }
}
unsigned int mesh::getElementStride() const{
  return m_elementStride;
}
float mesh::getMaxX() const{
  float currentMax = -128.0f;
  for(int i = 0; i < m_verticiesSize; i += 2){
    if(m_verticies[i] > currentMax){
      currentMax = m_verticies[i];
    }
  }
  return currentMax;
}
float mesh::getMaxY() const{
  float currentMax = -64.0f;
  for(int i = 1; i < m_verticiesSize; i += 2){
    if(m_verticies[i] > currentMax){
      currentMax = m_verticies[i];
    }
  }
  return currentMax;
}
float mesh::getMinX() const{
  float currentMin = 128.0f;
  for(int i = 0; i < m_verticiesSize; i += 2){
    if(m_verticies[i] < currentMin){
      currentMin = m_verticies[i];
    }
  }
  return currentMin;
}
float mesh::getMinY() const{
  float currentMin = 64.0f;
  for(int i = 1; i < m_verticiesSize; i += 2){
    if(m_verticies[i] < currentMin){
      currentMin = m_verticies[i];
    }
  }
  return currentMin;
}
void mesh::operator = (const mesh& i_other){
  this->centreX = i_other.centreX;
  this->centreY = i_other.centreY;
  for(int i = 0; i < m_verticiesSize; ++i){
    this->m_verticies[i] = i_other.m_verticies[i];
  }
  this->m_vertexStride = i_other.m_vertexStride;
  this->m_elementStride = i_other.m_elementStride;
  this->m_elementAmount = i_other.m_elementAmount;
}

// ============== mesh cache ======================

meshCache::meshCache(const unsigned int& i_initialSize) : m_size(i_initialSize), m_count(0){
  m_cache = new mesh*[i_initialSize];
}
meshCache::~meshCache(){
  delete[] m_cache;
}

unsigned int meshCache::getCount() const{
  return m_count;
}

void meshCache::addToCache(mesh* i_mesh){
  if(m_count < m_size){
    m_cache[m_count] = i_mesh;
    ++m_count;
  }
}

mesh* meshCache::operator [] (const unsigned int& i_index){
  return m_cache[i_index];
}
