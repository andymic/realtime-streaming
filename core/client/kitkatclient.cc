#include "kitkatclient.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;
using namespace cv;

bool KitKatClient::FileExist(const char * filename)
{
    ifstream infile(filename);
    return infile.good();
}

int KitKatClient::ShowImage(const char * path)
{
	if(!FileExist(path))
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

    return (true);
}

int KitKatClient::ReadVideo(const string & filename)
{
	if(FileExist(filename.c_str()))
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
          return 1;
      }
    }
    else
    {
      cout<<"File does not exist"<<endl;
      return -1;
    }
    return 1;
}

// vector<Mat> KitKatClient::GetVideoFrames(const string & filename)
// {
// 	if(FileExist(filename.c_str()))
//     {
//       const char * window_name = "kitkat";
//       VideoCapture capture(filename);
 
//       namedWindow(window_name, WINDOW_KEEPRATIO);
//       Mat frame;

//       vector<Mat> frames;

//       for(;;)
//       {
//         capture >> frame;
//         if(frame.empty())
//           break;

//       	frames.push_back(frame);

//       }
//     }
//     else
//     {
//       cout<<"File does not exist"<<endl;
//       return NULL;
//     }
//     return frames;
// }
