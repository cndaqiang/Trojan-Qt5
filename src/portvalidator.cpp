#include "portvalidator.h"
#include "trojanvalidator.h"

#include <QTcpServer>

PortValidator::PortValidator(QObject *parent)
    : QValidator(parent)
{}

QValidator::State PortValidator::validate(QString &input, int &) const
{
    if (TrojanValidator::validatePort(input)) {
        return Acceptable;
    }
    else
        return Invalid;
}

bool PortValidator::isInUse(int port)
{
    /** Use TcpServer to listen to the port specified. */
    QTcpServer *server = new QTcpServer();
    bool status = server->listen(QHostAddress::LocalHost, port);
    if (status) {
        server->close();
        server->deleteLater();
        return false;
    } else {
        server->close();
        server->deleteLater();
        return true;
    }
}
