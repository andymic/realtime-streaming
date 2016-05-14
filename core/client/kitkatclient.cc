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
      Mat frame = Mat::zeros(480 , 640, CV_8UC1);

      for(;;)
      {
        capture >> frame;
        if(frame.empty())
          break;

        //cout<<"frame data sent from the client: "<<frame<<endl;
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

void KitKatClient::SendVideoToServer(const char * addr, int port, const string & filepath)
{
	if(FileExist(filepath.c_str()))
    {
      VideoCapture capture(filepath);

      Mat frame = Mat::zeros(420 , 640, CV_8UC1);
      int fsize =frame.total()*frame.elemSize();

      client_sock = new ClientSocket(addr, port);

      if(!frame.isContinuous())
        frame = frame.clone();

      for(;;)
      {
        capture >> frame;
        if(frame.empty())
          break;

        client_sock->SendStream(frame, fsize);  
      }
    }
    else
    {
      cout<<"File does not exist"<<endl;
      return;
    }
}

void KitKatClient::ReadStreamFromServer(const char * ip, int port){
  client_sock = new ClientSocket(ip, port);
  client_sock->CaptureStream(ip, port);
}

KitKatClient::~KitKatClient(){
  delete client_sock;
}
