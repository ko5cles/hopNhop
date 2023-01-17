//
// Created by Ze Pan on 11/29/22.
//

#ifndef ASSIGNMENT4TEX_RESOURCES_H
#define ASSIGNMENT4TEX_RESOURCES_H

#include <map>
#include "Texture.h"
#include "Shader.h"
#include "BoxRenderer.h"
#include <string>

class Resources{
public:
    // resource storage
    static std::map<std::string, Shader> Shaders;
    static std::map<std::string, Texture> Textures;
    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader LoadShader(const char *vShaderFile, const char *fShaderFile, std::string name);
    // retrieves a stored shader
    static Shader& GetShader(std::string name);
    // loads (and generates) a texture from file
    static Texture LoadTexture(const char *file, bool alpha, std::string name);
    static Texture LoadTextureCubMap(const char *file, bool alpha, std::string name);
    // retrieves a stored texture
    static Texture& GetTexture(std::string name);
    // properly de-allocates all loaded resources
    static void Clear();
private:
    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    Resources() { };
    // loads and generates a shader from file
    static Shader loadShaderFromFile(const std::string& vShaderFile, const std::string& fShaderFile);
    // loads a single texture from file
    static Texture loadTextureFromFile(const char *file, bool alpha);
    static Texture loadTextureCubeMapFromFile(const char *file, bool alpha);
};



#endif //ASSIGNMENT4TEX_RESOURCES_H
