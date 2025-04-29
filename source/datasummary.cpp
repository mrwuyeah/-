#include "datasummary.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QNetworkInterface>
#include <QTimer>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

CDataSummary::CDataSummary(QWidget *parent) : CAbstractCard(parent)
{
    qDebug() << "[DataSummary] Initializing data summary widget...";

    // 初始化TCP客户端
    m_tcpSocket = new QTcpSocket(this);
    connect(m_tcpSocket, &QTcpSocket::connected, this, &CDataSummary::onConnected);
    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &CDataSummary::onReadyRead);
    connect(m_tcpSocket, &QTcpSocket::disconnected, this, &CDataSummary::onDisconnected);
    connect(m_tcpSocket, &QTcpSocket::errorOccurred, this, &CDataSummary::onErrorOccurred);

    // 设置自动重连定时器
    QTimer::singleShot(1000, this, &CDataSummary::connectToServer);

    // UI初始化保持不变
    qDebug() << "[UI] Setting up user interface...";
    setTitle("车辆行驶状况汇总");
    QVBoxLayout *layoutMain = new QVBoxLayout(getMainWnd());
    layoutMain->setContentsMargins(10, 0, 10, 0);
    layoutMain->setSpacing(0);

    // 状态标签初始化
    m_statusLabel = new QLabel("正常", this);
    m_pedestrianLabel = new QLabel("正常", this);
    m_obstacleLabel = new QLabel("安全", this);

    // 设置标签样式
    m_statusLabel->setAlignment(Qt::AlignCenter);
    m_pedestrianLabel->setAlignment(Qt::AlignCenter);
    m_obstacleLabel->setAlignment(Qt::AlignCenter);

    m_statusLabel->setStyleSheet("QLabel{color:#4CAF50; font-size:36px; font-weight: bold;}");
    m_pedestrianLabel->setStyleSheet("QLabel{color:#efeb7b; font-size:36px; font-weight: bold;}");
    m_obstacleLabel->setStyleSheet("QLabel{color:#4CAF50; font-size:36px; font-weight: bold;}");

    // 布局设置
    QHBoxLayout *layoutRow = new QHBoxLayout();
    layoutRow->addWidget(m_statusLabel);
    layoutRow->addWidget(CreateSeparator(true, this));
    layoutRow->addWidget(m_pedestrianLabel);
    layoutRow->addWidget(CreateSeparator(true, this));
    layoutRow->addWidget(m_obstacleLabel);
    layoutRow->setContentsMargins(0, 0, 0, 0);
    layoutMain->addLayout(layoutRow);

    // 描述标签
    QLabel *desc1 = new QLabel("驾驶状态监测", this);
    QLabel *desc2 = new QLabel("检测行人报警", this);
    QLabel *desc3 = new QLabel("检测障碍物报警", this);
    desc1->setAlignment(Qt::AlignCenter);
    desc2->setAlignment(Qt::AlignCenter);
    desc3->setAlignment(Qt::AlignCenter);
    desc1->setStyleSheet("QLabel{color:#637c9f; font-size:24px;}");
    desc2->setStyleSheet("QLabel{color:#637c9f; font-size:24px;}");
    desc3->setStyleSheet("QLabel{color:#637c9f; font-size:24px;}");

    QHBoxLayout *descLayout = new QHBoxLayout();
    descLayout->addWidget(desc1);
    descLayout->addWidget(desc2);
    descLayout->addWidget(desc3);
    layoutMain->addLayout(descLayout);
    layoutMain->addWidget(CreateSeparator(false, this));

    qDebug() << "[UI] User interface setup completed";
}

void CDataSummary::connectToServer()
{
    if (m_tcpSocket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "[Network] Attempting to connect to server...";
        m_tcpSocket->connectToHost("127.0.0.1", 12347); // 修改为实际的服务器IP和端口
    }
}

CDataSummary::~CDataSummary()
{
    qDebug() << "[DataSummary] Destroying data summary widget...";

    if (m_tcpSocket) {
        qDebug() << "[Network] Disconnecting socket...";
        m_tcpSocket->disconnectFromHost();
        if (m_tcpSocket->state() != QAbstractSocket::UnconnectedState) {
            qDebug() << "[Network] Waiting for socket to disconnect...";
            if (!m_tcpSocket->waitForDisconnected(1000)) {
                qDebug() << "[Network Warning] Socket did not disconnect gracefully";
            }
        }
        m_tcpSocket->deleteLater();
    }

    qDebug() << "[DataSummary] Destruction completed";
}

void CDataSummary::onConnected()
{
    qDebug() << "[Network] Connected to server";
    qDebug() << "[Network] Server address:" << m_tcpSocket->peerAddress().toString();
    qDebug() << "[Network] Server port:" << m_tcpSocket->peerPort();
}

void CDataSummary::onReadyRead()
{
    if (!m_tcpSocket) {
        qDebug() << "[Network Error] Read attempt with null socket";
        return;
    }

    qDebug() << "[Network] Data available from server";
    qDebug() << "[Network] Bytes available:" << m_tcpSocket->bytesAvailable();

    while (m_tcpSocket->canReadLine()) {
        QByteArray rawData = m_tcpSocket->readLine();
        QString data = QString::fromUtf8(rawData).trimmed();

        qDebug() << "[Network] Received data:" << data;
        qDebug() << "[Network] Raw data (hex):" << rawData.toHex();

        // 简单协议处理：FATIGUE:1 或 FATIGUE:0
        if (data.startsWith("FATIGUE:")) {
            QString value = data.mid(8).trimmed();
            bool isFatigue = (value == "1");

            qDebug() << "[Data] Processing FATIGUE message";
            qDebug() << "[Data] Fatigue state:" << isFatigue;
            qDebug() << "[Data] Original value:" << value;

            QString newStatus = isFatigue ? "疲劳驾驶" : "正常驾驶";
            QString newColor = isFatigue ? "#F44336" : "#4CAF50";

            qDebug() << "[UI] Updating status label to:" << newStatus;
            qDebug() << "[UI] Color:" << newColor;

            m_statusLabel->setText(newStatus);
            m_statusLabel->setStyleSheet(
                QString("QLabel{color:%1; font-size:36px; font-weight: bold;}").arg(newColor));

            qDebug() << "[Data] Update completed";
        } else {
            qDebug() << "[Network Warning] Received unexpected message format:" << data;
        }
    }
}

void CDataSummary::onDisconnected()
{
    qDebug() << "[Network] Disconnected from server";
    // 自动重连
    QTimer::singleShot(3000, this, &CDataSummary::connectToServer);
}

void CDataSummary::onErrorOccurred(QAbstractSocket::SocketError socketError)
{
    qDebug() << "[Network Error] Socket error occurred";
    qDebug() << "[Network Error] Error code:" << socketError;
    qDebug() << "[Network Error] Error string:" << m_tcpSocket->errorString();
    // 自动重连
    QTimer::singleShot(3000, this, &CDataSummary::connectToServer);
}
