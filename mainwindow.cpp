#include "mainwindow.h"

#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(800, 600);
    this->setWindowTitle("adb tool");
    init();
    initUI(parent);
}

MainWindow::~MainWindow()
{
    delete centerWidget;
    delete mainLayout;
    delete configRepo;
}

void MainWindow::init()
{
    configRepo = new ConfigReopostory();
    QString configPath = QDir::homePath() + "/Documents/self/qt_project/adb_tool/config/config.json";
    configRepo->readConfig(configPath);
}

void MainWindow::initUI(QWidget *parent)
{
    centerWidget = new QWidget();
    mainLayout = new QVBoxLayout(centerWidget);

    showAccount();

    centerWidget->setLayout(mainLayout);

    setCentralWidget(centerWidget);
}

void MainWindow::showAccount()
{
    accountView = new QListView();
    accountView->setModel(configRepo->getUserListModel());
    accountView->show();
    mainLayout->addWidget(accountView);
}
