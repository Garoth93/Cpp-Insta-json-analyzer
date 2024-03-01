#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <qtableview.h>
#include "engine.h"

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

    void init();

    QString selectDirectory();

    void populateNoFollowing();
    void popoluateNoFollower();
    void pulatePendinfRequestFollowing();

private:
    Ui::MainWindow *ui;

    Engine engine;

    QStandardItemModel * modelNoFollowing=nullptr, * modelNoFollower=nullptr;
    QTableView * tableViewNoFollowing=nullptr, * tableViewNoFollower=nullptr;

    QStandardItemModel * modelPendingFollowing=nullptr;
    QTableView * tablePendingFollowing=nullptr;
};
#endif // MAINWINDOW_H
