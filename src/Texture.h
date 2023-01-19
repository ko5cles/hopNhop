//
// Created by Ze Pan on 11/29/22.
//

#ifndef ASSIGNMENT4TEX_TEXTURE_H
#define ASSIGNMENT4TEX_TEXTURE_H
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
#include <vector>

class Texture{
public:
    // holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    unsigned int ID;
    // texture image dimensions
    unsigned int Width, Height; // width and height of loaded image in pixels
    // texture Format
    unsigned int Internal_Format; // format of texture object
    unsigned int Image_Format; // format of loaded image
    // texture configuration
    unsigned int Wrap_S; // wrapping mode on S axis
    unsigned int Wrap_T; // wrapping mode on T axis
    unsigned int Filter_Min; // filtering mode if texture pixels < screen pixels
    unsigned int Filter_Max; // filtering mode if texture pixels > screen pixels
    // constructor (sets default texture modes)
    Texture();
    // destructor
    //~Texture();
    // generates texture from image data
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void GenerateDepth(unsigned int width, unsigned int height);
    void GenerateCubeMap(unsigned int width, unsigned int height, std::vector<unsigned char*> data);
    // binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
    void BindCubeMap() const;
};

#endif //ASSIGNMENT4TEX_TEXTURE_H
