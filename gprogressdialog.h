#ifndef GPROGRESSDIALOG_H
#define GPROGRESSDIALOG_H

#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include "dabstractdialog.h"
#include "dwaterprogress.h"
#include "ddialog.h"
DWIDGET_BEGIN_NAMESPACE

class GProgressDialog: public DDialog
{
public:
    GProgressDialog(QWidget *parent = nullptr);
    void setLabelText(QString text);
    void setValue(int value);
    int maximum();
    int minimum();
    int value();
    void setCancelButtonText(QString text);
    void setRange(int min, int max);


private:
    DWaterProgress *m_progressbar;
    QLabel *m_tipsText;
    QPushButton *m_cancelButton;
    QGridLayout *m_layout;
    QWidget *m_dialogWidget;
    // 需要自行实现范围的计算
    int m_maximum = 100;
    int m_minimum = 0;
    int m_value = 0;
    bool m_busy = false;



};

DWIDGET_END_NAMESPACE

#endif // GPROGRESSDIALOG_H
