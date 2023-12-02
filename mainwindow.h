#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;
    QTimer* black_timer = new QTimer(this);
    QTimer* white_timer = new QTimer(this);
    QTimer* sec_counter = new QTimer(this);
    QTime zero_time = QTime(0, 0);
    int max_time = 0;
    int white_remains = 0;
    int black_remains = 0;

    void initTimers(int max_time);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateTimer();
    void gameTimeout();
    void on_start_button_clicked();
    void on_switch_button_clicked();
};
#endif // MAINWINDOW_H
