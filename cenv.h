#ifndef CENV_H
#define CENV_H

//  This program is to simulate tennis throwing.
//  At an area of 6.4(m) x 4.8(m), map to screen as 640x480.
//  A tennis with 5cm diameter, map to 5 pixel.
//  As max 0.64s to get 6.4m, speedX should be 10m/s.
//  The gravity falldown in 0.4s = 0.5 x 9.8 x 0.64 x 0.64 = 0.201(m).
//  Start point is on center of left side. Start Angle < arctan(0.375),
//  which is about 20.5 degree.

class Cenv
{
public:
    Cenv();

private:
    double angle;    // 0 ~ 15 degree.
    double speed;    // 12 ~ 20 m/s
    double vx, vy;

public:
    int light;
    int count;
    double rx, ry;

    void Start(char *sz);
    int Step();     //  a 100us step.

};

#endif // CENV_H
