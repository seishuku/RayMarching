#version 330

uniform samplerCube TexReflect;

uniform mat4 mv;
uniform mat4 mvinv;

uniform float fFOV;
uniform ivec2 iSize;

uniform float fTime;

layout(location=0) out vec4 Output;

const int STEPS=200;

const float MINIMUM=0.001;
const float MAXIMUM=10000.0;

const float EPSILON=0.001;

float sdSphere(vec3 p, float r)
{
    return length(p)-r;
}

float sdTorus(vec3 p, vec2 t)
{
    vec2 q=vec2(length(p.xz)-t.x,p.y);
    return length(q)-t.y;
}

float sdRoundBox(vec3 p, vec3 b, float r)
{
    vec3 q=abs(p)-b;
    return length(max(q, 0.0))+min(max(q.x, max(q.y, q.z)), 0.0)-r;
}

float sdCutHollowSphere(vec3 p, float r, float h, float t)
{
    float w=sqrt(r*r-h*h);
    vec2 q=vec2(length(p.xz), p.y);

    return ((h*q.x<w*q.y)?length(q-vec2(w,h)):abs(length(q)-r))-t;
}

float opUnion(float d1, float d2)
{
    return min(d1, d2);
}

float opSubtraction(float d1, float d2)
{
    return max(-d1,d2);
}

float opIntersection(float d1, float d2)
{
    return max(d1,d2);
}

float opSmoothUnion(float d1, float d2, float k )
{
    float h=clamp(0.5+0.5*(d2-d1)/k, 0.0, 1.0);

    return mix(d2, d1, h)-k*h*(1.0-h);
}

float sdScene(vec3 p)
{
    float displacement=sin(sin(0.25*p.x+fTime)*sin(0.25*p.y+fTime)*sin(0.25*p.z+fTime)+fTime)*4.0;

    return opSmoothUnion
            (
                opSmoothUnion
                (
                    sdRoundBox(p+vec3(0.0, 0.0, 0.0), vec3(100.0, 100.0, 100.0), 25.0),
                    sdSphere(p+vec3(-100.0, 0.0, 0.0), 100.0)+displacement,
                    50.0
                ),
                sdSphere(p+vec3(100.0, 0.0, 0.0), 100.0),
                50.0
            );
}

vec3 calcNormal(vec3 p)
{
    vec2 e=vec2(1.0, -1.0)*EPSILON;

    return normalize(e.xyy*sdScene(p+e.xyy)+e.yyx*sdScene(p+e.yyx)+e.yxy*sdScene(p+e.yxy)+e.xxx*sdScene(p+e.xxx));
}

float shortestDistanceToSurface(vec3 eye, vec3 marchingDirection)
{
    float depth=MINIMUM;

    for(int i=0;i<STEPS;i++)
    {
        float dist=sdScene(eye+depth*marchingDirection);

        if(dist<EPSILON)
            return depth;

        depth+=dist;

        if(depth>=MAXIMUM)
            return MAXIMUM;
    }

    return MAXIMUM;
}

vec3 rayDirection()
{
    vec2 xy=gl_FragCoord.xy-iSize /2.0;
    float z=iSize.y/tan(radians(fFOV)/2.0);

    return normalize(vec3(xy, z));
}

void main()
{
    vec3 ro=vec3(mvinv*vec4(0.0, 0.0, 0.0, 1.0));
    vec3 rd=mat3(mvinv)*rayDirection();

    float dist=shortestDistanceToSurface(ro, rd);

    vec3 p=ro+rd*dist;      // Position
    vec3 n=calcNormal(p);   // Normal
    vec3 e=normalize(ro-p); // Eye

/*
    vec3 lightPosition=vec3(2, 2, -7);
    vec3 lightDirection=normalize(lightPosition-p);

    float dif=max(dot(n, lightDirection), 0.0);
*/

    vec3 r=reflect(-e, n);//normalize((2.0*dot(e, n))*n-e);
    vec3 rf=refract(-e, n, 1.0/1.1);

    vec4 SkyBox=texture(TexReflect, normalize(rd));
    vec4 Scene=mix(texture(TexReflect, rf), texture(TexReflect, r), pow(1.0-dot(e, n), 2.0));

    if(dist>MAXIMUM-EPSILON)
        Output=pow(pow(2.0, 5.0)*SkyBox,  vec4(0.45, 0.45, 0.45, 0.0));
    else
        Output=pow(pow(2.0, 5.0)*Scene,  vec4(0.45, 0.45, 0.45, 0.0));
}
