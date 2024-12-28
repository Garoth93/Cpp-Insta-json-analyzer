#ifndef ENGINE_H
#define ENGINE_H

#include "profilemanagement.h"

class Engine
{
private:
    ProfileManagement * profileManagement = nullptr;
    QString pathDirectoryFile;

public:
    Engine();

    void init();

    ProfileManagement *getProfileManagement() const;
    QString getPathDirectoryFile() const;
    void setPathDirectoryFile(const QString &newPathDirectoryFile);

    static QList<Profile> getFollowerListFromJson(QString path);
    static QList<Profile> getFollowingListFromJson(QString path);
    static QList<Profile> getPendinfRequestFollowingListFromJson(QString path);

    void populateFollowerList();
    void populateFollowingList();
    void populatePendinfRequestFollowingList();

    bool createTxtPendingRequest(QString & pathFileReturn,QString dir,QString nomeFile = "pendingRequest.txt");
    bool createTxtDontFollowing(QString & pathFileReturn,QString dir,QString nomeFile = "dontFollowing.txt");
    bool createTxtDontFollower(QString & pathFileReturn,QString dir,QString nomeFile = "dontFollower.txt");
};

#endif // ENGINE_H
