#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QFileDialog>
#include <QPalette>
#include <QColorDialog>
#include <QFontDialog>
#include <QLabel>
#include <QDebug>
#include <QTextCursor>
#include <QFile>
#include <QMessageBox>
#include <QIODevice>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_file_triggered();

    void on_actionSave_triggered();

    void on_actionSave_2_triggered();

    void on_actionRevoke_triggered();

    void on_actionForward_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionShear_triggered();

    void on_actionColor_triggered();

    void on_actionTextcolor_triggered();

    void on_actionFont_triggered();

    void on_textEdit_cursorPositionChanged();

    void on_actionNew_file_triggered();

    void on_actionClose_triggered();

    void on_actionExit_triggered();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
    QLabel *line_lable;
    QTextCursor *cursor;

    QString filepath;
    QFile *file;
    QString displayString;

    int column;
    int line;
    bool textchanged;
};

#endif // MAINWINDOW_H
