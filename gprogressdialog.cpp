#include "gprogressdialog.h"

DWIDGET_USE_NAMESPACE

GProgressDialog::GProgressDialog(QWidget *parent)
    : DDialog(parent)
{
    m_progressbar = new DWaterProgress;
    m_tipsText = new QLabel();
    m_cancelButton = new QPushButton(tr("Cancel"));

    // 开启动画
    m_progressbar->start();

    m_layout = new QGridLayout();
    m_layout->addWidget(m_progressbar, 0, 0);
    m_layout->addWidget(m_tipsText, 0, 1);

    m_dialogWidget = new QWidget();
    m_dialogWidget->setLayout(m_layout);
    this->addContent(m_dialogWidget);

    addButton(tr("Cancel"), true, ButtonType::ButtonWarning);
}

void GProgressDialog::setLabelText(QString text)
{
    // 设置文本居中
    m_tipsText->setText(text);
}

void GProgressDialog::setValue(int value)
{
    if (m_busy) {
        // 显示繁忙动画
        m_progressbar->setValue(100);
        m_progressbar->setTextVisible(false);
        return;
    }
    m_value = value;
    m_progressbar->setTextVisible(true);
    m_progressbar->setValue((m_value - m_minimum) * 100 / (m_maximum - m_minimum));
}

int GProgressDialog::value()
{
    return m_value;
}

void GProgressDialog::setCancelButtonText(QString text)
{
    m_cancelButton->setText(text);
}

void GProgressDialog::setRange(int min, int max)
{
    m_maximum = max;
    m_minimum = min;
    m_busy = false;
    if (min == 0 && max == 0) {
        // 繁忙动画
        m_busy = true;
    }
    setValue(m_value);
}

int GProgressDialog::minimum()
{
    return m_minimum;
}

int GProgressDialog::maximum()
{
    return m_maximum;
}
