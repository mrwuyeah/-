#ifndef VISUALIZEDATA_H
#define VISUALIZEDATA_H

#include <QWidget>
#include "dynamicsearth.h"
#include "title.h"
#include <QDebug>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>



class CDynamicsEarth;
class CTitle;
class CVisualizeData : public QWidget
{
    Q_OBJECT

public:
    CVisualizeData(QWidget *parent = 0);
    ~CVisualizeData();

private:
    void Layout();

private:
    CTitle *m_pTitle;
    CDynamicsEarth *m_pDynamicsEarth;


    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event) override;
};

#endif // VISUALIZEDATA_H
