#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timerID(0),
    img_blank(cv::Mat(480,640,CV_8UC3,cv::Scalar(255,255,255))),
    img_object(cv::Mat(480,640,CV_8UC3,cv::Scalar(0,0,0))),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    img_blank.row(240).setTo(cv::Scalar(192, 192, 192));
    timerID = startTimer(40);
    ShowImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timerID) {
        if (m_env.light) {
            for (int i=0; i<100; i++) {
                m_env.Step();
            }
            ShowImage();

            if (m_deep < 63) {
                m_deep++;
                m_ops[m_deep].tp = m_env.count * 1.e-4;
                m_ops[m_deep].xp = m_env.rx;
                m_ops[m_deep].yp = m_env.ry;
                img_object.copyTo(m_ops[m_deep].img);
            }
            if (!m_env.light) {
                ShowCaps();

                for (int i=0; i<m_deep; i+=CONST_GAP) {
                    printf("@%f\t(%f,%f)\n", m_ops[i].tp, m_ops[i].xp, m_ops[i].yp);
                }
                printf("......\n");
                printf("@%f\t(%f,%f)\n", m_ops[m_deep].tp, m_ops[m_deep].xp, m_ops[m_deep].yp);
                printf("-----------------------------\n");

                CVPOSITION c0, c1, c2;
                c0 = GetCircles(m_ops[CONST_GAP].img);
                c1 = GetCircles(m_ops[CONST_GAP*2].img);
                c2 = GetCircles(m_ops[CONST_GAP*3].img);
                printf("-----------------------------\n");

#if 1
                m_hawk.SpeedCalc(c0.rx, c0.ry, c1.rx, c1.ry, c2.rx, c2.ry, 0.01*CONST_GAP);
#else
                m_hawk.SpeedCalc(m_ops[CONST_GAP].xp, m_ops[CONST_GAP].yp,
                        m_ops[CONST_GAP*2].xp, m_ops[CONST_GAP*2].yp,
                        m_ops[CONST_GAP*3].xp, m_ops[CONST_GAP*3].yp, 0.01*CONST_GAP);
#endif
            }
        }
    }
}

void MainWindow::ShowImage()
{
    int xp = m_env.rx * 100;
    int yp = m_env.ry * 100;

    img_blank.copyTo(img_object);

    cv::circle(img_object, cv::Point(xp, 240 + yp), 3, cv::Scalar(0, 0, 255), 3, cv::LINE_8, 0);

    cv::Mat image;
    cv::cvtColor(img_object, image, CV_BGR2RGB);
    QImage img = QImage(image.data, image.cols, image.rows, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::ShowCaps()
{
    cv::Mat image;
    cv::resize(m_ops[CONST_GAP].img, image, cv::Size(128,96));
    cv::cvtColor(image, image, CV_BGR2RGB);
    QImage img = QImage(image.data, image.cols, image.rows, QImage::Format_RGB888);
    ui->cap0->setPixmap(QPixmap::fromImage(img));
    ui->cap0->resize(ui->cap0->pixmap()->size());

    cv::resize(m_ops[CONST_GAP*2].img, image, cv::Size(128,96));
    cv::cvtColor(image, image, CV_BGR2RGB);
    img = QImage(image.data, image.cols, image.rows, QImage::Format_RGB888);
    ui->cap1->setPixmap(QPixmap::fromImage(img));
    ui->cap1->resize(ui->cap1->pixmap()->size());

    cv::resize(m_ops[CONST_GAP*3].img, image, cv::Size(128,96));
    cv::cvtColor(image, image, CV_BGR2RGB);
    img = QImage(image.data, image.cols, image.rows, QImage::Format_RGB888);
    ui->cap2->setPixmap(QPixmap::fromImage(img));
    ui->cap2->resize(ui->cap2->pixmap()->size());
}

CVPOSITION MainWindow::GetCircles(cv::Mat image)
{
    cv::Mat img;
    std::vector<cv::Vec3f> circles;

    cv::cvtColor(image, img, CV_BGR2GRAY);
    cv::GaussianBlur(img, img, cv::Size(3,3), 1.5);
    cv::HoughCircles(img, circles, CV_HOUGH_GRADIENT, 2, 50, 200, 10, 3, 6);

    std::vector<cv::Vec3f>::const_iterator itc = circles.begin();

    CVPOSITION center;
    center.rx = 0.01 * (*itc)[0];
    center.ry = 0.01 * ((*itc)[1] - 240);

    int count = 0;
    while(itc != circles.end()) {
        count++;
        printf("circles %i (ox,oy) = (%f,%f)\n", count, (*itc)[0], (*itc)[1]);
        itc++;
    }
    return center;
}

void MainWindow::on_pbstart_clicked()
{
    char sz[256];
    m_env.Start(sz);
    printf("%s",sz);
    ui->status->setText(sz);

    m_deep = 0;
    m_ops[0].xp = m_env.rx;
    m_ops[0].yp = m_env.ry;
}

