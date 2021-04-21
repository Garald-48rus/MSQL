#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    ui->lineEdit->setText("localhost");
    ui->lineEdit_2->setText("TestDB");
    ui->lineEdit_3->setText("SA");

    mss = new QMessageBox();
}

login::~login()
{
    delete ui;
    delete mss;
}

void login::on_pushButton_clicked()
{
    //QODBC
    //QPSQL
    //QMYSQL
    //QStringLiteral
    /*QString connectString = "DRIVER=/opt/microsoft/msodbcsql17/lib64/libmsodbcsql-17.7.so.1.1;"
     "SERVER=localhost;DATABASE = TestDB;";
    db.setDatabaseName(connectString);*/

    db = QSqlDatabase::addDatabase("QODBC"); 
   // db.setDatabaseName("DRIVER={SQL Server};SERVER=localhost;DATABASE=TestDB;");
    db.setDatabaseName("DRIVER={/opt/microsoft/msodbcsql17/lib64/libmsodbcsql-17.7.so.2.1};"
   "SERVER="+ui->lineEdit->text()+";DATABASE="+ui->lineEdit_2->text()+";");
    db.setUserName(ui->lineEdit_3->text());
    db.setPassword(ui->lineEdit_4->text());
    QStringList drivers = QSqlDatabase::drivers();
      db.open();

    if(db.open()){

        mss->setText("Соединились");
    }
    else {
        mss->setText("НЕТ соединения");

    }

    mss->show();

    this->close();
}
