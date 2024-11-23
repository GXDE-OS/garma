#include "dialogmanager.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>

DialogManager::DialogManager()
{

}

QSize DialogManager::getAutoSize()
{
    // 获取屏幕分辨率
    QSize size = QGuiApplication::screens().first()->availableGeometry().size();
    size.setWidth(size.width() / 5);
    size.setHeight(size.height() / 5);
    return size;
}
