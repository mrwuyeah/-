#include "visualizedata.h"
#include "dynamicsearth.h"
#include "title.h"
#include <QDebug>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>

#include "abstractcard.h"
#include "alarmsummary.h"
#include "histroychart.h"
#include "piechart.h"
#include "datasummary.h"
#include "dynamicalarm.h"
#include "rollalarm.h"
#include "circulardialsummary.h"

CVisualizeData::CVisualizeData(QWidget *parent)
    : QWidget(parent)
{
    m_pTitle = new CTitle(this);
    m_pDynamicsEarth = new CDynamicsEarth(this);

    m_pTitle->setFixedHeight(105);
    m_pDynamicsEarth->setMinimumSize(300, 300);

    resize(1200, 800);
    setAttribute(Qt::WA_StyledBackground);
    //setStyleSheet("background-image: url(:/image/res/bg.jpg); background-repeat: no-repeat; background-position: center; background-attachment: fixed;");
    //showFullScreen();
    // 绘制背景图片

    setCursor(QCursor(QPixmap(":/image/res/pointer.png")));

    Layout();
}

void CVisualizeData::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // 避免未使用参数的警告

    QPainter painter(this);
    if (!painter.isActive()) {
        return; // 确保 QPainter 已激活
    }

    // 绘制背景图片
    QPixmap background(":/image/res/bg.jpg");
    if (!background.isNull()) {
        painter.drawPixmap(rect(), background.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}

CVisualizeData::~CVisualizeData()
{

}

void CVisualizeData::Layout()
{
    QVBoxLayout *layoutMain = new QVBoxLayout(this);
    layoutMain->setMargin(0);
    layoutMain->setSpacing(0);

    QVBoxLayout *layoutLeft = new QVBoxLayout();
    layoutLeft->setSpacing(10);
    layoutLeft->setMargin(0);
    layoutLeft->addWidget(new CAlarmSummary(), 2);
    layoutLeft->addWidget(new CHistroyChart(), 1);

    QVBoxLayout *layoutCenter = new QVBoxLayout();
    layoutCenter->setSpacing(10);
    layoutCenter->setMargin(0);
    layoutCenter->addWidget(new CDataSummary(), 1);
    layoutCenter->addWidget(m_pDynamicsEarth, 2);
    layoutCenter->addWidget(new CCirculardialSummary(), 1);

    QVBoxLayout *layoutRight = new QVBoxLayout();
    layoutRight->setSpacing(10);
    layoutRight->setMargin(0);
    layoutRight->addWidget(new CPieChart(), 3);
    layoutRight->addWidget(new CDynamicAlarm(), 1);
    layoutRight->addWidget(new CRollAlarm(), 2);

    QHBoxLayout *layoutContent = new QHBoxLayout();
    layoutContent->setMargin(10);
    layoutContent->setSpacing(40);
    layoutContent->addLayout(layoutLeft, 2);
    layoutContent->addLayout(layoutCenter, 3);
    layoutContent->addLayout(layoutRight, 2);

    layoutMain->addWidget(m_pTitle);
    layoutMain->addLayout(layoutContent, 1);
}

void CVisualizeData::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        isFullScreen() ? showNormal() : showFullScreen();
    }
}
