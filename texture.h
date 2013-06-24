#ifndef TEXTURE_H
#define TEXTURE_H

#include <QtGui>
#include <ANN.h>
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "neighbor.h"
#include <vector>
//#include "test.h"
using namespace std;

class Texture
{
public:
    int					nPts;					// actual number of data points
    int                 dim;
    int                 k;
    int                 eps;
    int                 maxPts;
    ANNpointArray		dataPts;				// data points
    ANNpoint			queryPt;				// query point
    ANNidxArray			nnIdx;					// near neighbor indices
    ANNdistArray		dists;					// near neighbor distances
    ANNkd_tree*			kdTree;					// search structure
    ANNpoint p;
    IplImage* img;
    IplImage* whiteNoise;
    int neighborWidth;
    vector< vector<Neighbor*> > allNeighbor;
    int Height;
    int Width;
public:
    Texture(QString path);
    Texture(IplImage* input);
    Texture(Texture* texture, int size);    //the new texture will be only one of the size
    ~Texture();
void printPt(ostream &out, ANNpoint p);
    void init();
    void preprocess();
    void readNeighbor(Neighbor* n, ANNpoint p);
    void search(Neighbor* origin, char* color, int neighborWidth);
    void whiteNoiseGen(int width, int height);
    void findBest(Neighbor* origin, char* color, int neighborWidth);
    void textureGen(int width, int height, int neighborWidth);
    int char2int(char c);
    void allNeighborGen(int neighborWidth);
    void allNeighborRelease(void);
};

#endif // TEXTURE_H
