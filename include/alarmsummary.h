#ifndef ALARMSUMMARY_H
#define ALARMSUMMARY_H

#include "abstractcard.h"
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>

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
    QChart *createBarChart(int valueCount) const;
    QWidget *getVideoContainer1() const;

signals:

public slots:

private slots:

private:
    QMediaPlayer *player1;       // 视频播放器
    QVideoWidget *videoWidget1;  // 视频显示控件
    QMediaPlaylist *playlist1;
    QWidget *videoContainer1;
    Q_PROPERTY(QWidget *videoContainer1 READ getVideoContainer1 CONSTANT FINAL)
};

DataTable generateRandomData(int listCount, int valueMax, int valueCount);

#endif // ALARMSUMMARY_H
