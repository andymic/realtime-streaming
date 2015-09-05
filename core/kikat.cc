//============================================================================
// Name        : kitkat.cpp
// Author      : Andy
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;

int main( int argc, char** argv )
{
    // argv[1] - whaere the image is located
    char* imagePath = argv[1];

    // create a MAT object for input image
    Mat image;

    // load an image
    image = imread( imagePath, 1 );

    if( argc != 2 || !image.data )
    {
        printf( " No image data \n " );
        return -1;
    }

    // create a MAT object for gray image
    Mat gray_image;

    // convert to Greyscale format
    // cvtColor( image, gray_image, CV_BGR2GRAY );
    cvtColor( image, gray_image, COLOR_BGR2GRAY );

    // save the transformed image to a file
    imwrite( "../images/GrayImage.jpg", gray_image );

    // creates two windows
    namedWindow( imagePath, CV_WINDOW_AUTOSIZE );
    namedWindow( "Gray image", CV_WINDOW_AUTOSIZE );

    // imshow() displays an image in the specified window. 
    // If the window was created with the CV_WINDOW_AUTOSIZE flag, 
    // the image is shown with its original size
    imshow( imagePath, image );
    imshow( "Gray image", gray_image );

    // wait for key press
    waitKey(0);

    return 0;
}