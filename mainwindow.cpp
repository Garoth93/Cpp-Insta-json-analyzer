#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>
#include <QDesktopServices>
#include <QMessageBox>

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

    engine.init();

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

    ui->pb_txtDontFollow->setIcon(QIcon(":/icons/csv.png"));
    ui->pb_txtDontFollow->setToolTip(QString("Crea csv degli account che non segui"));
    connect(ui->pb_txtDontFollow, &QPushButton::clicked, [=](){
        QString dir = selectDirectory()+"/";

        QString filePathReturn = "";

        if(engine.createTxtDontFollowing(filePathReturn,dir))
        {
            QMessageBox msg;
            msg.setText(QString("creato file %1").arg(filePathReturn));
            msg.exec();
        }
    });

    ui->pb_txtTheyDontFollow->setIcon(QIcon(":/icons/csv.png"));
    ui->pb_txtTheyDontFollow->setToolTip(QString("Crea csv degli account che non ti seguono"));
    connect(ui->pb_txtTheyDontFollow, &QPushButton::clicked, [=](){
        QString dir = selectDirectory()+"/";

        QString filePathReturn = "";

        if(engine.createTxtDontFollower(filePathReturn,dir))
        {
            QMessageBox msg;
            msg.setText(QString("creato file %1").arg(filePathReturn));
            msg.exec();
        }
    });

    ui->pb_txtPending->setIcon(QIcon(":/icons/csv.png"));
    ui->pb_txtPending->setToolTip(QString("Crea csv degli account con richieste inviate"));
    connect(ui->pb_txtPending, &QPushButton::clicked, [=](){
        QString dir = selectDirectory()+"/";

        QString filePathReturn = "";

        if(engine.createTxtPendingRequest(filePathReturn,dir))
        {
            QMessageBox msg;
            msg.setText(QString("creato file %1").arg(filePathReturn));
            msg.exec();
        }
    });


    auto handleLinkClick = [](const QModelIndex &index) {
        if (index.isValid() && index.column() == colonne::href) {
            QString link = index.data(Qt::DisplayRole).toString();

            QDesktopServices::openUrl(QUrl(link));
        }
    };

    QObject::connect(tableViewNoFollowing, &QTableView::clicked, [&](const QModelIndex &index) {
        handleLinkClick(index);
    });

    QObject::connect(tableViewNoFollower, &QTableView::clicked, [&](const QModelIndex &index) {
        handleLinkClick(index);
    });

    QObject::connect(tablePendingFollowing, &QTableView::clicked, [&](const QModelIndex &index) {
        handleLinkClick(index);
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
    {
        modelNoFollowing->deleteLater();
    }

    modelNoFollowing = new QStandardItemModel();

    QStringList titHeader;

    titHeader << "NAME" << "HREF" << "DATA";

    modelNoFollowing->setHorizontalHeaderLabels(titHeader);

    tableViewNoFollowing->setModel(modelNoFollowing);

    foreach(Profile item,engine.getProfileManagement()->getDontFollowingList())
    {
        QList <QStandardItem *> lItemS;

        lItemS << new QStandardItem(item.getName()) << new QStandardItem(item.getHref()) << new QStandardItem(item.getDateTime().toString("dd-MM-yyyy hh:mm"));

        foreach(QStandardItem * items,lItemS)
        {
            items->setEditable(false);
        }

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

        foreach(QStandardItem * items,lItemS)
        {
            items->setEditable(false);
        }

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

        foreach(QStandardItem * items,lItemS)
        {
            items->setEditable(false);
        }

        modelPendingFollowing->appendRow(lItemS);
    }

    tablePendingFollowing->resizeColumnsToContents();
}
