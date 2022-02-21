#ifndef CHAR_H
#define CHAR_H
#include <Arduino.h>
#include "utilities.h"
#include "mesh.h"
#include "renderer.h"
#include "collision.h"

struct joyStick {
  int xPin = A1;
  int yPin = A0;
  vec2 getDirectionVector() const;
  void operator = (const joyStick& i_other);
};

class character {
public:
  ~character();
  static character* getInstance();

  void onUpdate(renderer* i_ren);
  void getInput(worldCollision& i_worldColliders);
  void setLocation(const vec2& i_location, collider* i_worldColliders);

  mesh* getMesh() const;
  void setMesh(mesh* i_mesh);
  collider* getCollider();
  vec2 getForwardVec() const;
  vec2Ray getForwardLine() const;
private:
  mesh* characterMesh;
  joyStick control;
  vec2 forwardVec;
  vec2 lastDirectionVec;
  vec2Ray lastDirectionLine;
  collider collide;
  character();
  static character* characterInstance;
};

#endif