#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    line_lable = new QLabel(" line:0 column:0 ");
    ui->statusBar->addPermanentWidget(line_lable);

    textchanged = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//file
void MainWindow::on_actionOpen_file_triggered()
{
    filepath = QFileDialog::getOpenFileName(this,"open file",QDir::currentPath(),"TXT(*.txt);;CPP(*.cpp)");
    if(!filepath.isEmpty())
    {
        file = new QFile(filepath);
        qDebug() << filepath;
        qDebug() << file->fileName();
        if(!file->open(QIODevice::ReadWrite))
        {
            QMessageBox::warning(this,"WARING","can't open file!!!");
        }
        else
        {
            while(!file->atEnd())
            {
                QByteArray line = file->readLine();
                QString str(line);
                displayString.append(str);
                str.clear();
            }
            ui->textEdit->clear();
            ui->textEdit->setPlainText(displayString);
            displayString.clear();
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    if(!filepath.isEmpty())
    {
        QTextStream out(file);
        file->resize(0);
        out << ui->textEdit->toPlainText();
    }
}

void MainWindow::on_actionSave_2_triggered()
{
    if(!filepath.isEmpty())
    {
        QString new_file = QFileDialog::getSaveFileName(this,"file save as",QDir::currentPath(),"TXT(*.txt);;CPP(*.cpp)");
        file->copy(new_file);
    }
}

void MainWindow::on_actionNew_file_triggered()
{
    if(filepath.isEmpty())
    {
        filepath = QFileDialog::getSaveFileName(this,"file save as",QDir::currentPath(),"TXT(*.txt);;CPP(*.cpp)");
        if(!filepath.isEmpty())
        {
            file = new QFile(filepath);
            if(!file->open(QIODevice::ReadWrite))
            {
                QMessageBox::warning(this,"WARING","can't open file!!!");
            }
        }
    }
}

void MainWindow::on_actionClose_triggered()
{
    if(!filepath.isEmpty())
    {
        QFile file(filepath);
        file.close();
        filepath.clear();
        ui->textEdit->clear();
    }
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

//edit

void MainWindow::on_actionRevoke_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionForward_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionShear_triggered()
{
    ui->textEdit->cut();
}

//tool
void MainWindow::on_actionColor_triggered()
{
    QColor paseColor = QColorDialog::getColor(Qt::white,this,"pasecolor");
    if(paseColor.isValid())
    {
        QPalette pasePalette = ui->textEdit->palette();
        pasePalette.setColor(QPalette::Active,QPalette::Base,paseColor);
        ui->textEdit->setPalette(pasePalette);
    }
}

void MainWindow::on_actionTextcolor_triggered()
{
    QColor textColor = QColorDialog::getColor(Qt::black,this,"textcolor");
    if(textColor.isValid())
    {
        QPalette textPalette = ui->textEdit->palette();
        textPalette.setColor(QPalette::Active,QPalette::Text,textColor);
        ui->textEdit->setPalette(textPalette);
    }
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,QFont("Arial",18),this,"font");
    if(ok)
    {
        ui->textEdit->setFont(font);
    }
}


//
void MainWindow::on_textEdit_cursorPositionChanged()
{
    cursor = new QTextCursor(ui->textEdit->textCursor());
    line = cursor->blockNumber();
    column = cursor->columnNumber();
    QString string = QString(" line:%1 column:%2 ").arg(line).arg(column);
    line_lable->setText(string);
}

void MainWindow::on_textEdit_textChanged()
{
        qDebug() << "textchanged";
}
