#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPrinter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionSave_as_triggered();

    void on_actionAbout_Notepad_triggered();

    void on_actionPrint_triggered();

    void on_actionPrint_preview_triggered();

    void on_actionColor_triggered();

    void on_actionFont_triggered();

    void on_actionFInd_triggered();

    void on_actionFind_and_replace_triggered();

    void on_actionRich_text_triggered();

    void on_actionPlain_text_triggered();

protected:

    void dragEnterEvent(QDragEnterEvent *event);

    void dragLeaveEvent(QDragLeaveEvent *event);

    void dragMoveEvent(QDragMoveEvent *event);

    void dropEvent(QDropEvent *event);

private:
    Ui::MainWindow *ui;

    QString file_path;

    void loadSubWindow(QWidget *widget);

};
#endif // MAINWINDOW_H
