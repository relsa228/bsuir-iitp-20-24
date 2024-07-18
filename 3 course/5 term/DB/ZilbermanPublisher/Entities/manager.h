#ifndef MANAGER_H
#define MANAGER_H

#include <QString>

class Manager
{
public:
    Manager();
    Manager(const QString &name, const QString &surname, const QString &patronymic, const QString &username, const QString &position);
    Manager(QString id, QString name, QString surname,
            QString patronymic, QString username, QString position, bool is_active);
    Manager(const QString &id, const QString &name, const QString &surname, const
            QString &patronymic, const QString &username, const QString &position, const QString &lastAuthTime, bool is_active);

    const QString &getId() const;
    const QString &getUsername() const;
    const QString &getName() const;
    const QString &getSurname() const;
    const QString &getPatronymic() const;
    const QString &getPosition() const;
    bool getIs_active() const;

    const QString &getLastAuthTime() const;

private:
    QString id;

    QString name;
    QString surname;
    QString patronymic;
    QString username;

    QString position;
    QString lastAuthTime;
    bool is_active;
};

#endif // MANAGER_H
