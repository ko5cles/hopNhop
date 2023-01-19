//
// Created by Ze Pan on 11/27/22.
//
#include "Game.h"
#include "BoxRenderer.h"
#include "ShadowRenderer.h"
#include "EnvironmentRenderer.h"
#include "QuadRenderer.h"
#include "BoxOutliner.h"

const unsigned int SHADOW_WIDTH = 1600, SHADOW_HEIGHT = 1200;

BoxRenderer* brenderer;
EnvironmentRenderer* erenderer;
ShadowRenderer* srenderer;
QuadRenderer* qrenderer;
BoxOutliner* boutliner;
Texture* depthMap;

HopObject *Player;
Camera* camera;

const glm::vec3 PLAYER_SIZE(0.5f,0.5f,0.5f);
const float DETECTION_CONSTANT=0.2;

Game::Game(unsigned int width, unsigned int height): State{GAME_ACTIVE}, Keys{}, Width{width}, Height{height}{}
Game::~Game()
{
    delete brenderer;
    delete erenderer;
    delete srenderer;
    delete qrenderer;
    delete boutliner;
    glDeleteTextures(1,&depthMap->ID);
}

void Game::Init()
{
    Resources::LoadShader("box_vertex.glsl", "box_fragment.glsl", "box");
    // set render-specific controls
    brenderer = new BoxRenderer(Resources::GetShader("box"));

    Resources::LoadShader("shadow_vertex.glsl","shadow_fragment.glsl","shadow");
    srenderer= new ShadowRenderer(Resources::GetShader("shadow"));

    Resources::LoadShader("cubemap_vertex.glsl","cubemap_fragment.glsl","cubemap");
    erenderer= new EnvironmentRenderer(Resources::GetShader("cubemap"));

    Resources::LoadShader("quad_vertex.glsl","quad_fragment.glsl","quad");
    qrenderer= new QuadRenderer(Resources::GetShader("quad"));

    Resources::LoadShader("outline_vertex.glsl","outline_fragment.glsl","outliner");
    boutliner=new BoxOutliner(Resources::GetShader("outliner"));

    depthMap=new Texture();
    depthMap->GenerateDepth(SHADOW_WIDTH,SHADOW_HEIGHT);

    Resources::LoadTexture("wood_container.jpeg",false,"wood_container");
    Resources::LoadTexture("block_solid.png",false,"block_solid");
    Resources::LoadTexture("brick_wall.jpg",false,"brick_wall");
    Resources::LoadTexture("snow_ground.jpg",false,"snow_ground");
    Resources::LoadTexture("gift_wrap.jpg",false,"gift_wrap");
    Resources::LoadTexture("green_gift_wrap.jpg",false,"green_gift_wrap");
    Resources::LoadTexture("grass.png",true,"grass");
    Resources::LoadTextureCubMap("PondWinter",false,"PondWinter");

    GameLevel test;
    test.Load("test.txt",this->Width, this->Height);
    this->Levels.push_back(test);
    this->Level=0;

    GameObject start=this->Levels[this->Level].Start;
    glm::vec3 startPos=start.Position;

    glm::vec3 playerPos(startPos.x,startPos.y,startPos.z+start.Size.z/2.f+PLAYER_SIZE.z/2.f);
    Player=new HopObject(start,playerPos,PLAYER_SIZE,Resources::GetTexture("green_gift_wrap"));

    camera = new Camera(float(this->Width)/float(this->Height));
    camera->Update(*Player);
}

void Game::Update(float dt)
{
    if(this->State==GAME_ACTIVE){
        //Update object movement
        if(Player->State==HOP_RELEASE){
            Player->Move(dt);
            Player->Expand(dt);
            CheckCollision();
            camera->Update(*Player);
        }
        if(this->CheckComplete()){
            std::cout<<"you win!";
            this->State=GAME_WIN;
        }
    }

}

