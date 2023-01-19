//
// Created by Ze Pan on 12/13/22.
//
#include "ShadowRenderer.h"
#include "BoxRenderer.h"
ShadowRenderer::ShadowRenderer(Shader& sha)
{
    this->sha = sha;
    this->initRenderData();
}

ShadowRenderer::~ShadowRenderer()
{
    glDeleteVertexArrays(1, &this->boxVAO);
}

void ShadowRenderer::DrawBox(glm::mat4 & modelMatrix, glm::mat4 & lightSpaceMatrix)
{
    this->sha.Use();
    this->sha.SetMatrix4("modelMatrix",modelMatrix);
    this->sha.SetMatrix4("lightSpaceMatrix",lightSpaceMatrix);

    glBindVertexArray(this->boxVAO);
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);
}

void ShadowRenderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0,0,-1,0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0,0,-1,1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0,0,-1, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0,0,-1,1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0,0,-1,0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 0,0,-1, 0.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,  0,0,1,0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0,0,1,1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0,0,1,1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0,0,1,1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0,0,1,0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0,0,1,0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  -1,0,0,1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1,0,0, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  -1,0,0,0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  -1,0,0,0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  -1,0,0,0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  -1,0,0,1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1,0,0,1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1,0,0,0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1,0,0,1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1,0,0,0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1,0,0,1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1,0,0,0.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0,-1,0,0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0,-1,0,1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0,-1,0,1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0,-1,0,1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0,-1,0,0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0,-1,0,0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0,1,0,0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0,1,0,1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0,1,0,1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0,1,0,1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0,1,0,0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0,1,0,0.0f, 0.0f
    };

    glGenVertexArrays(1, &this->boxVAO);
    glBindVertexArray(this->boxVAO);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
