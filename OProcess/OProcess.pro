
TEMPLATE = app
QT  += axserver
QT += widgets


RC_FILE  = oprocess.rc

# install

#target.path = $$[QT_INSTALL_EXAMPLES]/activeqt/comapp
#target.path =
#INSTALLS += target

HEADERS += \
    oprocess.h

SOURCES += \
    oprocess.cpp \
    main.cpp

RESOURCES +=
