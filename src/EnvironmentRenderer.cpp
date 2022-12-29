//
// Created by Ze Pan on 12/12/22.
//
#include "EnvironmentRenderer.h"

EnvironmentRenderer::EnvironmentRenderer(Shader &sha) {
    this->sha=sha;
    this->initRenderData();
}

EnvironmentRenderer::~EnvironmentRenderer() {
    glDeleteVertexArrays(1, &this->environmentVAO);
}

void EnvironmentRenderer::Draw(Texture &texture, glm::vec3 position, glm::mat4 viewMatrix, glm::mat4 projMatrix) {
    glDepthFunc(GL_LEQUAL);

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);

    this->sha.Use();
    this->sha.SetMatrix4("viewMatrix",viewMatrix);
    this->sha.SetMatrix4("projMatrix",projMatrix);
    this->sha.SetMatrix4("modelMatrix",modelMatrix);

    glActiveTexture(GL_TEXTURE0);
    texture.BindCubeMap();

    glBindVertexArray(this->environmentVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glDepthFunc(GL_LESS);
}

void EnvironmentRenderer::initRenderData() {
    unsigned int VBO;
    float vertices[] = {
            // positions
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
    };
    glGenVertexArrays(1, &this->environmentVAO);
    glBindVertexArray(environmentVAO);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
