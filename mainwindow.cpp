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
    addPassengerButton = new QPushButton("Add Passenger", this);
    passengerListDisplay = new QTextEdit(this);
    passengerListDisplay->setReadOnly(true);
    elevatorDisplay = new QTextEdit(this);
    elevatorDisplay->setReadOnly(true);

    passengerNameInput = new QLineEdit(this);
    passengerNameInput->setPlaceholderText("Enter Passenger Name");
    passengerNameInput->setFixedWidth(70);
    passengerWeightInput = new QLineEdit(this);
    passengerWeightInput->setPlaceholderText("Enter Passenger Weight");
    startFloorInput = new QLineEdit(this);
    startFloorInput->setPlaceholderText("Enter Starting Floor");
    destinationFloorInput = new QLineEdit(this);
    destinationFloorInput->setPlaceholderText("Enter Destination Floor");

    pressFloorButTimeInput = new QLineEdit(this);
    pressFloorButTimeInput->setPlaceholderText("Floor Button Press Time");
    pressOpenTimeInput = new QLineEdit(this);
    pressOpenTimeInput->setPlaceholderText("OpenDoor Button Press Time");
    pressCloseTimeInput = new QLineEdit(this);
    pressCloseTimeInput->setPlaceholderText("CloseDoor Button Press Time");
    pressHelpTimeInput = new QLineEdit(this);
    pressHelpTimeInput->setPlaceholderText("Help Button Press Time");
    passengerNumObstructsInput = new QLineEdit(this);
    passengerNumObstructsInput->setPlaceholderText("Enter Number of Obstructions");

    passengerNameInput->setFixedWidth(INPUT_FIELD_WIDTH);
    passengerWeightInput->setFixedWidth(INPUT_FIELD_WIDTH);
    startFloorInput->setFixedWidth(INPUT_FIELD_WIDTH);
    destinationFloorInput->setFixedWidth(INPUT_FIELD_WIDTH);
    pressFloorButTimeInput->setFixedWidth(INPUT_FIELD_WIDTH);
    pressOpenTimeInput->setFixedWidth(INPUT_FIELD_WIDTH);
    pressCloseTimeInput->setFixedWidth(INPUT_FIELD_WIDTH);
    pressHelpTimeInput->setFixedWidth(INPUT_FIELD_WIDTH);
    passengerNumObstructsInput->setFixedWidth(INPUT_FIELD_WIDTH);
    addPassengerButton->setFixedWidth(INPUT_FIELD_WIDTH);

    // Setup Floors, ECS and PassengeList
    timestep = 0;
    ecs = new ECS();
    floorList = new FloorList();
    for (int i = 0; i < FLOOR_COUNT; i++)
        floorList->add_floor(new Floor(i, ecs));
    passengers = new PassengerList();

    startFloor = floorList->get(START_FLOOR_IND);
    // Initializes elevators with their start floor
    ecs->set_elevator_start_floor(ELEVATOR_COUNT, startFloor);

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
    layout->addWidget(elevatorDisplay);
    layout->addWidget(startButton);

    centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    // Connect signals to slots
    connect(startButton, SIGNAL(clicked()), this, SLOT(on_startButton_clicked()));
    connect(addPassengerButton, SIGNAL(clicked()), this, SLOT(on_addPassengerButton_clicked()));

    // Initialize the timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateSimulation()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addPassengerButton_clicked()
{
    QString n, w, sfn, dfn;
    string name = n.toStdString();
    float weight;
    int startFloorNum, destFloorNum, floorButT = 0;
    bool ok = true;

    n = passengerNameInput->text();
    name = n.toStdString();
    w = passengerWeightInput->text();
    weight = w.toFloat(&ok);
    if (!ok) return;
    sfn = startFloorInput->text();
    startFloorNum = sfn.toInt(&ok);
    if (!ok) return;
    dfn = destinationFloorInput->text();
    destFloorNum = dfn.toInt(&ok);
    if (!ok) return;
    floorButT = pressFloorButTimeInput->text().toInt(&ok);
    if (!ok) return;
    /*
    openT = pressOpenTimeInput->text().toInt(&ok);
    if (!ok) return;
    closeT = pressCloseTimeInput->text().toInt(&ok);
    if (!ok) return;
    helpT = pressHelpTimeInput->text().toInt(&ok);
    if (!ok) return;
    numObs = passengerNumObstructsInput->text().toInt(&ok);
    if (!ok) return;
    */
    Floor* pFloor = floorList->get(startFloorNum-1);

    if (!n.isEmpty() && !w.isEmpty() && !sfn.isEmpty() && !dfn.isEmpty() && pFloor!= nullptr) {
        QString passengerInfo =
                "Passenger: " + n +
                " | Weight: " + w +
                " | Start Floor: " + sfn +
                " | Destination Floor: " + dfn;
        passengerListDisplay->append(passengerInfo);
        Passenger* p = new Passenger(name, weight, pFloor, destFloorNum, floorButT, NONE, NONE, NONE, NONE);
        passengers->add_passenger(p);
        startFloor->add_passenger(p);

        // Clear input fields
        passengerNameInput->clear();
        passengerWeightInput->clear();
        startFloorInput->clear();
        destinationFloorInput->clear();
        pressFloorButTimeInput->clear();
        pressOpenTimeInput->clear();
        pressCloseTimeInput->clear();
        pressHelpTimeInput->clear();
        passengerNumObstructsInput->clear();
    }
}
void MainWindow::on_startButton_clicked() {
    if (passengers->getNumPassengers() == 0)
        return;

    passengerListDisplay->append("\nStarting simulation...");
    // Start the simulation timer
    timer->start(3000);
}

