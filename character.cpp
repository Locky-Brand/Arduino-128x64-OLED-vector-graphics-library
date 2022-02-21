#include "character.h"

//============joyStick===========================
vec2 joyStick::getDirectionVector() const{
  vec2 dir;
  dir.x = map(analogRead(xPin), 0, 1023, 0, 11);
  dir.y = map(analogRead(yPin), 0, 1023, 0, 11);
  return dir;
}

void joyStick::operator = (const joyStick& i_other){
  xPin = i_other.xPin;
  yPin = i_other.yPin;
}

//============character==========================
character* character::characterInstance = nullptr;

character::~character(){

}
character* character::getInstance(){
  if(characterInstance == nullptr){
    characterInstance = new character;
  }
  return characterInstance;
}

void character::onUpdate(renderer* i_ren){
  
}
void character::getInput(worldCollision& i_worldColliders){
  vec2 dir = control.getDirectionVector();
  lastDirectionVec = {dir.x - 5, dir.y - 5};

  // rotate to face move direction
  float rot = pi/12;
  float dotProd = 0;
  if(digitalRead(42)){
    characterMesh->rotate(-rot);
    forwardVec.rotate(-rot);
  }
  else if(digitalRead(38)){
    characterMesh->rotate(rot);
    forwardVec.rotate(rot);
  }
  else{
    dotProd = forwardVec.x * lastDirectionVec.x + forwardVec.y * lastDirectionVec.y;
  }
  if(dotProd != 0){
    rot = acos(dotProd/(sqrt(lastDirectionVec.x * lastDirectionVec.x + lastDirectionVec.y * lastDirectionVec.y)));
    characterMesh->rotate(rot);
    forwardVec.rotate(rot);
  }
  
  // detect collision before movement
  collide.location[0] += lastDirectionVec;
  collide.location[1] += lastDirectionVec;
  i_worldColliders.getCollision()[collide.worldIndex]->location[0] += lastDirectionVec;
  i_worldColliders.getCollision()[collide.worldIndex]->location[1] += lastDirectionVec;
  characterMesh->translate(lastDirectionVec.x, lastDirectionVec.y);
  for(int i = collide.worldIndex; i < i_worldColliders.getCount(); ++i){
    if(collide.location[1].x+2 > i_worldColliders.getCollision()[i]->location[0].x &&
       collide.location[0].x-2 < i_worldColliders.getCollision()[i]->location[1].x &&
       collide.location[1].y-2 < i_worldColliders.getCollision()[i]->location[0].y &&
       collide.location[0].y+2 > i_worldColliders.getCollision()[i]->location[1].y
    ){
      collide.location[0] -= lastDirectionVec;
      collide.location[1] -= lastDirectionVec;
      i_worldColliders.getCollision()[collide.worldIndex]->location[0] -= lastDirectionVec;
      i_worldColliders.getCollision()[collide.worldIndex]->location[1] -= lastDirectionVec;
      characterMesh->translate(-lastDirectionVec.x, -lastDirectionVec.y);
    }
  }
}

mesh* character::getMesh() const{
  return characterMesh;
}
void character::setMesh(mesh* i_mesh){
  characterMesh = i_mesh;
}
collider* character::getCollider(){
  return &collide;
}
vec2 character::getForwardVec() const {
  return forwardVec;
}
vec2Ray character::getForwardLine() const {
  return lastDirectionLine;
}

void character::setLocation(const vec2& i_location, collider* i_worldColliders){
  vec2 translator = i_location - characterMesh->getCentre();
  collide.location[0] += translator;
  collide.location[1] += translator;
  i_worldColliders[collide.worldIndex].location[0] += translator;
  i_worldColliders[collide.worldIndex].location[1] += translator;
  characterMesh->translate(translator.x, translator.y);
}

character::character() {
  collide.location[0] = {1.0f, 1.0f};
  collide.location[1] = {5.0f, 5.0f};
  collide.worldIndex = 0;
  forwardVec = {1.0f, 0.0f};
}