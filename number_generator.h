#ifndef NUMBER_GENERATOR_H
#define NUMBER_GENERATOR_H

#include <QObject>
#include <QVector>
#include <QRandomGenerator>
#include <QTimer>

#include <qwt_plot_curve.h>

class number_generator : public QObject
{
    Q_OBJECT
public:
    explicit number_generator(QwtPlotCurve *curve, QObject *parent = nullptr);
    ~number_generator();

signals:
    void ask_to_replot();

public slots:
    void start_number_generation();
    void pause_number_generation();

private slots:
    void add_number_to_vector();

private:
    QRandomGenerator *rg = QRandomGenerator::global();
    QTimer *timer = nullptr;
    QwtPlotCurve *curve = nullptr;
    QVector<double> y_coords;
    double last = 0;
};

#endif // NUMBER_GENERATOR_H
