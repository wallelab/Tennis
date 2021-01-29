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

    m_x0 = x1;
    m_y0 = y1;
    m_t0 = (-b + sqrt( b*b - 4*c))/2.0;
    m_vy = (y1 - 0.5 * 9.8 * m_t0 * m_t0) / m_t0;
    printf("Speed Calc\tt0 = %f\tvx = %f\tvy = %f\n", m_t0, m_vx, m_vy);

    printf("Forecast\tYp = %f\n\n", Forecast(6.4));

}

double Chawk::Forecast(double xp)
{
    double dt = (xp - m_x0) / m_vx;
    double tp = m_t0 + dt;
    double yp = (m_vy * tp) + (0.5 * 9.8 * tp * tp);

    return yp;
}
