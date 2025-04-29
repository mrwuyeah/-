#ifndef DATASUMMARY_H
#define DATASUMMARY_H

#include "abstractcard.h"
#include <QTcpSocket>
#include <QLabel>

class CDataSummary : public CAbstractCard
{
    Q_OBJECT
public:
    explicit CDataSummary(QWidget *parent = nullptr);
    ~CDataSummary();

private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *m_tcpSocket;
    QLabel *m_statusLabel;      // 驾驶状态标签
    QLabel *m_pedestrianLabel;  // 行人检测标签（固定值）
    QLabel *m_obstacleLabel;    // 障碍物检测标签（固定值）

    void connectToServer();
};

#endif // DATASUMMARY_H
