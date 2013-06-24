#include <time.h>
#include <windows.h>
#include "texture.h"
#include "iostream"

using namespace std;

int global;
Texture::Texture(QString path)
{
    img = cvLoadImage(path.toStdString().c_str());
//    cout << "channels" << img->nChannels <<endl;
//    cout << "depth" << img->depth <<endl;
//    cout << "width" << img->width <<endl;
//    cout << "height" << img->height <<endl <<endl;

}

Texture::Texture(IplImage* input) {
    img = input;
}

Texture::Texture(Texture* texture, int size) {
    int width = (texture->img->width+1)/size;
    int height = (texture->img->height+1)/size;

    img = cvCreateImage(cvSize(width, height),8,3);
    cvResize(texture->img,img,CV_INTER_LINEAR);
}

Texture::~Texture()
{
    cvReleaseImage(&img);
    cvReleaseImage(&whiteNoise);
}

void Texture::init(){
    nPts = 0;									// read data points
    k = 1;
    eps = 0;
}

void Texture::search(Neighbor* origin, char* color, int neighborWidth){
    readNeighbor(origin, p);
    kdTree->annkSearch(						// search
                    p,						// query point
                    k,								// number of near neighbors
                    nnIdx,							// nearest neighbors (returned)
                    dists,							// distance (returned)
                    eps);
    Neighbor* n = new Neighbor(img, this->nnIdx[0]/img->height, this->nnIdx[0]%img->height, neighborWidth);
    color[0] = n->data[n->size*3 - 3];
    color[1] = n->data[n->size*3 - 2];
    color[2] = n->data[n->size*3 - 1];
}

void Texture::findBest(Neighbor* origin, char* color, int neighborWidth) {
    Neighbor *n;
    double min = 255*255*3*(origin->size-1);
/*
    for(int j=0; j<img->height; j++) {
        for(int i=0; i<img->width; i++) {
            n = new Neighbor(img, j, i, neighborWidth); //j行i列
            double result;
            if((result = origin->difNeighbor(n)) < min) {
                color[0] = n->data[n->size*3 - 3];
                color[1] = n->data[n->size*3 - 2];
                color[2] = n->data[n->size*3 - 1];
                min = result;
//                cout <<"min"<<endl;
            }
//            cout<<j<<" "<<i<<" "<<result<<" ";
//            cout << char2int(n->data[n->size*3 - 3])<<" "
//                 << char2int(n->data[n->size*3 - 2])<<" "
//                 << char2int(n->data[n->size*3 - 1])<<endl;

            delete n;
        }
    }
*/
    for(int j=0; j<allNeighbor.size(); j++) {
        for(int i=0; i<allNeighbor[j].size(); i++) {
            n = allNeighbor[j][i];
            double result;
            if((result = origin->difNeighbor(n)) < min) {
                color[0] = n->data[n->size*3 - 3];
                color[1] = n->data[n->size*3 - 2];
                color[2] = n->data[n->size*3 - 1];
                min = result;
//                cout <<"min"<<endl;
            }
//            cout<<j<<" "<<i<<" "<<result<<" ";
//            cout << char2int(n->data[n->size*3 - 3])<<" "
//                 << char2int(n->data[n->size*3 - 2])<<" "
//                 << char2int(n->data[n->size*3 - 1])<<endl;
        }
    }
}

void Texture::whiteNoiseGen(int width, int height) {
    whiteNoise = cvCreateImage(cvSize(width, height), img->depth, img->nChannels);
    whiteNoise->origin = img->origin;
//    whiteNoise->widthStep = width;

    cvSetZero(whiteNoise);
    srand(time(NULL));
    int count=0;
    CvScalar s;
    for(int j=0; j<whiteNoise->height; j++) {
        for(int i=0; i<whiteNoise->width; i++, count++) {

            s.val[0]=rand()%256;    //B
            s.val[1]=rand()%256;    //G
            s.val[2]=rand()%256;    //R
//            printf("%d, B=%f, G=%f, R=%f\n",count,s.val[0],s.val[1],s.val[2]);
            cvSet2D(whiteNoise,j,i,s);
        }
    }
}

