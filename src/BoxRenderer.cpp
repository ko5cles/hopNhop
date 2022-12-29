//
// Created by Ze Pan on 11/29/22.
//
#include "BoxRenderer.h"

BoxRenderer::BoxRenderer(Shader& sha)
{
    this->sha = sha;
    this->initRenderData();
}

BoxRenderer::~BoxRenderer()
{
    glDeleteVertexArrays(1, &this->boxVAO);
}

void BoxRenderer::DrawBox(Texture &texture, Texture& depthMap,glm::mat4 light,glm::vec3 camPos, glm::mat4 viewMatrix, glm::mat4 projMatrix, glm::vec3 position, glm::vec3 color, glm::vec3 size, float rotate)
{
    // prepare transformations
    this->sha.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);  // first transldate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::scale(model, size); // last scale

    this->sha.SetMatrix4("modelMatrix",model);
    this->sha.SetMatrix4("viewMatrix",viewMatrix);
    this->sha.SetMatrix4("projMatrix",projMatrix);
    this->sha.SetMatrix4("lightSpaceMatrix",light);

    this->sha.SetVector3f("light_pos_0",light_pos_0);
    this->sha.SetVector3f("light_pos_1",light_pos_1);

    // render textured quad
    this->sha.SetVector3f("box_color",color);
    this->sha.SetVector3f("cam_pos",camPos);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glActiveTexture(GL_TEXTURE1);
    depthMap.Bind();

    this->sha.SetInteger("cube_texture",0);
    this->sha.SetInteger("shadow_map",1);

    glBindVertexArray(this->boxVAO);
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);
}

void BoxRenderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0,0,-1,0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0,0,-1, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0,0,-1,1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0,0,-1,1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f, 0,0,-1, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0,0,-1,0.0f, 0.0f,

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
            0.5f,  0.5f, -0.5f,  1,0,0,1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1,0,0,0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1,0,0,0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1,0,0,0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1,0,0,1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0,-1,0,0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0,-1,0,1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0,-1,0,1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0,-1,0,1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0,-1,0,0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0,-1,0,0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0,1,0,0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0,1,0,1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0,1,0,1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0,1,0,1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0,1,0,0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0,1,0,0.0f, 1.0f
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
