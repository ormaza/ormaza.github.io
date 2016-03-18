#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image;
  Vec3b val;

  image= imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "nao abriu biel.png" << endl;

  namedWindow("janela",WINDOW_AUTOSIZE);

  int x = image.size().width;
  int y = image.size().height;

  Mat A(image,Rect(0,0,x/2,y/2));
  Mat B(image,Rect(x/2,0,x/2,y/2));
  Mat C(image,Rect(0,y/2,x/2,y/2));
  Mat D(image,Rect(x/2,y/2,x/2,y/2));

  Mat out = image.clone();

  A.copyTo(out(Rect(x/2,y/2,x/2,y/2)));
  B.copyTo(out(Rect(0,y/2,x/2,y/2)));
  C.copyTo(out(Rect(x/2,0,x/2,y/2)));
  D.copyTo(out(Rect(0,0,x/2,y/2)));
  
  imshow("janela", out);  
  waitKey();
  return 0;
}