void Texture::preprocess(){
    init();
    dim = ((neighborWidth*neighborWidth)/2)*3;
    maxPts = img->height * img->width;
    k = 1;

    queryPt = annAllocPt(dim);					// allocate query point
    dataPts = annAllocPts(maxPts, dim);			// allocate data points
    nnIdx = new ANNidx[k];						// allocate near neigh indices
    dists = new ANNdist[k];						// allocate near neighbor dists
    p = annAllocPt(dim);
    cout << "*******************dim : " << dim << "************************" << endl;
    return ;
}

void Texture::textureGen(int width, int height, int neighborWidth) {
    this->neighborWidth = neighborWidth;
    double t0 = GetTickCount();
    this->Width = width;
    this->Height = height;
    whiteNoiseGen(width, height);
    this->preprocess();
    double t1 = GetTickCount();
    allNeighborGen(neighborWidth);
    kdTree = new ANNkd_tree(					// build search structure
        dataPts,					// the data points
        maxPts,						// number of points
        dim);						// dimension of space

//    cout << "2" << endl;
    CvScalar s;
    char bestColor[3];
    Neighbor *n;
    double t2 = GetTickCount();
    //n = new Neighbor(whiteNoise, 0, 0, neighborWidth);  //j行i列
    for(int j=0; j<whiteNoise->height; j++) {
        for(int i=0; i<whiteNoise->width; i++) {
            //n->set(whiteNoise, j, i, neighborWidth);  //j行i列
            n = new Neighbor(whiteNoise, j, i, neighborWidth);  //j行i列
            //findBest(n, bestColor, neighborWidth);
//            cout << "1" << endl;
            this->search(n, bestColor, neighborWidth);
//            cout << "3" << endl;
            s.val[0]=char2int(bestColor[2]);    //B
            s.val[1]=char2int(bestColor[1]);    //G
            s.val[2]=char2int(bestColor[0]);    //R
            cvSet2D(whiteNoise,j,i,s);
            delete n;
        }
    }
    cout << "lala" << endl;
    double t3 = GetTickCount();
//    allNeighborRelease();
    double t4 = GetTickCount();
    cout << "GetTickCount:" << t1-t0 << endl;
    cout << "GetTickCount:" << t2-t1 << endl;
    cout << "GetTickCount:" << t3-t2 << endl;
    cout << "GetTickCount:" << t4-t3 << endl;

}

void Texture::allNeighborGen(int neighborWidth) {
    cout<<"startGen"<<endl;
    Neighbor *n;
    for(int j=0; j<img->height; j++) {   //j行i列
        vector<Neighbor*> line;
        allNeighbor.push_back(line);
        for(int i=0; i<img->width; i++) {
            n = new Neighbor(img, j, i, neighborWidth);
            allNeighbor[j].push_back(n);
//            cout << "before read" << endl;
            readNeighbor(n, dataPts[j*img->height + i]);
//            cout << j*img->height + i << " read f" << endl;
//            cout<<j<<" "<<i<<endl;
            delete n;
        }
    }
}

void Texture::printPt(ostream &out, ANNpoint p)			// print point
{
    out << "(" << p[0];
    for (int i = 1; i < dim; i++) {
        out << ", " << p[i];
    }
    out << ")\n";
}

void Texture::readNeighbor(Neighbor* n, ANNpoint p){
    for(int i = 0; i < dim; ++i){
        p[i] = n->getRGB(i/3, i%3);
    }
    //printPt(cout, p);
}

void Texture::allNeighborRelease(void) {
    Neighbor *n;
    for(int j=0; j<allNeighbor.size(); j++) {   //j行i列
        for(int i=0; i<allNeighbor[j].size(); i++) {
            n = allNeighbor[j][i];
            delete n;
        }
    }
}

int Texture::char2int(char c) {
    int i = (int) c;
    if(i >= 0)
        return i;
    else
        return i+256;
}
