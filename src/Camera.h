//
// Created by Ze Pan on 12/2/22.
//

#ifndef ASSIGNMENT4TEX_CAMERA_H
#define ASSIGNMENT4TEX_CAMERA_H

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

#include <HopObj.h>

class Camera{
public:
    Camera(){};
    Camera(float aspect, float fov=35, float near=0.1, float far=100);
    void Update(const HopObject& hop);
    void Rise(float dt);
    void Zoom(float dt);
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjMatrix();
    glm::vec3 CameraDirection;
    glm::vec3 CameraPos;
    glm::vec3 CameraTarget;

private:
    glm::vec3 CameraUp;
    glm::vec3 CameraRight;
    float CameraRadiusV=5;
    float CameraRadiusH=5;
    float Fov;
    float Aspect;
    float Near;
    float Far;
};

#endif //ASSIGNMENT4TEX_CAMERA_H
