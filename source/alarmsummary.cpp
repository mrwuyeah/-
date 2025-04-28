#include "alarmsummary.h"
#include "qjsonarray.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtCharts/QChartView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QRandomGenerator>
#include <QtWidgets/QApplication>
#include <QDebug>
#include <QPainter>
#include <QDir>
#include <QMessageBox>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

CAlarmSummary::CAlarmSummary(QWidget *parent) : CAbstractCard(parent)
{
    // 初始化TCP服务器
    m_tcpServer = new QTcpServer(this);
    m_clientSocket = nullptr;

    if (!m_tcpServer->listen(QHostAddress::Any, 12345)) {
        qDebug() << "Server could not start:" << m_tcpServer->errorString();
    } else {
        qDebug() << "Server started on port 12345";
    }

    connect(m_tcpServer, &QTcpServer::newConnection, this, &CAlarmSummary::onNewConnection);
    connect(m_tcpServer, &QTcpServer::acceptError, this, &CAlarmSummary::onServerError);

    setTitle("车内状态汇总");
    QVBoxLayout *layoutMain = new QVBoxLayout();
    QVBoxLayout *layoutMain1 = new QVBoxLayout(getMainWnd());
    layoutMain1->setContentsMargins(10, 0, 10, 0);
    layoutMain->setSpacing(10);
    layoutMain1->setSpacing(10);

    // 温度、湿度、光照强度显示标签
    {
        m_tempLabel = new QLabel("--℃", this);
        m_humidityLabel = new QLabel("--%", this);
        m_lightLabel = new QLabel("--", this);
        m_tempLabel->setAlignment(Qt::AlignCenter);
        m_humidityLabel->setAlignment(Qt::AlignCenter);
        m_lightLabel->setAlignment(Qt::AlignCenter);
        m_tempLabel->setStyleSheet("QLabel{color:#c5ccff; font-size:24px; font-weight: bold;}");
        m_humidityLabel->setStyleSheet("QLabel{color:#c5ccff; font-size:24px; font-weight: bold;}");
        m_lightLabel->setStyleSheet("QLabel{color:#c5ccff; font-size:24px; font-weight: bold;}");
        QHBoxLayout *layoutRow = new QHBoxLayout();
        layoutRow->addWidget(m_tempLabel);
        layoutRow->addWidget(CreateSeparator(true, this));
        layoutRow->addWidget(m_humidityLabel);
        layoutRow->addWidget(CreateSeparator(true, this));
        layoutRow->addWidget(m_lightLabel);
        layoutRow->setContentsMargins(0, 10, 0, 0);
        layoutMain->addLayout(layoutRow);
    }

    // 温度、湿度、光照强度标签说明
    {
        QLabel *label1 = new QLabel("温度", this);
        QLabel *label2 = new QLabel("湿度", this);
        QLabel *label3 = new QLabel("光照强度", this);
        label1->setAlignment(Qt::AlignCenter);
        label2->setAlignment(Qt::AlignCenter);
        label3->setAlignment(Qt::AlignCenter);
        label1->setStyleSheet("QLabel{color:rgba(255, 255, 255, 100); font-size:12px;}");
        label2->setStyleSheet("QLabel{color:rgba(255, 255, 255, 100); font-size:12px;}");
        label3->setStyleSheet("QLabel{color:rgba(255, 255, 255, 100); font-size:12px;}");
        QHBoxLayout *layoutRow = new QHBoxLayout();
        layoutRow->addWidget(label1);
        layoutRow->addWidget(label2);
        layoutRow->addWidget(label3);
        layoutMain->addLayout(layoutRow);
    }

    layoutMain->addWidget(CreateSeparator(false, this));

    // 其他传感器数据显示
    {
        fatigueCountLabel = new QLabel("0 mg/L", this);
        QLabel *label2 = new QLabel("1h30min", this);
        QLabel *label3 = new QLabel("正常", this);
        fatigueCountLabel->setAlignment(Qt::AlignCenter);
        label2->setAlignment(Qt::AlignCenter);
        label3->setAlignment(Qt::AlignCenter);
        fatigueCountLabel->setStyleSheet("QLabel{color:#c5ccff; font-size:24px; font-weight: bold;}");
        label2->setStyleSheet("QLabel{color:#c5ccff; font-size:24px; font-weight: bold;}");
        label3->setStyleSheet("QLabel{color:#c5ccff; font-size:24px; font-weight: bold;}");
        QHBoxLayout *layoutRow = new QHBoxLayout();
        layoutRow->addWidget(fatigueCountLabel);
        layoutRow->addWidget(CreateSeparator(true, this));
        layoutRow->addWidget(label2);
        layoutRow->addWidget(CreateSeparator(true, this));
        layoutRow->addWidget(label3);
        layoutRow->setContentsMargins(0, 10, 0, 0);
        layoutMain->addLayout(layoutRow);
    }

    // 其他传感器标签说明
    {
        QLabel *label1 = new QLabel("空气酒精含量", this);
        QLabel *label2 = new QLabel("持续驾驶时长", this);
        QLabel *label3 = new QLabel("驾驶者驾驶状态", this);
        label1->setAlignment(Qt::AlignCenter);
        label2->setAlignment(Qt::AlignCenter);
        label3->setAlignment(Qt::AlignCenter);
        label1->setStyleSheet("QLabel{color:rgba(255, 255, 255, 100); font-size:12px;}");
        label2->setStyleSheet("QLabel{color:rgba(255, 255, 255, 100); font-size:12px;}");
        label3->setStyleSheet("QLabel{color:rgba(255, 255, 255, 100); font-size:12px;}");
        QHBoxLayout *layoutRow = new QHBoxLayout();
        layoutRow->addWidget(label1);
        layoutRow->addWidget(label2);
        layoutRow->addWidget(label3);
        layoutMain->addLayout(layoutRow);
    }

    layoutMain1->addLayout(layoutMain, 5);

    // 视频区域标题
    QLabel *label1 = new QLabel("车内疲劳检测", this);
    label1->setAlignment(Qt::AlignCenter);
    label1->setStyleSheet("QLabel{color:#49bcf7; font-size:20px; border: 1px solid rgba(25,186,139,40); background: rgba(255,255,255,12)}");
    QLabel *label2 = new QLabel("车外道路检测", this);
    label2->setAlignment(Qt::AlignCenter);
    label2->setStyleSheet("QLabel{color:#49bcf7; font-size:20px; border: 1px solid rgba(25,186,139,40); background: rgba(255,255,255,12)}");

    QHBoxLayout *layoutRow = new QHBoxLayout();
    layoutRow->addWidget(CreateSeparator(false, this));
    layoutRow->addWidget(label1);
    layoutRow->addWidget(CreateSeparator(false, this));

    QHBoxLayout *layoutRow2 = new QHBoxLayout();
    layoutRow2->addWidget(CreateSeparator(false, this));
    layoutRow2->addWidget(label2);
    layoutRow2->addWidget(CreateSeparator(false, this));

    layoutMain1->addLayout(layoutRow, 1);

    // 视频容器1 - 用于显示疲劳检测实时帧
    videoContainer1 = new QWidget(this);
    videoContainer1->setStyleSheet("background: black; border: 1px solid rgba(255, 255, 255, 50);");
    videoLabel = new QLabel(videoContainer1);
    videoLabel->setAlignment(Qt::AlignCenter);
    videoLabel->setStyleSheet("background: transparent;");
    QVBoxLayout *videoLayout1 = new QVBoxLayout(videoContainer1);
    videoLayout1->addWidget(videoLabel);
    videoContainer1->setLayout(videoLayout1);
    videoContainer1->setMinimumHeight(300);
    videoContainer1->setMaximumHeight(600);

    // 初始化Python进程
    process = new QProcess(this);
    pythonScriptPath = "C:/Users/18163/Desktop/bishe/Fatigue-Driven-Detection-Based-on-CNN/main.py"; // 修改为你的Python脚本路径

    connect(process, &QProcess::readyReadStandardOutput, this, &CAlarmSummary::readProcessOutput);
    connect(process, QOverload<int>::of(&QProcess::finished), this, &CAlarmSummary::processFinished);

    // 启动检测
    startDetection();

    QHBoxLayout *buttonLayout = new QHBoxLayout();

    // 播放按钮
    QPushButton *playButton = new QPushButton("开始检测", this);
    playButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #4CAF50;"
        "   border: none;"
        "   color: white;"
        "   padding: 8px 16px;"
        "   font-size: 14px;"
        "   border-radius: 4px;"
        "   min-width: 80px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #45a049;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #3e8e41;"
        "}"
        );
    playButton->setFixedHeight(36);

    // 暂停按钮
    QPushButton *pauseButton = new QPushButton("停止检测", this);
    pauseButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #f44336;"
        "   border: none;"
        "   color: white;"
        "   padding: 8px 16px;"
        "   font-size: 14px;"
        "   border-radius: 4px;"
        "   min-width: 80px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #d32f2f;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #b71c1c;"
        "}"
        );
    pauseButton->setFixedHeight(36);

    buttonLayout->addStretch();
    buttonLayout->addWidget(playButton);
    buttonLayout->addSpacing(10);  // 添加按钮间距
    buttonLayout->addWidget(pauseButton);
    buttonLayout->addStretch();

    // 视频播放器2 (保持不变)
    QMediaPlaylist *playlist2 = new QMediaPlaylist(this);
    QString videoPath2 = "C:/Users/18163/Desktop/QT/qt_test_1/test_1/4.mp4";
    playlist2->addMedia(QUrl::fromLocalFile(videoPath2));
    // QString videoPath2 = ":/image/res/3.mp4";  // 使用资源文件中的视频
    // playlist2->addMedia(QUrl(videoPath2));  // 使用QUrl加载资源路径
    player2 = new QMediaPlayer(this);
    QVideoWidget *videoWidget2 = new QVideoWidget(this);
    videoWidget2->setMinimumHeight(300);
    videoWidget2->setMaximumHeight(600);
    player2->setPlaylist(playlist2);
    player2->setVideoOutput(videoWidget2);
    // player2->play();
    // 连接按钮信号
    connect(playButton, &QPushButton::clicked, [this]() {
        player2->play();
    });
    connect(pauseButton, &QPushButton::clicked, [this]() {
        player2->pause();
    });
    videoWidget2->setStyleSheet("background: transparent; border: 1px solid rgba(255, 255, 255, 50);");

    layoutMain1->addWidget(videoContainer1, 9);
    layoutMain1->addLayout(layoutRow2, 1);
    layoutMain1->addWidget(videoWidget2, 9);
    layoutMain1->addLayout(buttonLayout);





}

