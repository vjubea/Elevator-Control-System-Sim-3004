QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ECS.cpp \
    Elevator.cpp \
    ElevatorBell.cpp \
    ElevatorDestButton.cpp \
    ElevatorDisplay.cpp \
    ElevatorDoor.cpp \
    Floor.cpp \
    FloorButton.cpp \
    FloorList.cpp \
    FloorRequests.cpp \
    Passenger.cpp \
    PassengerList.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ECS.h \
    Elevator.h \
    ElevatorBell.h \
    ElevatorDestButton.h \
    ElevatorDisplay.h \
    ElevatorDoor.h \
    Floor.h \
    FloorButton.h \
    FloorList.h \
    FloorRequests.h \
    Passenger.h \
    PassengerList.h \
    header.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
