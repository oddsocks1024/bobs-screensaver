/*
Copyright (C) 2009 Ian Chapman

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
#include "config.h"
#ifdef HAVE_GL_GL_H
#include <GL/gl.h>
#else
#include <OpenGL/gl.h>
#endif
#ifdef HAVE_GL_GLU_H
#include <GL/glu.h>
#else
#include <OpenGL/glu.h>
#endif
#include "SDL.h"

/* Draw a frame every 10ms */
#define FRAME_INTERVAL 10

/* Time to next effect switch in ms */
#define EFFECT_SWITCH 60000

/* Bob Plane Size (actually its half width -x to +x) */
#define BOBPSIZE 0.5f

/* Default Number of Bobs */
#define BOBNUM 500

/* Minimum Number of Bobs */
#define MINBOBNUM 100

/* Max Number of Bobs */
#define MAXBOBNUM 2000

/* Number of Effects */
#define N_FX 7

/* Number of textures to load */
#define N_TEXTURES 16

/* Define an approximation of PI */
#define GL_PI 3.14159265359

#ifndef BOBSTRUCTS__H
#define BOBSTRUCTS__H
struct bobfield
{
    float x;
    float y;
    float z;
    float xspeed;
    float yspeed;
    float size;
    unsigned int texture;
};
#endif

#ifndef BOBENUMS__H
#define BOBENUMS__H
enum TIMERS
{
    TIM_FRAME_INTERVAL,
    TIM_MODEL_SWITCH
};
#endif

/* Globals */
extern struct bobfield bobs[];
extern GLuint textures[];
extern GLfloat pointsize[];
extern unsigned int bobnum;

/* Protos */
int _exit_(int code);
void initburstFX(void);
void burstFX(void);
void initwobbleFX(void);
void wobbleFX(void);
void initbounceFX(void);
void bounceFX(void);
void initfountainFX(void);
void fountainFX(void);
void initmultiplyFX(void);
void multiplyFX(void);
void initspinburstFX(void);
void spinburstFX(void);
void initrainFX(void);
void rainFX(void);
int genRandInt(int low, int high);
float genRandFloat(float low, float high);
Uint32 _frametimer(Uint32 interval, void *param);
Uint32 _modelswitchtimer(Uint32 interval, void *param);
SDL_Surface *loadTexture(char *filename);
void initTextures(void);
void errTextures(void);
