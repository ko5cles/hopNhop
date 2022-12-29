//
// Created by Ze Pan on 11/30/22.
//

#ifndef ASSIGNMENT4TEX_GAMEOBJ_H
#define ASSIGNMENT4TEX_GAMEOBJ_H

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include "Texture.h"
#include "BoxRenderer.h"
#include "ShadowRenderer.h"


// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
    // object state
    glm::vec3   Position, Size, Velocity;
    glm::vec3   Color;
    float       Rotation;
    bool        IsSolid;
    bool        Destroyed;
    // render state
    Texture   Box;
    // constructor(s)
    GameObject();
    GameObject(glm::vec3 pos, glm::vec3 size, Texture box, glm::vec3 color = glm::vec3(1.0f), glm::vec3 velocity = glm::vec3(0.0f));
    // draw sprite
    virtual void Draw(BoxRenderer&, Texture& depthMap, glm::mat4 light, glm::vec3 camPos, glm::mat4 viewMatrix, glm::mat4 projMatrix);
    virtual void Draw(ShadowRenderer&, glm::vec3 camPos, glm::mat4 viewMatrix, glm::mat4 projMatrix);
};

#endif

#endif //ASSIGNMENT4TEX_GAMEOBJ_H
