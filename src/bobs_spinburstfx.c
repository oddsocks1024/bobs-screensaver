#include "bobs.h"

void initspinburstFX(void)
{
    int i;

    for (i = 0 ; i < bobnum ; i++) {
        bobs[i].x = 0.0f;
        bobs[i].y = 0.0f;
        bobs[i].xspeed = genRandFloat(-0.005f, 0.005f);
        bobs[i].yspeed = genRandFloat(-0.005f, 0.005f);
        bobs[i].texture = genRandInt(0, N_TEXTURES-1);
    }
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -0.7f);
}

void spinburstFX(void)
{
    int i;
    static float zrot = 0.5f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(pointsize[1]);

    for (i = 0; i < bobnum ; i++) {
        if ((bobs[i].x > BOBPSIZE) || (bobs[i].x < -BOBPSIZE) || (bobs[i].y < -BOBPSIZE) || (bobs[i].y > BOBPSIZE)) {
            bobs[i].x = 0.0f;
            bobs[i].y = 0.0f;
            bobs[i].xspeed = genRandFloat(-0.005f, 0.005f);
            bobs[i].yspeed = genRandFloat(-0.005f, 0.005f);
        } else {
            bobs[i].x += bobs[i].xspeed;
            bobs[i].y += bobs[i].yspeed;
        }

        glBindTexture(GL_TEXTURE_2D, textures[bobs[i].texture]);
        glBegin(GL_POINTS);
        glVertex3f(bobs[i].x, bobs[i].y, 0.0f);
        glEnd();
    }

    glRotatef(zrot, 0.0f, 0.0f, 1.0f );

    SDL_GL_SwapBuffers();
}
