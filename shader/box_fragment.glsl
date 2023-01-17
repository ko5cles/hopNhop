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
    if(projCoords.z>1) return 0;
    float currentDepth = projCoords.z;
    float bias = max(0.01 * (1.0 - dot(normalize(n), light_pos_0-pos)), 0.001);

    float shadow=0;
    vec2 pixel_size=1/textureSize(shadow_map,0);
    for(int x=-1;x<2;x++){
        for(int y=-1; y<2;y++){
            float closestDepth = texture(shadow_map, projCoords.xy+pixel_size*vec2(x,y)).r;
            shadow+=(currentDepth-bias>closestDepth?1:0);
        }
    }
    shadow/=9;
    return shadow;

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
    vec3 color=0.2*(vec3(1.f)+lamb*dcolor)+(1-shadow)*(spec*dcolor+lamb*dcolor);

    fragcolor=vec4(color,1);
}
