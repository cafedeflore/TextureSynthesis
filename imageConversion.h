#ifndef IMAGECONVERSION_H
#define IMAGECONVERSION_H

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "QImage"

IplImage* QImage2IplImage(QImage *qImg);
QImage* IplImage2QImage(IplImage *iplImg);

#endif // IMAGECONVERSION_H
