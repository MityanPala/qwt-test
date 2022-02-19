#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->top_panel->setMinimumWidth(388);
    ui->top_panel->setMinimumHeight(233);

    plot = new QwtPlot(ui->top_panel);
}

MainWindow::~MainWindow()
{
    this->stop_button_clicked();
    if (plot)
        delete plot;

    delete ui;
}

void MainWindow::play_button_clicked()
{
    if (!curve)
    {
        curve = new QwtPlotCurve();
        curve->setStyle(QwtPlotCurve::CurveStyle::Dots);
        curve->setPen(QColor(Qt::blue), 5);
        curve->attach(plot);

        thr = new QThread(this);
        ng = new number_generator(curve);
        ng->moveToThread(thr);
        connect(this, &MainWindow::ask_to_start_generation, ng, &number_generator::start_number_generation);
        connect(this, &MainWindow::ask_to_pause_generation, ng, &number_generator::pause_number_generation);
        connect(ng, &number_generator::ask_to_replot, this, &MainWindow::perform_replot);
        thr->start();
    }
    emit this->ask_to_start_generation();
}

void MainWindow::pause_button_clicked()
{
    emit this->ask_to_pause_generation();
}

void MainWindow::stop_button_clicked()
{
    if (!thr)
        return;
    ng->deleteLater();
    ng = nullptr;
    thr->terminate();
    thr->wait();
    delete thr;
    thr = nullptr;
    delete curve;
    curve = nullptr;
    plot->replot();
}

void MainWindow::perform_replot()
{
    plot->replot();
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    e->accept();
    if (plot != nullptr)
    {
        plot->setFixedWidth(ui->top_panel->width());
        plot->setFixedHeight(ui->top_panel->height());
    }
}
