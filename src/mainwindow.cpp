#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    imageLabel.reset(ui->label_and_photo);
    recentFilesMenu.reset(ui->open_file_recently);

    createRecentMenu();
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_open_file_triggered() {
    QString file_path = QFileDialog::getOpenFileName(this,
                                                     "Выбрать файл",
                                                     "C:/Users/zarion/Pictures",
                                                     "All Files (*.*);; BMP (*.bmp);; JPEG (*.jpg;*.jpeg);; PNG (*.png);");
    if (!file_path.isEmpty()) {
        loadFile(file_path);
    }
}

void MainWindow::loadFile(const QString &file_path){
    QFile file(file_path);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this,
                             "Ошибка загрузки файла",
                             tr("Не удалось найти файл: %1.")
                                 .arg(file_path));
        return;
    }

    my_smart_ptr<QImage> image_ptr(new QImage(file_path));
    if (image_ptr->format() == QImage::Format_Invalid) {
        QMessageBox::warning(this,
                             "Ошибка загрузки файла",
                             tr("Не удалось загрузить файл: %1.")
                                 .arg(file_path));
        return;
    }

    imageLabel->setPixmap(QPixmap::fromImage(image_ptr->scaled(image_ptr->size().width(), image_ptr->size().height(), Qt::IgnoreAspectRatio), Qt::AutoColor));
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->show();

    resize(image_ptr->size().width(), image_ptr->size().height());

    adjustForCurrentFile(file_path);
}


void MainWindow::openRecent() {
    QAction *action = qobject_cast<QAction *>(sender());
    if (action != nullptr) {
        loadFile(action->data().toString());
    }
}


void MainWindow::createRecentMenu() {
    QAction* recentFileAction = nullptr;
    for (int i = 0; i < maxFileNr; ++i) {
        recentFileAction = new QAction(this);
        recentFileAction->setVisible(false);
        QObject::connect(recentFileAction, &QAction::triggered, this, &MainWindow::openRecent);
        recentFileActionList.append(recentFileAction);

        recentFilesMenu->addAction(recentFileActionList.at(i));
    }

    updateRecentActionList();
}



void MainWindow::adjustForCurrentFile(const QString &filePath){
    currentFilePath = filePath;
    setWindowFilePath(currentFilePath);

    QSettings settings;

    QStringList recentFilePaths = settings.value("PhotoViewer").toStringList();
    recentFilePaths.removeAll(filePath);
    recentFilePaths.prepend(filePath);
    while (recentFilePaths.size() > maxFileNr) {
        recentFilePaths.removeLast();
    }
    settings.setValue("PhotoViewer", recentFilePaths);

    updateRecentActionList();
}


void MainWindow::updateRecentActionList(){
    QSettings settings;

    QStringList recentFilePaths = settings.value("PhotoViewer").toStringList();

    int itEnd = 0;
    if (recentFilePaths.size() <= maxFileNr) {
        itEnd = recentFilePaths.size();
    } else {
        itEnd = maxFileNr;
    }

    for (int i = 0; i < itEnd; ++i) {
        QString strippedName = QFileInfo(recentFilePaths.at(i)).fileName();
        recentFileActionList.at(i)->setText(strippedName);
        recentFileActionList.at(i)->setData(recentFilePaths.at(i));
        recentFileActionList.at(i)->setVisible(true);
    }

    for (int i = itEnd; i < maxFileNr; ++i)
        recentFileActionList.at(i)->setVisible(false);
}
