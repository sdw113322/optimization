#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polys.h"
#include "powell.h"
#include <string>

using namespace std;

QString PowellOut(vector<array<double,8> > input){
    QString result;
    result += "<table><thead><tr><th>i</th><th>j</th><th>u x</th><th>u y</th><th>alpha</th><th>x</th><th>y</th><th>f(x,y)</th></tr></thead><tbody>";
    for(int i=0;i<input.size();i++){
        result += "<tr>";
        for(int j=0;j<8;j++){
            result += "<td>";
            result += QString::number(input[i][j]);
            result += "</td>";
        }
        result += "</tr>";
    }
    result += "</tbody></table>";
    return result;
}

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
    QString o = PowellOut(powell(a,0.5,0.5,5,0,5,0,0.000001));
    ui->textBrowser->append(o);
}
