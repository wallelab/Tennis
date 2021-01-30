#ifndef CHAWK_H
#define CHAWK_H


class Chawk
{
public:
    Chawk();

private:
    double m_x0, m_y0, m_t0;
    double m_vx, m_vy;

public:
    void SpeedCalc(double x0, double y0, double x1, double y1,
                   double x2, double y2, double dt);

    double Forecast(double xp);
    void AdjParam(double x, double y, double dt);

};

#endif // CHAWK_H
