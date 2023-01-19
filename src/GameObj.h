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
#include "BoxOutliner.h"

class GameObject
{
public:
    glm::vec3 Position, Size, Velocity;
    float Rotation;
    glm::vec3 Color;
    glm::mat4 modelMatrix=glm::mat4(1.0f);
    bool        IsSolid;
    bool        Destroyed;
    Texture   BoxTexture;
    // constructor(s)
    GameObject();
    GameObject(glm::vec3 pos, glm::vec3 size, Texture box);
    // draw sprite
    virtual void Draw(BoxRenderer&, Texture& depthMap, glm::mat4 light, glm::vec3 camPos, glm::mat4 viewMatrix, glm::mat4 projMatrix);
    virtual void Draw(ShadowRenderer& srenderer, glm::mat4& lightSpaceMatrix);
    virtual void Draw(float scale, glm::vec3 color, BoxOutliner& renderer, const glm::mat4& viewMatrix, const glm::mat4& projMatrix);
};

#endif

#endif //ASSIGNMENT4TEX_GAMEOBJ_H
