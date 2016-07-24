#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Magic Fountain Alpha 1.0.0");

    courierfont = QFont("Courier");
    courierfont.setPointSize(12);

    ui->plainTextEdit->setFont(courierfont);

    connect(ui->plainTextEdit, SIGNAL(textChanged()), this, SLOT(refreshPreview()));
    connect(ui->actionExport_as_PDF, SIGNAL(triggered()), this, SLOT(exportAsPDF()));
    connect(ui->actionExport_as_HTML, SIGNAL(triggered()), this, SLOT(exportAsHTML()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(quickSave()));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionPrint, SIGNAL(triggered()), this, SLOT(print()));

    connect(ui->actionBold, SIGNAL(triggered()), this, SLOT(setBold()));
    connect(ui->actionItalic, SIGNAL(triggered()), this, SLOT(setItalic()));
    connect(ui->actionUnderline, SIGNAL(triggered()), this, SLOT(setUnderline()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshPreview(){
    Script currentscript(ui->plainTextEdit->toPlainText());

    ui->textBrowser->setHtml(currentscript.toHtml());

    ui->textBrowser->setCurrentFont(courierfont);
}

void MainWindow::exportAsPDF(){
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", QString(), "PDF files (*.pdf)");
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty()){
                 fileName.append(".pdf");
        }
        QPrinter printer(QPrinter::ScreenResolution);
        printer.setPageMargins(25.0, 25.0, 10.0, 25.0, QPrinter::Millimeter);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);

        ui->textBrowser->document()->print(&printer);
    }
}

void MainWindow::exportAsHTML(){
    QString fileName = QFileDialog::getSaveFileName(this, "Export HTML", QString(), "HTML files (*.html)");
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty()){
             fileName.append(".html");
        }

        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
             QTextStream stream(&file);
             stream << ui->textBrowser->toHtml();
             file.close();
        }
    }
}

void MainWindow::print(){
        QPrinter printer(QPrinter::ScreenResolution);
        printer.setPageMargins(25.0, 25.0, 10.0, 25.0, QPrinter::Millimeter);

        QPrintDialog dialog(&printer, this);
        dialog.setWindowTitle(tr("Print Document"));

        if (dialog.exec() != QDialog::Accepted) {
           return;
        }

        ui->textBrowser->document()->print(&printer);
}

void MainWindow::openFile(){
    QString filename = QFileDialog::getOpenFileName(this, "Open Fountain file", QString(), "Text files (*.fountain *.txt *.markdown *.md)");
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText(file.readAll());
        filepath = filename;
        file.close();

        QTextCursor cursor = ui->plainTextEdit->textCursor();
        cursor.movePosition(QTextCursor::Start);
        ui->plainTextEdit->setTextCursor(cursor);
    }
}

void MainWindow::saveAs(){
    QString filename = QFileDialog::getSaveFileName(this, "Save Fountain file", QString(), "Text files (*.fountain *.txt *.markdown *.md)");
    if (filename.isEmpty()){
        return;
    }

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(&file);
        stream << ui->plainTextEdit->toPlainText();
        file.close();
        filepath = filename;
    }
}

void MainWindow::quickSave(){
    if(filepath.isEmpty()){
        saveAs();
        return;
    }

    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(&file);
        stream << ui->plainTextEdit->toPlainText();
        file.close();
    }
}

QString MainWindow::checkBoldItalicUnderline(QString text){
    QString temp, result = text;

    //Check Bold with Italic, ex: ***something***
    while(result.contains("***") && result.mid(result.indexOf("***") + 3).contains("***")){
        result.replace(result.indexOf("***"), 3, "<b><i>");
        result.replace(result.indexOf("***"), 3, "</i></b>");
    }

    //Check Bold, ex: **something**
    while(result.contains("**") && result.mid(result.indexOf("**") + 2).contains("**")){
        result.replace(result.indexOf("**"), 2, "<b>");
        result.replace(result.indexOf("**"), 2, "</b>");
    }

    //Check Italic, ex: *something*
    while(result.contains("*") && result.mid(result.indexOf("*") + 1).contains("*")){
        result.replace(result.indexOf("*"), 1, "<i>");
        result.replace(result.indexOf("*"), 1, "</i>");
    }

    //Check Underline, ex: _something_
    while(result.contains("_") && result.mid(result.indexOf("_") + 1).contains("_")){
        result.replace(result.indexOf("_"), 1, "<u>");
        result.replace(result.indexOf("_"), 1, "</u>");
    }

    return result;
}

void MainWindow::setBold(){
    if(ui->plainTextEdit->textCursor().selectedText().isEmpty()){
        ui->plainTextEdit->insertPlainText("****");

        QTextCursor cursor = ui->plainTextEdit->textCursor();
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 2);
        ui->plainTextEdit->setTextCursor(cursor);
    }
    else{
        QString selected = ui->plainTextEdit->textCursor().selectedText();
        ui->plainTextEdit->textCursor().clearSelection();
        ui->plainTextEdit->insertPlainText("**" + selected + "**");
    }
}

void MainWindow::setItalic(){
    if(ui->plainTextEdit->textCursor().selectedText().isEmpty()){
        ui->plainTextEdit->insertPlainText("**");

        QTextCursor cursor = ui->plainTextEdit->textCursor();
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
        ui->plainTextEdit->setTextCursor(cursor);
    }
    else{
        QString selected = ui->plainTextEdit->textCursor().selectedText();
        ui->plainTextEdit->textCursor().clearSelection();
        ui->plainTextEdit->insertPlainText("*" + selected + "*");
    }
}

void MainWindow::setUnderline(){
    if(ui->plainTextEdit->textCursor().selectedText().isEmpty()){
        ui->plainTextEdit->insertPlainText("__");

        QTextCursor cursor = ui->plainTextEdit->textCursor();
        cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
        ui->plainTextEdit->setTextCursor(cursor);
    }
    else{
        QString selected = ui->plainTextEdit->textCursor().selectedText();
        ui->plainTextEdit->textCursor().clearSelection();
        ui->plainTextEdit->insertPlainText("_" + selected + "_");
    }
}

