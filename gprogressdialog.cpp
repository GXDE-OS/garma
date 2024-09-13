#include "gprogressdialog.h"

DWIDGET_USE_NAMESPACE

GProgressDialog::GProgressDialog(QWidget *parent)
    : DAbstractDialog(parent)
{
    m_progressbar = new DWaterProgress;
    m_tipsText = new QLabel();
    m_cancelButton = new QPushButton(tr("Cancel"));

    // 开启动画
    m_progressbar->start();

    connect(m_cancelButton, &QPushButton::clicked, this, [this](){
        this->close();
    });

    m_layout = new QVBoxLayout();
    m_layout->addWidget(m_tipsText);
    m_layout->addWidget(m_progressbar);
    m_layout->addWidget(m_cancelButton);

    setLayout(m_layout);
}

void GProgressDialog::setLabelText(QString text)
{
    // 设置文本居中
    m_tipsText->setText("<p align='center'>" + text + "</p>");
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
    m_progressbar->setValue((m_value - m_minimum) * 1.0 / (m_maximum - m_minimum));
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
