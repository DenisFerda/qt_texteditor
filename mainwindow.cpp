#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QColorDialog>
#include <QColor>
#include <QFont>
#include <QFontDialog>
#include <QShortcut>
#include <QDialog>
#include <QDialogButtonBox>
#include <QInputDialog>
#include <QPainter>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMdiArea>
#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setCentralWidget(ui->textEdit);
    this->setCentralWidget(ui->mdiArea);
    setAcceptDrops(true);
}


void MainWindow::dragEnterEvent(QDragEnterEvent *event){

    event->accept();

}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *event){

    event->accept();

}

void MainWindow::dragMoveEvent(QDragMoveEvent *event){

    event->accept();

}

void MainWindow::dropEvent(QDropEvent *event){

    QString text;
    text = event->mimeData()->text();

    ui->textEdit->append(text);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{

    QWidget *widget = new QWidget(this);
    QTextEdit *textEdit = new QTextEdit(widget);

    textEdit->setObjectName("myTextEdit");
    QMdiSubWindow *mdiWindows = ui->mdiArea->addSubWindow(widget);

    mdiWindows->setWindowState(Qt::WindowMaximized);
    mdiWindows->layout()->addWidget(textEdit);

    mdiWindows->show();

}

//void MainWindow::loadSubWindow(QWidget *widget){

//    auto window = ui->mdiArea->addSubWindow(widget);

//    window->setWindowTitle(widget->windowTitle());
//    //window->setWindowIcon(widget->windowIcon());
//    window->setWindowState(Qt::WindowMaximized);

//    window->show();

//}


void MainWindow::on_actionOpen_triggered()
{

    QString file_name = QFileDialog::getOpenFileName(this, "Open the File");
    QFile file(file_name);
    file_path = file_name;

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "..", "file not open");
        return;
    }

    QTextStream in(&file);
    QString text = in.readAll();

    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{

    QFile file(file_path);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "..", "file not open");
        return;
    }

    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();

    out << text;

    file.flush();
    file.close();

}

void MainWindow::on_actionSave_as_triggered()
{

    QString file_name = QFileDialog::getSaveFileName(this, "Save the File");
    QFile file(file_name);

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "..", "file not open");
        return;
    }

    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();

    out << text;

    file.flush();
    file.close();

}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{

    //QTextEdit * textEdit = ui->mdiArea->currentSubWindow()->widget()->findChild<QTextEdit*>();

    QTextEdit * textEdit = ui->mdiArea->activeSubWindow()->widget()->findChild<QTextEdit*>("myTextEdit");

    if(textEdit != NULL){

        textEdit->copy();

    }else if(textEdit == NULL){
        QMessageBox mess;
        mess.setText("NULL");
        mess.exec();
    }else{
        QMessageBox mess;
        mess.exec();
    }
}

void MainWindow::on_actionPaste_triggered()
{
    QTextEdit * textEdit = ui->mdiArea->activeSubWindow()->widget()->findChild<QTextEdit*>("myTextEdit");

    textEdit->paste();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionAbout_Notepad_triggered()
{
    QString about_text;
    about_text = "Autor: Denis Ferda\n";
    about_text += "Semestrální projekt\n";
    about_text += "Multiplatformní programování\n";
    about_text += "UTB | 2020";

    QMessageBox::about(this, "About Text Editor 1.0", about_text);

}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("...");

    QPrintDialog dialog(&printer, this);

    if(dialog.exec() == QDialog::Rejected){
        return;
    }

    ui->textEdit->print(&printer);

}

void MainWindow::on_actionPrint_preview_triggered()
{



}

void MainWindow::on_actionColor_triggered()
{

    QColor color = QColorDialog::getColor(Qt::white, this, "Color picker");

    if(color.isValid()){

        QTextEdit * textEdit = ui->mdiArea->activeSubWindow()->widget()->findChild<QTextEdit*>();

        textEdit->setTextColor(color);
    }

}

void MainWindow::on_actionFont_triggered()
{
    bool x;

    QFont font = QFontDialog::getFont(&x, this);

    if(x){

        ui->textEdit->setFont(font);

    }else{
        return;
    }

}

void MainWindow::on_actionFInd_triggered()
{

    QString findText = QInputDialog::getText(this, tr("Find"),
                                             tr("Find expression: "), QLineEdit::Normal);
    if (!findText.isEmpty()){

        QString text = ui->textEdit->toPlainText();

        if(text.contains(findText)){
            QMessageBox mess;
            mess.setWindowTitle("Text found");
            mess.setText(tr("Expression was found in text!"));

            mess.exec();
        }else{
            QMessageBox mess;
            mess.setWindowTitle("Text not found");
            mess.setText(tr("Expression not found in text!"));

            mess.exec();
            }
        }else{
            QMessageBox mess;
            mess.setWindowTitle("Empty expression");
            mess.setText(tr("Expression cannot be empty!"));

            mess.exec();
    }
}

// Fuknce pro vyhledání a nahrazení textu
void MainWindow::on_actionFind_and_replace_triggered()
{

    QInputDialog dia;

    QString findText;

    findText = dia.getText(this, tr("Find and Replace"),
                                         tr("Expression which want to replace: "), QLineEdit::Normal);

    QString text = ui->textEdit->toPlainText();

    if(!text.contains(findText)){

        QMessageBox mess;
        mess.setWindowTitle("Text not found");
        mess.setText(tr("Expression not found in text!"));

        mess.exec();

    }else if(findText == ""){

        QMessageBox mess;
        mess.setWindowTitle("Empty expression");
        mess.setText("Replace expression cannot be empty!");

        mess.exec();

    }else{

    QInputDialog diaRep;

    QString replaceText = diaRep.getText(this, tr("Find and Replace"),
                                         tr("Expression for replace: "), QLineEdit::Normal);


    text.replace(findText, replaceText);

    ui->textEdit->setText(text);

    QMessageBox mess;
    mess.setWindowTitle(tr("Text was replaced"));
    mess.setText(findText+" was replaced by "+replaceText);

    mess.exec();

    }

}

void MainWindow::on_actionRich_text_triggered()
{


}

void MainWindow::on_actionPlain_text_triggered()
{

}
