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




#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


CAlarmSummary::CAlarmSummary(QWidget *parent) : CAbstractCard(parent)
{
    setTitle("车内状态汇总");

    QVBoxLayout *layoutMain = new QVBoxLayout();
    QVBoxLayout *layoutMain1 = new QVBoxLayout(getMainWnd());
    layoutMain1->setContentsMargins(10, 0, 10, 0);
    layoutMain->setSpacing(10);
    layoutMain1->setSpacing(10);

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



    layoutMain1->addLayout(layoutMain, 5);

    QLabel *label1 = new QLabel("车内疲劳检测", this);
    label1->setAlignment(Qt::AlignCenter);
    label1->setStyleSheet("QLabel{color:#49bcf7; font-size:20px; border: 1px solid rgba(25,186,139,40); background: rgba(255,255,255,12)}");

    QLabel *label2 = new QLabel("车外障碍监测", this);
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

    // QChartView *chart = new QChartView(createBarChart(10));
    // chart->setRenderHint(QPainter::Antialiasing);
    // chart->setAttribute(Qt::WA_TranslucentBackground);
    // setStyleSheet("background: transparent;");  //透明色
    // layoutMain->addWidget(chart);
    // 添加视频播放器 1
    playlist1 = new QMediaPlaylist(this);
    player1 = new QMediaPlayer(this);

    // 创建一个容器 widget
    videoContainer1 = new QWidget(this);
    // videoContainer1->setStyleSheet("background: blue; border: 1px solid rgba(255, 255, 255, 50);");

    videoWidget1 = new QVideoWidget(videoContainer1);
    // 创建一个布局用于容器
    QVBoxLayout *videoLayout1 = new QVBoxLayout(videoContainer1);
    // 创建 QVideoWidget 并添加到容器中
    videoLayout1->addWidget(videoWidget1);
    videoContainer1->setLayout(videoLayout1);

    player1->setVideoOutput(videoWidget1); // 设置视频输出
    QString videoPath;
    // videoPath = "C:\\Users\\18163\\Desktop\\QT\\qt_test_1\\test_1\\11.mp4";
    playlist1->addMedia(QUrl::fromLocalFile(videoPath));
    // playlist1->addMedia(QUrl("qrc:/image/res/1.mp4")); // 添加第一个视频
    player1->setPlaylist(playlist1); // 设置播放列表


    // 设置视频播放器的最小和最大高度
    videoContainer1->setMinimumHeight(300); // 最小高度为 300
    videoContainer1->setMaximumHeight(600); // 最大高度为 600



    // 播放视频
    player1->play();


    // 设置视频播放器样式
    videoWidget1->setStyleSheet("background: transparent; border: 1px solid rgba(255, 255, 255, 50);");


    // 添加视频播放器 2:/image/res/1.mp4
    QMediaPlaylist *playlist2 = new QMediaPlaylist(this);
    QString videoPath2;
    // videoPath2 = "C:\\Users\\18163\\Desktop\\QT\\qt_test_1\\test_1\\22.mp4";
    playlist2->addMedia(QUrl::fromLocalFile(videoPath2));
    //playlist2->addMedia(QUrl("qrc:/new/2.mp4")); // 添加第二个视频

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

    connect(player1, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), [](QMediaPlayer::Error error) {
        qDebug() << "Media player error:" << error;
    });

    layoutMain1->addWidget(videoContainer1,9);
    layoutMain1->addLayout(layoutRow2,1);
    layoutMain1->addWidget(videoWidget2,9);


}

QWidget *CAlarmSummary::getVideoContainer1() const
{
    return 0;
}

DataTable generateRandomData(int listCount, int valueMax, int valueCount)
{
    DataTable dataTable;

    // generate random data
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = 30 + QRandomGenerator::global()->bounded(valueMax / 2);
            // yValue = yValue + QRandomGenerator::global()->bounded(valueMax / (qreal) valueCount);
            QPointF value((j + QRandomGenerator::global()->generateDouble()) * ((qreal) valueCount / (qreal) valueCount),
                          yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            // QPointF value((j + QRandomGenerator::global()->generateDouble()) * ((qreal) valueCount / (qreal) valueCount),
            //               yValue);
            // QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
            yValue = 0;
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
