#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListView>
#include <QScopedPointer>
#include <QComboBox>
#include <QLineEdit>

#include "repo/configrepo.h"
#include "repo/command.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centerWidget = nullptr;
    QVBoxLayout *mainLayout = nullptr;

    QScopedPointer<QHBoxLayout> firstRowContainer;
    QScopedPointer<QComboBox> deviceComboBox;
    QScopedPointer<QPushButton> refreshDeviceButton;
    QScopedPointer<QPushButton> debugFragmentButton;

    QScopedPointer<QComboBox> accountComboBox;
    QScopedPointer<QPushButton> accountButton;
    QScopedPointer<QHBoxLayout> secondContainer;

    QScopedPointer<QHBoxLayout> thirdRowContainer;
    QScopedPointer<QPushButton> deeplink;
    QScopedPointer<QLineEdit> deeplinkText;

    ConfigReopostory *configRepo = nullptr;
    QScopedPointer<Command> command;

    void init();
    void initUI(QWidget *parent);

    void showAccount();
    void onAccountButtonClicked();
    void showDebugFragment();
    void onDebugFragmentButtonClicked();

    void showDevices();
    void onRefreshDevicesClicked();

    void showDeeplink();
    void onExecuteDeepLink();
};
#endif // MAINWINDOW_H
