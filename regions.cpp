#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image;
  Vec3b val;
  int p1x,p2x,p1y,p2y;

  image= imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "nao abriu biel.png" << endl;

  namedWindow("janela",WINDOW_AUTOSIZE);

  cin>>p1x>>p1y>>p2x>>p2y;

  for(int i=p1x;i<p2x;i++){
    for(int j=p1y;j<p2y;j++){
    	for(int k=0;k<3;k++) image.at<Vec3b>(i,j)[k] = 255-image.at<Vec3b>(i,j)[k];
    }
  }
  
  imshow("janela", image);  
  waitKey();
  return 0;
}
