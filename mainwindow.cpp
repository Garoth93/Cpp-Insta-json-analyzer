#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    this->setWindowTitle("Instagram json data analyzer");

    tableViewNoFollowing = ui->tableViewNoFollowing;
    tableViewNoFollower = ui->tableViewNoFollower;
    tablePendingFollowing = ui->tablePendingRequest;

    ui->pb_choseDirectory->setIcon(QIcon(":/icons/directory.png"));
    connect(ui->pb_choseDirectory, &QPushButton::clicked, [=](){
        QString dir = selectDirectory()+"/";
        engine.setPathDirectoryFile(dir);
        ui->label_directory->setText(dir);
    });

    ui->pb_eleborate->setIcon(QIcon(":/icons/process.png"));
    connect(ui->pb_eleborate, &QPushButton::clicked, [=](){
        engine.init();
        populateNoFollowing();
        popoluateNoFollower();
        pulatePendinfRequestFollowing();
    });
}

QString MainWindow::selectDirectory()
{
    QString desktopLocation = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString directory = QFileDialog::getExistingDirectory(this,
                                                          tr("Seleziona una directory"),
                                                          desktopLocation,
                                                          QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog);

    return  directory;
}

void MainWindow::populateNoFollowing()
{
    if(modelNoFollowing)
        modelNoFollowing->deleteLater();
    modelNoFollowing=new QStandardItemModel();
    QStringList titHeader;
    titHeader << "NAME" << "HREF" << "DATA";
    modelNoFollowing->setHorizontalHeaderLabels(titHeader);
    tableViewNoFollowing->setModel(modelNoFollowing);

    foreach(Profile item,engine.getProfileManagement()->getDontFollowingList())
    {
        QList <QStandardItem *> lItemS;
        lItemS << new QStandardItem(item.getName()) << new QStandardItem(item.getHref()) << new QStandardItem(item.getDateTime().toString("dd-MM-yyyy hh:mm"));
        modelNoFollowing->appendRow(lItemS);
    }

    tableViewNoFollowing->resizeColumnsToContents();
}

void MainWindow::popoluateNoFollower()
{
    if(modelNoFollower)
        modelNoFollower->deleteLater();
    modelNoFollower=new QStandardItemModel();
    QStringList titHeader;
    titHeader << "NAME" << "HREF" << "DATA";
    modelNoFollower->setHorizontalHeaderLabels(titHeader);
    tableViewNoFollower->setModel(modelNoFollower);

    foreach(Profile item,engine.getProfileManagement()->getDontFollowerList())
    {
        QList <QStandardItem *> lItemS;
        lItemS << new QStandardItem(item.getName()) << new QStandardItem(item.getHref()) << new QStandardItem(item.getDateTime().toString("dd-MM-yyyy hh:mm"));
        modelNoFollower->appendRow(lItemS);
    }

    tableViewNoFollower->resizeColumnsToContents();
}

void MainWindow::pulatePendinfRequestFollowing()
{
    if(modelPendingFollowing)
        modelPendingFollowing->deleteLater();
    modelPendingFollowing=new QStandardItemModel();
    QStringList titHeader;
    titHeader << "NAME" << "HREF" << "DATA";
    modelPendingFollowing->setHorizontalHeaderLabels(titHeader);
    tablePendingFollowing->setModel(modelPendingFollowing);

    foreach(Profile item,engine.getProfileManagement()->getPendinFollowingRequestList())
    {
        QList <QStandardItem *> lItemS;
        lItemS << new QStandardItem(item.getName()) << new QStandardItem(item.getHref()) << new QStandardItem(item.getDateTime().toString("dd-MM-yyyy hh:mm"));
        modelPendingFollowing->appendRow(lItemS);
    }

    tablePendingFollowing->resizeColumnsToContents();
}
