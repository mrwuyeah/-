#include "dynamicsearth.h"
#include <QPainter>
#include <QTimerEvent>
#include <QDebug>


CDynamicsEarth::CDynamicsEarth(QWidget *parent) : QWidget(parent)
{



    // 初始化地球图片
    resizeEvent(nullptr);

    // 设置透明按钮
    m_mapButton = new QPushButton(this);
    m_mapButton->setStyleSheet("background: transparent; border: none;");
    m_mapButton->setCursor(Qt::PointingHandCursor);
    m_mapButton->setGeometry(0, 0, 100, 100);

    // 定时旋转
    startTimer(40);
}

void CDynamicsEarth::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // 绘制背景地球
    if (!m_pixBg.isNull()) {
        painter.drawPixmap(
            (width() - m_pixBg.width()) / 2,
            (height() - m_pixBg.height()) / 2,
            m_pixBg
            );
    }

    // 绘制旋转效果
    if (!m_pixMask1.isNull()) {
        painter.save();
        painter.translate(rect().center());
        painter.rotate(angle);
        painter.drawPixmap(
            -m_pixMask1.width() / 2,
            -m_pixMask1.height() / 2,
            m_pixMask1
            );
        painter.restore();
    }
}

void CDynamicsEarth::timerEvent(QTimerEvent *event)
{
    angle = (angle + 1) % 360;
    update();
}

void CDynamicsEarth::resizeEvent(QResizeEvent *event)
{
    // 加载并缩放图片
    m_pixBg = QPixmap(":/image/res/map.png").scaled(244, 244, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_pixMask1 = QPixmap(":/image/res/lbx.png").scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 调整按钮位置 - 安全版本

}

void CDynamicsEarth::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QRect earthRect(
            (width() - m_pixBg.width()) / 2,
            (height() - m_pixBg.height()) / 2,
            m_pixBg.width(),
            m_pixBg.height()
            );

        if (earthRect.contains(event->pos())) {
            showMap();
        }
    }
    QWidget::mousePressEvent(event);  // 确保调用基类实现
}

void CDynamicsEarth::showMap()
{
    // if (!QWebEngineView::supportsMultipleWindows()) {
    //     qWarning() << "WebEngine doesn't support multiple windows!";
    //     return;
    // }

    if (!m_webView) {
        m_webView = new QWebEngineView(); // 不指定父对象
        m_webView->setAttribute(Qt::WA_DeleteOnClose);
        connect(m_webView, &QWebEngineView::destroyed, [this]() {
            m_webView = nullptr;
        });

        // 先加载空白页面测试
        m_webView->setHtml("<h1>Loading...</h1>");
    }

    m_webView->resize(800, 600);
    // 加载 HTML 文件
    m_webView->load(QUrl("qrc:/new/map.html"));
    m_webView->show();
    m_webView->raise();
}
