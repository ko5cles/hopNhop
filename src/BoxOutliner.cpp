//
// Created by Ze Pan on 1/16/23.
//
#include "BoxOutliner.h"

BoxOutliner::BoxOutliner(Shader &Program) {
    this->Program=Program;
    this->initRenderData();
}

BoxOutliner::~BoxOutliner() {
    glDeleteVertexArrays(1,&this->boxVAO);
    glDeleteBuffers(1,&this->boxVBO);
}

void BoxOutliner::DrawOutline(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projMatrix, glm::vec3 color) {

    glEnable(GL_CULL_FACE);
    this->Program.Use();

    this->Program.SetMatrix4("modelMatrix",modelMatrix);
    this->Program.SetMatrix4("viewMatrix",viewMatrix);
    this->Program.SetMatrix4("projMatrix",projMatrix);
    this->Program.SetVector3f("color",color);

    glBindVertexArray(BoxOutliner::boxVAO);
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);
    glDisable(GL_CULL_FACE);
}

void BoxOutliner::initRenderData() {
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f,  0.5f,
    };

    glGenVertexArrays(1, &this->boxVAO);
    glBindVertexArray(this->boxVAO);

    glGenBuffers(1, &this->boxVBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->boxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}