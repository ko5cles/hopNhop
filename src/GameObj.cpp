//
// Created by Ze Pan on 11/30/22.
//
#include "GameObj.h"
GameObject::GameObject(){ };

GameObject::GameObject(glm::vec3 pos, glm::vec3 size, Texture box)
        : Position{pos}, Size{size}, Box{box}, Rotation{0.0f}, IsSolid(false), Destroyed(false) {
    //transformations are: scale happens first, then rotation, and then final translation happens; reversed order
    this->modelMatrix = glm::translate(this->modelMatrix, this->Position);
    this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->Rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    this->modelMatrix = glm::scale(this->modelMatrix, this->Size);
};

void GameObject::Draw(BoxRenderer &renderer,Texture& depthMap, glm::mat4 light, glm::vec3 camPos, glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
    renderer.DrawBox(this->Box, depthMap, light, camPos,viewMatrix, projMatrix, this->Position, this->Color, this->Size, this->Rotation);
}

void GameObject::Draw(ShadowRenderer &renderer,glm::vec3 camPos, glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
    renderer.DrawBox(this->Box, camPos,viewMatrix, projMatrix, this->Position, this->Color, this->Size, this->Rotation);
}

void GameObject::Draw(float scale, glm::vec3 color, BoxOutliner &renderer, const glm::mat4& viewMatrix, const glm::mat4& projMatrix)
{
    renderer.DrawOutline(glm::scale(this->modelMatrix,glm::vec3(scale)), viewMatrix, projMatrix, color);
}
