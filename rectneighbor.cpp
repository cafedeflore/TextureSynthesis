#include "rectNeighbor.h"

RectNeighbor::RectNeighbor(){}
RectNeighbor::RectNeighbor(IplImage* img, int x, int y, int n)  //x行y列
{
    width = n;
    size = n*n;
    data = new char[size * 3];  //r,g,b

    int count=0;
    for(int j=(-width/2); j<=width/2; j++) {
        for(int i=(-width/2); (i<=width/2) && (count<size); i++, count++) {
            getColor(img, j+x, i+y, data+3*count);
        }
    }

}

RectNeighbor::~RectNeighbor() {
    delete []data;
    data = NULL;
}

void RectNeighbor::getColor(IplImage* img, int x, int y, char* color) { //x行y列
    int channels = img->nChannels;
    char *data = img->imageData;

    x = getCoor(x, img->height);
    y = getCoor(y, img->width);

//    cout <<x<<" "<<y<<endl;

    data += img->widthStep * x;

    color[0] = data[y * channels + 2];  //r
    color[1] = data[y * channels + 1];  //g
    color[2] = data[y * channels];  //b

//    cout<<global2++<<" "<<(int)color[0]+128<<" "<<(int)color[1]+128<<" "<<(int)color[2]+128<<" ";
}

double RectNeighbor::difRectNeighbor(RectNeighbor *rectNeighbor) {
    double dif=0;
    for(int i=0; i<size; i++) {
        dif += L2Norm(&data[i*3], &rectNeighbor->data[i*3]);
    }
    return dif;
}

double RectNeighbor::L2Norm(char* color1, char* color2) {
    double result = 0;
    result += (char2int(color1[0]) - char2int(color2[0])) * (char2int(color1[0]) - char2int(color2[0]));
    result += (char2int(color1[1]) - char2int(color2[1])) * (char2int(color1[1]) - char2int(color2[1]));
    result += (char2int(color1[2]) - char2int(color2[2])) * (char2int(color1[2]) - char2int(color2[2]));

//    cout<<"color1 "<<char2int(color1[0])<<" "<<char2int(color1[1])<<" "<<char2int(color1[2])<<endl;
//    cout<<"color2 "<<char2int(color2[0])<<" "<<char2int(color2[1])<<" "<<char2int(color2[2])<<endl;
    return result;
}

int RectNeighbor::getCoor(int x, int n) {
    if(x < 0)
        return x+n;
    else if(x >= n)
        return x-n;
    else
        return x;
}

int RectNeighbor::char2int(char c) {
    int i = (int) c;
    if(i >= 0)
        return i;
    else
        return i+256;
}