void MainWindow::updateUI() {

    elevatorDisplay->clear();
    for (size_t i = 0; i < ELEVATOR_COUNT; i++) {
        Elevator* el = ecs->getElevator(i);
        QString elevatorInfo =
                "Elevator # " + QString::number(el->getCarNum()) +
                " | Curr Floor # " + QString::number(el->getCurrFloor()->getFloorNum()) +
                " | State: " +
                (el->getCurrDirection() != IDLE ? "Moving " + QString::fromStdString(el->getCurrDirection()): "IDLE");
        elevatorDisplay->append(elevatorInfo);
    }
}

void MainWindow::allow_passenger_action(PassengerList* pList, int &timestep) {
    timestep++;
    Passenger* passenger =  nullptr;
    for (int i = 0; i < pList->getNumPassengers(); ++i) {
        passenger = pList->get_at(i);
        if (timestep == passenger->getPressFloorButT()) {
            passenger->press_floor_button(timestep);
        }
        if (timestep == passenger->getPressOpenT()) {
            passenger->press_open_door_button(timestep);
        }
        if (timestep == passenger->getPressCloseT()) {
            passenger->press_close_door_button(timestep);
        }
        if (timestep == passenger->getPressHelpT()) {
            passenger->press_help_button(timestep);
        }
    }
}
void MainWindow::simulateElMovement(ECS* ecs, FloorList* floorList, int &timestep) {
    timestep++;
    Elevator* el = nullptr;
    int elCurrFloorNum = NONE;
    // Each Elevator moves 1 floor
    for (int i = 0; i < ELEVATOR_COUNT; i++) {
        el = ecs->getElevator(i);
        elCurrFloorNum = el->getCurrFloor()->getFloorNum();

        if (el->getCurrDirection() == UP && elCurrFloorNum < floorList->getNumFloors()) {
            floorList->get(elCurrFloorNum)->detect_me(el, timestep); // check these
        }
        else if (el->getCurrDirection() == DOWN && elCurrFloorNum > 1) {
            floorList->get(elCurrFloorNum-2)->detect_me(el, timestep); // check these
        }
        else {
            cout << "Elevator #" << el->getCarNum() << " is IDLE"
                 << " on Floor #" << elCurrFloorNum << ".\n" << endl;
            floorList->get(elCurrFloorNum-1)->detect_me(el, timestep);
        }
    }
}
void MainWindow::simulateElBoardUnboard(ECS* ecs, int &timestep) {
    timestep++;
    for (int i = 0; i < ELEVATOR_COUNT; i++) {
        Elevator* el = ecs->getElevator(i);
        // Checks if elevator is still
        if (el->getIsMoving() == true)
            return;

        // Allow Passengers to Unboard Elevator
        Floor* elCurrFloor = el->getCurrFloor();
        Passenger* nextUnboarding = nullptr;
        do {
            // Checks current elevator passengers
            nextUnboarding = el->getPassengers()->get_next_unboarding(elCurrFloor->getFloorNum());
            if (nextUnboarding != nullptr) {
                // Issue happens after
                nextUnboarding->unboard_elevator(timestep);
            }
        } while (nextUnboarding != nullptr);

        // Allow Passengers to Board Elevator
        Passenger* passenger = nullptr;
        string p_heading = "";
        int numObs = 0;

        for (int i = 0; i < elCurrFloor->getNumPassengers(); i++) {
            passenger = elCurrFloor->getPassengers()->get_at(i);
            if (passenger == nullptr) {
                qInfo("CPP_ERR: Passenger was found empty");
            }
            p_heading = passenger->getHeading();
            if (p_heading == REACHED_DEST || p_heading == "")
                continue;

            if (p_heading == el->getCurrDirection() || el->getCurrDirection() == IDLE) {
                passenger->board_elevator(timestep);
            }
            if (passenger->getNumObstructs() > 0) {
                numObs += passenger->getNumObstructs();
                passenger->no_more_obstructs();
            }
        }
        el->ready_to_move(numObs, timestep);
    }
}
void MainWindow::updateSimulation() {
    updateUI(); // Update the UI with the current simulation state
    // Simulation Loop
    // TODO: Check why Floor Button # is wrong for toggle off
    // TODO: Finish Safety and Timestep System
    // TODO: Take video of 7 scenarios
    if (passengers->all_reached_dest()) {
        timer->stop();
        passengerListDisplay->append("Simulation completed.");
        return;
    }
    // Run simulation for one timestep
    allow_passenger_action(passengers, timestep);

    simulateElMovement(ecs, floorList, timestep);

    allow_passenger_action(passengers, timestep);

    simulateElBoardUnboard(ecs, timestep);

    allow_passenger_action(passengers, timestep);

    timer->start(3000);
}
