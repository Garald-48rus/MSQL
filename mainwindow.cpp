#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);//вызов коннтекстово меню
    QObject::connect(ui->tableView, &MainWindow::customContextMenuRequested, this, &MainWindow::CustomMenuReg);


    fl = false;
}
//========================================
MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete logwin;
    delete  maadobj;
    delete  mizmenenie;

}

//==================================================
void MainWindow::on_action_triggered()
{
    logwin = new login();
    logwin->show();

}
//====================================================
void MainWindow::on_pushButton_clicked()
{
    fl = true;
    model = new QSqlQueryModel();
    //model = new QSqlTableModel();
   // model->setTable("Primer");
   // model->select();
    model->setQuery("SELECT * FROM primer");

    model->setHeaderData(0,Qt::Horizontal,"Номер");
    model->setHeaderData(1,Qt::Horizontal,"Название товара");
    model->setHeaderData(2,Qt::Horizontal,"Поставщик");
    model->setHeaderData(3,Qt::Horizontal,"Изображение");
    model->setHeaderData(4,Qt::Horizontal,"Дата");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}
//===========================================================
void MainWindow::on_pushButton_2_clicked()
{
    maadobj = new addobject();
    QObject::connect(maadobj,&addobject::refresh_table,this, &MainWindow::obr_ref_tab);
    maadobj->show();
}
//================================================
void MainWindow::obr_ref_tab(){


    on_pushButton_clicked();
}
//===============================================================
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int temp_mod;
    temp_mod = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();

    ui->lineEdit->setText(QString::number(temp_mod));

    QSqlQuery* qerly = new QSqlQuery();
    qerly->prepare("SELECT name, post, picadr, data FROM primer WHERE id =:id");
    qerly->bindValue(":id",temp_mod);

    if(qerly->exec()){

      qerly->next();
      ui->lineEdit_2->setText(qerly->value(0).toString());
      ui->lineEdit_3->setText(qerly->value(1).toString());

      ui->label_4->setScaledContents(true);
      ui->label_4->setPixmap(QPixmap(qerly->value(2).toString()));

      ui->dateEdit->setDate(QDate(qerly->value(3).toDate()));

    }



}
//==============================================================
void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery* qerly = new QSqlQuery();
    qerly->prepare("UPDATE primer SET name=?,post=? WHERE id=?");
    qerly->bindValue(0,ui->lineEdit_2->text());
    qerly->bindValue(1,ui->lineEdit_3->text());
    qerly->bindValue(2,ui->lineEdit->text());

    qerly->exec();
    on_pushButton_clicked();
}
//====================================================================
void MainWindow::on_pushButton_4_clicked()
{
    QSqlQuery* qerly = new QSqlQuery();
    qerly->prepare("DELETE FROM primer WHERE id=?");
    qerly->bindValue(0,ui->lineEdit->text());

  if(qerly->exec()){
    on_pushButton_clicked();}
}
//==========================================================
void MainWindow::CustomMenuReg(QPoint point){

 if(fl){

     QModelIndex index = ui->tableView->indexAt(point);
     globid = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toInt();

     QMenu* menu = new QMenu(this);
     QAction* izm = new QAction("Изменить", this);
     QObject::connect(izm, &QAction::triggered, this, &MainWindow::izm_zap);

     QAction* del = new QAction("Удалить", this);
     QObject::connect(del, &QAction::triggered, this,&MainWindow::del_zap);

     menu->addAction(izm);
     menu->addAction(del);

     menu->popup(ui->tableView->viewport()->mapToGlobal(point));
 }

}
//==============================================
void MainWindow::del_zap(){

    QSqlQuery* qerly = new QSqlQuery();
    qerly->prepare("DELETE FROM primer WHERE id=?");

    qerly->bindValue(0,globid);

    if(qerly->exec()){

        on_pushButton_clicked();
    }

}
//==================================================
void MainWindow::izm_zap(){

   mizmenenie = new izmenenie();
   QObject::connect(this, &MainWindow::sendID,mizmenenie, &izmenenie::obrSendID);
   emit sendID(globid);

   mizmenenie->show();

   QObject::connect(mizmenenie, &izmenenie::ref,this,&MainWindow::on_pushButton_clicked);

   disconnect(this, &MainWindow::sendID,mizmenenie, &izmenenie::obrSendID);
}
//===============================================



