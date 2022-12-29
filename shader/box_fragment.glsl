#version 330 core
out vec4 fragcolor;

in vec3 n;
in vec3 pos;
in vec2 tcoord;
in vec4 pos_lightspace;

uniform sampler2D cube_texture;
uniform sampler2D shadow_map;

uniform vec3 box_color;
uniform vec3 light_pos_0;
uniform vec3 light_pos_1;
uniform vec3 cam_pos;

float ShadowCalculation(vec4 pos_lightspace)
{
    vec3 projCoords = pos_lightspace.xyz / pos_lightspace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadow_map, projCoords.xy).r;
    float currentDepth = projCoords.z;

    if(currentDepth-closestDepth>0.001) return 1;
    else return 0;
}

void main()
{
    float shadow=ShadowCalculation(pos_lightspace);
    vec3 N=normalize(n);
    vec3 L=normalize(light_pos_0-pos);

    float lamb=max(dot(N,L),0);
    float spec=0;
    if(lamb>0){
        vec3 R=reflect(-L,N);
        vec3 V=normalize(cam_pos-light_pos_0);
        float angle=max(dot(R,V),0);
        spec=pow(angle,64);
    }
    vec3 dcolor=vec3(texture(cube_texture,tcoord));
    vec3 color=0.15*vec3(1.f)+(1-shadow)*(lamb*dcolor+spec*dcolor);

    vec3 L_1=normalize(light_pos_1-pos);
    float lamb_1=max(dot(N,L_1),0);
    float spec_1=0;
    if(lamb_1>0){
        vec3 R_1=reflect(-L_1,N);
        vec3 V_1=normalize(cam_pos-light_pos_1);
        float angle_1=max(dot(R_1,V_1),0);
        spec_1=pow(angle_1,64);
    }
    vec3 color_1=0.15*vec3(1.f)+(lamb_1*dcolor+spec_1*dcolor);


    fragcolor=vec4(0.8*color+0.2*color_1,1);
}
