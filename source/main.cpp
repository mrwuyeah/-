#include "visualizedata.h"
#include <QApplication>
#include <QtWebEngineWidgets>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{

    // 配置 OpenGL 核心模式
    // QSurfaceFormat format;
    // format.setVersion(4, 6);  // 匹配你的显卡驱动版本
    // format.setProfile(QSurfaceFormat::CoreProfile);
    // format.setRenderableType(QSurfaceFormat::OpenGL);
    // format.setSwapInterval(1);  // 启用垂直同步
    // QSurfaceFormat::setDefaultFormat(format);


    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 9));

    CVisualizeData w;
    w.show();
    return a.exec();
}
