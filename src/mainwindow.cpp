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
    timer_updateChart = new QTimer(this);
    connect(timer_updateChart, &QTimer::timeout, this, &MainWindow::UpdateChart);
    // Init the Sample Timer 
    timer_SampleData = new QTimer(this);
    connect(timer_SampleData, &QTimer::timeout, this, &MainWindow::SampleData);


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
    // Updating axis 
    chart->axisX()->setRange(0, max_t);
    chart->axisY()->setRange(-1, 1); 
    // Adding Chart options
    // Enable both zooming and panning
    chartView->setRubberBand(QtCharts::QChartView::RectangleRubberBand);
    chartView->setDragMode(QtCharts::QChartView::ScrollHandDrag);
    chartView->setRenderHint(QPainter::Antialiasing, true); // Enable antialiasing for smoother rendering

    // Adding the Plot to frame 
    FixLayouts();
    ui->plotFrame->layout()->addWidget(chartView);

    // Starting Chart Timer
    start_time = std::chrono::high_resolution_clock::now();
    timer_updateChart->start(delta_t_update*1000);

    // Starting data update
    timer_SampleData->start(delta_t*1000);


}


void MainWindow::ClearPressed()
{
    // Clearing old series 
    series->clear();
    _timeData.clear();
    _sampledData.clear();
}

void MainWindow::StopPressed()
{
    // Clearing old series 
    std::cout<<"Stopping Plotting"<<std::endl;
    // timer_updateChart->stop(); 
    timer_SampleData->stop(); 

    jth_t_update = 0;
    ith_t = 0;
    if(sampledData.size() == 0)
    {
        // Stopping update timer
        timer_updateChart->stop(); 
        // Clearing Vectors
        timeData.clear();
        sampledData.clear();

        // Stop execution timer
        auto end_time = std::chrono::high_resolution_clock::now();

        // Clearing Vectors 
        // Calculate the duration in milliseconds
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "Function execution time: " << duration.count() << " milliseconds" << std::endl;
    }
}


void MainWindow::UpdateChart()
{
    // Incrementing ith_t_update
    jth_t_update += delta_t_update;

    // Saving collected data points and clearing vectors
    std::vector<double> jth_sampledData = std::move(sampledData); 
    std::vector<double> jth_timeData    = std::move(timeData);


    // Updating Plot 
    size_t size_data = jth_sampledData.size();
    size_t size_time = jth_timeData.size();

    std::copy(jth_sampledData.begin(), jth_sampledData.end(), std::back_inserter(_sampledData));
    std::copy(jth_timeData.begin(), jth_timeData.end(), std::back_inserter(_timeData));

    if(size_data != size_time)
    {
        std::cout<< "ERROR SIZE MISTMATCH" << std::endl;
        return;
    }
    // Updating the size vectors 
    // Sporatically Append data to limit size
    for (size_t i = 0; i < size_data; ++i) {
        if ((i + 1) % 300 == 0)
        { // Add 1 to adjust for 1-based indexing
            series->append(jth_timeData[i], jth_sampledData[i]);
        }
    }
    std::cout<< "------------------------------"<< std::endl;
    std::cout<< "Sample size: "<<size_data << std::endl;
    std::cout<< "Data size  : "<<_sampledData.size() << std::endl;
    std::cout<< "Series size: "<<series->count() << std::endl;
    if(max_t<=jth_t_update)
    {
        StopPressed();
    }

}

void MainWindow::SampleData()
{
    // Incrementing ith_t
    ith_t += delta_t;

    // Adding data Point 
    timeData.push_back(ith_t);
    sampledData.push_back(sin(ith_t));

    if(max_t<=ith_t)
    {
        timer_SampleData->stop();
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
