#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "cenv.h"
#include "chawk.h"


#define CONST_GAP   6

typedef struct {
    double rx;
    double ry;
} CVPOSITION;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    int timerID;
    int ticktock;
    cv::Mat img_blank, img_object;
    Cenv m_env;
    Chawk m_hawk;

    typedef struct {
        double tp;
        double xp;
        double yp;
        cv::Mat img;
    } CHAIN_OP;

    int m_deep;
    CHAIN_OP m_ops[64];

    void ShowImage();
    void ShowCaps();

    CVPOSITION GetCircles(cv::Mat image);

private:
    Ui::MainWindow *ui;

protected:
    void timerEvent(QTimerEvent *);

private slots:
    void on_pbstart_clicked();

};

#endif // MAINWINDOW_H
