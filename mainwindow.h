#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListView>
#include <QScopedPointer>
#include <QComboBox>
#include <QLineEdit>
#include <QCloseEvent>

#include "repo/configrepo.h"
#include "repo/command.h"
#include "repo/otp_code_repo.h"
#include "net/networkmanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QScopedPointer<QWidget> centerWidget;
    QScopedPointer<QVBoxLayout> mainLayout;

    QScopedPointer<QHBoxLayout> firstRowContainer;

    QScopedPointer<QComboBox> deviceComboBox;
    QScopedPointer<QPushButton> refreshDeviceButton;
    QScopedPointer<QPushButton> debugFragmentButton;
    QScopedPointer<QComboBox> packageNameComboBox;
    QScopedPointer<QPushButton> uninstallButton;

    QScopedPointer<QHBoxLayout> secondContainer;

    QScopedPointer<QComboBox> accountComboBox;
    QScopedPointer<QPushButton> accountButton;
    QScopedPointer<QPushButton> otpButton;

    QScopedPointer<QHBoxLayout> thirdRowContainer;

    QScopedPointer<QPushButton> deeplinkButton;
    QScopedPointer<QLineEdit> deeplinkText;

    QScopedPointer<QLineEdit> customCommandText;
    QScopedPointer<QPushButton> customCommandButton;

    QScopedPointer<ConfigReopostory> configRepo;
    QScopedPointer<Command> command;
    QScopedPointer<OtpCodeRepo> otpCodeRepo;

    QScopedPointer<NetworkManager> networkManager;

    void init();
    void initUI();

    void showAccount();
    void onAccountButtonClicked();
    void showOTPButton();
    void onExcuteOTP();
    void showDebugFragment();
    void onDebugFragmentButtonClicked();

    void showDevices();
    void onRefreshDevicesClicked();

    void showPackageNames();

    void showUninstallButton();
    void onExcuteUninstall();

    void showDeeplink();
    void onExecuteDeepLink();

    void showCustomCommand();
    void onExecuteCustomCommand();

private slots:
    void requestFinished(const QString &result);
};
#endif // MAINWINDOW_H
