//
// Created by Ze Pan on 12/1/22.
//

#ifndef ASSIGNMENT4TEX_HOPOBJ_H
#define ASSIGNMENT4TEX_HOPOBJ_H

#include "GameObj.h"
#include "Texture.h"

enum HOP_STATE{HOP_CHARGE,HOP_RELEASE,HOP_STATIC};
class HopObject:public GameObject{
public:
    HOP_STATE State;
    GameObject Support;
    float Height;
    const glm::vec3 InitialFront=glm::vec3(1.f,0.f,0.f);
    glm::vec3 Velocity;
    glm::vec3 Front=InitialFront;
    //constructor
    HopObject();
    HopObject(GameObject& Support, glm::vec3 pos, glm::vec3 size, Texture texture);
    void Compress(float dt);
    void Expand(float dt);
    glm::vec3 SetInitialSpeed(glm::vec3 direction);
    glm::vec3 Move(float dt);
    void Reset(glm::vec3 pos, glm::vec3 velocity);
    void Rotate(float dt);
    void UpdateModelMatrix();
};

#endif //ASSIGNMENT4TEX_HOPOBJ_H
