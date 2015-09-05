//============================================================================
// Name        : kitkat.cpp
// Author      : Andy
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <fstream>

using namespace std;
using namespace cv;

class Opencv
{
public:
  Opencv(){}
  bool DoesFileExist(const char *fileName)
  {
      ifstream infile(fileName);
      return infile.good();
  }

  int ShowImage(const char * path)
  {

    if(!DoesFileExist(path))
    {
      cout<<"File not found"<<endl;
      return (false);
    }

    // create a MAT object for input image
    Mat image;

    // load an image
    image = imread( path, CV_LOAD_IMAGE_COLOR );

    if(!image.data )
    {
        printf( " No image data \n " );
        return (false);
    }

    namedWindow( path, 1 );


    // imshow() displays an image in the specified window. 
    // If the window was created with the CV_WINDOW_AUTOSIZE flag, 
    // the image is shown with its original size
    imshow( path, image );
    waitKey(0);
  }
  ~Opencv(){}
};


int main( int argc, char** argv )
{
  Opencv * c = new Opencv();
  c->ShowImage("");
    return 0;
}