//
// Created by Ze Pan on 1/16/23.
//

#ifndef ASSIGNMENT4TEX_BOXOUTLINER_H
#define ASSIGNMENT4TEX_BOXOUTLINER_H

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

class BoxOutliner{
public:
    BoxOutliner(Shader& Program);
    ~BoxOutliner();
    void DrawOutline(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix, glm::vec3 color= glm::vec3(1.0f));
    Shader Program;
    unsigned int boxVAO;
    unsigned int boxVBO;
    void initRenderData();
};

#endif //ASSIGNMENT4TEX_BOXOUTLINER_H
