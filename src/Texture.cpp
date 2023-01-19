//
// Created by Ze Pan on 11/29/22.
//
#include "Texture.h"

Texture::Texture(): Width{0}, Height{0}, Internal_Format{GL_RGB}, Image_Format{GL_RGB}, Wrap_S{GL_REPEAT}, Wrap_T{GL_REPEAT}, Filter_Min{GL_LINEAR}, Filter_Max{GL_LINEAR}
{
    glGenTextures(1, &this->ID);
}
//Texture::~Texture()
//{
//    glDeleteTextures(1,&this->ID);
//}

void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->Width = width;
    this->Height = height;
    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    // unbind texture
    //glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::GenerateDepth(unsigned int width, unsigned int height) {
    this->Width = width;
    this->Height = height;
    this->Filter_Max=GL_NEAREST;
    this->Filter_Min=GL_NEAREST;
    this->Internal_Format=GL_DEPTH_COMPONENT;
    this->Image_Format=GL_DEPTH_COMPONENT;
    this->Wrap_S=GL_CLAMP_TO_BORDER;
    this->Wrap_T=GL_CLAMP_TO_BORDER;
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format,
                 width, height, 0, this->Image_Format, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    // unbind texture
    //glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

void Texture::GenerateCubeMap(unsigned int width, unsigned int height, std::vector<unsigned char *>data) {
    this->Width = width;
    this->Height = height;
    glBindTexture(GL_TEXTURE_CUBE_MAP,this->ID);
    if(data.size()!=6) return;
    else{
        for(int i=0; i<data.size(); i++){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data[i]);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        //unbind texture
        glBindTexture(GL_TEXTURE_CUBE_MAP,0);
    }
}

void Texture::BindCubeMap() const {
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->ID);
}

