#include "alarmsummary.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>

#include <QMediaPlaylist>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


CAlarmSummary::CAlarmSummary(QWidget *parent) : CAbstractCard(parent)
{
    setTitle("车内状态汇总");

    QVBoxLayout *layoutMain = new QVBoxLayout(getMainWnd());
    layoutMain->setContentsMargins(10, 0, 10, 0);
    layoutMain->setSpacing(10);

    {
        QLabel *label1 = new QLabel("29℃", this);
        QLabel *label2 = new QLabel("70%", this);
        QLabel *label3 = new QLabel("50%", this);

        label1->setAlignment(Qt::AlignCenter);
        label2->setAlignment(Qt::AlignCenter);
        label3->setAlignment(Qt::AlignCenter);

        label1->setStyleSheet("QLabel{color:#c5ccff; font-size:24px; font-weight: bold;}");
        label2->setStyleSheet("QLabel{color:#c5ccff; font-size:24px; font-weight: bold;}");
        label3->setStyleSheet("QLabel{color:#c5ccff; font-size:24px; font-weight: bold;}");

        QHBoxLayout *layoutRow = new QHBoxLayout();
        layoutRow->addWidget(label1);
        layoutRow->addWidget(CreateSeparator(true, this));
        layoutRow->addWidget(label2);
        layoutRow->addWidget(CreateSeparator(true, this));
        layoutRow->addWidget(label3);
        layoutRow->setContentsMargins(0, 10, 0, 0);

        layoutMain->addLayout(layoutRow);
    }

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

    {
        QLabel *label1 = new QLabel("0 mg/L", this);
        QLabel *label2 = new QLabel("1h30min", this);
        QLabel *label3 = new QLabel("正常", this);

        label1->setAlignment(Qt::AlignCenter);
        label2->setAlignment(Qt::AlignCenter);
        label3->setAlignment(Qt::AlignCenter);

        label1->setStyleSheet("QLabel{color:#c5ccff; font-size:24px; font-weight: bold;}");
        label2->setStyleSheet("QLabel{color:#c5ccff; font-size:24px; font-weight: bold;}");
        label3->setStyleSheet("QLabel{color:#c5ccff; font-size:24px; font-weight: bold;}");

        QHBoxLayout *layoutRow = new QHBoxLayout();
        layoutRow->addWidget(label1);
        layoutRow->addWidget(CreateSeparator(true, this));
        layoutRow->addWidget(label2);
        layoutRow->addWidget(CreateSeparator(true, this));
        layoutRow->addWidget(label3);
        layoutRow->setContentsMargins(0, 10, 0, 0);

        layoutMain->addLayout(layoutRow);
    }

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

    {
        QLabel *label1 = new QLabel("车内疲劳检测", this);
        label1->setAlignment(Qt::AlignCenter);
        label1->setStyleSheet("QLabel{color:#49bcf7; font-size:15px; border: 1px solid rgba(25,186,139,40); background: rgba(255,255,255,12)}");

        QLabel *label2 = new QLabel("车外障碍监测", this);
        label2->setAlignment(Qt::AlignCenter);
        label2->setStyleSheet("QLabel{color:#49bcf7; font-size:15px; border: 1px solid rgba(25,186,139,40); background: rgba(255,255,255,12)}");

        QHBoxLayout *layoutRow = new QHBoxLayout();
        layoutRow->addWidget(CreateSeparator(false, this));
        layoutRow->addWidget(label1);
        layoutRow->addWidget(CreateSeparator(false, this));

        QHBoxLayout *layoutRow2 = new QHBoxLayout();
        layoutRow2->addWidget(CreateSeparator(false, this));
        layoutRow2->addWidget(label2);
        layoutRow2->addWidget(CreateSeparator(false, this));

        layoutMain->addLayout(layoutRow);

        // QChartView *chart = new QChartView(createBarChart(10));
        // chart->setRenderHint(QPainter::Antialiasing);
        // chart->setAttribute(Qt::WA_TranslucentBackground);
        // setStyleSheet("background: transparent;");  //透明色
        // layoutMain->addWidget(chart);
        // 添加视频播放器 1
        QMediaPlaylist *playlist1 = new QMediaPlaylist(this);
        playlist1->addMedia(QUrl("qrc:/new/1.mp4")); // 添加第一个视频
        playlist1->setPlaybackMode(QMediaPlaylist::Loop); // 设置循环播放模式

        QMediaPlayer *player1 = new QMediaPlayer(this);
        QVideoWidget *videoWidget1 = new QVideoWidget(this);

        // 设置视频播放器的最小和最大高度
        videoWidget1->setMinimumHeight(300); // 最小高度为 300
        videoWidget1->setMaximumHeight(600); // 最大高度为 600

        player1->setPlaylist(playlist1); // 设置播放列表
        player1->setVideoOutput(videoWidget1); // 设置视频输出


        player1->play();

        // 设置视频播放器样式
        videoWidget1->setStyleSheet("background: transparent; border: 1px solid rgba(255, 255, 255, 50);");


        // 添加视频播放器 2:/image/res/1.mp4
        QMediaPlaylist *playlist2 = new QMediaPlaylist(this);
        playlist2->addMedia(QUrl("qrc:/new/2.mp4")); // 添加第二个视频
        playlist2->setPlaybackMode(QMediaPlaylist::Loop); // 设置循环播放模式

        QMediaPlayer *player2 = new QMediaPlayer(this);
        QVideoWidget *videoWidget2 = new QVideoWidget(this);

        // 设置视频播放器的最小和最大高度
        videoWidget2->setMinimumHeight(300); // 最小高度为 300
        videoWidget2->setMaximumHeight(600); // 最大高度为 600

        player2->setPlaylist(playlist2); // 设置播放列表
        player2->setVideoOutput(videoWidget2); // 设置视频输出


        player2->play();

        // 设置视频播放器样式
        videoWidget2->setStyleSheet("background: transparent; border: 1px solid rgba(255, 255, 255, 50);");

        layoutMain->addWidget(videoWidget1);
        layoutMain->addLayout(layoutRow2);
        layoutMain->addWidget(videoWidget2);
    }

}

