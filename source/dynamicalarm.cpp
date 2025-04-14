#include "dynamicalarm.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QDebug>


#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

CDynamicAlarm::CDynamicAlarm(QWidget *parent) : CAbstractCard(parent)
{
    setTitle("红外报警");

    QVBoxLayout *layoutMain = new QVBoxLayout(getMainWnd());
    layoutMain->setMargin(20);
    layoutMain->setSpacing(20);

    {
        CLineSlider *slider = new CLineSlider(this);
        slider->setFixedHeight(8);
        layoutMain->addWidget(slider);

        {
            QPropertyAnimation *animation1 = new QPropertyAnimation(slider, "value");
            animation1->setDuration(1000);
            animation1->setStartValue(55);
            animation1->setEndValue(75);
            animation1->setEasingCurve(QEasingCurve::OutQuad);

            QPropertyAnimation *animation2 = new QPropertyAnimation(slider, "value");
            animation2->setDuration(2000);
            animation2->setStartValue(80);
            animation2->setEndValue(60);
            animation2->setEasingCurve(QEasingCurve::InCubic);

            // 创建动画组并添加动画对象
            QSequentialAnimationGroup *group = new QSequentialAnimationGroup();
            group->addAnimation(animation1);
            group->addAnimation(animation2);
            group->setLoopCount(-1);

            // 启动动画组
            group->start();
        }
    }

    {
        QLabel *label1 = new QLabel("最近障碍物距离:", this);
        QLabel *label2 = new QLabel("60厘米", this);
        QLabel *label3 = new QLabel("障碍物方向:", this);
        QLabel *label4 = new QLabel("右前方", this);

        label1->setStyleSheet("QLabel{color:#637c9f; font-size:12px;}");
        label2->setStyleSheet("QLabel{color:#ff0000; font-size:12px;}");
        label3->setStyleSheet("QLabel{color:#637c9f; font-size:12px;}");
        label4->setStyleSheet("QLabel{color:#efeb7b; font-size:12px;}");

        QHBoxLayout *layoutRow = new QHBoxLayout();
        layoutRow->addWidget(label1);
        layoutRow->addWidget(label2);
        layoutRow->addStretch(1);
        layoutRow->addWidget(label3);
        layoutRow->addWidget(label4);
        layoutRow->setSpacing(6);

        layoutMain->addLayout(layoutRow);
    }

    // 添加视频播放器 1
    playlist3 = new QMediaPlaylist(this);
    player3 = new QMediaPlayer(this);

    // 创建一个容器 widget
    videoContainer3 = new QWidget(this);
    videoContainer3->setStyleSheet("background: blue; border: 1px solid rgba(255, 255, 255, 50);");

    videoWidget3 = new QVideoWidget(videoContainer3);
    // 创建一个布局用于容器
    QVBoxLayout *videoLayout3 = new QVBoxLayout(videoContainer3);
    // 创建 QVideoWidget 并添加到容器中
    videoLayout3->addWidget(videoWidget3);
    videoContainer3->setLayout(videoLayout3);

    player3->setVideoOutput(videoWidget3); // 设置视频输出
    QString videoPath;
    videoPath = "C:\\Users\\18163\\Desktop\\QT\\qt_test_1\\test_1\\3.mp4";
    playlist3->addMedia(QUrl::fromLocalFile(videoPath));
    // playlist1->addMedia(QUrl("qrc:/image/res/1.mp4")); // 添加第一个视频
    player3->setPlaylist(playlist3); // 设置播放列表


    // 设置视频播放器的最小和最大高度
    videoContainer3->setMinimumHeight(300); // 最小高度为 300
    videoContainer3->setMaximumHeight(600); // 最大高度为 600
    // 将容器 widget 添加到主布局
    layoutMain->addWidget(videoContainer3);


    // 在CDynamicAlarm构造函数中添加两个按钮
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
    layoutMain->addLayout(buttonLayout);

    // 连接按钮信号
    connect(playButton, &QPushButton::clicked, [this]() {
        player3->play();
    });
    connect(pauseButton, &QPushButton::clicked, [this]() {
        player3->pause();
    });



    // // 播放视频
    // player3->play();
}



int CLineSlider::getValue() const
{
    return m_value;
}

void CLineSlider::setValue(int value)
{
    m_value = value;
    update();
}
