#include "SDL.h"
#include <iostream>
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
    //SDL_Window *window;
    //SDL_Surface *image;

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

            case SDLK_r:
                cx = -1.5f;
                cy = -1.0f;
                cz = 0.5f;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;

            case SDLK_t:
                char filename[128];
                static int screenshotNr = 0;
                sprintf(filename, "screen_single%i.bmp", screenshotNr);
                screenshotNr++;
            	SDL_SaveBMP(screen, filename);
                break;

            case SDLK_g:
                char file_name_[128];
                static int screen_shotNr_ = 0;
                for (int i = 0; i < 10; ++i) {
                    sprintf(file_name_, "screen_sequence_minus_direction%i.bmp", screen_shotNr_);
                    screen_shotNr_++;
                	cz -= 0.01;
                	bulb.Calc( cx, cy, cz, zoom );
                	UpdateScreen(screen, &bulb);
					SDL_SaveBMP(screen, file_name_);
                }
                cx = -1.5f;
                cy = -1.0f;
                cz = 0.5f;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;

            case SDLK_h:
                char filename_[128];
                static int screenshotNr_ = 0;
                for (int i = 0; i < 50; ++i) {
                    sprintf(filename_, "screen_sequence_minus_direction%i.bmp", screenshotNr_);
                    screenshotNr_++;
                	cz -= 0.01;
                	bulb.Calc( cx, cy, cz, zoom );
                	UpdateScreen(screen, &bulb);
					SDL_SaveBMP(screen, filename_);
                }
                cx = -1.5f;
                cy = -1.0f;
                cz = 0.5f;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;

            case SDLK_j:
                char filename0[128];
                static int screenshotNr0 = 0;
                for (int i = 0; i < 100; ++i) {
                    sprintf(filename0, "screen_sequence_minus_direction%i.bmp", screenshotNr0);
                    screenshotNr0++;
                	cz -= 0.01;
                	bulb.Calc( cx, cy, cz, zoom );
                	UpdateScreen(screen, &bulb);
					SDL_SaveBMP(screen, filename0);
                }
                cx = -1.5f;
                cy = -1.0f;
                cz = 0.5f;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;

            case SDLK_b:
                char filename1[128];
                static int screenshotNr1 = 0;
                for (int i = 0; i < 10; ++i) {
                    sprintf(filename1, "screen_sequence_plus_direction%i.bmp", screenshotNr1);
                    screenshotNr1++;
                	cz += 0.01;
                	bulb.Calc( cx, cy, cz, zoom );
                	UpdateScreen(screen, &bulb);
					SDL_SaveBMP(screen, filename1);
                }
                cx = -1.5f;
                cy = -1.0f;
                cz = 0.5f;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;

            case SDLK_n:
                char _filename_[128];
                static int _screenshotNr_ = 0;
                for (int i = 0; i < 50; ++i) {
                    sprintf(_filename_, "screen_sequence_plus_direction%i.bmp", _screenshotNr_);
                    _screenshotNr_++;
                	cz += 0.01;
                	bulb.Calc( cx, cy, cz, zoom );
                	UpdateScreen(screen, &bulb);
					SDL_SaveBMP(screen, _filename_);
                }
                cx = -1.5f;
                cy = -1.0f;
                cz = 0.5f;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;

            case SDLK_m:
                char filename2[128];
                static int screenshotNr2 = 0;
                for (int i = 0; i < 100; ++i) {
                    sprintf(filename2, "screen_sequence_plus_direction%i.bmp", screenshotNr2);
                    screenshotNr2++;
                	cz += 0.01;
                	bulb.Calc( cx, cy, cz, zoom );
                	UpdateScreen(screen, &bulb);
					SDL_SaveBMP(screen, filename2);
                }
                cx = -1.5f;
                cy = -1.0f;
                cz = 0.5f;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;

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

            case SDLK_DOWN:
                cy -= 10/zoom;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;

            case SDLK_UP:
                cy += 10/zoom;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;

            case SDLK_PAGEDOWN:
                cx -= 20/zoom;
                cy -= 20/zoom;
                zoom = zoom / 1.1f;
                bulb.Calc( cx, cy, cz, zoom );
                UpdateScreen(screen, &bulb);
                break;

            case SDLK_PAGEUP:
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
