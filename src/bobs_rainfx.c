#include "bobs.h"

void initrainFX(void)
{
    int i;

    for (i = 0 ; i < bobnum ; i++) {
        bobs[i].x = genRandFloat(-0.5f, 0.5f);
        bobs[i].y = 0.5f;
        bobs[i].xspeed = genRandFloat(-0.001f, 0.001f);
        bobs[i].yspeed = genRandFloat(-0.01f, -0.001);
    }
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -0.7f);
    glBindTexture(GL_TEXTURE_2D, textures[genRandInt(0, N_TEXTURES-1)]);
    glPointSize(pointsize[1]);
}

void rainFX(void)
{
    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_POINTS);

    for (i = 0; i < bobnum ; i++) {
        if ((bobs[i].x > BOBPSIZE) || (bobs[i].x < -BOBPSIZE) || (bobs[i].y < -BOBPSIZE) || (bobs[i].y > BOBPSIZE)) {
            bobs[i].x = genRandFloat(-0.5f, 0.5f);
            bobs[i].y = 0.5f;
            bobs[i].xspeed = genRandFloat(-0.001f, 0.001f);
            bobs[i].yspeed = genRandFloat(-0.01f, -0.001);
        } else {
            bobs[i].x += bobs[i].xspeed;
            bobs[i].y += bobs[i].yspeed;
        }
        glVertex3f(bobs[i].x, bobs[i].y, 0.0f);
    }

    glEnd();

    SDL_GL_SwapBuffers();
}
