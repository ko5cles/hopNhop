//
// Created by Ze Pan on 12/2/22.
//
#include "Camera.h"
const float CAMERA_SPEED=2;
Camera::Camera(float aspect, float fov, float near, float far)
:Aspect(aspect),Fov(fov),Near(near),Far(far){};

void Camera::Update(const HopObject &hop){
    CameraTarget=hop.Position;
    CameraPos=hop.Position-hop.Front*CameraRadiusH+glm::vec3(0.f,0.f,CameraRadiusV);
    CameraDirection=glm::normalize(CameraTarget-CameraPos);
    CameraRight=glm::normalize(glm::cross(CameraDirection,glm::vec3(0.f,0.f,1.f)));
    CameraUp=glm::normalize(glm::cross(CameraRight,CameraDirection));
}

void Camera::Rise(float dt) {
    if(dt<0){
        if(CameraRadiusV<=0) return;
    }
    CameraRadiusV+=CAMERA_SPEED*dt;
}

void Camera::Zoom(float dt) {
    if(dt>0){
        if(CameraRadiusH<=0.1) return;
    }
    CameraRadiusH-=CAMERA_SPEED*dt;
}
glm::mat4 Camera::GetProjMatrix() {
    return glm::perspective(glm::radians(Fov), Aspect, Near, Far);
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(CameraPos, CameraTarget, CameraUp);
}