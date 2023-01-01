#include "bobs.h"
#include <math.h>

void initmultiplyFX(void)
{
    int i;

    for (i = 0; i < bobnum ; i ++)
    {
        bobs[i].x = 0.0f;
        bobs[i].y = 0.0f;
        bobs[i].xspeed = genRandFloat(-0.0001f, 0.0001f);
        bobs[i].yspeed = genRandFloat(-0.0001f, 0.0001f);
    }

    glBindTexture(GL_TEXTURE_2D, textures[genRandInt(0, N_TEXTURES-1)]);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -0.7f);
}

void multiplyFX(void)
{
    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (i = 0 ; i < bobnum ; i++) {
        bobs[i].x += genRandFloat(-0.002f, 0.002f) +  bobs[i].xspeed;
        bobs[i].y += genRandFloat(-0.002f, 0.002f) +  bobs[i].yspeed;
        glPointSize(pointsize[1]);
        glBegin(GL_POINTS);
        glVertex3f(bobs[i].x, bobs[i].y, 0.0f);
        glEnd();

        if ((bobs[i].x > BOBPSIZE) || (bobs[i].x < -BOBPSIZE) || (bobs[i].y < -BOBPSIZE/2) || (bobs[i].y > BOBPSIZE)) {
            bobs[i].x = 0.0f;
            bobs[i].y = 0.0f;
            bobs[i].xspeed = genRandFloat(-0.0002f, 0.0002f);
            bobs[i].yspeed = genRandFloat(-0.0002f, 0.0002f);
        }
    }

    SDL_GL_SwapBuffers();
}
