#ifndef DEFINE_GLOBAL_H
#define DEFINE_GLOBAL_H

#include <dapplication.h>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    #define SKIP_EMPTY Qt::SkipEmptyParts
#else
    #define SKIP_EMPTY QString::SkipEmptyParts
#endif
DWIDGET_USE_NAMESPACE

#define IF_IS(_TYPE_) if (const _TYPE_ *t = qobject_cast<const _TYPE_*>(w))

#define NEXT_ARG QString((++i < args.count()) ? args.at(i) : QString())
#define WARN_UNKNOWN_ARG(_KNOWN_) if (args.at(i).startsWith("--") && args.at(i) != _KNOWN_) qDebug() << "unspecific argument" << args.at(i);
#define SHOW_DIALOG m_dialog = dlg; connect(dlg, SIGNAL(finished(int)), SLOT(dialogFinished(int))); dlg->show();
#define READ_INT(_V_, _TYPE_, _ERROR_) bool ok; const int _V_ = NEXT_ARG.to##_TYPE_(&ok); if (!ok) return !error(_ERROR_)

#define NEW_DIALOG DDialog *dlg = new DDialog; \
    QWidget *dialogWidget = new QWidget(dlg); \
    QVBoxLayout *vl = new QVBoxLayout(dialogWidget); \
    dialogWidget->setLayout(vl); \
    dlg->addContent(dialogWidget); \
    if (m_popup) dlg->setWindowFlags(Qt::Popup);
/*#define FINISH_DIALOG(_BTNS_)   QDialogButtonBox *btns = new QDialogButtonBox(_BTNS_, Qt::Horizontal, dlg);\
                                vl->addWidget(btns);\
                                connect(btns, SIGNAL(accepted()), dlg, SLOT(accept()));\
                                connect(btns, SIGNAL(rejected()), dlg, SLOT(reject()));*/
#define FINISH_OK_CANCEL_DIALOG dlg->addButton(tr("Cancel")); \
    dlg->addButton(tr("OK"), true, DDialog::ButtonType::ButtonRecommend);

#endif // DEFINE_GLOBAL_H
