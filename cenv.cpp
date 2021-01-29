#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "cenv.h"


Cenv::Cenv()
{
    light = 0;
    angle = 0.;
    speed = 0.;

    srand((int)time(0));
}

void Cenv::Start(char *sz)
{
    double ka = 4.656612873077393e-10f * rand();
    double ks = 4.656612873077393e-10f * rand();

    angle = ka * 15.;
    speed = ks * 8. + 12.;

    double rad = angle * 3.1415926 / 180.;
    vx = speed * cos(rad);
    vy = -speed * sin(rad);

    rx = 0.;
    ry = 0.;

    count = 0;
    light = 1;

    sprintf(sz, "ang = %f\nspd = %f\nvx = %f\nvy= %f\n", angle, speed, vx, vy);
}

int Cenv::Step()
{
    if (light) {
        count ++;

        double t = count * (1.e-4);
        rx = vx * t;
        ry = (vy * t) + (0.5* 9.8 * t * t);

        if (rx > 6.4) light = 0;
    }

    return light;
}
