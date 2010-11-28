#ifndef ADOPTERWINDOW_H
#define ADOPTERWINDOW_H

#include <QMainWindow>
#include <QList>

class QWidget;
class QToolBar;
class QAction;
class BookView;
class QVBoxLayout;
class Progress;
class TranslucentButton;

/**
 * A toplevel window that can adopt a BookView and other children.
 * On Maemo, it can also grab the volume keys.
 */
class AdopterWindow: public QMainWindow
{
    Q_OBJECT

public:
    explicit AdopterWindow(QWidget *parent = 0);

    /** Adopt book view and decorations. */
    void takeBookView(BookView *bookView, Progress *prog,
                      TranslucentButton *prev, TranslucentButton *next);

    /** Release book view and decorations. */
    void leaveBookView();

    /** Return true if the book view is currently adopted. */
    bool hasBookView();

    /**
     * Add action that is visible on the tool bar.
     * @param   receiver    Object receiving "activated" signal.
     * @param   slot        Slot receiving "activated" signal.
     * @param   iconName    Base name of tool bar icon in resource file.
     * @param   text        Tool bar item text.
     * @param   important   On Symbian, only "important" actions are added to
     *                      the tool bar. All actions are added to the Options
     *                      menu though.
     */
    QAction *addToolBarAction(QObject *receiver, const char *slot,
                              const QString &iconName, const QString &text,
                              bool important = false);

    /** Add spacing to tool bar. */
    void addToolBarSpace();

    /** Show window. */
    void show();

    /** If grab is true, volume keys will navigate the book view. */
    void grabVolumeKeys(bool grab);

public slots:
    /** Handle settings changes. */
    void onSettingsChanged(const QString &key);

protected:
    /** Return true, if we are in portrait mode. */
    bool portrait();

    /** Handle key press events. */
    void keyPressEvent(QKeyEvent *event);

    /**
     * Handle show events.
     * On Symbian, volume keys can only be grabbed, if the window is shown.
     */
    void showEvent(QShowEvent *event);

    /** Handle resize events. */
    void resizeEvent(QResizeEvent *event);

#ifdef Q_WS_MAEMO_5
    /** Actually grab the volume keys. */
    void doGrabVolumeKeys(bool grab);
#endif

protected slots:
    void placeDecorations();

private:
    BookView *bookView;     /**< Book view widget. */
    bool grabbingVolumeKeys;/**< True, if volume keys should be grabbed. */
    QToolBar *toolBar;      /**< Tool bar. */
    Progress *progress;     /**< Reading progress indicator. */
    TranslucentButton *previousButton;  /**< Previous page indicator. */
    TranslucentButton *nextButton;      /**< Next page indicator. */
};

#endif // ADOPTERWINDOW_H
