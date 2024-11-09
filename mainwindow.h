#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
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
    QPushButton *startButton;
    QLineEdit *passengerNameInput;
    QLineEdit *startFloorInput;
    QLineEdit *destinationFloorInput;
    QPushButton *addPassengerButton;
    std::vector<QLabel*> elevatorStateLabels;
    QTextEdit *passengerListDisplay;
    QStringList passengers;

    void startSimulation();
    void updateUI();

private slots:
    void on_startButton_clicked();
    void on_addPassengerButton_clicked();
};
#endif // MAINWINDOW_H
