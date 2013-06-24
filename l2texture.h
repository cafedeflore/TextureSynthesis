#ifndef L2TEXTURE_H
#define L2TEXTURE_H

#include "texture.h"
#include "l2neighbor.h"

class L2Texture
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
    int neighborWidth;
    Texture *upperTexture;
    Texture *lowerTexture;
public:
    L2Texture();
    L2Texture(QString path);
    L2Texture(IplImage* input);
    ~L2Texture();

    void init();
    void preprocess();
    void readNeighbor(L2Neighbor* n, ANNpoint p);
    void search(L2Neighbor* origin, char* color, int neighborWidth);
    void readAll(int neighborWidth);
    void findBest(L2Neighbor* origin, char* color, int neighborWidth);
    void textureGen(int width, int height, int neighborWidth);
    int char2int(char c);
};

#endif // L2TEXTURE_H
