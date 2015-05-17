#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polys.h"
#include "powell.h"
#include <string>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString x = ui->lineEdit->text();
    string y = x.toStdString();
    Polys a(y);
    for(int i=0;i<a.p.size();i++){
        ui->textBrowser->append("c=");
        ui->textBrowser->append(QString::number(a.p[i].c));
        ui->textBrowser->append("\n");
        ui->textBrowser->append("x=");
        ui->textBrowser->append(QString::number(a.p[i].x));
        ui->textBrowser->append("\n");
        ui->textBrowser->append("y=");
        ui->textBrowser->append(QString::number(a.p[i].y));
        ui->textBrowser->append("\n");
        ui->textBrowser->append("z=");
        ui->textBrowser->append(QString::number(a.p[i].z));
        ui->textBrowser->append("\n");
        ui->textBrowser->append("\n");
        ui->textBrowser->append(QString::number(a.eval(1,2,3)));
    }
}
