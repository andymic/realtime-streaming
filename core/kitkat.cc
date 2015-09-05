//============================================================================
// Name        : kitkat.cc
// Author      : Andy
// Version     : 1.0
// Copyright   : Use this code at your own risk...your pants may fall off!
// Description : OpenCV experimentation in C++, Ansi-style
//============================================================================
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;
using namespace cv;

#define img_path "/home/andy/Pictures/rockon.jpg"
#define vid_path "/home/andy/Videos/Moving Takahashi-HD.mp4"

class Opencv
{
    public:
    Opencv(){}
    bool DoesFileExist(const char *filename)
    {
        ifstream infile(filename);
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
            cout<<" No image data"<<endl;
            return (false);
        }
        namedWindow( path, 1 );
        // imshow() displays an image in the specified window.
        // If the window was created with the CV_WINDOW_AUTOSIZE flag,
        // the image is shown with its original size
        imshow( path, image );
        waitKey(0);
    }
    void ReadVideo(const string & filename)
    {
      if(DoesFileExist(filename.c_str()))
      {
        const char * window_name = "kitkat";
        VideoCapture capture(filename);
 
        namedWindow(window_name, WINDOW_KEEPRATIO);
        Mat frame;

        for(;;)
        {
          capture >> frame;
          if(frame.empty())
            break;

          imshow(window_name, frame);

          //following up each draw with waitKey so that
          // highgui has time to process the draw request
          char key = (char)waitKey(30);

          if(key == 'q')
            return;
        }


      }
      else
      {
        cout<<"File does not exist"<<endl;
      }
      
    }
    ~Opencv(){}
};
int main( int argc, char** argv )
{
    Opencv * c = new Opencv();
    c->ReadVideo(vid_path);
    return 0;
}