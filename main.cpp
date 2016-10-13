#include <QtGui/QApplication>
#include <QDeclarativeItem>                     // for root object
#include "qmlapplicationviewer.h"
#include "hextool.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    HexTool *hextool;

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/n9hextool/main.qml"));
    viewer.showExpanded();

    // get the QML root object for signal-slot connections
    QObject *qml = viewer.rootObject();

    // Create the back-end processor and pass in the root object.
    // Make viewer the parent object.
    hextool = new HexTool(qml, &viewer);

    // Catch application exit to save the settings
    QObject::connect(QCoreApplication::instance(),SIGNAL(aboutToQuit()),
        hextool,SLOT(closeEvent()));

    return app->exec();
}
