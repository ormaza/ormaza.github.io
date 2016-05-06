#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

#define STEP 5
#define JITTER 3

int main(int argc, char** argv){
  vector<int> yrange;
  vector<int> xrange;

  Mat image, border, points, out;

  /*
  image: imagem original
  border: imagem canny
  points: imagem pontilhista
  */

  int width, height, gray;
  int x, y;
  
  image= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

  srand(time(0));
  
  if(!image.data){
  cout << "nao abriu" << argv[1] << endl;
    cout << argv[0] << " imagem.jpg";
    exit(0);
  }

  width=image.size().width;
  height=image.size().height;

  xrange.resize(height/STEP);
  yrange.resize(width/STEP);
  
  iota(xrange.begin(), xrange.end(), 0); 
  iota(yrange.begin(), yrange.end(), 0);

  for(uint i=0; i<xrange.size(); i++){
    xrange[i]= xrange[i]*STEP+STEP/2;
    yrange[i]= yrange[i]*STEP+STEP/2;
  }
  
  points = Mat(height, width, CV_8U, Scalar(255));

  random_shuffle(xrange.begin(), xrange.end());

  int raio;

  out = image.clone();

  for(int limiar=0; limiar<=200; limiar+=10){

    Canny(image, border, limiar, 3*limiar);
    // imwrite("canny.png", border);

    random_shuffle(xrange.begin(), xrange.end());

    for(auto i : xrange){
      random_shuffle(yrange.begin(), yrange.end());
      for(auto j : yrange){
        if(border.at<uchar>(i,j) == 255)
        {
        raio = rand()%4;
        x = i+rand()%(2*JITTER)-JITTER+1;
        y = j+rand()%(2*JITTER)-JITTER+1;
        gray = image.at<uchar>(x,y);
        circle(out,
               cv::Point(y,x),
               raio,
               CV_RGB(gray,gray,gray),
               -1,
               CV_AA);
      }
      }
  }
}

  imwrite("out.png", out);
  
  return 0;
}
