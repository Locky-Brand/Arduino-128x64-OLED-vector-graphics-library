#ifndef RENDERER_H
#define RENDERER_H
#include "OLEDDriver.h"
#include "utilities.h"
#include "mesh.h"
#include "static_texture.h"
#include "collision.h"
#include "utilities.h"

class renderer {
public:
  renderer();
  ~renderer();

  void begin(const uint8_t& i2c_addr);

  void placeBit(const unsigned int& x, const unsigned int& y, const bool& i_look); // places a bit of graphic data in the frame buffer
  void preRender(); // refreshes renderer
  void render(mesh& i_mesh); // renders a single object
  void render(mesh* i_meshCache, const unsigned int& i_meshCacheSize); // renders an array of objects
  void render(const meshCache& i_meshCache); // renders a mesh cache
  void render(); // just renders the screen
  void renderRay(const vec2Ray& i_ray, const unsigned int& i_length); // renders a ray
  void renderTex(const static_texture& i_Stex); // renders one static texture
  void drawLine(const vec2& i_from, const vec2& i_to);
  void frameBegin();
  void frameEnd();

  OLED screen;
private:
  void drawLines(mesh& i_mesh);
  void swapBuffers();
  void placeMapBit(const unsigned int& x, const unsigned int& y, const bool& i_look);
  void drawMapLines(mesh& i_mesh);

  uint8_t m_frameBuffer[1024]; 
  uint8_t* m_MapBuffer;
};

#endif
