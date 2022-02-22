#ifndef MESH_H
#define MESH_H
#include <Arduino.h>
#include "utilities.h"

// generate 2D primatives more conviniently with gfxData functions
struct gfxData{
  float* verts;
  unsigned int vertexStride;
  unsigned int vertsSize;
  unsigned int elementStride;
  unsigned int elementAmount;
  vec2 pos;
};

gfxData genCircle(const float& i_radius, const float& i_centrePosX, const float& i_centrePosY, const unsigned int& i_resolution = 6);
gfxData genQuad(const float& i_width, const float& i_height, const float& i_centrePosX, const float& i_centrePosY);
enum triType{
  ISOSCELES,
  RIGHT
};
gfxData genTri(const float& i_base, const float& i_height, const float& i_centrePosX, const float& i_centrePosY, triType i_type);

class mesh {
public:
  mesh();

  // primative 2D mesh with no texture
  mesh(float* i_verticies, const unsigned int& i_vertexStride, const unsigned int& i_verticiesSize, const unsigned int& i_elememtStride, const unsigned int& i_elementAmount); 
  mesh(const gfxData& i_data);

  // primative 2D mesh that is filled with a supplied bitmap
  mesh(float* i_verticies, uint8_t* i_bitMap, const unsigned int& i_vertexStride, const unsigned int& i_bitMapStride, const unsigned int& i_verticiesSize, const unsigned int& i_bitMapSize, const unsigned int& i_elememtStride, const unsigned int& i_elementAmount);

  // copy
  mesh(const mesh& i_other);
  void operator = (const mesh& i_other);

  ~mesh();

  // translation and rotation functions
  void rotate(const float& i_rotation);
  void translate(const float& i_translateX, const float& i_translateY);
  void setPos(const float& i_setX, const float& i_setY);
  void scale(const float& i_scaleFactor);

  // getters and setters
  uint8_t* getBitMap() const;
  float* getVerticies() const;
  unsigned int getVertexStride() const;
  unsigned int getBitMapStride() const;
  unsigned int getVerticiesSize() const;
  unsigned int getBitMapSize() const;
  unsigned int getElementStride() const;
  vec2 getCentre() const;
  bool getBitMapCoord(const unsigned int& i_indexByte, const unsigned int& i_indexBit) const;
  float operator [] (const unsigned int& i_index);
  float getMaxX() const;
  float getMaxY() const;
  float getMinX() const;
  float getMinY() const;
  
private:
  friend class meshCache;
  
  float centreX;
  float centreY;
  uint8_t* m_bitMap;
  float* m_verticies;   
  unsigned int m_vertexStride;
  unsigned int m_bitMapStride;
  unsigned int m_verticiesSize;
  unsigned int m_bitMapSize;
  unsigned int m_elementStride;
  unsigned int m_elementAmount;
};

class meshCache {
public:
  meshCache(const unsigned int& i_initialSize);
  ~meshCache();

  void addToCache(mesh* i_mesh);

  unsigned int getCount() const;

  mesh* operator [] (const unsigned int& i_index);
private:
  unsigned int m_count;
  unsigned int m_size;
  mesh** m_cache;
};

#endif
