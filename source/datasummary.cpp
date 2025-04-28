#include "datasummary.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QRandomGenerator>
#include <QFont>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

CDataSummary::CDataSummary(QWidget *parent) : CAbstractCard(parent)
{
    setTitle("车辆行驶状况汇总");
    // // 设置字体
    // // 设置字体
    // QFont font;
    // font.setFamily("微软雅黑"); // 设置字体名称
    // font.setPointSize(18);     // 设置字体大小
    // font.setBold(true);        // 设置字体加粗

    // // 创建一个 QLabel 来显示标题
    // QLabel *titleLabel = new QLabel("车辆行驶状况汇总", this);
    // titleLabel->setFont(font);
    // titleLabel->setAlignment(Qt::AlignCenter);

    // 将标题标签添加到布局中
    QVBoxLayout *layoutMain = new QVBoxLayout(getMainWnd());
    layoutMain->setContentsMargins(10, 0, 10, 0);
    layoutMain->setSpacing(0);
    // layoutMain->addWidget(titleLabel);

    QTimer *timer = new QTimer(this);


    {
        // QLabel *label1 = new QLabel("6786", this);
        // QLabel *label2 = new QLabel("465", this);
        // QLabel *label3 = new QLabel("34532", this);
        QLabel *label1 = new QLabel("5", this);
        QLabel *label2 = new QLabel("正常", this);
        QLabel *label3 = new QLabel("异常", this);

        label1->setAlignment(Qt::AlignCenter);
        label2->setAlignment(Qt::AlignCenter);
        label3->setAlignment(Qt::AlignCenter);

        label1->setStyleSheet("QLabel{color:#efeb7b; font-size:36px; font-weight: bold;}");
        label2->setStyleSheet("QLabel{color:#efeb7b; font-size:36px; font-weight: bold;}");
        label3->setStyleSheet("QLabel{color:red; font-size:36px; font-weight: bold;}");

        QHBoxLayout *layoutRow = new QHBoxLayout();
        layoutRow->addWidget(label1);
        layoutRow->addWidget(CreateSeparator(true, this));
        layoutRow->addWidget(label2);
        layoutRow->addWidget(CreateSeparator(true, this));
        layoutRow->addWidget(label3);
        layoutRow->setContentsMargins(0, 0, 0, 0);

        layoutMain->addLayout(layoutRow);

        // connect(timer, &QTimer::timeout, [=]
        // {
        //     label1->setText(QString::number(QRandomGenerator::global()->bounded(8000)));
        //     label2->setText(QString::number(QRandomGenerator::global()->bounded(500)));
        //     label3->setText(QString::number(QRandomGenerator::global()->bounded(40000)));
        // });

    }

    {
        QLabel *label1 = new QLabel("5分钟内检测疲劳次数", this);
        QLabel *label2 = new QLabel("疲劳报警", this);
        QLabel *label3 = new QLabel("夜间行人报警", this);

        label1->setAlignment(Qt::AlignCenter);
        label2->setAlignment(Qt::AlignCenter);
        label3->setAlignment(Qt::AlignCenter);

        label1->setStyleSheet("QLabel{color:#637c9f; font-size:24px;}");
        label2->setStyleSheet("QLabel{color:#637c9f; font-size:24px;}");
        label3->setStyleSheet("QLabel{color:#637c9f; font-size:24px;}");

        QHBoxLayout *layoutRow = new QHBoxLayout();
        layoutRow->addWidget(label1);
        layoutRow->addWidget(label2);
        layoutRow->addWidget(label3);

        layoutMain->addLayout(layoutRow);
    }

    layoutMain->addWidget(CreateSeparator(false, this));

    // {
    //     QLabel *label1 = new QLabel("/", this);
    //     QLabel *label2 = new QLabel("/", this);
    //     QLabel *label3 = new QLabel("/", this);

    //     label1->setAlignment(Qt::AlignCenter);
    //     label2->setAlignment(Qt::AlignCenter);
    //     label3->setAlignment(Qt::AlignCenter);

    //     label1->setStyleSheet("QLabel{color:#ff0000; font-size:36px; font-weight: bold;}");
    //     label2->setStyleSheet("QLabel{color:#efeb7b; font-size:36px; font-weight: bold;}");
    //     label3->setStyleSheet("QLabel{color:red; font-size:36px; font-weight: bold;}");

    //     QHBoxLayout *layoutRow = new QHBoxLayout();
    //     layoutRow->addWidget(label1);
    //     layoutRow->addWidget(CreateSeparator(true, this));
    //     layoutRow->addWidget(label2);
    //     layoutRow->addWidget(CreateSeparator(true, this));
    //     layoutRow->addWidget(label3);
    //     layoutRow->setContentsMargins(0, 0, 0, 0);

    //     layoutMain->addLayout(layoutRow);

    //     // connect(timer, &QTimer::timeout, [=]
    //     // {
    //     //     label1->setText(QString::number(QRandomGenerator::global()->bounded(150)));
    //     //     label2->setText(QString::number(QRandomGenerator::global()->bounded(5000)));
    //     //     label3->setText(QString::number(QRandomGenerator::global()->bounded(300)));
    //     // });
    // }

    // {
    //     QLabel *label1 = new QLabel("待开发", this);
    //     QLabel *label2 = new QLabel("待开发", this);
    //     QLabel *label3 = new QLabel("待开发", this);

    //     label1->setAlignment(Qt::AlignCenter);
    //     label2->setAlignment(Qt::AlignCenter);
    //     label3->setAlignment(Qt::AlignCenter);

    //     label1->setStyleSheet("QLabel{color:#637c9f; font-size:24px;}");
    //     label2->setStyleSheet("QLabel{color:#637c9f; font-size:24px;}");
    //     label3->setStyleSheet("QLabel{color:#637c9f; font-size:24px;}");

    //     QHBoxLayout *layoutRow = new QHBoxLayout();
    //     layoutRow->addWidget(label1);
    //     layoutRow->addWidget(label2);
    //     layoutRow->addWidget(label3);

    //     layoutMain->addLayout(layoutRow);
    // }

    timer->start(1000);
}
