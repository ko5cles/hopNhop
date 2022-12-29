//
// Created by Ze Pan on 12/1/22.
//
#include "HopObj.h"
const float ROTATE_SPEED=45.f;
const float COMPRESS_SPEED=0.1;

HopObject::HopObject():GameObject(),State{HOP_STATIC} {
    Height=this->Size.z;
};
HopObject::HopObject(GameObject& support, glm::vec3 pos, glm::vec3 size,Texture texture,glm::vec3 color, glm::vec3 velocity)
:GameObject(pos,size,texture,color, velocity),State{HOP_STATIC}, Support{support},Height{size.z} {};

void HopObject::Compress(float dt) {
    if(this->Size.z>this->Height/2.f){
        float z=Size.z-dt*COMPRESS_SPEED;
        this->Size.z=this->Height/2.f>z?this->Height/2.f:z;
        this->Position.z=this->Support.Position.z+this->Support.Size.z/2.f+this->Size.z/2.f;
    }
}

void HopObject::Expand(float dt) {
    if(this->Size.z<this->Height){
        float z=Size.z+dt*0.25f;
        this->Size.z=z<this->Height?z:this->Height;
    }
}

glm::vec3 HopObject::SetInitialSpeed(glm::vec3 direction) {
    float ratio=(this->Height/this->Size.z-1)*1.2f+0.4f;
    glm::vec2 xny=glm::normalize(glm::vec2(direction.x,direction.y));
    this->Velocity=Front*ratio+glm::vec3(0.f,0.f,9.8);
    return this->Velocity;
}

glm::vec3 HopObject::Move(float dt) {
    this->Position+=this->Velocity*dt;
    this->Velocity.z-=9.8f*dt;
    return this->Position;
}

void HopObject::Reset(glm::vec3 pos, glm::vec3 velocity) {
    this->Position=pos;
    this->Velocity=velocity;
    this->State=HOP_STATIC;
}

void HopObject::Rotate(float dt) {
    this->Rotation+=ROTATE_SPEED*dt;
    if(this->Rotation>360) this->Rotation-=360;
    else if(this->Rotation<-360) this->Rotation+=360;
    glm::mat3 rot=glm::rotate(glm::mat4(1.f),glm::radians(this->Rotation),glm::vec3(0.f,0.f,1.f));
    this->Front=rot*this->InitialFront;
}
