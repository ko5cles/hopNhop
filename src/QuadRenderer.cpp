//
// Created by Ze Pan on 12/24/22.
//
#include "QuadRenderer.h"

QuadRenderer::QuadRenderer(Shader &sha) {
    this->sha=sha;
    this->initRenderData();
}

QuadRenderer::~QuadRenderer() {
    glDeleteVertexArrays(1, &this->quadVAO);
}

void QuadRenderer::Draw(Texture &texture) {
    this->sha.Use();
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES,0,6);
    glBindVertexArray(0);
}

void QuadRenderer::initRenderData() {
    unsigned int VBO;
    float vertices[]={-1,1,0,
                      1,1,0,
                      -1,-1,0,
                      -1,-1,0,
                      1,1,0,
                      1,-1,0};

    glGenVertexArrays(1, &this->quadVAO);
    glBindVertexArray(this->quadVAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
