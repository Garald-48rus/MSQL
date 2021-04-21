#include "izmenenie.h"
#include "ui_izmenenie.h"

izmenenie::izmenenie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::izmenenie)
{
    ui->setupUi(this);
}
//============================================
izmenenie::~izmenenie()
{
    delete ui;
}
//=====================================
void izmenenie::obrSendID(int n){

    QSqlQuery* qerly = new QSqlQuery();
    qerly->prepare("SELECT name, post FROM primer WHERE id=?");
    qerly->bindValue(0,n);

    if(qerly->exec()){
        qerly->next();
        ui->lineEdit->setText(qerly->value(0).toString());
        ui->lineEdit_2->setText(qerly->value(1).toString());
        ui->lineEdit_3->setText(QString::number(n));
    }

}
//===============================================================
void izmenenie::on_pushButton_clicked()
{
    QSqlQuery* qerly = new QSqlQuery();
    qerly->prepare("UPDATE primer SET name = ?, post = ? WHERE id = ?");
    qerly->bindValue(0,ui->lineEdit->text());
    qerly->bindValue(1,ui->lineEdit_2->text());
    qerly->bindValue(2,ui->lineEdit_3->text().toInt());

    if(qerly->exec()){

      emit ref();


    }
   this->close();

}
