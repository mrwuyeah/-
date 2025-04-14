#ifndef DYNAMICSEARTH_H
#define DYNAMICSEARTH_H

#include <QWidget>
#include <QWebEngineView>
#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>

class CDynamicsEarth : public QWidget
{
    Q_OBJECT
public:
    explicit CDynamicsEarth(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;

protected:
    void paintEvent(QPaintEvent *) override;
    void timerEvent(QTimerEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void showMap();
    void initWebView();

    QPixmap m_pixBg;
    QPixmap m_pixMask1;
    QPixmap m_pixMask2;
    QPushButton *m_mapButton;
    QWebEngineView *m_webView = nullptr;
    int angle = 0;

    QLabel *m_titleLabel;  // 添加标题标签成员变量
};

#endif // DYNAMICSEARTH_H
