#ifndef PROFILE_H
#define PROFILE_H

#include <qdatetime.h>
#include <qstring.h>

class Profile
{
private:
    QString name;
    QString href;
    QDateTime dateTime;
public:
    Profile();

    QString getName() const;
    void setName(const QString &newName);
    QString getHref() const;
    void setHref(const QString &newHref);
    QDateTime getDateTime() const;
    void setDateTime(const QDateTime &newDateTime);
};

#endif // PROFILE_H
