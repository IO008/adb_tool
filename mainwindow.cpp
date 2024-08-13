#include "mainwindow.h"

#include <QDir>
#include <QDebug>
#include <QProcess>

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
    command.reset(new Command());
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
    accountLayout.reset(new QHBoxLayout());
    accountButton.reset(new QPushButton("input"));
    accountComboBox.reset(new QComboBox());

    foreach (const QString &userName, *configRepo->getUserNameList())
    {
        accountComboBox->addItem(userName);
    }
    accountLayout.data()->addWidget(accountComboBox.data());
    accountLayout.data()->addWidget(accountButton.data());
    mainLayout->addLayout(accountLayout.data());

    connect(accountButton.data(), &QPushButton::clicked, this, &MainWindow::onAccountButtonClicked);
}

void MainWindow::onAccountButtonClicked()
{
    qDebug() << "onAccountButtonClicked";
    QList<QString> devices = command->getDevices();
    foreach (const QString &device, devices)
    {
        qDebug() << device;
    }
}
