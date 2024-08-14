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

    showDevices();
    showAccount();

    mainLayout->addStretch();
    centerWidget->setLayout(mainLayout);

    setCentralWidget(centerWidget);
}

void MainWindow::showAccount()
{
    accountContainer.reset(new QHBoxLayout());
    accountButton.reset(new QPushButton("input"));
    accountComboBox.reset(new QComboBox());

    foreach (const QString &userName, *configRepo->getUserNameList())
    {
        accountComboBox->addItem(userName);
    }
    accountContainer.data()->addWidget(accountComboBox.data());
    accountContainer.data()->addWidget(accountButton.data());
    mainLayout->addLayout(accountContainer.data());

    accountContainer->addStretch();

    connect(accountButton.data(), &QPushButton::clicked, this, &MainWindow::onAccountButtonClicked);
}

void MainWindow::onAccountButtonClicked()
{
    command->nextFocus(deviceComboBox->currentText());
    command->inputText(deviceComboBox->currentText(), accountComboBox->currentText());
    command->nextFocus(deviceComboBox->currentText());
    command->inputText(deviceComboBox->currentText(), configRepo->getPassword(accountComboBox->currentText()));
    command->hideKeyboard(deviceComboBox->currentText());
}

void MainWindow::showDevices()
{
    deviceContainer.reset(new QHBoxLayout());
    deviceComboBox.reset(new QComboBox());
    refreshDeviceButton.reset(new QPushButton("refresh"));

    QList<QString> devices = command->getDevices();

    foreach (const QString &device, devices)
    {
        deviceComboBox->addItem(device);
    }
    deviceContainer->addWidget(deviceComboBox.data());
    deviceContainer->addWidget(refreshDeviceButton.data());

    deviceContainer->addStretch();
    mainLayout->addLayout(deviceContainer.data());

    connect(refreshDeviceButton.data(), &QPushButton::clicked, this, &MainWindow::onRefreshDevicesClicked);
}

void MainWindow::onRefreshDevicesClicked()
{
    deviceComboBox->clear();
    QList<QString> devices = command->getDevices();
    foreach (const QString &device, devices)
    {
        deviceComboBox->addItem(device);
    }
}
