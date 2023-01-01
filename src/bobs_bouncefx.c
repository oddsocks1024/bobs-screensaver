#include "bobs.h"

void initbounceFX(void)
{
    int i;
    int inittype = genRandInt(0, 3);

    /* Choose a random initialisation */
    switch (inittype) {
        case 0:
            for (i = 0 ; i < bobnum ; i++) {
                bobs[i].x = genRandFloat(-BOBPSIZE,BOBPSIZE);
                bobs[i].y = genRandFloat(-BOBPSIZE,BOBPSIZE);
                bobs[i].xspeed = genRandFloat(-0.005f, 0.005f);
                bobs[i].yspeed = genRandFloat(-0.005f, 0.005f);
                bobs[i].size = genRandFloat(pointsize[0], pointsize[1]);
            }
            break;
        case 1:
            for (i = 0 ; i < bobnum ; i++) {
                bobs[i].x = 0.0f;
                bobs[i].y = 0.0f;
                bobs[i].xspeed = genRandFloat(-0.005f, 0.005f);
                bobs[i].yspeed = genRandFloat(-0.005f, 0.005f);
                bobs[i].size = genRandFloat(pointsize[0], pointsize[1]);
            }
            break;
        case 2:
            for (i = 0 ; i < bobnum ; i++) {
                bobs[i].x = genRandFloat(-BOBPSIZE,BOBPSIZE);
                bobs[i].y = 0.0f;
                bobs[i].xspeed = genRandFloat(-0.005f, 0.005f);
                bobs[i].yspeed = genRandFloat(-0.005f, 0.005f);
                bobs[i].size = genRandFloat(pointsize[0], pointsize[1]);
            }
            break;
        case 3:
            for (i = 0 ; i < bobnum ; i++) {
                bobs[i].x = 0.0f;
                bobs[i].y = genRandFloat(-BOBPSIZE,BOBPSIZE);
                bobs[i].xspeed = genRandFloat(-0.005f, 0.005f);
                bobs[i].yspeed = genRandFloat(-0.005f, 0.005f);
                bobs[i].size = genRandFloat(pointsize[0], pointsize[1]);
            }
            break;
    }

    glBindTexture(GL_TEXTURE_2D, textures[genRandInt(0, N_TEXTURES-1)]);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -0.7f);
}

void bounceFX(void)
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (i = 0; i < bobnum ; i++) {
        if ((bobs[i].x > BOBPSIZE) || (bobs[i].x < -BOBPSIZE) || (bobs[i].y < -BOBPSIZE) || (bobs[i].y > BOBPSIZE)) {
            bobs[i].x = genRandFloat(-BOBPSIZE,BOBPSIZE);
            bobs[i].y = genRandFloat(-BOBPSIZE,BOBPSIZE);
            bobs[i].xspeed = genRandFloat(-0.005f, 0.005f);
            bobs[i].yspeed = genRandFloat(-0.005f, 0.005f);
        } else {
            bobs[i].x += bobs[i].xspeed;
            bobs[i].y += bobs[i].yspeed;
        }

        glPointSize(bobs[i].size);
        glBegin(GL_POINTS);
        glVertex3f(bobs[i].x, bobs[i].y, 0.0f);
        glEnd();
    }

    SDL_GL_SwapBuffers();
}
