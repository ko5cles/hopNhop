//
// Created by Ze Pan on 11/29/22.
//

#ifndef ASSIGNMENT4TEX_BOXRENDERER_H
#define ASSIGNMENT4TEX_BOXRENDERER_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
// GLFW is necessary to handle the OpenGL context
#include <GLFW/glfw3.h>
#endif

// OpenGL Mathematics Library
#include <glm/glm.hpp> // glm::vec3
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif
#include "Shader.h"
#include "Texture.h"
#include "Resources.h"

const glm::vec3 light_pos_0=glm::vec3(-12,0,10);
const glm::vec3 light_pos_1=glm::vec3 (13,5,10);

class BoxRenderer{
public:
    BoxRenderer(Shader& sha);
    ~BoxRenderer();
    void DrawBox(Texture& texture,Texture& depthmap, glm::mat4& lightSpaceMatrix, glm::vec3& camPos,glm::mat4& modelMatrix, glm::mat4& viewMatrix, glm::mat4& projMatrix);
    Shader Program;
    unsigned int boxVAO;
    unsigned int boxVBO;
    void initRenderData();
};

#endif //ASSIGNMENT4TEX_BOXRENDERER_H
