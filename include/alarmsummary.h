#ifndef ALARMSUMMARY_H
#define ALARMSUMMARY_H

#include "abstractcard.h"
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <QTcpServer>
#include <QTcpSocket>
#include <QLabel>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPushButton>


QT_CHARTS_BEGIN_NAMESPACE
    class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

        QT_CHARTS_USE_NAMESPACE

    typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

class CAlarmSummary : public CAbstractCard
{
    Q_OBJECT
public:
    explicit CAlarmSummary(QWidget *parent = nullptr);
    ~CAlarmSummary();
    QWidget *getVideoContainer1() const;
    bool isFatigue() const { return m_fatigue; };

private slots:
    void onNewConnection();
    void onClientReadyRead();
    void onClientDisconnected();
    void onServerError(QAbstractSocket::SocketError socketError);
    void startDetection();
    void readProcessOutput();
    void processFinished(int exitCode);
    void updateFrame(const QJsonObject &data);

private:
    bool m_fatigue = false;
    // 视频相关成员
    QLabel *videoLabel;
    QProcess *process;
    QString pythonScriptPath;
    QWidget *videoContainer1;
    QMediaPlayer *player2;

    // TCP服务器相关成员
    QTcpServer *m_tcpServer;
    QTcpSocket *m_clientSocket;

    // 传感器显示标签
    QLabel *m_tempLabel;
    QLabel *m_humidityLabel;
    QLabel *m_lightLabel;

    // 数据更新方法
    void setTemperature(float value);
    void setHumidity(float value);
    void setLightIntensity(float value);
    void drawDetections(QPixmap &pixmap, const QJsonArray &detections);

    QPushButton *playButton;

    QLabel* m_fatigueCountLabel;
    int m_fatigueAlarmCount = 0;  //

signals:
    void fatigueStatusChanged(bool isFatigue);  // 新增信号
};

DataTable generateRandomData(int listCount, int valueMax, int valueCount);

#endif // ALARMSUMMARY_H
