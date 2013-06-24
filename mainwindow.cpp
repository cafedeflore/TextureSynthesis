#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sourceImg = NULL;
    texture = NULL;
    l2Texture = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_triggered()
{
    QString path=QFileDialog::getOpenFileName(this);
    if(!path.isEmpty()){
        QFile file(path);
        if(!file.open(QFile::ReadOnly|QFile::Text)){
            QMessageBox::warning(this,tr("Open image."),tr("Cannot load image %1\n%2.")
                                 .arg(path).arg(file.errorString()));
            return;
        }


//        texture = new Texture(path);
        ui->sourceLine->setText(path);
        sourceImg = cvLoadImage(path.toStdString().c_str());

        QImage *qImg = new QImage();
        qImg = IplImage2QImage(sourceImg);
        QGraphicsScene *scene = new QGraphicsScene();
        scene->addPixmap(QPixmap::fromImage(*qImg));
        ui->textureView->setScene(scene);
    }
    return;
}

void MainWindow::on_generateButton_clicked()
{
    int method;
    int width;
    int height;
    if(sourceImg == NULL) {
        QMessageBox::warning(this,tr("Warning."),tr("Please load a texture."));
        return;
    }
    if(ui->widthEdit->text().isEmpty() || ui->heightEdit->text().isEmpty()) {
        QMessageBox::warning(this,tr("Warning."),tr("Please input size of image for generation"));
        return;
    }
    if(((width = ui->widthEdit->text().toInt()) == 0) ||
       ((height = ui->heightEdit->text().toInt()) == 0)) {
        QMessageBox::warning(this,tr("Warning."),tr("The size should be integer."));
        return;
    }

    method = ui->method->currentIndex();
    switch(method) {
    case 0:{texture = new Texture(sourceImg); texture->textureGen(width, height, 5); break;}
    case 1:{texture = new Texture(sourceImg); texture->textureGen(width, height, 7); break;}
    case 2:{texture = new Texture(sourceImg); texture->textureGen(width, height, 9); break;}
    case 3:{l2Texture = new L2Texture(sourceImg); l2Texture->textureGen(width, height, 5); break;}
    case 4:{l2Texture = new L2Texture(sourceImg); l2Texture->textureGen(width, height, 7); break;}
    case 5:{l2Texture = new L2Texture(sourceImg); l2Texture->textureGen(width, height, 9); break;}
    default:;
    }

    IplImage* img;
    switch(method) {
    case 0:
    case 1:
    case 2: {
        img=cvCreateImage(cvSize(texture->whiteNoise->width,texture->whiteNoise->height),8,3);
        cvResize(texture->whiteNoise,img,CV_INTER_NN);
        break;
    }
    case 3:;
    case 4:;
    case 5: {
        img=cvCreateImage(cvSize(l2Texture->lowerTexture->whiteNoise->width,l2Texture->lowerTexture->whiteNoise->height),8,3);
        cvResize(l2Texture->lowerTexture->whiteNoise,img,CV_INTER_NN);
        break;
    }
    default:;
    }

//    IplImage* img=cvCreateImage(cvSize(texture->whiteNoise->width*5,texture->whiteNoise->height*5),8,3);
//    cvResize(texture->whiteNoise,img,CV_INTER_NN);
    QImage *qImg = new QImage();
    qImg = IplImage2QImage(img);
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addPixmap(QPixmap::fromImage(*qImg));
    ui->graphicsView->setScene(scene);
    cvReleaseImage(&img);
}
