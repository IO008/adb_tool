#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListView>
#include <QScopedPointer>
#include <QComboBox>

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

    QScopedPointer<QComboBox> accountComboBox;
    QScopedPointer<QPushButton> accountButton;
    QScopedPointer<QHBoxLayout> accountLayout;

    ConfigReopostory *configRepo = nullptr;
    QScopedPointer<Command> command;

    void init();
    void initUI(QWidget *parent);

    void showAccount();
    void onAccountButtonClicked();
};
#endif // MAINWINDOW_H
