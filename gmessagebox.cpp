#include "gmessagebox.h"
#include "dapplication.h"
#include <QStyle>
#include <QPixmap>
#include <QLabel>
#include <QDebug>
DWIDGET_USE_NAMESPACE
GMessageBox::GMessageBox(QWidget *parent): DDialog(parent)
{

}

GMessageBox::GMessageBox(QWidget *parent,
                         const QString &title,
                         const QString &text): DDialog(parent)
{
    this->setText(text);
    this->setTitle(title);
}

GMessageBox::Icon GMessageBox::icon() const
{
    return nowIcon;
}

void GMessageBox::setIcon(Icon icon)
{
    enum QStyle::StandardPixmap dialogIcon;
    nowIcon = icon;
    switch(icon)
    {
    case Icon::NoIcon:
        return;
        break;
    case Icon::Critical:
        dialogIcon = (enum QStyle::StandardPixmap)11;
        break;
    case Icon::Information:
        dialogIcon = (enum QStyle::StandardPixmap)9;
        break;
    case Icon::Question:
        dialogIcon = (enum QStyle::StandardPixmap)12;
        break;
    case Icon::Warning:
        dialogIcon = (enum QStyle::StandardPixmap)10;
        break;
    }
    this->setIconPixmap(DApplication::style()->standardIcon(dialogIcon).pixmap(64, 64));
}

void GMessageBox::setStandardButtonsWithList(QList<StandardButtons> buttons)
{
    QStringList buttonsList;
    for(StandardButtons i: buttons) {
        switch(i) {
        case StandardButton::Ok:
            buttonsList << tr("OK");
            break;
        case StandardButton::Save:
            buttonsList << tr("Save");
            break;
        case StandardButton::SaveAll:
            buttonsList << tr("Save All");
            break;
        case StandardButton::Open:
            buttonsList << tr("Open");
            break;
        case StandardButton::Yes:
            buttonsList << tr("Yes");
            break;
        case StandardButton::YesToAll:
            buttonsList << tr("Yes To All");
            break;
        case StandardButton::No:
            buttonsList << tr("No");
            break;
        case StandardButton::NoToAll:
            buttonsList << tr("No To All");
            break;
        case StandardButton::Abort:
            buttonsList << tr("Abort");
            break;
        case StandardButton::Retry:
            buttonsList << tr("Retry");
            break;
        case StandardButton::Ignore:
            buttonsList << tr("Ignore");
            break;
        case StandardButton::Close:
            buttonsList << tr("Close");
            break;
        case StandardButton::Cancel:
            buttonsList << tr("Cancel");
            break;
        case StandardButton::Discard:
            buttonsList << tr("Discard");
            break;
        case StandardButton::Help:
            buttonsList << tr("Help");
            break;
        case StandardButton::Apply:
            buttonsList << tr("Apply");
            break;
        case StandardButton::Reset:
            buttonsList << tr("Reset");
            break;
        case StandardButton::RestoreDefaults:
            buttonsList << tr("Restore Defaults");
            break;
        }
    }
    for(int i = 0; i < buttonsList.count() - 1; ++i) {
        this->addButton(buttonsList.at(i));
    }
    this->addButton(buttonsList.at(buttonsList.length() - 1), true, ButtonType::ButtonRecommend);
}

void GMessageBox::setText(const QString &text)
{
    QLabel *label = findChild<QLabel*>("MessageLabel");
    if (label) {
        qDebug() << "Find Label";
        label->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
        label->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    }
    QString newText = text;
    this->setMessage(newText.replace("\\n", "\n"));
}

