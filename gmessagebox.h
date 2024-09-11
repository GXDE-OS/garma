#ifndef GMESSAGEBOX_H
#define GMESSAGEBOX_H

#include <QObject>
#include "ddialog.h"

DWIDGET_BEGIN_NAMESPACE
class GMessageBox: public DDialog
{
    Q_OBJECT
public:
    enum Icon {
        // keep this in sync with QMessageDialogOptions::Icon
        NoIcon = 0,
        Information = 1,
        Warning = 2,
        Critical = 3,
        Question = 4
    };
    Q_ENUM(Icon)

    enum StandardButton {
        // keep this in sync with QDialogButtonBox::StandardButton and QPlatformDialogHelper::StandardButton
        //NoButton           = 0x00000000,
        Ok                 = 0x00000400,
        Save               = 0x00000800,
        SaveAll            = 0x00001000,
        Open               = 0x00002000,
        Yes                = 0x00004000,
        YesToAll           = 0x00008000,
        No                 = 0x00010000,
        NoToAll            = 0x00020000,
        Abort              = 0x00040000,
        Retry              = 0x00080000,
        Ignore             = 0x00100000,
        Close              = 0x00200000,
        Cancel             = 0x00400000,
        Discard            = 0x00800000,
        Help               = 0x01000000,
        Apply              = 0x02000000,
        Reset              = 0x04000000,
        RestoreDefaults    = 0x08000000,

        FirstButton        = Ok,                // internal
        LastButton         = RestoreDefaults,   // internal

        YesAll             = YesToAll,          // obsolete
        NoAll              = NoToAll,           // obsolete

        Default            = 0x00000100,        // obsolete
        Escape             = 0x00000200,        // obsolete
        FlagMask           = 0x00000300,        // obsolete
        ButtonMask         = ~FlagMask          // obsolete
    };
    typedef StandardButton Button;  // obsolete
    Q_DECLARE_FLAGS(StandardButtons, StandardButton)

    explicit GMessageBox(QWidget *parent = nullptr);
    GMessageBox(QWidget *parent,
                const QString &title, const QString &text);


    void setText(const QString &text);

    Icon icon() const;
    void setIcon(Icon);

    //void setStandardButtons(StandardButtons buttons);
    void setStandardButtonsWithList(QList<StandardButtons> buttons);


    // DDialog 已实现该函数
    //QPixmap iconPixmap() const;
    //void setIconPixmap(const QPixmap &pixmap);

private:
    Icon nowIcon;
};
DWIDGET_END_NAMESPACE

#endif // GMESSAGEBOX_H
