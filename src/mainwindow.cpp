#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Connecting buttons to functions
    connect(ui->startButton, SIGNAL(released()), this, SLOT(PlotPressed()));
    connect(ui->clearButton, SIGNAL(released()), this, SLOT(ClearPressed()));
    connect(ui->stopButton, SIGNAL(released()), this, SLOT(StopPressed()));

    

    // Init the Plot series 
    series    = new QtCharts::QLineSeries();
    chart     = new QtCharts::QChart();
    chartView = new QtCharts::QChartView(chart);

    // Init the update Timer 
    timer     = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::UpdateChart);


    // Doing Layout fixes
    FixLayouts();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::PlotPressed()
{
    std::cout<<"Starting Plotting"<<std::endl;

    // Retriving the time values 
    max_t   = ui->timBox->value();
    delta_t = ui->deltaBox->value();
    // Plotting Pre checks
    chart->removeSeries(series);
    // Creating Data series 
    // for (float i = 0; i < max_t; i += delta_t) 
    // {
    //  series->append(i, sin(i));
    // }

    // Series actions
    /////////////////
    series->setName("Sine Wave"); // Set the name for the series


    // Chart options
    ////////////////
    chart->addSeries(series);        // Adding series to chart 
    chart->createDefaultAxes();      //     
    // chart->setTitle("Sin Waves"); // Setting Title 
    chart->setMargins(QMargins(0, 0, 0, 0)); // Set your desired margin values here
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom); 

    // Adding Chart options
    // Enable both zooming and panning
    chartView->setRubberBand(QtCharts::QChartView::RectangleRubberBand);
    chartView->setDragMode(QtCharts::QChartView::ScrollHandDrag);

    // Adding the Plot to frame 
    FixLayouts();
    ui->plotFrame->layout()->addWidget(chartView);

    // Starting Timer
    timer->start(delta_t*1000);
}


void MainWindow::ClearPressed()
{
    // Clearing old series 
    series->clear();
}

void MainWindow::StopPressed()
{
    // Clearing old series 
    std::cout<<"Stopping Plotting"<<std::endl;
    timer->stop(); 
    ith_t = 0;
}


void MainWindow::UpdateChart()
{
    // Check if max time is reached 
    ith_t += delta_t;

    // Appending new data point
    series->append(ith_t, sin(ith_t));
    // Updating axis 
    chart->axisX()->setRange(0, max_t);
    chart->axisY()->setRange(-1, 1); 

    if(max_t<=ith_t)
    {
        StopPressed();
    }

}


void MainWindow::FixLayouts()
{
    // PLOT FRAME //
    //************//
    ui->plotFrame->setContentsMargins(0, 0, 0, 0);

    // BUTTON FRAME //
    //**************//
}
