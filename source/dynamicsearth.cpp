#include "dynamicsearth.h"
#include <QPainter>
#include <QTimerEvent>
#include <QDebug>
#include <QWebEngineSettings>  // 必须添加
#include <QWebEngineView>      // 如果使用 QWebEngineView


CDynamicsEarth::CDynamicsEarth(QWidget *parent) : QWidget(parent)
{

    // 启用 OpenGL 渲染和透明背景
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_AlwaysStackOnTop);
    setAttribute(Qt::WA_PaintOnScreen);  // 直接渲染到屏幕，绕过 Qt 的合成器

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

void CDynamicsEarth::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHints(
        QPainter::Antialiasing |
        QPainter::SmoothPixmapTransform |
        QPainter::TextAntialiasing
        );

    // 使用 GPU 优化的 drawPixmap 重载
    if (!m_pixBg.isNull()) {
        QRectF targetRect(
            (width() - m_pixBg.width()) / 2.0,
            (height() - m_pixBg.height()) / 2.0,
            m_pixBg.width(),
            m_pixBg.height()
            );
        painter.drawPixmap(targetRect, m_pixBg, m_pixBg.rect());
    }

    // 旋转效果（GPU 加速）
    if (!m_pixMask1.isNull()) {
        painter.save();
        painter.translate(rect().center());
        painter.rotate(angle);
        painter.drawPixmap(
            -m_pixMask1.width() / 2.0,
            -m_pixMask1.height() / 2.0,
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

        // 启用 WebEngine 的硬件加速
        QWebEngineSettings::defaultSettings()->setAttribute(
            QWebEngineSettings::Accelerated2dCanvasEnabled, true
            );
        QWebEngineSettings::defaultSettings()->setAttribute(
            QWebEngineSettings::WebGLEnabled, true
            );
        QWebEngineSettings::defaultSettings()->setAttribute(
            QWebEngineSettings::PluginsEnabled, true
            );

        m_webView = new QWebEngineView();
        m_webView->page()->settings()->setAttribute(
            QWebEngineSettings::LocalStorageEnabled, true
            );

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
