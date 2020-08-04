#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pgBar->setMinimum(0);
    ui->pgBar->setMaximum(1);
    ui->pgBar->setValue(0);
    ui->lblData->setText("Ready...");
    connect(ui->btnOK, &QPushButton::clicked, this, &MainWindow::okHandler);
    connect(ui->btnCancel, &QPushButton::clicked, this, &MainWindow::cancelHandler);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::progressUpdateHandler(int step, const QString &data)
{
    ui->pgBar->setValue(step);
    ui->lblData->setText(ui->lblData->text() + ":" + data);
}

void MainWindow::threadFinishedHandler()
{
    QMessageBox::information(this,"Info","Thread has finished");
}

void MainWindow::okHandler()
{
    ui->pgBar->setMinimum(0);
    ui->pgBar->setMaximum(ui->txtIn->text().size());
    ui->lblData->setText("");

    QThread* thread = new QThread;
    WorkThread *worker = new WorkThread(ui->txtIn->text());
    worker->moveToThread(thread);
    connect(worker, &WorkThread::ProgressUpdate, this, &MainWindow::progressUpdateHandler);
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), this, SLOT(threadFinishedHandler()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void MainWindow::cancelHandler()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
    event->accept();
}


