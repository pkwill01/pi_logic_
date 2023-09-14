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
#include <chrono>
#include <vector>

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
    void SampleData();
    void UpdateChart();
    QTimer *timer_updateChart;
    QTimer *timer_SampleData;
    QtCharts::QLineSeries *series;
    QtCharts::QChart *chart;
    QtCharts::QChartView *chartView;
    std::chrono::high_resolution_clock::time_point start_time; // Specify the data type
    double max_t = 10;
    // Update Variables 
    double ith_t = 0;
    double delta_t = 0.5;
    std::vector<double> _sampledData; 
    std::vector<double> _timeData; 
    // Data History 
    std::vector<double> sampledData; 
    std::vector<double> timeData; 
    // Chart Variables 
    double jth_t_update = 0;
    double delta_t_update = .5;


private slots:
    void PlotPressed();
    void ClearPressed();
    void StopPressed();

};
#endif // MAINWINDOW_H
