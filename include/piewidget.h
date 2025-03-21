#ifndef PIEWIDGET_H
#define PIEWIDGET_H

#include <QPainterPath>
#include <QWidget>
#include <QList>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

class CPieWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CPieWidget(QWidget *parent = nullptr);

    struct Item
    {
        qreal percent;
        QString name;
        QColor color;
        QPainterPath path;
    };

    void append(qreal percent, QString name);

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);

private:
    QList<Item> m_listItem;
};

#endif // PIEWIDGET_H
