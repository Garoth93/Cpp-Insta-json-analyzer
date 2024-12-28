#ifndef PROFILEMANAGEMENT_H
#define PROFILEMANAGEMENT_H

#include "profile.h"
#include <qlist.h>

class ProfileManagement
{
private:
    QList<Profile> followingList;
    QList<Profile> followerList;
    QList<Profile> pendinFollowingRequestList;
public:
    ProfileManagement();

    QList<Profile> getFollowingList() const;
    void setFollowingList(const QList<Profile> &newFollowingList);

    QList<Profile> getFolloweringList() const;
    void setFollowerList(const QList<Profile> &newFollowerList);

    QList<Profile> getDontFollowingList();
    QList<Profile> getDontFollowerList();

    void printFollowingList();
    void printFollowerList();

    QList<Profile> getPendinFollowingRequestList() const;
    void setPendinFollowingRequestList(const QList<Profile> &newPendinFollowingRequestList);

    bool createTxtPendingRequest(QString &pathFileReturn,QString dir,QString nomeFile = "pendingRequest.txt");
    bool createTxtDontFollowing(QString &pathFileReturn,QString dir,QString nomeFile = "dontFollowing.txt");
    bool createTxtDontFollower(QString &pathFileReturn,QString dir,QString nomeFile = "dontFollowing.txt");
};

#endif // PROFILEMANAGEMENT_H
