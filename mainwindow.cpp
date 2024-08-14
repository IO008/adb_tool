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

    firstRowContainer.reset(new QHBoxLayout());

    showDevices();
    showPackageNames();
    showUninstallButton();
    showDebugFragment();

    firstRowContainer->addStretch();
    mainLayout->addLayout(firstRowContainer.data());

    secondContainer.reset(new QHBoxLayout());

    showAccount();
    showOTPButton();

    secondContainer->addStretch();
    mainLayout->addLayout(secondContainer.data());

    thirdRowContainer.reset(new QHBoxLayout());

    showDeeplink();
    showCustomCommand();

    thirdRowContainer->addStretch();
    mainLayout->addLayout(thirdRowContainer.data());

    mainLayout->addStretch();
    centerWidget->setLayout(mainLayout);
    setCentralWidget(centerWidget);
}

void MainWindow::showAccount()
{
    accountButton.reset(new QPushButton("input"));
    accountComboBox.reset(new QComboBox());

    foreach (const QString &userName, *configRepo->getUserNameList())
    {
        accountComboBox->addItem(userName);
    }
    secondContainer.data()->addWidget(accountComboBox.data());
    secondContainer.data()->addWidget(accountButton.data());

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

void MainWindow::showOTPButton()
{
    networkManager.reset(new NetworkManager());
    otpButton.reset(new QPushButton("get otp code"));
    secondContainer->addWidget(otpButton.data());

    connect(otpButton.data(), &QPushButton::clicked, this, &MainWindow::onExcuteOTP);
    connect(networkManager.data(), &NetworkManager::requestFinished, this, &MainWindow::requestFinished);
}

void MainWindow::requestFinished(const QString &result)
{
    otpButton->setEnabled(true);
    qDebug() << "MainWindow requestFinished" << result;
}

void MainWindow::onExcuteOTP()
{
    otpButton->setEnabled(false);
    networkManager->makeRequest(QUrl("https://www.google.com"));
}

void MainWindow::showDevices()
{
    deviceComboBox.reset(new QComboBox());
    refreshDeviceButton.reset(new QPushButton("refresh"));

    QList<QString> devices = command->getDevices();

    foreach (const QString &device, devices)
    {
        deviceComboBox->addItem(device);
    }
    firstRowContainer->addWidget(deviceComboBox.data());
    firstRowContainer->addWidget(refreshDeviceButton.data());

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

void MainWindow::showPackageNames()
{
    packageNameComboBox.reset(new QComboBox());
    packageNameComboBox->clear();
    packageNameComboBox->addItems(configRepo->getPackageNames());
    firstRowContainer->addWidget(packageNameComboBox.data());
}

void MainWindow::showUninstallButton()
{
    uninstallButton.reset(new QPushButton("uninstall"));
    firstRowContainer->addWidget(uninstallButton.data());

    connect(uninstallButton.data(), &QPushButton::clicked, this, &MainWindow::onExcuteUninstall);
}

void MainWindow::onExcuteUninstall()
{
    command->uninstall(deviceComboBox->currentText(), packageNameComboBox->currentText());
}

void MainWindow::showDebugFragment()
{
    debugFragmentButton.reset(new QPushButton("debug fragment"));
    firstRowContainer->addWidget(debugFragmentButton.data());

    connect(debugFragmentButton.data(), &QPushButton::clicked, this, &MainWindow::onDebugFragmentButtonClicked);
}

void MainWindow::onDebugFragmentButtonClicked()
{
    command->debugFragment(deviceComboBox->currentText());
}

void MainWindow::showDeeplink()
{
    deeplinkText.reset(new QLineEdit());
    deeplinkButton.reset(new QPushButton("deeplink"));
    thirdRowContainer->addWidget(deeplinkText.data());
    thirdRowContainer->addWidget(deeplinkButton.data());
    connect(deeplinkButton.data(), &QPushButton::clicked, this, &MainWindow::onExecuteDeepLink);
}

void MainWindow::onExecuteDeepLink()
{
    QString text = deeplinkText->text();
    command->deeplink(deviceComboBox->currentText(), text, packageNameComboBox->currentText());
}

void MainWindow::showCustomCommand()
{
    customCommandText.reset(new QLineEdit());
    customCommandButton.reset(new QPushButton("custom command"));
    thirdRowContainer->addWidget(customCommandText.data());
    thirdRowContainer->addWidget(customCommandButton.data());
    connect(customCommandButton.data(), &QPushButton::clicked, this, &MainWindow::onExecuteCustomCommand);
}

void MainWindow::onExecuteCustomCommand()
{
    command->customCommand(deviceComboBox->currentText(), customCommandText->text());
}