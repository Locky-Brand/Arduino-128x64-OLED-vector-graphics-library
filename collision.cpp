#include "collision.h"

collider::collider(){
  location[0] = {-1.0f, -1.0f};
  location[0] = {-1.0f, -1.0f};
  worldIndex = 0;
}

void collider::operator = (const collider& i_other){
  this->location[0] = i_other.location[0];
  this->location[1] = i_other.location[1];
}

worldCollision::worldCollision() : mCollision(5){

}
worldCollision::~worldCollision(){

}

void worldCollision::addToCollision(collider* i_collide){
  mCollision.push_back(i_collide);
  i_collide->worldIndex = mCollision.getCount();
}

unsigned int worldCollision::getCount() const{
  return mCollision.getCount();
}
collider** worldCollision::getCollision(){
  return mCollision.getArr();
}