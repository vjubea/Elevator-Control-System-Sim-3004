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
    passengerWeightInput = new QLineEdit(this);
    passengerWeightInput->setPlaceholderText("Enter Passenger Weight");
    passengerNumObstructsInput = new QLineEdit(this);

    startFloorInput->setPlaceholderText("Enter Starting Floor");
    destinationFloorInput = new QLineEdit(this);
    destinationFloorInput->setPlaceholderText("Enter Destination Floor");
    addPassengerButton = new QPushButton("Add Passenger", this);

    pressFloorButTimeInput->setPlaceholderText("Floor Button Press Time");
    pressFloorButTimeInput = new QLineEdit(this);
    pressOpenTimeInput->setPlaceholderText("OpenDoor Button Press Time");
    pressOpenTimeInput = new QLineEdit(this);
    pressCloseTimeInput->setPlaceholderText("CloseDoor Button Press Time");
    pressCloseTimeInput = new QLineEdit(this);
    pressHelpTimeInput->setPlaceholderText("Help Button Press Time");
    pressHelpTimeInput = new QLineEdit(this);

    passengerNumObstructsInput->setPlaceholderText("Enter Number of Obstructions");
    startFloorInput = new QLineEdit(this);

    passengerListDisplay = new QTextEdit(this);
    passengerListDisplay->setReadOnly(true);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    // Passenger Inputs
    layout->addWidget(passengerNameInput);
    layout->addWidget(passengerWeightInput);
    layout->addWidget(startFloorInput);
    layout->addWidget(destinationFloorInput);
    layout->addWidget(pressFloorButTimeInput);
    layout->addWidget(pressOpenTimeInput);
    layout->addWidget(pressCloseTimeInput);
    layout->addWidget(pressHelpTimeInput);
    layout->addWidget(passengerNumObstructsInput);

    layout->addWidget(addPassengerButton);
    layout->addWidget(passengerListDisplay);
    layout->addWidget(startButton);

    // Setup Floors and ECS
    floorList = new FloorList();
    for (int i = 1; i <= FLOOR_COUNT; i++)
        floorList->add_floor(new Floor(i));
    startFloor = floorList->get(START_FLOOR_IND);
    ecs = new ECS(ELEVATOR_COUNT, startFloor);

    // Add labels for each elevator state
    for (size_t i = 0; i < ELEVATOR_COUNT; ++i) {
        QLabel* elevatorLabel = new QLabel(this);
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

void MainWindow::on_addPassengerButton_clicked()
{
    QString name = passengerNameInput->text();
    QString weight = passengerWeightInput->text();
    QString startFloorNum = startFloorInput->text();
    QString destFloorNum = destinationFloorInput->text();
    QString floorButT = pressFloorButTimeInput->text();
    QString openT = pressOpenTimeInput->text();
    QString closeT = pressCloseTimeInput->text();
    QString helpT = pressHelpTimeInput->text();
    QString numObs = passengerNumObstructsInput->text();

    if (!name.isEmpty() && !startFloorNum.isEmpty() && !destFloorNum.isEmpty()) {
        QString passengerInfo =
                "Passenger: " + name +
                " | Start Floor: " + startFloorNum +
                " | Destination Floor: " + destFloorNum;

        passengerListDisplay->append(passengerInfo);
        passengers->add_passenger(
                    new Passenger(
                        name, weight, startFloorNum, destFloorNum, floorButT, openT, closeT, helpT, numObs
                        ));
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
    startSimulation(passengers);
}

void MainWindow::updateUI() {
    // TO CHANGE
    for (size_t i = 0; i < ELEVATOR_COUNT; ++i) {
        Elevator* el = ecs->getElevator(i);
        elevatorStateLabels[i]->setText(QString("Elevator %1 | Current Floor %2 | State: %3")
            .arg(el->getCarNum())
            .arg(el->getCurrFloor()->getFloorNum())
            .arg(el->getIsMoving() ? "moving" : "idle"));
    }
}

void allow_passenger_action(PassengerList* pList, int* timestep) {
    Passenger* passenger =  nullptr;
    for (int i = 0; i < pList->getNumPassengers(); ++i) {
        passenger = pList->get_at(i);
        if (*timestep == passenger->getPressFloorButT() - 1) {
            passenger->press_floor_button(timestep);
        }
        else if (*timestep == passenger->getPressOpenT() - 1) {
            passenger->press_open_door_button(timestep);
        }
        else if (*timestep == passenger->getPressCloseT() - 1) {
            passenger->press_close_door_button(timestep);
        }
        else if (*timestep == passenger->getPressHelpT() - 1) {
            passenger->press_help_button(timestep);
        }
    }
}
void MainWindow::startSimulation(PassengerList* people) {
    PassengerList* passengers = people;
    if (passengers->getNumPassengers() == 0)
        return;
    // Setup
    int timestep = 0;
    Passenger* nextUnboarding = nullptr;
    Passenger* passenger = nullptr;
    string p_heading = "";
    Elevator* el = nullptr;
    Floor* elCurrFloor = nullptr;
    int elCurrFloorNum = -1;

    // Simulation Loop
    while (passengers->all_reached_dest() != true) {
        updateUI();

        allow_passenger_action(passengers, &timestep);

        // Each Elevator moves 1 floor
        for (int i = 0; i < ELEVATOR_COUNT; i++) {
            el = ecs->getElevator(i);
            elCurrFloorNum = el->getCurrFloor()->getFloorNum();

            if (el->getCurrDirection() == UP && elCurrFloorNum < floorList->getNumFloors()) {
                floorList->get(elCurrFloorNum)->detect_me(el, &timestep); // check these
            }
            else if (el->getCurrDirection() == DOWN && elCurrFloorNum > 0) {
                floorList->get(elCurrFloorNum-2)->detect_me(el, &timestep); // check these
            }
            else {
                cout << "Elevator #" << el->getCarNum() << " is IDLE"
                     << " on Floor #" << elCurrFloorNum << ".\n" << endl;
                el->stop(&timestep);
            }
        }
        allow_passenger_action(passengers, &timestep);

        // Each Elevator allows Unboarding and Boarding
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
                    nextUnboarding->unboard_elevator(&timestep);
                }
            } while (nextUnboarding != nullptr);

            // Allow Passengers to Board Elevator
            passenger = nullptr;
            p_heading = nullptr;
            int numObs = 0;
            for (int i = 0; i < elCurrFloor->getNumPassengers(); i++) {
                passenger = elCurrFloor->getPassengers()->get_at(i);
                p_heading = passenger->getHeading();
                if (p_heading == REACHED_DEST)
                    continue;

                if (p_heading == el->getCurrDirection()) {
                    passenger->board_elevator(&timestep);
                }
                if (passenger->getNumObstructs() > 0) {
                    numObs += passenger->getNumObstructs();
                    passenger->no_more_obstructs();
                }
            }
            el->ready_to_move(numObs, &timestep);
        }
        allow_passenger_action(passengers, &timestep);
    }
}
