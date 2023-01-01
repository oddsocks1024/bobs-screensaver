#include <stdlib.h>
#include <time.h>

/* Generate a random integer between low and high inclusive */
int genRandInt(int low, int high)
{
    static int seed = 1;
    int num;

    /* Gets called only once as seed is static */
    if (seed == 1) {
        srand(time(NULL));
        seed = 0;
    }

    /* Generate number between limits, inclusive */
    num = (rand() % (high - low + 1) + low);
    return (num);
}

/* Generate a random float between low and high inclusive */
float genRandFloat(float low, float high)
{
    static int seed = 1;
    float num;

    if (seed == 1) {
        srand(time(NULL));
        seed = 0;
    }

    num = (rand() / ((float)(RAND_MAX) + 1.0)) * (high - low) + low;
    return num;
}
