#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QTimer>
class ECS;
class FloorList;
class Floor;
class PassengerList;

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
    QPushButton *addPassengerButton;
    QTextEdit *passengerListDisplay;
    QTextEdit *elevatorDisplay;

    QLineEdit *passengerNameInput;
    QLineEdit *passengerWeightInput;
    QLineEdit *startFloorInput;
    QLineEdit *destinationFloorInput;
    QLineEdit *pressFloorButTimeInput;
    QLineEdit *pressOpenTimeInput;
    QLineEdit *pressCloseTimeInput;
    QLineEdit *pressHelpTimeInput;
    QLineEdit *passengerNumObstructsInput;
    QWidget *centralWidget;

    ECS* ecs;
    PassengerList* passengers;
    FloorList* floorList;
    Floor* startFloor;

    QTimer *timer;
    int timestep;

    void allow_passenger_action(PassengerList*, int&);
    void simulateElMovement(ECS*, FloorList*, int&);
    void simulateElBoardUnboard(ECS*, int&);
    void updateUI();

private slots:
    void on_startButton_clicked();
    void on_addPassengerButton_clicked();
    void updateSimulation();
};
#endif // MAINWINDOW_H
