#ifndef BULBER_H
#define BULBER_H



class Bulber {
public:
    Bulber(int w, int h);
    ~Bulber();

    void Calc(float x, float y, float z, float zoom);

    void Blit(unsigned char* , int pitch);

private:
    float bulb(int xpos, int ypos);

    int mWidth;
    int mHeight;
    float mX;
    float mY;
    float mZ;
    float mZoom;
};



#endif
