#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Magic Fountain Alpha 1.0.0");

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

void MainWindow::refreshPreview()
{
    QTextDocument* document = ui->plainTextEdit->document();
    QTextBlock block;
    QString text;
    QString content = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">";
    content += "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">";
    content += "p, li { white-space: pre-wrap; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; }";
    content += "</style></head><body style=\" font-family:'Courier 10 Pitch'; font-size:12pt; font-weight:400; font-style:normal;\">";

    int blockcount = ui->plainTextEdit->blockCount();
    int i = 0;

    while(i < blockcount){
        block = document->findBlockByNumber(i);
        text = block.text().trimmed();

        if(text.left(1) == "!"){ //Forced action
            content.append("<p>" + checkBoldItalicUnderline(text.mid(1)) + "</p>");
        }
        else if(text.left(6) == "Title:"){ //Title
            content.append("<br/><br/><br/><br/><br/><br/><br/><br/><br/><p style=\"text-align: center;\">" + checkBoldItalicUnderline(text.mid(6).trimmed()));
            i++;
            block = document->findBlockByNumber(i);
            text = block.text();

            while(text.left(1) == "\t" && i < blockcount){
                content.append("<br/>" + checkBoldItalicUnderline(text.trimmed()));

                i++;
                block = document->findBlockByNumber(i);
                text = block.text();
            }
            i--;
            content.append("<br/></p>");
        }
        else if(text.left(7) == "Credit:"){ //Credit
            content.append("<p style=\"text-align: center;\">" + checkBoldItalicUnderline(text.mid(7).trimmed()) + "</p>");
        }
        else if(text.left(7) == "Author:"){ //Author
            content.append("<p style=\"text-align: center;\">" + checkBoldItalicUnderline(text.mid(7).trimmed()) + "<br/></p>");
        }
        else if(text.left(7) == "Source:"){ //Source
            content.append("<p style=\"text-align: center;\">" + checkBoldItalicUnderline(text.mid(7).trimmed()) + "<br/></p>");
        }
        else if(text.left(11) == "Draft date:"){ //Draft date
            content.append("<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><p style=\"text-align: left;\">" + checkBoldItalicUnderline(text.mid(11).trimmed()) + "</p>");
        }
        else if(text.left(8) == "Contact:"){ //Contact
            content.append("<p style=\"text-align: left;\">" + checkBoldItalicUnderline(text.mid(8).trimmed()));
            i++;
            block = document->findBlockByNumber(i);
            text = block.text();

            while(text.left(1) == "\t" && i < blockcount){
                content.append("<br/>" + checkBoldItalicUnderline(text.trimmed()));

                i++;
                block = document->findBlockByNumber(i);
                text = block.text();
            }
            i--;
            content.append("<br/></p>");
        }
        else if(text.left(2) == "# "){ //Act
            content.append("<p>" + checkBoldItalicUnderline(text.mid(2)) + "</p>");
        }
        else if(text.left(3) == "## "){ //Sequence
            content.append("<p>" + checkBoldItalicUnderline(text.mid(3)) + "</p>");
        }
        else if(text.left(4) == "### "){ //Scene
            content.append("<p>" + checkBoldItalicUnderline(text.mid(4)) + "</p>");
        }
        else if(text.left(3).toLower() == "int" || text.left(3).toLower() == "ext" || text.left(8).toLower() == "int./ext" || text.left(7).toLower() == "int/ext" || text.left(3).toLower() == "i/e"){ //Scene heading
            content.append("<p>" + checkBoldItalicUnderline(text) + "</p>");
        }
        else if(text.left(1) == ">"){
            if(text.right(1) == "<"){ //Centered
                content.append("<p style=\"text-align:center;\">" + checkBoldItalicUnderline(text.mid(1, text.size()-2)) + "</p>");
            }
            else{ //Transition
                content.append("<p style=\"text-align:right;\">" + checkBoldItalicUnderline(text.mid(1)) + "</p>");
            }
        }
        else if(text.right(3) == "TO:"){ //Transition
            content.append("<p style=\"text-align: right;\">" + checkBoldItalicUnderline(text) + "</p>");
        }
        else if(text.left(1) == "." && text.mid(1, 1) != "."){ //Forced scene heading
            content.append("<p>" + checkBoldItalicUnderline(text.mid(1)) + "</p>");
        }
        else if(text.toUpper() == text && !text.isEmpty()){ //Dialogue
            content.append("<p>                     " + checkBoldItalicUnderline(text) + "</p>"); //Character name
            i++;
            block = document->findBlockByNumber(i);
            text = block.text().trimmed();

            while(!text.isEmpty() && i < blockcount){
                block = document->findBlockByNumber(i);
                text = block.text().trimmed();

                if(text.left(1) == "(" && text.right(1) == ")"){ //Parenthetical
                    content.append("<p>               " + checkBoldItalicUnderline(text) + "</p>");
                }
                else{ //Text
                    content.append("<p>           " + checkBoldItalicUnderline(text) + "</p>");
                }

                i++;
            }
            i--;
        }
        else{ //Default action
            content.append("<p>" + checkBoldItalicUnderline(text) + "</p>");
        }

        i++;
    }

    content += "</body></html>";

    ui->textBrowser->setHtml(content);
}

void MainWindow::exportAsPDF(){
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", QString(), "*.pdf");
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty()){
                 fileName.append(".pdf");
        }
        QPrinter printer(QPrinter::HighResolution);
        printer.setPageMargins(30.0, 25.0, 25.0, 25.0, QPrinter::Millimeter);
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
        QPrinter printer(QPrinter::HighResolution);
        printer.setPageMargins(30.0, 25.0, 25.0, 25.0, QPrinter::Millimeter);

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

