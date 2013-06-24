#include "l2texture.h"
#include "iostream"

L2Texture::L2Texture()
{
}

L2Texture::L2Texture(QString path) {
    lowerTexture = new Texture(path);
    upperTexture = new Texture(lowerTexture, 2);   // 2 means the size of upper is half of lower
}

L2Texture::L2Texture(IplImage* input) {
    lowerTexture = new Texture(input);
    upperTexture = new Texture(lowerTexture, 2);

//    cvNamedWindow("haha");
//    cvShowImage("haha", upperTexture->img);
//    cvWaitKey(0);
//    cvDestroyWindow("haha");
}

L2Texture::~L2Texture() {
    delete lowerTexture;
    delete upperTexture;
}

void L2Texture::init(){
    nPts = 0;									// read data points
    k = 1;
    eps = 0;
}

void L2Texture::search(L2Neighbor* origin, char* color, int neighborWidth){
    readNeighbor(origin, p);
    kdTree->annkSearch(						// search
                    p,						// query point
                    k,								// number of near neighbors
                    nnIdx,							// nearest neighbors (returned)
                    dists,							// distance (returned)
                    eps);
    L2Neighbor* n = new L2Neighbor(lowerTexture->img, upperTexture->img, this->nnIdx[0]/lowerTexture->img->height, this->nnIdx[0]%lowerTexture->img->height, neighborWidth);
    color[0] = n->lowerNeighbor->data[n->lowerNeighbor->size*3 - 3];
    color[1] = n->lowerNeighbor->data[n->lowerNeighbor->size*3 - 2];
    color[2] = n->lowerNeighbor->data[n->lowerNeighbor->size*3 - 1];
}

void L2Texture::readNeighbor(L2Neighbor* n, ANNpoint p){
    for(int i = 0; i < dim; ++i){
        p[i] = n->getRGB(i/3, i%3);
    }
    //printPt(cout, p);
}

void L2Texture::preprocess(){
    init();
    dim = ((neighborWidth*neighborWidth)/2)*3 + ((neighborWidth+2)/4*2+1)*((neighborWidth+2)/4*2+1);
    maxPts = this->lowerTexture->img->height * this->lowerTexture->img->width;
    k = 1;

    queryPt = annAllocPt(dim);					// allocate query point
    dataPts = annAllocPts(maxPts, dim);			// allocate data points
    nnIdx = new ANNidx[k];						// allocate near neigh indices
    dists = new ANNdist[k];						// allocate near neighbor dists
    p = annAllocPt(dim);
    cout << "*******************dim : " << dim << "************************" << endl;
    return ;
}

void L2Texture::readAll(int neighborWidth){
    cout << "start read all" << endl;
    L2Neighbor *n;
    for(int j=0; j<lowerTexture->img->height; j++) {
        for(int i=0; i<lowerTexture->img->width; i++) {
            n = new L2Neighbor(lowerTexture->img, upperTexture->img, j, i, neighborWidth);  //j行i列
            this->readNeighbor(n, this->dataPts[j*lowerTexture->img->height + i]);
            delete n;
        }
    }
}


void L2Texture::textureGen(int width, int height, int neighborWidth) {
    this->neighborWidth = neighborWidth;
    // 3->3 5->3 7->5 9->5 11->7 13->7...
    upperTexture->textureGen((width+1)/2, (height+1)/2, (neighborWidth+2)/4*2+1);
    lowerTexture->whiteNoiseGen(width, height);
    this->preprocess();
    CvScalar s;
    char bestColor[3];
    L2Neighbor *n;
    readAll(neighborWidth);
    kdTree = new ANNkd_tree(					// build search structure
        dataPts,					// the data points
        maxPts,						// number of points
        dim);						// dimension of space
    for(int j=0; j<lowerTexture->whiteNoise->height; j++) {
        for(int i=0; i<lowerTexture->whiteNoise->width; i++) {
            n = new L2Neighbor(lowerTexture->whiteNoise, upperTexture->whiteNoise, j, i, neighborWidth);  //j行i列
//            findBest(n, bestColor, neighborWidth);
            this->search(n, bestColor, neighborWidth);
            s.val[0]=char2int(bestColor[2]);    //B
            s.val[1]=char2int(bestColor[1]);    //G
            s.val[2]=char2int(bestColor[0]);    //R
            cvSet2D(lowerTexture->whiteNoise,j,i,s);
            delete n;
//            cout << "result"<<j<<" "<<i<<":";
//            cout << char2int(bestColor[0])<<" "
//                 << char2int(bestColor[1])<<" "
//                 << char2int(bestColor[2])<<endl;
        }
    }


//    cout<<lowerTexture->img->width<<" "<<lowerTexture->img->height<<endl;
//    cout<<lowerTexture->whiteNoise->width<<" "<<lowerTexture->whiteNoise->height<<endl;
//    cout<<upperTexture->img->width<<" "<<upperTexture->img->height<<endl;
//    cout<<upperTexture->whiteNoise->width<<" "<<upperTexture->whiteNoise->height<<endl;
}

void L2Texture::findBest(L2Neighbor* origin, char* color, int neighborWidth){
    L2Neighbor *n;
    double min = 255*255*3*(origin->lowerNeighbor->size-1 + origin->upperNeighbor->size);

    for(int j=0; j<lowerTexture->img->height; j++) {
        for(int i=0; i<lowerTexture->img->width; i++) {
            n = new L2Neighbor(lowerTexture->img, upperTexture->img, j, i, neighborWidth);   //j行i列
            double result;
            if((result = origin->difL2Neighbor(n)) < min) {
                color[0] = n->lowerNeighbor->data[n->lowerNeighbor->size*3 - 3];
                color[1] = n->lowerNeighbor->data[n->lowerNeighbor->size*3 - 2];
                color[2] = n->lowerNeighbor->data[n->lowerNeighbor->size*3 - 1];
                min = result;
                cout <<"min"<<endl;
            }
//            cout<<j<<" "<<i<<" "<<result<<" ";
//            cout << char2int(n->lowerNeighbor->data[n->lowerNeighbor->size*3 - 3])<<" "
//                 << char2int(n->lowerNeighbor->data[n->lowerNeighbor->size*3 - 2])<<" "
//                 << char2int(n->lowerNeighbor->data[n->lowerNeighbor->size*3 - 1])<<endl;
            delete n;
        }
    }
}

int L2Texture::char2int(char c) {
    int i = (int) c;
    if(i >= 0)
        return i;
    else
        return i+256;
}
