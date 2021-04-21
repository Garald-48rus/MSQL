#include "addobject.h"
#include "ui_addobject.h"

addobject::addobject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addobject)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());

    QSqlQuery* qerly = new QSqlQuery();
    qerly->exec("SELECT post FROM postable");

    while (qerly->next()) {

        ui->comboBox->addItem(qerly->value(0).toString());

    }

    postcombo = 0;
}

addobject::~addobject()
{
    delete ui;
}

void addobject::on_pushButton_clicked()
{



    QSqlQuery *qerly = new QSqlQuery();
    qerly->prepare("INSERT INTO primer(name, post, picadr, data) VALUES(:name,:post, :picadr, :date)");
    qerly->bindValue(":name",ui->lineEdit->text());
    qerly->bindValue(":post",ui->comboBox->itemText(postcombo));
    qerly->bindValue(":picadr",imgadr);
    qerly->bindValue(":date", ui->dateEdit->text());
    //qerly->exec();

    QMessageBox* mss = new QMessageBox();
    if(!qerly->exec()){

        mss->setText("Запрос не выплнен");
        mss->show();
    }

    else {
        emit refresh_table();
    }
    this->close();
}
//==========================================================
void addobject::on_toolButton_clicked()
{
    imgadr = QFileDialog::getOpenFileName(0, "Открыть изображение",".../","*.jpg");
    ui->label_3->setScaledContents(true);
    ui->label_3->setPixmap(QPixmap(imgadr));
}

void addobject::on_comboBox_currentIndexChanged(int index)
{
   postcombo = index;
}
