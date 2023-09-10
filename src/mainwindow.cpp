#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connecting buttons to functions
    connect(ui->plotButton, SIGNAL(released()), this, SLOT(PlotPressed()));
    connect(ui->timeButton, SIGNAL(released()), this, SLOT(TimePressed()));


    // Init the Plot series 
    series = new QtCharts::QLineSeries();
    chart = new QtCharts::QChart();
    chartView = new QtCharts::QChartView(chart);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::PlotPressed()
{
    // Plotting Pre checks
    chart->removeSeries(series);
    maxTime = 10;
    // Creating Data series 
    for (float i = 0; i < maxTime; i += .5) 
    {
     series->append(i, sin(i));
    }


    // Chart options
    chart->addSeries(series);
    chart->setTitle("Sin Waves");
    chart->createDefaultAxes();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom); 

    // Adding Chart options
    // Enable both zooming and panning
    chartView->setRubberBand(QtCharts::QChartView::RectangleRubberBand);
    chartView->setDragMode(QtCharts::QChartView::ScrollHandDrag);

    // Adding the Plot to frame 
    ui->plotFrame->layout()->addWidget(chartView);
}
void MainWindow::TimePressed()
{
    // Clearing old series 
    series->clear();
    
    // adding new data to series 
    maxTime += 20;
    for (float i = 0; i < maxTime; i += .5) 
    {
     series->append(i, sin(i));
    }

    // Realign axis 
    chart->axisX()->setRange(0, maxTime);
}
