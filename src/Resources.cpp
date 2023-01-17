//
// Created by Ze Pan on 11/29/22.
//
#include <Resources.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
std::map<std::string, Texture> Resources::Textures;
std::map<std::string, Shader> Resources::Shaders;

Shader Resources::LoadShader(const char *vShaderFile, const char *fShaderFile, std::string name)
{
    Shaders.insert({name,loadShaderFromFile(vShaderFile, fShaderFile)});
    return Shaders[name];
}

Shader& Resources::GetShader(std::string name)
{
    return Shaders[name];
}

Texture Resources::LoadTexture(const char *file, bool alpha, std::string name)
{
    Textures.insert({name, loadTextureFromFile(file, alpha)});
    return Textures[name];
}

Texture Resources::LoadTextureCubMap(const char *file, bool alpha, std::string name) {
    Textures.insert({name, loadTextureCubeMapFromFile(file,alpha)});
    return Textures[name];
}

Texture& Resources::GetTexture(std::string name)
{
    return Textures[name];
}

void Resources::Clear()
{
    // (properly) delete all shaders
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader Resources::loadShaderFromFile(const std::string & vShaderFile,const std::string & fShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile("../shader/"+vShaderFile);
        std::ifstream fragmentShaderFile("../shader/"+fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    Shader sha;
    sha.Compile(vertexCode.c_str(),fragmentCode.c_str());
    return sha;
}

Texture Resources:: loadTextureFromFile(const char *file, bool alpha){
    Texture tex;
    if (alpha)
    {
        tex.Internal_Format = GL_RGBA;
        tex.Image_Format = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(("../textures/"+std::string(file)).c_str(), &width, &height, &nrChannels, 0);
    // now generate texture
    tex.Generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return tex;
}

Texture Resources::loadTextureCubeMapFromFile(const char *file, bool alpha) {
    Texture tex;
    if (alpha){
        tex.Internal_Format = GL_RGBA;
        tex.Image_Format = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    std::vector<unsigned char*> data;
    data.resize(6);
    data[0]=stbi_load(("../textures/"+std::string(file)+"/right.jpg").c_str(), &width, &height, &nrChannels, 0);
    data[1]=stbi_load(("../textures/"+std::string(file)+"/left.jpg").c_str(), &width, &height, &nrChannels, 0);
    data[2]=stbi_load(("../textures/"+std::string(file)+"/top.jpg").c_str(), &width, &height, &nrChannels, 0);
    data[3]=stbi_load(("../textures/"+std::string(file)+"/bottom.jpg").c_str(), &width, &height, &nrChannels, 0);
    data[4]=stbi_load(("../textures/"+std::string(file)+"/front.jpg").c_str(), &width, &height, &nrChannels, 0);
    data[5]=stbi_load(("../textures/"+std::string(file)+"/back.jpg").c_str(), &width, &height, &nrChannels, 0);
    // now generate texture
    tex.GenerateCubeMap(width, height, data);
    // and finally free image data
    for(auto & i : data)
        stbi_image_free(i);
    return tex;
}

