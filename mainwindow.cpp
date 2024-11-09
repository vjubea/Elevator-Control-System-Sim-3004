#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QStringList>
#include "ECS.h"
#include "FloorList.h"

MainWindow::MainWindow(QWidget *parent) // Put other input in here
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup UI elements
    startButton = new QPushButton("Start Simulation", this);
    passengerNameInput = new QLineEdit(this);
    passengerNameInput->setPlaceholderText("Enter Passenger Name");
    startFloorInput = new QLineEdit(this);
    startFloorInput->setPlaceholderText("Enter Starting Floor");
    destinationFloorInput = new QLineEdit(this);
    destinationFloorInput->setPlaceholderText("Enter Destination Floor");
    addPassengerButton = new QPushButton("Add Passenger", this);
    passengerListDisplay = new QTextEdit(this);
    passengerListDisplay->setReadOnly(true);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(passengerNameInput);
    layout->addWidget(startFloorInput);
    layout->addWidget(destinationFloorInput);
    layout->addWidget(addPassengerButton);
    layout->addWidget(passengerListDisplay);
    layout->addWidget(startButton);

    // Add labels for each elevator state
    for (size_t i = 0; i < elevators->size(); ++i) {
        QLabel *elevatorLabel = new QLabel(this);
        elevatorStateLabels.push_back(elevatorLabel);
        layout->addWidget(elevatorLabel);
    }

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Connect signals to slots
    connect(startButton, SIGNAL (clicked()), this, SLOT (on_startButton_clicked()));
    connect(addPassengerButton, SIGNAL (clicked()), this,  SLOT (on_addPassengerButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addPassengerButton_clicked() {
    //TO CHANGE
    QString passengerName = passengerNameInput->text();
    QString startFloor = startFloorInput->text();
    QString destinationFloor = destinationFloorInput->text();
    if (!passengerName.isEmpty() && !startFloor.isEmpty() && !destinationFloor.isEmpty()) {
        QString passengerInfo =
                "Passenger: " + passengerName +
                " | Start Floor: " + startFloor +
                " | Destination Floor: " + destinationFloor;

        passengers << passengerInfo;
        passengerListDisplay->append(passengerInfo);
        // Clear input fields
        passengerNameInput->clear();
        startFloorInput->clear();
        destinationFloorInput->clear();
    }
}

void MainWindow::on_startButton_clicked() {
    // Stops allowing user to add Passengers
    passengerNameInput->hide();
    startFloorInput->hide();
    destinationFloorInput->hide();
    addPassengerButton->hide();

    passengerListDisplay->append("Starting simulation...");
    startSimulation();
}

void MainWindow::updateUI() {
    // TO CHANGE
    for (size_t i = 0; i < elevators->size(); ++i) {
        Elevator &elevator = (*elevators)[i];
        elevatorStateLabels[i]->setText(QString("Elevator %1: Floor %2, State: %3")
            .arg(elevator.getCarNum())
            .arg(elevator.getCurrFloorNum())
            .arg(elevator.isMoving() ? "moving" : "idle"));
    }
}

void MainWindow::startSimulation() {
    // Setup
    int timestep = 0;
    FloorList* floorList = new FloorList();
    for (int i = 1; i <= FLOOR_COUNT; i++)
        floorList->add_floor(new Floor(i));

    Floor* startFloor = floorList->get(START_FLOOR_IND);
    ECS* ecs = new ECS(ELEVATOR_COUNT, startFloor);
    Passenger* nextUnboarding = nullptr;
    Passenger* passenger = nullptr;
    string p_heading = "";
    Elevator* el = nullptr;
    Floor* elCurrFloor = nullptr;
    int elCurrFloorNum = -1;

    // UI should allow to add passengers, with all required values.
    PassengerList* passengers = new PassengerList();
    passengers->add_passenger(new Passenger("Name", 75.6f, startFloor, 5));
    for (int i = 0; i < PASSENGER_CAP; i++) {
        /*
        int floorButtonTime, startFloorNum, destFloorNum = -1;
        string direction = "";
        bool clicksOpenDoor, clicksCloseDoor, clicksHelpButton = false;

        passengers->add_passenger(new Passenger("Name", 75.6f, floorList->get(0), 5));
        */
    }

    // Simulation Loop
    while (passengers->all_reached_dest() != true) {
        updateUI();
        for (int i = 0; i < passengers->getNumPassengers(); i++) {
            // Check if they click any button at that timestep
            // If they do
            // passenger->press_floor_button()
        }

        // Each Elevator moves 1 floor
        for (int i = 0; i < ELEVATOR_COUNT; i++) {
            el = ecs->getElevator(i);
            elCurrFloorNum = el->getCurrFloor()->getFloorNum();

            if (el->getCurrDirection() == UP && elCurrFloorNum < floorList->getNumFloors()) {
                floorList->get(elCurrFloorNum)->detect_me(el); // check these
            }
            else if (el->getCurrDirection() == DOWN && elCurrFloorNum > 0) {
                floorList->get(elCurrFloorNum-2)->detect_me(el); // check these
            }
            else {
                cout << "Elevator #" << el->getCarNum() << " is IDLE"
                     << " on Floor #" << elCurrFloorNum << ".\n" << endl;
                el->stop();
            }
        }

        for (int i = 0; i < ELEVATOR_COUNT; i++) {
            el = ecs->getElevator(i);
            // Check if elevator did not stop
            if (el->getIsMoving() == true)
                continue;

            // Allow Passengers to Unboard Elevator
            elCurrFloor = el->getCurrFloor();
            nextUnboarding = nullptr;
            do {
                // Checks current elevator passengers
                nextUnboarding = el->getPassengers()->get_next_unboarding(elCurrFloor->getFloorNum());
                if (nextUnboarding != nullptr) {
                    nextUnboarding->unboard_elevator(timestep);
                }
            } while (nextUnboarding != nullptr);

            // Allow Passengers to Board Elevator
            passenger = nullptr;
            p_heading = nullptr;
            for (int i = 0; i < elCurrFloor->getNumPassengers(); i++) {
                passenger = elCurrFloor->getPassengers()->get_at(i);
                p_heading = passenger->getHeading();
                if (p_heading == REACHED_DEST)
                    continue;

                if (p_heading == el->getCurrDirection()) {
                    passenger->board_elevator(timestep);
                }
            }
            timestep++;
        }
    }
}
