#ifndef ENGINE_H
#define ENGINE_H

#include "profilemanagement.h"

class Engine
{
private:
    ProfileManagement * profileManagement=nullptr;
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
};

#endif // ENGINE_H