CAlarmSummary::~CAlarmSummary()
{
    if (m_clientSocket) {
        m_clientSocket->disconnectFromHost();
        m_clientSocket->deleteLater();
    }
    if (m_tcpServer) {
        m_tcpServer->close();
        m_tcpServer->deleteLater();
    }
    if (process) {
        process->terminate();
        process->waitForFinished();
        delete process;
    }
}

// TCP服务器相关方法
void CAlarmSummary::onNewConnection()
{
    if (m_clientSocket) {
        m_clientSocket->disconnectFromHost();
        m_clientSocket->deleteLater();
    }

    m_clientSocket = m_tcpServer->nextPendingConnection();
    connect(m_clientSocket, &QTcpSocket::readyRead, this, &CAlarmSummary::onClientReadyRead);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &CAlarmSummary::onClientDisconnected);

    qDebug() << "New connection from:" << m_clientSocket->peerAddress().toString();
}

void CAlarmSummary::onClientReadyRead()
{
    if (!m_clientSocket) return;

    while (m_clientSocket->canReadLine()) {
        QString data = QString::fromUtf8(m_clientSocket->readLine()).trimmed();
        qDebug() << "Received:" << data;

        QStringList parts = data.split(", ");
        for (const QString &part : parts) {
            QStringList keyValue = part.split(":");
            if (keyValue.size() == 2) {
                QString key = keyValue[0].trimmed();
                float value = keyValue[1].trimmed().toFloat();
                if (key == "DHT11_T") {
                    setTemperature(value);
                } else if (key == "DHT11_H") {
                    setHumidity(value);
                } else if (key == "Light") {
                    setLightIntensity(value * 100);
                }
            }
        }
    }
}

