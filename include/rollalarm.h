#ifndef ROLLALARM_H
#define ROLLALARM_H

#include "abstractcard.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QDebug>
#include <QTimer>
#include <QDateTime>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

struct AlarmItem {
    QString addr1;
    QString addr2;
    QString code;
    QString time;
};

class CRollWidget : public QWidget {
    Q_OBJECT
    Q_PROPERTY(int value READ getValue WRITE setValue)
public:
    explicit CRollWidget(QWidget *parent = nullptr);
    void append(const QString &message);
    void append(const QString &addr1, const QString &addr2, const QString &code, const QString &time);
    int getValue() const;
    void setValue(int _value);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QList<AlarmItem> m_value;
    int value = 0;
};

class CRollAlarm : public CAbstractCard {
    Q_OBJECT
public:
    explicit CRollAlarm(QWidget *parent = nullptr);

private:
    int m_alarmCount = 0;
};

#endif // ROLLALARM_H
