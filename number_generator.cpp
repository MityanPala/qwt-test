#include "number_generator.h"

number_generator::number_generator(QwtPlotCurve *curve, QObject *parent)
    : QObject{parent}
{
    this->curve = curve;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &number_generator::add_number_to_vector);
}

number_generator::~number_generator()
{
    timer->deleteLater();
}

void number_generator::start_number_generation()
{
    if (!timer->isActive())
        timer->start(500);
}

void number_generator::pause_number_generation()
{
    if (timer->isActive())
        timer->stop();
}

/*  addition of the new generated number to last one is just to make "curve" smoother */
void number_generator::add_number_to_vector()
{
    double cur_num = rg->bounded(5.0);
    int add_or_subtract = rg->bounded(0, 2);
    if (add_or_subtract == 0)
        last += cur_num;
    else
        last -= cur_num;
    y_coords.append(last);
    curve->setSamples(y_coords);
    emit this->ask_to_replot();
}
