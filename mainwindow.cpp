#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTimers(int max_time)
{
    for (auto timer: {black_timer, white_timer}){
        timer->setTimerType(Qt::PreciseTimer);
        timer->setInterval(max_time);
        connect(timer, &QTimer::timeout, this, &MainWindow::gameTimeout);
    }
    sec_counter->setTimerType(Qt::PreciseTimer);
    sec_counter->setInterval(1000);
    connect(sec_counter, &QTimer::timeout, this, &MainWindow::updateTimer);
    ui->label->setText(zero_time.addMSecs(max_time).toString("mm:ss"));
    ui->label_2->setText(zero_time.addMSecs(max_time).toString("mm:ss"));
    black_remains = max_time;
    white_remains = max_time;
}

void MainWindow::updateTimer()
{
    QLabel* label = black_timer->isActive() ? ui->label : ui->label_2;
    int rem = black_timer->isActive() ? black_timer->remainingTime() : white_timer->remainingTime();
    label->setText(zero_time.addMSecs(rem).toString("mm:ss"));
}

void MainWindow::gameTimeout()
{
    black_timer->stop();
    white_timer->stop();
    sec_counter->stop();
    ui->label->setText(zero_time.addMSecs(max_time).toString("mm:ss"));
    ui->label_2->setText(zero_time.addMSecs(max_time).toString("mm:ss"));
}

void MainWindow::on_start_button_clicked()
{
    max_time = ui->lineEdit->text().toInt()*60000;
    initTimers(max_time);
    white_timer->start();
    sec_counter->start();
}

void MainWindow::on_switch_button_clicked()
{
    if (black_timer->isActive()){
        black_remains = black_timer->remainingTime();
        black_timer->stop();
        white_timer->start(white_remains);
    }
    else{
        white_remains = white_timer->remainingTime();
        white_timer->stop();
        black_timer->start(black_remains);
    }
}
