#include "rollalarm.h"

CRollWidget::CRollWidget(QWidget *parent) : QWidget(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void CRollWidget::append(const QString &message) {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

    // 简化版报警信息，只显示消息和时间
    append("系统", "警报", message, formattedDateTime);
}

void CRollWidget::append(const QString &addr1, const QString &addr2, const QString &code, const QString &time) {
    m_value.append({addr1, addr2, code, time});
    // 限制最多显示20条报警信息
    if (m_value.size() > 20) {
        m_value.removeFirst();
    }

    QPropertyAnimation *animation = new QPropertyAnimation(this, "value");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(100);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void CRollWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);

    QRect rcClient = rect();
    const int LINE_HEIGHT = 32;
    int nRow = rcClient.height() / LINE_HEIGHT;

    painter.setPen(QColor(255, 255, 255, 150));

    QRect rcRealClient = rcClient;
    if (m_value.length() > nRow) {
        rcRealClient = rcClient;
        rcRealClient.setTop(rcRealClient.top() - (LINE_HEIGHT * ((double)value / 100.0)));
    }

    int i = 0;
    foreach (auto item, m_value.mid(m_value.size() - nRow - 1)) {
        QRect rcText = rcRealClient;
        rcText.setTop(rcText.top() + i * LINE_HEIGHT);
        rcText.setHeight(LINE_HEIGHT);

        // 简化显示格式：时间 + 报警信息
        QString strText = QString("%1 - %2").arg(item.time).arg(item.code);

        QFontMetrics elideFont(painter.font());
        if (elideFont.horizontalAdvance(strText) > rcText.width()) {
            painter.drawText(rcText, Qt::AlignLeft | Qt::AlignVCenter,
                             elideFont.elidedText(strText, Qt::ElideRight, rcText.width()));
        } else {
            painter.drawText(rcText, Qt::AlignLeft | Qt::AlignVCenter, strText);
        }
        i++;
    }
}

int CRollWidget::getValue() const {
    return value;
}

void CRollWidget::setValue(int _value) {
    value = _value;
    update();
}

CRollAlarm::CRollAlarm(QWidget *parent) : CAbstractCard(parent) {
    setTitle("滚动报警");

    QVBoxLayout *layoutMain = new QVBoxLayout(getMainWnd());
    layoutMain->setContentsMargins(20, 20, 20, 20);
    layoutMain->setSpacing(20);

    CRollWidget *slider = new CRollWidget(this);
    layoutMain->addWidget(slider);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=] {
        m_alarmCount++;
        QDateTime currentDateTime = QDateTime::currentDateTime();

        // 简单的报警信息生成
        QString alarmMsg;
        if (m_alarmCount % 5 == 0) {
            alarmMsg = "系统检测到疲劳驾驶";
        } else if (m_alarmCount % 3 == 0) {
            alarmMsg = "酒精含量超标警告";
        } else {
            alarmMsg = "系统运行正常";
        }

        // 使用简化版的append方法
        slider->append(alarmMsg);
    });
    timer->start(3000); // 每3秒生成一条报警信息
}
