/*
Copyright (C) 2009-2012 Ian Chapman

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "bobs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

unsigned int ogl15 = 0;
unsigned int bobnum;
unsigned int fxswitch;
GLfloat pointsize[2];
struct bobfield bobs[MAXBOBNUM];
GLuint textures[N_TEXTURES];
void (*drawFX)(void);

/* Try to exit cleanly */
int _exit_(int code)
{
    if(SDL_WasInit(SDL_INIT_VIDEO) != 0) {
        glDeleteTextures(N_TEXTURES,textures);
        SDL_Quit();
    }
    exit(code);
}


/* Select a random effect */
void selectFX(void)
{
    int r = genRandInt(0, (N_FX-1));

    switch (r) {
        case 0:
            initburstFX();
            drawFX = burstFX;
            break;
        case 1:
            initwobbleFX();
            drawFX = wobbleFX;
            break;
        case 2:
            initbounceFX();
            drawFX = bounceFX;
            break;
        case 3:
            initfountainFX();
            drawFX = fountainFX;
            break;
        case 4:
            initmultiplyFX();
            drawFX = multiplyFX;
            break;
        case 5:
            initspinburstFX();
            drawFX = spinburstFX;
            break;
        case 6:
            initrainFX();
            drawFX = rainFX;
            break;
    }
}

/* Initialise OpenGL */
void initOpenGL(int w, int h)
{
    glViewport(0, 0, w, h);

    if ( gluCheckExtension((const GLubyte*) "GL_ARB_point_sprite", glGetString(GL_EXTENSIONS)) == GLU_TRUE) {
        ogl15 = 1;
    }

    initTextures();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LEQUAL);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat) w/ (GLfloat) h,  0.0f, 2.0f); /* Calc Aspect Ratio */
    glMatrixMode(GL_MODELVIEW);

    if (ogl15 == 1) {
        glEnable(GL_BLEND);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_POINT_SPRITE);
        glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else { /* Fallback if we can't use point sprites */
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_POINT_SMOOTH);
        glColor3ub(genRandInt(100,255), genRandInt(100,255), genRandInt(100,255));
    }

    glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, pointsize); /* Determine allowed point size ranges */
    if (pointsize[0] < 10.0f) { /* Limit minimum size */
        pointsize[0] = 10.0f;
    }
    if (pointsize[1] > 32.0f) { /* Limit maximum size */
        pointsize[1] = 32.0f;
    }
}


void mainloop(int scr_w, int scr_h)
{
    SDL_TimerID timerMain;
    SDL_TimerID timerModelSwitch;
    SDL_Event event;
    SDL_Surface* mainSurface;
    int _quit = 0;


    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        _exit_(1);
    }

#if SDL_PATCHLEVEL > 12
    SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, 1 );
#endif

    /* Some SDL installations don't default to desktop display size if 0 is passed */
    /* so if we fail, try with some defaults */
    if ((mainSurface = SDL_SetVideoMode(scr_w, scr_h, 0, SDL_OPENGL)) == NULL) {
        scr_w = 640;
        scr_h = 480;
        if ((mainSurface = SDL_SetVideoMode(scr_w, scr_h, 0, SDL_OPENGL)) == NULL) {
            fprintf(stderr, "Unable to create OpenGL screen: %s\n", SDL_GetError());
            _exit_(2);
        }
    }

    SDL_WM_SetCaption("Bobs Screensaver", NULL);
    initOpenGL(mainSurface->w, mainSurface->h); /* Init OpenGL view port */
    timerMain = SDL_AddTimer(FRAME_INTERVAL, _frametimer, NULL); /* Init framerate timer */
    timerModelSwitch = SDL_AddTimer(fxswitch, _modelswitchtimer, NULL); /* Init model switch timer */
    SDL_ShowCursor(SDL_DISABLE);

    /* Choose the initial effect */
    selectFX();

    while ( SDL_WaitEvent(&event) && _quit == 0) {
        switch (event.type) {
            case SDL_QUIT: _quit = 1; break;
            case SDL_USEREVENT:
                if (event.user.code == TIM_FRAME_INTERVAL) {
                    drawFX();
                } else if (event.user.code == TIM_MODEL_SWITCH) {
                    selectFX();
                }
                break;
            case SDL_KEYDOWN: _quit = 1; break;
        }
    }

    SDL_ShowCursor(SDL_ENABLE);
    SDL_RemoveTimer(timerMain);
    SDL_RemoveTimer(timerModelSwitch);
}

int main(int argc, char **argv)
{
    int i;
    char *wid_env;
    static char sdlwid[100];
    Uint32 wid = 0;
    Display *dpy;
    XWindowAttributes winattr;

    /* Some Defaults */
    winattr.width = 0;
    winattr.height = 0;
    bobnum = BOBNUM;
    fxswitch = EFFECT_SWITCH;

    /* See if we've been given a window argument and options*/
    for (i = 0; i < argc ; i++) {
        if (!strcmp (argv[i], "-window-id")) {
            wid = strtol(argv[i+1], (char **) NULL, 0); /* Base 0 autodetects hex/dec */
        } else if (!strcmp (argv[i], "-bobnum")) {
            bobnum = strtol(argv[i+1], (char **) NULL, 0);
            if ((bobnum < MINBOBNUM) || (bobnum > MAXBOBNUM)) {
                bobnum = BOBNUM;
            }
        } else if (!strcmp (argv[i], "-switch")) {
            fxswitch = (strtol(argv[i+1], (char **) NULL, 0) * 1000);
            if ((fxswitch < 30000) || (fxswitch > 600000)) {
                fxswitch = EFFECT_SWITCH;
            }
        }
    }

    /* If no window argument, check environment */
    if (wid == 0) {
        if ((wid_env = getenv("XSCREENSAVER_WINDOW")) != NULL ) {
            wid = strtol(wid_env, (char **) NULL, 0); /* Base 0 autodetects hex/dec */
        }
    }

    /* Get win attrs if we've been given a window, otherwise we'll use our own */
    if (wid != 0 ) {
        if ((dpy = XOpenDisplay(NULL)) != NULL) { /* Use the default display */
            XGetWindowAttributes(dpy, (Window) wid, &winattr);
            XCloseDisplay(dpy);
            snprintf(sdlwid, 100, "SDL_WINDOWID=0x%X", wid);
            putenv(sdlwid); /* Tell SDL to use this window */
        }
    }

    mainloop(winattr.width, winattr.height);
    _exit_(0);
    return 0; /* Silence Warnings */
}
