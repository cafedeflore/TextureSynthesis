#include "imageConversion.h"

IplImage* QImage2IplImage(QImage *qImg)
{
    IplImage *imgHeader = cvCreateImageHeader( cvSize(qImg->width(), qImg->height()), IPL_DEPTH_8U, 4);
    imgHeader->imageData = (char*) qImg->bits();

    uchar* newdata = (uchar*) malloc(sizeof(uchar) * qImg->byteCount());
    memcpy(newdata, qImg->bits(), qImg->byteCount());
    imgHeader->imageData = (char*) newdata;

    return imgHeader;
}

QImage* IplImage2QImage(IplImage *iplImg)
{
    int h = iplImg->height;
    int w = iplImg->width;
    int channels = iplImg->nChannels;
    QImage *qImg = new QImage(w, h, QImage::Format_ARGB32);
    char *data = iplImg->imageData;

    for (int y = 0; y < h; y++, data += iplImg->widthStep) {
        for (int x = 0; x < w; x++) {
            char r, g, b, a = 0;
            if (channels == 1) {
                r = data[x * channels];
                g = data[x * channels];
                b = data[x * channels];
            }
            else if (channels == 3 || channels == 4) {
                r = data[x * channels + 2];
                g = data[x * channels + 1];
                b = data[x * channels];
            }

            if (channels == 4) {
                a = data[x * channels + 3];
                qImg->setPixel(x, y, qRgba(r, g, b, a));
            }
            else {
                qImg->setPixel(x, y, qRgb(r, g, b));
            }
        }
    }
    return qImg;
}
