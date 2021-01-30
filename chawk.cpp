#include <stdio.h>
#include <math.h>

#include "chawk.h"

Chawk::Chawk()
{
    m_vx = 0;
    m_vy = 0;
}

//  The 3-point is (t-1), (t), (t+1)
void Chawk::SpeedCalc(double x0, double y0, double x1, double y1,
                       double x2, double y2, double dt)
{
    double dx = x2 - x0;
    double dy = y2 - y0;


    m_vx = dx / (2. * dt);

#if 1
    m_t0 = x1 / m_vx;
    m_vy = (y1 - 0.5 * 9.8 * m_t0 * m_t0) / m_t0;
#else
//  y(1) - y(-1)
//  ------------ = dt *(vy + gt0)
//       2
    double v1 = dy / (2. * dt);
    printf("check\tv1 - y1/t0 = %f \n", v1 - y1/0.04);


//        y(0)     1
//  v1 - ------ = ---* g * t0
//         t0      2

    double b = -2.0 * v1 / 9.8;
    double c = 2.0 * y1 / 9.8;

    m_t0 = (-b + sqrt( b*b - 4*c))/2.0;
    m_vy = (y1 - 0.5 * 9.8 * m_t0 * m_t0) / m_t0;
#endif

    m_x0 = x1;
    m_y0 = y1;

    printf("Speed Calc\tt0 = %f\tvx = %f\tvy = %f\n", m_t0, m_vx, m_vy);
}

double Chawk::Forecast(double xp)
{
    double dt = (xp - m_x0) / m_vx;
    double tp = m_t0 + dt;
    double yp = (m_vy * tp) + (0.5 * 9.8 * tp * tp);

    return yp;
}

void Chawk::AdjParam(double x, double y, double dt)
{
    double xp, yp, ex, ey, t;

    t = m_t0 + dt;
    xp = m_vx * t;
    ex = x - xp;
    yp = (m_vy * t) + (0.5 * 9.8 * t * t);
    ey = y - yp;

    double delta;
//    delta = ex / m_vx;
//    delta = ey / (m_vy + 9.8 * t);
//    m_t0 += 0.1 * delta;

    delta = ey / t;
    m_vy += 0.5 * delta;

    printf("t0 = %f, vy = %f\n", m_t0, m_vy);
}

