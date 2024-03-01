#include "profile.h"

QString Profile::getName() const
{
    return name;
}

void Profile::setName(const QString &newName)
{
    name = newName;
}

QString Profile::getHref() const
{
    return href;
}

void Profile::setHref(const QString &newHref)
{
    href = newHref;
}

QDateTime Profile::getDateTime() const
{
    return dateTime;
}

void Profile::setDateTime(const QDateTime &newDateTime)
{
    dateTime = newDateTime;
}

Profile::Profile() {}