void CAlarmSummary::onClientDisconnected()
{
    qDebug() << "Client disconnected";
    m_clientSocket->deleteLater();
    m_clientSocket = nullptr;
}

void CAlarmSummary::onServerError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Server error:" << m_tcpServer->errorString();
}

QWidget *CAlarmSummary::getVideoContainer1() const
{
    return videoContainer1;
}

void CAlarmSummary::setTemperature(float value)
{
    if (m_tempLabel) {
        m_tempLabel->setText(QString("%1℃").arg(value, 0, 'f', 1));
    }
}

void CAlarmSummary::setHumidity(float value)
{
    if (m_humidityLabel) {
        m_humidityLabel->setText(QString("%1%").arg(value, 0, 'f', 1));
    }
}

void CAlarmSummary::setLightIntensity(float value)
{
    if (m_lightLabel) {
        m_lightLabel->setText(QString("%1%").arg(value, 0, 'f', 1));
    }
}

void CAlarmSummary::startDetection()
{
    if (!QFile::exists(pythonScriptPath)) {
        qDebug() << "Python script not found:" << pythonScriptPath;
        return;
    }

    process->start("python", {pythonScriptPath});
    if (!process->waitForStarted()) {
        qDebug() << "Failed to start Python process";
    }
}

void CAlarmSummary::readProcessOutput()
{
    static QByteArray buffer;

    buffer += process->readAllStandardOutput();

    while (buffer.contains('\n')) {
        int pos = buffer.indexOf('\n');
        QByteArray line = buffer.left(pos).trimmed();
        buffer = buffer.mid(pos + 1);

        if (line.isEmpty()) continue;

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(line, &error);

        if (error.error != QJsonParseError::NoError) {
            qDebug() << "JSON parse error:" << error.errorString();
            continue;
        }

        if (!doc.isObject()) {
            qDebug() << "Invalid JSON data";
            continue;
        }

        updateFrame(doc.object());
    }
}

