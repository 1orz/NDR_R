#pragma once
#include "basedsl.hpp"
#include <QSharedPointer>
#include <QVariant>
#include <QtCore>

class PPPoE final : public QThread {
    Q_OBJECT
public:
    explicit PPPoE(QObject *parent = nullptr);
    ~PPPoE() override = default;
    void run() override;
    void kill();
    bool dialRAS(const QString &entryName, const QString &userName,
                 const QString &password, const QString &deviceName);
    bool redialRAS();
    void hangUp();
    bool isDisconnect();

    QString lastError();
    QString getUserName();
    QString getIpAddress();
    QString getDeviceName() const;
    QStringList getAvailableInterfaces();

private:
    void setDeviceName(QString const &deviceName);
    QSharedPointer<BaseDsl> basedsl;
    QString entryName;
    QString userName;
    QString password;
    QString deviceName;
    QString errorMessage;
    bool preparePhoneBook();
    bool stopNow = false;
    bool isRedial = false;
    bool isDisconnectNaturally;
    bool dialSucceed;

signals:
    void dialFinished(bool);
    void redialFinished(bool);
    void hangedUp(bool); // normal exit
private slots:
    void threadFinished();
};