DataTable generateRandomData(int listCount, int valueMax, int valueCount)
{
    DataTable dataTable;

    // generate random data
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = yValue + QRandomGenerator::global()->bounded(valueMax / (qreal) valueCount);
            QPointF value((j + QRandomGenerator::global()->generateDouble()) * ((qreal) valueCount / (qreal) valueCount),
                          yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}

// QChart *CAlarmSummary::createBarChart(int valueCount) const
// {
//     Q_UNUSED(valueCount);
//     QChart *chart = new QChart();
//     chart->setMargins(QMargins(0, 0, 0, 0));
//     chart->setBackgroundBrush(Qt::transparent);
//     chart->setTitle("");
//     chart->setAnimationOptions(QChart::AllAnimations);

//     DataTable m_dataTable = generateRandomData(2, 1800, 7);

//     QStackedBarSeries *series = new QStackedBarSeries(chart);
//     for (int i(0); i < m_dataTable.count(); i++)
//     {
//         QBarSet *set = new QBarSet(i == 0 ? "人员报警" : "车辆报警");
//         set->setLabelColor(QColor("blue")); // 设置Series文本颜色为蓝色
//         for (const Data &data : m_dataTable[i])
//             *set << data.first.y();
//         series->append(set);
//     }
//     chart->addSeries(series);

//     chart->createDefaultAxes();
//     chart->axes(Qt::Vertical).first()->setRange(0, 2000);

//     // Add space to label to add space between labels and axis
//     QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
//     Q_ASSERT(axisY);
//     axisY->setLabelFormat("%.1f  ");

//     foreach (auto iter, chart->axes())
//     {
//         iter->setLabelsColor(QColor(255, 255, 255));
//     }

//     chart->legend()->setLabelColor(QColor(255, 255, 255));

//     return chart;
// }
