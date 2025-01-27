#include "gprogressdialog.h"
#include "dimagebutton.h"
#include "dapplication.h"
#include <QStyle>

DWIDGET_USE_NAMESPACE

GProgressDialog::GProgressDialog(QWidget *parent)
    : DDialog(parent)
{
    m_progressbar = new DWaterProgress;
    m_tipsText = new QLabel();
    m_cancelButton = new QPushButton(tr("Cancel"));
    m_progressbar->setFixedSize(60,60);
    // 开启动画
    m_progressbar->start();

    m_layout = new QGridLayout();
    m_layout->addWidget(m_progressbar, 0, 0);
    m_layout->addWidget(m_tipsText, 0, 1);

    m_dialogWidget = new QWidget();
    m_dialogWidget->setLayout(m_layout);
    this->addContent(m_dialogWidget);

    m_closeButton = this->findChild<DImageButton *>("CloseButton");

    // 最小化按钮
    m_miniButton = new DImageButton(this);
    m_miniButton ->setObjectName("MiniButton");
    m_miniButton ->adjustSize();
    m_miniButton->setStyleSheet("qproperty-normalPic: url(:/images/spinner_decrease_normal.png);"
                                "qproperty-hoverPic: url(:/images/spinner_decrease_hover.png);");
    //m_miniButton ->setFixedSize(DIALOG::CLOSE_BUTTON_WIDTH, DIALOG::CLOSE_BUTTON_HEIGHT);
    m_miniButton ->setAttribute(Qt::WA_NoMousePropagation);
    connect(m_miniButton, &DImageButton::clicked, this, &GProgressDialog::showMinimized);

    addButton(tr("Cancel"), true, ButtonType::ButtonWarning);

    installEventFilter(this);

    setFocusPolicy(Qt::StrongFocus);

    auto dialogIcon = (enum QStyle::StandardPixmap)9;
    this->setWindowIcon(DApplication::style()->standardIcon(dialogIcon));

    resizeMiniButton();
}

void GProgressDialog::resizeMiniButton()
{
    // 重新最小化按钮大小
    if (!m_closeButton || !m_miniButton) {
        return;
    }
    m_miniButton->setGeometry(m_closeButton->x() - m_closeButton->width() - m_closeButton->width() / 5,
                              m_closeButton->y(),
                              m_closeButton->width(),
                              m_closeButton->height());
}

void GProgressDialog::resizeEvent(QResizeEvent *event)
{
    DDialog::resizeEvent(event);
    // 重新计算最小化按钮大小
    resizeMiniButton();
}

void GProgressDialog::reject()
{
    // 通过重写 reject 来禁用 ESC 事件
    if (!m_isEnabledCloseButton) {
        // 如果设置为禁用关闭按钮且当前进度值不等于最大值（非繁忙状态），则不退出窗口
        if (m_value != m_maximum || m_busy) {
            return;
        }
    }
    qDebug() << m_value << m_maximum;
    DDialog::reject();
}

void GProgressDialog::setLabelText(QString text)
{
    // 设置文本居中
    m_tipsText->setText("    " + text.replace("\\n", "\n"));
    this->setWindowTitle(text);
}

void GProgressDialog::setValue(int value)
{
    if (m_busy) {
        // 显示繁忙动画
        m_progressbar->setValue(50);
        m_progressbar->setTextVisible(false);
        return;
    }
    m_value = value;
    m_progressbar->setTextVisible(true);
    m_progressbar->setValue((m_value - m_minimum) * 100 / (m_maximum - m_minimum));

    // 如果设置自动关闭则在等于最大值时自动关闭对话框
    if (m_maximum == m_value && property("Garma_autoclose").toBool()) {
        done(QDialog::Accepted);
    }
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

void GProgressDialog::setCloseButtonVisiable(bool status)
{
    m_isEnabledCloseButton = status;
    if (QPushButton *btn = this->findChild<QPushButton*>()) {
        if (m_isEnabledCloseButton) {
            btn->show();
            btn->setEnabled(true);
            btn->setAutoDefault(true);
            btn->setDefault(true);
        }
        else {
            btn->hide();
            btn->setDisabled(true);
            btn->setAutoDefault(false);
            btn->setDefault(false);
        }
    }

    // 关闭对话框右上角的关闭按钮
    if (DImageButton *diabtn = this->findChild<DImageButton*>("CloseButton")) {
        if (m_isEnabledCloseButton) {
           diabtn->show();
           diabtn->setEnabled(true);
        }
        else {
           diabtn->hide();
           diabtn->setDisabled(true);
        }
    }

    setOnButtonClickedClose(m_isEnabledCloseButton);
}


bool GProgressDialog::closeButtonVisiable() const
{
    return m_isEnabledCloseButton;
}

int GProgressDialog::minimum()
{
    return m_minimum;
}

int GProgressDialog::maximum()
{
    return m_maximum;
}
