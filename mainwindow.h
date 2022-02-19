#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QThread>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <number_generator.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void ask_to_start_generation();
    void ask_to_pause_generation();

private slots:
    void play_button_clicked();
    void pause_button_clicked();
    void stop_button_clicked();
    void perform_replot();

private:
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent *e);
    QThread *thr = nullptr;
    number_generator *ng = nullptr;
    QwtPlot *plot = nullptr;
    QwtPlotCurve *curve = nullptr;
};
#endif // MAINWINDOW_H
