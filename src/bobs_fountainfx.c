#include "bobs.h"

void initfountainFX(void)
{
    int i;

    for (i = 0 ; i < bobnum ; i++) {
        bobs[i].x = 0.0f;
        bobs[i].y = -0.5f;
        bobs[i].xspeed = genRandFloat(-0.02f, 0.02f);
        bobs[i].yspeed = genRandFloat(0.02f, 0.05f);
        bobs[i].size = genRandFloat(15.0f, 30.0f);
    }
    glBindTexture(GL_TEXTURE_2D, textures[genRandInt(0, N_TEXTURES-1)]);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -1.5f);
}

void fountainFX(void)
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (i = 0; i < bobnum ; i++) {
        bobs[i].yspeed -= 0.0007f;
        bobs[i].y += bobs[i].yspeed;
        bobs[i].x += bobs[i].xspeed;

        if (bobs[i].y < -0.5f) {
            bobs[i].x = 0.0f;
            bobs[i].y = -0.5f;
            bobs[i].xspeed = genRandFloat(-0.02f, 0.02f);
            bobs[i].yspeed = genRandFloat(0.02f, 0.05f);
        }

        glPointSize(bobs[i].size);
        glBegin(GL_POINTS);
        glVertex3f(bobs[i].x, bobs[i].y, bobs[i].z);
        glEnd();
    }

    SDL_GL_SwapBuffers();
}
