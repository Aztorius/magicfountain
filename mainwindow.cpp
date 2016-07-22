#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Magic Fountain Alpha 1.0.0");

    connect(ui->plainTextEdit, SIGNAL(textChanged()), this, SLOT(refreshPreview()));
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
    QString content = "";
    int blockcount = ui->plainTextEdit->blockCount();
    int i = 0;

    while(i < blockcount){
        block = document->findBlockByNumber(i);
        text = block.text();

        if(text.left(2) == "# "){
            content.append("<h1>" + text.mid(2) + "</h1>");
        }
        else if(text.left(3) == "## "){
            content.append("<h2>" + text.mid(3) + "</h2>");
        }
        else if(text.left(4) == "### "){
            content.append("<h3>" + text.mid(4) + "</h3>");
        }
        else if(text.left(3).toLower() == "int" || text.left(3).toLower() == "ext"){
            content.append("<p><b>" + text + "</b></p>");
        }
        else{   //Defaut is action

        }

        i++;
    }

    ui->textBrowser->setHtml(content);
}