void Game::ProcessInput(float dt)
{
    if(this->State==GAME_ACTIVE){
        //Object state
        if(Player->State==HOP_STATIC){
            if(Keys[GLFW_MOUSE_BUTTON_LEFT]){
                Player->State=HOP_CHARGE;
                Player->Compress(dt);
            }
        }else if(Player->State==HOP_CHARGE){
            if(Keys[GLFW_MOUSE_BUTTON_LEFT]){
                Player->Compress(dt);
            }else{
                Player->State=HOP_RELEASE;
                Player->SetInitialSpeed(camera->CameraDirection);
            }
        }
        //Camera
        if(Keys[GLFW_KEY_A]){
            Player->Rotate(-dt);
            camera->Update(*Player);
        }else if(Keys[GLFW_KEY_D]){
            Player->Rotate(dt);
            camera->Update(*Player);
        }else if(Keys[GLFW_KEY_W]){
            camera->Rise(dt);
            camera->Update(*Player);
        }else if(Keys[GLFW_KEY_S]){
            camera->Rise(-dt);
            camera->Update(*Player);
        }else if(Keys[GLFW_KEY_UP]){
            camera->Zoom(dt);
            camera->Update(*Player);
        }else if(Keys[GLFW_KEY_DOWN]){
            camera->Zoom(-dt);
            camera->Update(*Player);
        }
    }
}

void Game::Render()
{
  if (this->State==GAME_ACTIVE){
      /* Preprocessing */
      unsigned int depthMapFBO;
      glGenFramebuffers(1, &depthMapFBO);

      depthMap->Bind();
      glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap->ID, 0);
      glDrawBuffer(GL_NONE);
      glReadBuffer(GL_NONE);

      glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
      glClear(GL_DEPTH_BUFFER_BIT);

      glm::vec3 cen=glm::vec3(12.f,4.f,0.f);
      glm::vec3 dir=cen-light_pos_0;
      glm::vec3 rig=glm::cross(dir,glm::vec3(0,0,1));
      glm::vec3 up=glm::cross(rig,dir);

      glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.f);
      glm::mat4 lightView = glm::lookAt(light_pos_0,cen,up);
      glm::mat4 lightSpaceMatrix=lightProjection*lightView;

      this->Levels[this->Level].Draw(*srenderer, lightSpaceMatrix);
      Player->Draw(*srenderer,lightSpaceMatrix);

      /* Render the scene */

      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      glViewport(0, 0, 1600, 1200);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      //qrenderer->Draw(Resources::GetTexture("block_solid"));


      glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
      glStencilMask(0x00);
      this->Levels[this->Level].Draw(*brenderer, *depthMap, lightSpaceMatrix, camera->CameraPos, camera->GetViewMatrix(), camera->GetProjMatrix());

      glStencilFunc(GL_ALWAYS, 1, 0xFF);
      glStencilMask(0xFF);
      Player->Draw(*brenderer, *depthMap, lightSpaceMatrix, camera->CameraPos, camera->GetViewMatrix(), camera->GetProjMatrix());

      glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
      glStencilMask(0x00);
      glDisable(GL_DEPTH_TEST);
      Player->Draw(1.1,glm::vec3(1,1,1),*boutliner,camera->GetViewMatrix(),camera->GetProjMatrix());

      glStencilMask(0xFF);
      glStencilFunc(GL_ALWAYS, 1, 0xFF);
      glEnable(GL_DEPTH_TEST);

      glDeleteFramebuffers(1,&depthMapFBO);

  }
  //Resources::GetShader("cubemap").Use();
  //erenderer->Draw(Resources::GetTexture("PondWinter"),camera->CameraPos,camera->GetViewMatrix(),camera->GetProjMatrix());

}

