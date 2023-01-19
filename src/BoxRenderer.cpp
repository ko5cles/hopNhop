//
// Created by Ze Pan on 11/29/22.
//
#include "BoxRenderer.h"

BoxRenderer::BoxRenderer(Shader& sha)
{
    this->Program = sha;
    this->initRenderData();

}

BoxRenderer::~BoxRenderer()
{
    glDeleteVertexArrays(1, &this->boxVAO);
    glDeleteBuffers(1, &this->boxVBO);
}

void BoxRenderer::DrawBox(Texture &texture, Texture& depthMap,glm::mat4& lightSpaceMatrix,glm::vec3& camPos,glm::mat4& modelMatrix, glm::mat4& viewMatrix, glm::mat4& projMatrix)
{
    glEnable(GL_CULL_FACE);

    this->Program.Use();

    this->Program.SetMatrix4("modelMatrix", modelMatrix);
    this->Program.SetMatrix4("viewMatrix", viewMatrix);
    this->Program.SetMatrix4("projMatrix", projMatrix);
    this->Program.SetMatrix4("lightSpaceMatrix", lightSpaceMatrix);

    this->Program.SetVector3f("light_pos_0", light_pos_0);
    this->Program.SetVector3f("light_pos_1", light_pos_1);
    this->Program.SetVector3f("cam_pos", camPos);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glActiveTexture(GL_TEXTURE1);
    depthMap.Bind();

    this->Program.SetInteger("box_texture", 0);
    this->Program.SetInteger("shadow_map", 1);

    glBindVertexArray(BoxRenderer::boxVAO);
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);

    glDisable(GL_CULL_FACE);
}

void BoxRenderer::initRenderData()
{
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

    glGenBuffers(1, &this->boxVBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->boxVBO);
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
