#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListView>


#include "repo/configrepo.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centerWidget = nullptr;
    QVBoxLayout *mainLayout = nullptr;
    QListView *accountView = nullptr;
    QStringListModel *model = nullptr;

    ConfigReopostory *configRepo = nullptr;

    void init();
    void initUI(QWidget *parent);
    void showAccount();
};
#endif // MAINWINDOW_H