void CAlarmSummary::updateFrame(const QJsonObject &data)
{
    if (data["type"].toString() == "frame") {
        QByteArray imgData = QByteArray::fromBase64(data["image"].toString().toUtf8());
        QPixmap pixmap;

        if (pixmap.loadFromData(imgData, "JPG")) {
            // 如果有检测框数据，绘制检测框
            if (data.contains("detections")) {
                QJsonArray detections = data["detections"].toArray();
                drawDetections(pixmap, detections);
            }

            videoLabel->setPixmap(pixmap.scaled(videoLabel->size(),
                                                Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }


    }

    if (data["type"].toString() == "fatigue_summary") {
        // 获取疲劳帧数和比例
        int fatigueFrames = data["fatigue_frames"].toInt();
        double fatigueRatio = data["fatigue_ratio"].toDouble();

        qDebug() << "收到疲劳统计 - 帧数:" << fatigueFrames
                 << "比例:" << fatigueRatio;

        // 只有当疲劳比例>0.5时才累加
        if (fatigueRatio > 0.5) {
            fatigueCount += fatigueFrames;
            qDebug() << "有效疲劳事件，累计计数:" << fatigueCount;
        } else {
            qDebug() << "疲劳比例不足，不累加计数";

        }

        // 显示平均疲劳比例（总累计/总帧数）
        fatigueCountLabel->setText(QString::number(fatigueRatio, 'f', 2));
    }
}

void CAlarmSummary::drawDetections(QPixmap &pixmap, const QJsonArray &detections)
{
    QPainter painter(&pixmap);
    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);

    // 定义检测框颜色
    QHash<QString, QColor> colors = {
        {"face", QColor(255, 255, 0)},    // 黄色
        {"eye", QColor(0, 255, 0)},       // 绿色
        {"mouth", QColor(0, 0, 255)}      // 蓝色
    };

    for (const QJsonValue &detection : detections) {
        QJsonObject obj = detection.toObject();
        QString label = obj["label"].toString();
        float score = obj["score"].toDouble();
        QJsonObject bbox = obj["bbox"].toObject();

        int x1 = bbox["x1"].toInt();
        int y1 = bbox["y1"].toInt();
        int x2 = bbox["x2"].toInt();
        int y2 = bbox["y2"].toInt();

        QColor color = colors.value(label, Qt::white);
        painter.setPen(QPen(color, 2));
        painter.drawRect(x1, y1, x2-x1, y2-y1);

        // 绘制标签和置信度
        QString labelText = QString("%1: %2").arg(label).arg(score, 0, 'f', 2);
        painter.fillRect(x1, y1 - 20, QFontMetrics(font).horizontalAdvance(labelText) + 5, 20, color);
        painter.setPen(Qt::black);
        painter.drawText(x1 + 2, y1 - 5, labelText);
    }
}

void CAlarmSummary::processFinished(int exitCode)
{
    qDebug() << "Python process finished with exit code:" << exitCode;
}

DataTable generateRandomData(int listCount, int valueMax, int valueCount)
{
    DataTable dataTable;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = 30 + QRandomGenerator::global()->bounded(valueMax / 2);
            QPointF value((j + QRandomGenerator::global()->generateDouble()) * ((qreal) valueCount / (qreal) valueCount),
                          yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
            yValue = 0;
        }
        dataTable << dataList;
    }
    return dataTable;
}
