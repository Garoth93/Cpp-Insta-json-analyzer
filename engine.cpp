#include "engine.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>


ProfileManagement *Engine::getProfileManagement() const
{
    return profileManagement;
}

QString Engine::getPathDirectoryFile() const
{
    return pathDirectoryFile;
}

void Engine::setPathDirectoryFile(const QString &newPathDirectoryFile)
{
    pathDirectoryFile = newPathDirectoryFile;
}

QList<Profile> Engine::getFollowerListFromJson(QString path)
{
    path+="/followers_1.json";
    QList<Profile> toRet;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning("File open error");
        return toRet;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray())
    {
        qWarning("Error. Json not array");
        return  toRet;
    }

    QJsonArray jsonArray = doc.array();

    for (const QJsonValue &value : jsonArray)
    {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            QJsonArray stringListData = obj["string_list_data"].toArray();

            for (const QJsonValue &stringDataValue : stringListData)
            {
                QJsonObject stringData = stringDataValue.toObject();
                QString href = stringData["href"].toString();
                QString value = stringData["value"].toString();
                qint64 timestamp = stringData["timestamp"].toInt();

                Profile newProfileItem;
                newProfileItem.setName(value);
                newProfileItem.setHref(href);
                newProfileItem.setDateTime(QDateTime::fromSecsSinceEpoch(timestamp));

                toRet << newProfileItem;
            }
        }
    }
    return toRet;
}

QList<Profile> Engine::getFollowingListFromJson(QString path)
{
    path+="/following.json";
    QList<Profile> toRet;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning("File open error");
        return toRet;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    if (jsonDoc.isNull())
    {
        qWarning("Error in json converter");
        return toRet;
    }

    QJsonObject rootObject = jsonDoc.object();

    QJsonArray followingArray = rootObject["relationships_following"].toArray();

    foreach (const QJsonValue &followingValue, followingArray)
    {
        QJsonObject followingObject = followingValue.toObject();
        QJsonArray stringListData = followingObject["string_list_data"].toArray();
        foreach (const QJsonValue &stringDataValue, stringListData)
        {
            QJsonObject stringDataObject = stringDataValue.toObject();
            QString href = stringDataObject["href"].toString();
            QString value = stringDataObject["value"].toString();
            qint64 timestamp = stringDataObject["timestamp"].toInt();

            Profile newProfileItem;
            newProfileItem.setName(value);
            newProfileItem.setHref(href);
            newProfileItem.setDateTime(QDateTime::fromSecsSinceEpoch(timestamp));

            toRet << newProfileItem;
        }
    }
    return toRet;
}

QList<Profile> Engine::getPendinfRequestFollowingListFromJson(QString path)
{
    path+="/pending_follow_requests.json";

    QList<Profile> toRet;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning("File open error");
        return toRet;
    }

    QByteArray data = file.readAll();
    file.close();

    bool ok=true;

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) ok = false;

    if(ok && !doc.isObject()) ok = false;

    if(!ok)
    {
        qWarning("Error in json converter");
        return toRet;
    }

    QJsonObject jsonObj = doc.object();

    if (!jsonObj.contains("relationships_follow_requests_sent") || !jsonObj["relationships_follow_requests_sent"].isArray()) ok=false;

    if(!ok)
    {
        qWarning("Error in json converter");
        return toRet;
    }

    QJsonArray requestsArray = jsonObj["relationships_follow_requests_sent"].toArray();

    for (const QJsonValue& requestValue : requestsArray)
    {
        if (!requestValue.isObject()) continue;

        QJsonObject requestObj = requestValue.toObject();

        if (!requestObj.contains("string_list_data") || !requestObj["string_list_data"].isArray()) continue;

        QJsonArray stringListArray = requestObj["string_list_data"].toArray();

        for (const QJsonValue& stringListValue : stringListArray)
        {
            if (!stringListValue.isObject()) continue;

             QJsonObject stringListObj = stringListValue.toObject();

            if (!stringListObj.contains("href") || !stringListObj.contains("value") || !stringListObj.contains("timestamp")) continue;

            QString href = stringListObj["href"].toString();
            QString value = stringListObj["value"].toString();
            qint64 timestamp = stringListObj["timestamp"].toInt();

            Profile newProfileItem;
            newProfileItem.setName(value);
            newProfileItem.setHref(href);
            newProfileItem.setDateTime(QDateTime::fromSecsSinceEpoch(timestamp));

            toRet << newProfileItem;
        }
    }
    return toRet;
}

void Engine::populateFollowerList()
{
    profileManagement->setFollowerList(this->getFollowerListFromJson(pathDirectoryFile));
}

void Engine::populateFollowingList()
{
    profileManagement->setFollowingList(this->getFollowingListFromJson(pathDirectoryFile));
}

void Engine::populatePendinfRequestFollowingList()
{
   profileManagement->setPendinFollowingRequestList(this->getPendinfRequestFollowingListFromJson(pathDirectoryFile));
}

Engine::Engine() {}

void Engine::init()
{
    if(!profileManagement)
        profileManagement = new ProfileManagement();
    this->populateFollowerList();
    this->populateFollowingList();
    this->populatePendinfRequestFollowingList();
}
