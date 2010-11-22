#include <QtGui>

#include "fullscreenwindow.h"
#include "translucentbutton.h"
#include "progress.h"
#include "trace.h"
#include "settings.h"
#include "platform.h"

static const int MARGIN = 9;

FullScreenWindow::FullScreenWindow(QWidget *parent):
        AdopterWindow(parent), progress(0), previousButton(0), nextButton(0)
{
    TRACE;
    Q_ASSERT(parent);
#ifdef Q_WS_MAEMO_5
    setAttribute(Qt::WA_Maemo5StackedWindow, true);
    setAttribute(Qt::WA_Maemo5NonComposited, true);
#endif // Q_WS_MAEMO_5
#ifndef Q_OS_SYMBIAN
    toolBar->hide();
#endif
    QFrame *frame = new QFrame(this);
    QVBoxLayout *layout = new QVBoxLayout(frame);
    layout->setMargin(0);
    frame->setLayout(layout);
    setCentralWidget(frame);
    restoreButton = new TranslucentButton("view-normal", this);
    QRect screen = QApplication::desktop()->screenGeometry();
    restoreButton->setGeometry(
        screen.width() - TranslucentButton::pixels - MARGIN,
        screen.height() - TranslucentButton::pixels - MARGIN,
        TranslucentButton::pixels,
        TranslucentButton::pixels);
    connect(restoreButton, SIGNAL(triggered()), this, SIGNAL(restore()));
}

void FullScreenWindow::showFullScreen()
{
    TRACE;
    AdopterWindow::showFullScreen();
    restoreButton->flash(3000);
}

void FullScreenWindow::resizeEvent(QResizeEvent *e)
{
    TRACE;

    QRect screen = QApplication::desktop()->screenGeometry();
    int w = screen.width();
    int h = screen.height();

#ifdef Q_WS_MAEMO_5
    // Hack: FullScreenWindow can lose orientation on Maemo...
    QString orientation = Settings::instance()->value("orientation",
        Platform::instance()->defaultOrientation()).toString();
    if (((orientation == "portrait") && (w > h)) ||
        ((orientation == "landscape") && (w < h))) {
        int tmp = w;
        w = h;
        h = tmp;
    }
#endif // Q_WS_MAEMO_5

    restoreButton->setGeometry(
        w - TranslucentButton::pixels - MARGIN,
        h - TranslucentButton::pixels - MARGIN,
        TranslucentButton::pixels,
        TranslucentButton::pixels);

    if (hasChild(progress)) {
        progress->setGeometry(0, h - progress->thickness(),
                              w, progress->thickness());
    }
    if (hasChild(previousButton)) {
        previousButton->setGeometry(
                MARGIN,
                h - TranslucentButton::pixels - MARGIN,
                TranslucentButton::pixels,
                TranslucentButton::pixels);
    }
    if (hasChild(nextButton)) {
        nextButton->setGeometry(
        w - TranslucentButton::pixels - MARGIN,
        MARGIN,
        TranslucentButton::pixels,
        TranslucentButton::pixels);
    }

    restoreButton->flash(3000);
    AdopterWindow::resizeEvent(e);
}

void FullScreenWindow::takeChildren(BookView *view,
                                    Progress *prog,
                                    TranslucentButton *previous,
                                    TranslucentButton *next)
{
    TRACE;
    progress = prog;
    previousButton = previous;
    nextButton = next;
    QList<QWidget *> otherChildren;
    otherChildren << progress << previousButton << nextButton;
    AdopterWindow::takeChildren(view, otherChildren);
}
