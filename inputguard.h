#ifndef INPUTGUARD_H
#define INPUTGUARD_H

#include <QObject>
#include <QWidget>
#include <QWindow>
#include <dapplication.h>

DWIDGET_USE_NAMESPACE

class InputGuard : public QObject
{
public:
    InputGuard() : QObject(), m_guardedWidget(NULL), m_checkTimer(0) {}
    static void watch(QWidget *w) {
#if QT_VERSION >= 0x050000
        if (qApp->platformName() == "wayland")
            return;
#endif
        if (!s_instance)
            s_instance = new InputGuard;
        w->installEventFilter(s_instance);
    }
protected:
    bool eventFilter(QObject *o, QEvent *e) {
        QWidget *w = static_cast<QWidget*>(o);
        switch (e->type()) {
            case QEvent::FocusIn:
            case QEvent::WindowActivate:
                if (hasActiveFocus(w))
                    guard(w);
                break;
            case QEvent::FocusOut:
            case QEvent::WindowDeactivate:
                if (w == m_guardedWidget && !hasActiveFocus(w))
                    unguard(w);
                break;
            default:
                break;
        }
        return false;
    }
    void timerEvent(QTimerEvent *te) {
        if (te->timerId() == m_checkTimer && m_guardedWidget)
            check(m_guardedWidget);
        else
            QObject::timerEvent(te);
    }
private:
    bool check(QWidget *w) {
#if QT_VERSION >= 0x050000
        // try to re-grab
        if (!w->window()->windowHandle()->setKeyboardGrabEnabled(true))
            w->releaseKeyboard();
#endif
        if (w == QWidget::keyboardGrabber()) {
            w->setPalette(QPalette());
            return true;
        }
        w->setPalette(QPalette(Qt::white, Qt::red, Qt::white, Qt::black, Qt::gray,
                               Qt::white, Qt::white, Qt::red, Qt::red));
        return false;
    }
    void guard(QWidget *w) {
        w->grabKeyboard();
        if (check(w))
            m_guardedWidget = w;
        if (!m_checkTimer)
            m_checkTimer = startTimer(500);
    }
    bool hasActiveFocus(QWidget *w) {
        return w == DApplication::focusWidget() && w->isActiveWindow();
    }
    void unguard(QWidget *w) {
        Q_ASSERT(m_guardedWidget == w);
        killTimer(m_checkTimer);
        m_checkTimer = 0;
        m_guardedWidget = NULL;
        w->releaseKeyboard();
    }
private:
    QWidget *m_guardedWidget;
    int m_checkTimer;
    static InputGuard *s_instance;
};

#endif // INPUTGUARD_H
