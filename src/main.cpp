#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("PhotoViewer");
    app.setOrganizationName("PhotoViewer");
    MainWindow window;
    window.show();

    return app.exec();
}
