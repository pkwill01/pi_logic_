#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Qt Libaries 
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QDoubleSpinBox>
#include <QTimer>

// General Libaries 
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include<unistd.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void FixLayouts();
    void UpdateChart();
    QTimer *timer;
    QtCharts::QLineSeries *series;
    QtCharts::QChart *chart;
    QtCharts::QChartView *chartView;
    float max_t = 10;
    float ith_t = 0;
    float delta_t = 0.5;

private slots:
    void PlotPressed();
    void ClearPressed();
    void StopPressed();

};
#endif // MAINWINDOW_H