//assume the bottom of the hop object is always a square
CollideState Collide(const GameObject& cube, const HopObject& hop){
    float hopBottom=hop.Position.z-hop.Size.z/2.f;
    float cubeTop=cube.Position.z+cube.Size.z/2.f;
    float hopTop=hop.Position.z+hop.Size.z/2.f;
    float cubeBottom=cube.Position.z-cube.Size.z/2.f;

     if(hop.Velocity.z<=0){
         if(hopBottom<=cubeTop && hopTop>cubeBottom){
             float x_min=cube.Position.x-cube.Size.x/2.f;
             float x_max=cube.Position.x+cube.Size.x/2.f;
             float y_min=cube.Position.y-cube.Size.y/2.f;
             float y_max=cube.Position.y+cube.Size.y/2.f;

             float halfWidth=hop.Size.y/2.f;
             float halfLength=hop.Size.x/2.f;
             float halfHeight=hop.Size.z/2.f;

             glm::mat3 rot=glm::rotate(glm::mat4(1.f),glm::radians(hop.Rotation),glm::vec3(0.f,0.f,1.f));
             glm::vec3 tl=rot*glm::vec3(-halfLength,halfWidth,halfHeight)+hop.Position;
             glm::vec3 tr=rot*glm::vec3(halfLength,halfWidth,halfHeight)+hop.Position;
             glm::vec3 bl=rot*glm::vec3(-halfLength,-halfWidth,halfHeight)+hop.Position;
             glm::vec3 br=rot*glm::vec3(halfLength,-halfWidth,halfHeight)+hop.Position;

             bool topLeft=tl.x>x_min && tl.x<x_max &&tl.y>y_min&&tl.y<y_max;
             bool topRight=tr.x>x_min && tr.x<x_max &&tr.y>y_min&&tr.y<y_max;
             bool bottomLeft=bl.x>x_min && bl.x<x_max &&bl.y>y_min&&bl.y<y_max;
             bool bottomRight=br.x>x_min && br.x<x_max &&br.y>y_min&&br.y<y_max;

             if(topLeft||topRight||bottomLeft||bottomRight){
                 if(glm::abs(hopBottom-cubeTop)<DETECTION_CONSTANT) return  STAY;
                 else return DROP;
             }else{
                 return NONE;
             }
         }else{
             return NONE;
         }
     }else if(hop.Velocity.z>0){
         if(hopTop>=cubeBottom && hopBottom<cubeTop){
             float x_min=cube.Position.x-cube.Size.x/2.f;
             float x_max=cube.Position.x+cube.Size.x/2.f;
             float y_min=cube.Position.y-cube.Size.y/2.f;
             float y_max=cube.Position.y+cube.Size.y/2.f;

             float halfWidth=hop.Size.y/2.f;
             float halfLength=hop.Size.x/2.f;
             float halfHeight=hop.Size.z/2.f;

             glm::mat3 rot=glm::rotate(glm::mat4(1.f),glm::radians(hop.Rotation),glm::vec3(0.f,0.f,1.f));
             glm::vec3 tl=rot*glm::vec3(-halfLength,halfWidth,halfHeight)+hop.Position;
             glm::vec3 tr=rot*glm::vec3(halfLength,halfWidth,halfHeight)+hop.Position;
             glm::vec3 bl=rot*glm::vec3(-halfLength,-halfWidth,halfHeight)+hop.Position;
             glm::vec3 br=rot*glm::vec3(halfLength,-halfWidth,halfHeight)+hop.Position;

             bool topLeft=tl.x>x_min && tl.x<x_max &&tl.y>y_min&&tl.y<y_max;
             bool topRight=tr.x>x_min && tr.x<x_max &&tr.y>y_min&&tr.y<y_max;
             bool bottomLeft=bl.x>x_min && bl.x<x_max &&bl.y>y_min&&bl.y<y_max;
             bool bottomRight=br.x>x_min && br.x<x_max &&br.y>y_min&&br.y<y_max;

             if(topLeft||topRight||bottomLeft||bottomRight){
                 return DROP;
             }else{
                 return NONE;
             }
         }else{
             return NONE;
         }
     }
}


void Game::CheckCollision() {
    float playerBottom=Player->Position.z-Player->Size.z/2.f;
    if(playerBottom<-0.5)
    {
        glm::vec3 pos=Player->Support.Position;
        pos.z+=Player->Support.Size.z/2.f+Player->Size.z/2.f;
        Player->Reset(pos,glm::vec3(0.f));
    }
    for (GameObject &cube : this->Levels[this->Level].Cubes)
    {
        if (!cube.Destroyed)
        {
            int curCollideState= Collide(cube, *Player);
            if (curCollideState==STAY)
            {
                Player->State=HOP_STATIC;
                Player->Support=cube;
                Player->Position.z=cube.Position.z+Player->Size.z/2.f+cube.Size.z/2.f;
                return;
            }else if (curCollideState==DROP){
                Player->Velocity.x=0;
                Player->Velocity.y=0;
            }
        }
    }
}

bool Game::CheckComplete() {
    if(Player->Support.Position==this->Levels[this->Level].End.Position) return true;
    else return false;
}