QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Lab-2/BinaryTree.cpp \
    ../Lab-2/Node.cpp \
    ../Lab-3/SearchTree.cpp \
    TreeNodeGraphicsItem.cpp \
    main.cpp \
    treewidget.cpp

HEADERS += \
    ../Lab-2/BinaryTree.h \
    ../Lab-2/Node.h \
    ../Lab-3/SearchTree.h \
    TreeNodeGraphicsItem.h \
    treewidget.h

FORMS += \
    treewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
