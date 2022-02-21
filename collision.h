#ifndef COLL_H
#define COLL_H
#include "utilities.h"
#include "arduinoList.h"
//#include "character.h"

struct collider{
  collider();

  vec2 location[2]; // index 0 = top left corner, index 1 = bottomRight
  unsigned int worldIndex;

  void operator = (const collider& i_other);
};

class worldCollision{
public:
  worldCollision();
  ~worldCollision();
  
  void addToCollision(collider* i_collide);

  unsigned int getCount() const;
  collider** getCollision();
private:
  list<collider*> mCollision;
};

#endif