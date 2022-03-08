#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Bulber.h"


void UpdateScreen( SDL_Surface *screen, Bulber* bulb)
{
    unsigned char *raw_pixels;
    SDL_LockSurface(screen);

    raw_pixels = (unsigned char*)screen->pixels;

    bulb->Blit( raw_pixels, screen->pitch );

    SDL_UnlockSurface(screen);
    SDL_UpdateRect(screen,0,0,0,0);
}


int main()
{
    SDL_Surface *screen;

    //Initialize SDL's video system and check for errors
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
               printf("Unable to initialize SDL: %s\n",
                      SDL_GetError());
               return 1;
    };

    // Make sure SDL_Quit gets called when the program exits
    atexit(SDL_Quit);

    // Attempt to set a 640x480 24bpp video mode
    screen = SDL_SetVideoMode(640,480,24,SDL_SWSURFACE );
    if (screen == NULL) {
        printf("Unable to set video mode: %s\n",
               SDL_GetError());
        return 1;
    };
 
    int x,y;
    Bulber bulb(640,480);
    float cx = -1.5f;
    float cy = -1.0f;
    float cz = 0.5f;
    float zoom = 240.0f;

    bulb.Calc( cx, cy, cz, zoom );
    UpdateScreen(screen, &bulb);

    SDL_EnableKeyRepeat(300,100);

    SDL_Event event;
    bool run = true;
    for(;run;) {
        SDL_WaitEvent(&event);
        switch (event.type) {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
            case SDLK_a:
                cz -= 0.01;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;
            case SDLK_z:
                cz += 0.01;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;
            case SDLK_s:
                cz -= 0.001;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;
            case SDLK_x:
                cz += 0.001;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;
            case SDLK_d:
                cz -= 0.0001;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;
            case SDLK_c:
                cz += 0.0001;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;
            case SDLK_f:
                cz -= 0.00001;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;
            case SDLK_v:
                cz += 0.00001;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;
            case SDLK_LEFT:
                cx -= 10/zoom;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;
            case SDLK_RIGHT:
                cx += 10/zoom;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;
            case SDLK_F1:
                cy -= 10/zoom;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;
            case SDLK_F2:
                cy += 10/zoom;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;
            case SDLK_PAGEUP:
                cx -= 20/zoom;
                cy -= 20/zoom;
                zoom = zoom / 1.1f;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;
            case SDLK_PAGEDOWN:
                cx += 20/zoom;
                cy += 20/zoom;
                zoom = zoom * 1.1f;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;
            default:
                break;
            }
            break;

        case SDL_QUIT:
            run = false;
            break;
        }
    }

    return 0;
}
