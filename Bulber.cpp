#include "Bulber.h"
#include <math.h>

class float4 {
public:
    float4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};
    float4(float a,float b,float c,float d) : x(a),y(b),z(c),w(d) {};
    float4 operator* (const float4 &b)
        {
            return float4(x*b.x,y*b.y,z*b.z,w*b.w);
        }

    float x;
    float y;
    float z;
    float w;
};



class float3 {
public:
    float3() : x(0.0f), y(0.0f), z(0.0f) {};
    float3(float a,float b,float c) : x(a),y(b),z(c) {};
    float3 operator+ (const float3 &b)
        {
            return float3(x+b.x,y+b.y,z+b.z);
        }

    float x;
    float y;
    float z;
};

static inline float dot(const float3 &a, const float3 &b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}


static inline float bulb_iterate(float3 cval, int maxiter)
{
    float3 zval;

    float zr2;
    float zq2;
    float izr2;
    float izq2;
    float4 k2;
    float4 k4;
    float4 k6;
    float4 k8;
    float ko;
    float ki;
    float cozo8;
    float cozi8;
    float sizo8;
    float sizi8;
    float zr8;
    float dist = 32.0f;
    int i;

    zval = cval; 

    for (i = 0; i < maxiter ; i++) {
        zq2 = zval.x*zval.x + zval.z*zval.z;
        zr2 = zq2 + zval.y*zval.y;
        izr2 = 1.0f/zr2;
        izq2 = 1.0f/zq2;

        k2 = float4(izr2*zval.y*zval.y, izr2*zq2, izq2*zval.z*zval.z,
                    izq2*zval.x*zval.x);

        k4 = k2*k2;
        k6 = k4*k2;
        k8 = k4*k4;

        ko = izr2*zval.y*(float)sqrt(zq2);
        ki = izq2*zval.z*zval.x;

        cozo8 = k8.x+k8.y-28.0f*k6.x*k2.y-28.0f*k2.x*k6.y+68.0f*k4.y*k4.x;
        cozi8 = k8.z+k8.w-28.0f*k6.z*k2.w-28.0f*k2.z*k6.w+68.0f*k4.w*k4.z;
        sizo8 = 8.0f*ko*(k6.x-k6.y-7.0f*k2.y*k4.x+7.0f*k2.x*k4.y);
        sizi8 = 8.0f*ki*(k6.z-k6.w-7.0f*k2.w*k4.z+7.0f*k2.z*k4.w);

        zr8 = zr2*zr2;
        zr8 = zr8*zr8;
        zval = float3( zr8*sizo8*sizi8, zr8*cozo8, zr8*sizo8*cozi8 );

        zval = zval + cval;
        dist = dot(zval,zval);
        if (dist>2.0f) {
           break;
        }
    }

    if (dist>2.0f) {
        dist = ((float)log(dist-1.0f))/5.541263545f;
    } else {
        dist = 0.0f;
    }

    if (i==0) {
        dist = 0.0f;
    }

    return (float)i + 0.1f - dist;
}


float Bulber::bulb(int xpos, int ypos)
{
    float result = 0.0f;
    float3 cval;
    int i;
   
    cval.x = (float(xpos)/mZoom) + mX;
    cval.z = (float(ypos)/mZoom) + mY;
    cval.y = mZ;

    result = 36.031f * bulb_iterate(cval, 8);

    return result;
}

Bulber::Bulber(int w, int h) :
    mWidth(w),
    mHeight(h)
{
}


Bulber::~Bulber()
{
}

void Bulber::Calc(float x, float y, float z, float zoom)
{
    mX = x;
    mY = y;
    mZ = z;
    mZoom =zoom;
}

void Bulber::Blit(unsigned char* buf, int pitch)
{
    int r,g,b;
    int val;
    for (int i=0; i<mHeight; i++) {
        for (int j=0; j<mWidth; j++) {
            int offset = i*pitch + 3*j;
            val = r = g = b = (int)(2.0f*bulb(j,i));
#if 1
            if (val>=512) {
                r = 255;
                g = 0;
                b = 0;
            } else {
                r = 0;
                g = 256-(g>>1);
                b = b & 0xff;
            }
#endif
            buf[offset+0] = b;
            buf[offset+1] = g;
            buf[offset+2] = r;
        }
    }
}
