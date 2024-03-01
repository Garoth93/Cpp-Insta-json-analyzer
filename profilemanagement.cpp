#include "profilemanagement.h"
#include "qdebug.h"

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

ProfileManagement::ProfileManagement() {}
