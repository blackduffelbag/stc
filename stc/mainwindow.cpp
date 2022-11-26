#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QProgressBar>
#include <QRandomGenerator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Инециализация таблицы
    ui->tableWidget->setColumnCount(10);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->insertRow(0);
    ui->tableWidget->insertRow(1);
    ui->tableWidget->setVerticalHeaderLabels(QStringList()<<"Процесс"<<"Прогресс");

    //Инециализация потоков
    for(int i = 0; i < 10; i++) {
    int randomValue = qrand() % 40 + 10;
    QThread* thread_ = new QThread();
    Worker* worker_ = new Worker(i, randomValue);
    QProgressBar *prog = new QProgressBar();
    prog->setFormat("%p%");
    prog->setMinimum(0);
    prog->setMaximum(randomValue);

    worker_->moveToThread(thread_);
    ui->tableWidget->setItem(0,i, new QTableWidgetItem("Запущен до "+QString::number(randomValue)));


    connect(thread_, &QThread::finished, worker_, &Worker::deleteLater);
    connect(thread_, &QThread::started, worker_,  &Worker::func);
    connect(worker_, &Worker::progress, prog, &QProgressBar::setValue);


    Threads.push_back(thread_);
    ui->tableWidget->setCellWidget(1,i,prog);
    }
    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    //Запуск потоков
    for (int i = 0; i < Threads.size(); ++i) {
            Threads[i]->start();
            qDebug() << "*";
        }
}
