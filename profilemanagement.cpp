#include "profilemanagement.h"
#include "qdebug.h"

#include <QDir>

QList<Profile> ProfileManagement::getFollowingList() const
{
    return followingList;
}

QList<Profile> ProfileManagement::getFolloweringList() const
{
    return followerList;
}

QList<Profile> ProfileManagement::getDontFollowingList()
{
    QList<Profile> toRet;

    QStringList namesFollowing;

    foreach(Profile item,followingList)
        namesFollowing << item.getName();

    foreach(Profile item,followerList)
    {
        if(!namesFollowing.contains(item.getName()))
            toRet << item;
    }

    return toRet;
}

QList<Profile> ProfileManagement::getDontFollowerList()
{
    QList<Profile> toRet;

    QStringList namesFollower;

    foreach(Profile item,followerList)
        namesFollower << item.getName();

    foreach(Profile item,followingList)
    {
        if(!namesFollower.contains(item.getName()))
            toRet << item;
    }

    return toRet;
}

void ProfileManagement::printFollowingList()
{
    foreach(Profile item,followingList)
        qDebug() << item.getName();
}

void ProfileManagement::printFollowerList()
{
    foreach(Profile item,followerList)
        qDebug() << item.getName();
}

void ProfileManagement::setFollowingList(const QList<Profile> &newFollowingList)
{
    followingList.clear();
    followingList = newFollowingList;
}

void ProfileManagement::setFollowerList(const QList<Profile> &newFollowerList)
{
    followerList.clear();
    followerList = newFollowerList;
}

QList<Profile> ProfileManagement::getPendinFollowingRequestList() const
{
    return pendinFollowingRequestList;
}

void ProfileManagement::setPendinFollowingRequestList(const QList<Profile> &newPendinFollowingRequestList)
{
    pendinFollowingRequestList.clear();
    pendinFollowingRequestList = newPendinFollowingRequestList;
}

bool ProfileManagement::createTxtPendingRequest(QString &pathFileReturn, QString dir, QString nomeFile)
{
    QDir directory(dir);
    QString filePath = directory.filePath(nomeFile);

    pathFileReturn = filePath;

    QFile fileTxt(filePath);
    if (!fileTxt.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qCritical() << "Impossibile aprire il file per la scrittura";
        return false;
    }

    QTextStream out(&fileTxt);

    foreach(Profile item,this->getPendinFollowingRequestList())
    {
        out << item.getHref() << "\n";
    }

    fileTxt.close();

    return true;
}

bool ProfileManagement::createTxtDontFollowing(QString &pathFileReturn, QString dir, QString nomeFile)
{
    QDir directory(dir);
    QString filePath = directory.filePath(nomeFile);

    pathFileReturn = filePath;

    QFile fileTxt(filePath);
    if (!fileTxt.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qCritical() << "Impossibile aprire il file per la scrittura";
        return false;
    }

    QTextStream out(&fileTxt);

    foreach(Profile item,this->getDontFollowingList())
    {
        out << item.getName() << " - " << item.getHref() << "\n";
    }

    fileTxt.close();

    return true;
}

bool ProfileManagement::createTxtDontFollower(QString &pathFileReturn, QString dir, QString nomeFile)
{
    QDir directory(dir);
    QString filePath = directory.filePath(nomeFile);

    pathFileReturn = filePath;

    QFile fileTxt(filePath);
    if (!fileTxt.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qCritical() << "Impossibile aprire il file per la scrittura";
        return false;
    }

    QTextStream out(&fileTxt);

    foreach(Profile item,this->getDontFollowerList())
    {
        out << item.getName() << " - " << item.getHref() << "\n";
    }

    fileTxt.close();

    return true;
}

ProfileManagement::ProfileManagement() {}
