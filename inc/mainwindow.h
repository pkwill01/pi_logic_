#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Qt Libaries 
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
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
    QtCharts::QLineSeries *series;
    QtCharts::QChart *chart;
    QtCharts::QChartView *chartView;
    float maxTime = 10;

private slots:
    void PlotPressed();
    void TimePressed();
};
#endif // MAINWINDOW_H
