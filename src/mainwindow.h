#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QImage>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>
#include <QObject>
#include <QSettings>

#include "my_smart_ptr.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_open_file_triggered();

private:
    Ui::MainWindow *ui;

    const int maxFileNr = 5;

    my_smart_ptr<QLabel> imageLabel;
    my_smart_ptr<QMenu> fileMenu;
    my_smart_ptr<QMenu> recentFilesMenu;
    my_smart_ptr<QAction> openAction;
    QList<QAction *> recentFileActionList;
    QString currentFilePath;

    void openRecent();
    void createRecentMenu();
    void loadFile(const QString& filePath);

    void updateRecentActionList();
    void adjustForCurrentFile(const QString &filePath);
};
#endif // MAINWINDOW_H
