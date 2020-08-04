#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "WorkThread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void progressUpdateHandler(int step, const QString& data);
    void threadFinishedHandler();
    void okHandler();
    void cancelHandler();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
