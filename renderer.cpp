#include "renderer.h"

renderer::renderer() {
  m_MapBuffer = nullptr;
}
renderer::~renderer(){
  if(m_MapBuffer != nullptr){
    delete[] m_MapBuffer;
  }
}

void renderer::begin(const uint8_t& i2c_addr){
  screen.init();
}

void renderer::preRender(){
  bool mapValid = m_MapBuffer == nullptr;
  for(int i = 0; i < 1024; ++i){
    m_frameBuffer[i] = (mapValid)?(0x00):(m_MapBuffer[i]); 
  }
}

void renderer::render(){
  swapBuffers();
}
void renderer::render(mesh& i_mesh){
  drawLines(i_mesh);
  swapBuffers();
}
void renderer::render(mesh* i_meshCache, const unsigned int& i_meshCacheSize){
  for(int i = 0; i < i_meshCacheSize; ++i){
    drawLines(i_meshCache[i]);
  }
  swapBuffers();
}
void renderer::render(const meshCache& i_meshCache){
  for(int i = 0; i <= i_meshCache.getCount(); ++i){
    drawLines(*i_meshCache[i]);
  }
  swapBuffers();
}
void renderer::renderRay(const vec2Ray& i_ray, const unsigned int& i_length){
  for(int i = 0; i < i_length; ++i){
    placeBit(i_ray(i).x, i_ray(i).y, 1);
  }
}
void renderer::renderTex(const static_texture& i_Stex){
  vec2 temp_texCoord;
  for(int x = i_Stex.getTopLeftPos().x; (x - i_Stex.getTopLeftPos().x) < i_Stex.getWidth(); x += i_Stex.getBitWeightX()){
    for(int y = i_Stex.getTopLeftPos().y; (y - i_Stex.getTopLeftPos().y) < i_Stex.getHeight(); y += i_Stex.getBitWeightY()){
      temp_texCoord = {(y - i_Stex.getTopLeftPos().y), (x - i_Stex.getTopLeftPos().x)};
      placeBit(x, y, i_Stex[temp_texCoord]);
      for(unsigned int temp_y = 1; temp_y < i_Stex.getBitWeightY(); ++temp_y){
        placeBit(x, y+temp_y, i_Stex[temp_texCoord]);
      }
    }
  }
}
void renderer::placeBit(const unsigned int& x, const unsigned int& y, const bool& i_look){
  unsigned int byteCoord = (y/8) * 128 + x;
  unsigned int bitCoord = y;
  while(bitCoord >= 8){
    bitCoord -= 8;
  }
  if(((x < 128) && (x > 0) && (y < 64) && (y > 0)) && i_look != 0){
    bitWrite(m_frameBuffer[byteCoord], bitCoord, i_look);  
  }
}

void renderer::placeMapBit(const unsigned int& x, const unsigned int& y, const bool& i_look){
  unsigned int byteCoord = (y/8) * 128 + x;
  unsigned int bitCoord;
  while(bitCoord >= 8){
    bitCoord -= 8;
  }
  if(((x < 128) && (x > 0) && (y < 64) && (y > 0)) && i_look != 0){
    bitWrite(m_MapBuffer[byteCoord], bitCoord, i_look);  
  }
}

void renderer::frameBegin(){

}
void renderer::drawLines(mesh& i_mesh){
  float destX, destY;
  float currentX, currentY;
  int dy;
  int dx;
  float incrementY;
  float incrementX;
  for(int index = 0; index < i_mesh.getVerticiesSize(); index += i_mesh.getElementStride()){
    currentX = i_mesh.getVerticies()[index];
    currentY = i_mesh.getVerticies()[index+1];
    
    destX = i_mesh[index+i_mesh.getElementStride()];
    destY = i_mesh[index+i_mesh.getElementStride()+1];

    dx = destX - currentX;
    dy = destY - currentY;
    
    int steps = (abs(dy) > abs(dx))?(abs(dy)):(abs(dx));

    incrementX = dx/(float)steps;
    incrementY = dy/(float)steps;
        
    for(int i = 0; i <= steps; ++i){

      placeBit(assignRndedX(currentX), assignRndedX(currentY), 1);
      
      currentX += incrementX;
      currentY += incrementY;
    } 
  }
}
void renderer::drawLine(const vec2& i_from, const vec2& i_to){
  float currentX, currentY;
  float destX, destY;
  int dy;
  int dx;
  float incrementY;
  float incrementX;

  currentX = i_from.x;
  currentY = i_from.y;
  
  destX = i_to.x;
  destY = i_to.y;

  dx = destX - currentX;
  dy = destY - currentY;
  
  int steps = (abs(dy) > abs(dx))?(abs(dy)):(abs(dx));

  incrementX = dx/(float)steps;
  incrementY = dy/(float)steps;
      
  for(int i = 0; i <= steps; ++i){

    placeBit(assignRndedX(currentX), assignRndedX(currentY), 1);
    
    currentX += incrementX;
    currentY += incrementY;
  } 
}
void renderer::drawMapLines(mesh& i_mesh){
  float destX, destY;
  float currentX, currentY;
  int dy;
  int dx;
  float incrementY;
  float incrementX;
  for(int index = 0; index < i_mesh.getVerticiesSize(); index += i_mesh.getElementStride()){
    currentX = i_mesh.getVerticies()[index];
    currentY = i_mesh.getVerticies()[index+1];
    
    destX = i_mesh[index+i_mesh.getElementStride()];
    destY = i_mesh[index+i_mesh.getElementStride()+1];

    dx = destX - currentX;
    dy = destY - currentY;
    
    int steps = (abs(dy) > abs(dx))?(abs(dy)):(abs(dx));

    incrementX = dx/(float)steps;
    incrementY = dy/(float)steps;
        
    for(int i = 0; i <= steps; ++i){

      placeMapBit(assignRndedX(currentX), assignRndedX(currentY), 1);
      
      currentX += incrementX;
      currentY += incrementY;
    } 
  }
}
void renderer::swapBuffers(){ 
  screen.swapBuffersEx(m_frameBuffer);
}
void renderer::frameEnd(){

}
