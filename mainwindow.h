#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "texture.h"
#include "l2texture.h"
#include "imageConversion.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    IplImage *sourceImg;
    Texture *texture;
    L2Texture *l2Texture;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_openButton_triggered();

    void on_generateButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
