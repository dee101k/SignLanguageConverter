/*********************************************************
 * Developed by Kumar Shubham
*********************************************************/
// OpenCV
#include "cv.h"
#include "highgui.h"
#include "opencv2/imgproc/imgproc.hpp"
#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui/highgui.hpp>  // Video write

// C++
#include <iostream>
#include <string>
#include <utility>
 #include<fstream>


// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>
//#include"run.hpp"

using namespace std;
using namespace cv;

	

		

//run motor;//motor object
bool DEBUG;
static CvMemStorage* storage = 0;
static CvHaarClassifierCascade* cascade = 0;
CvCapture* capture=NULL;
 VideoWriter out;
int  mv_rt=0;
int mv_lt=0;
// Function to detect and draw any faces that is present in an image
void detect_and_draw( IplImage* img ) {
    int scale = 1;
    IplImage* temp = cvCreateImage( cvSize( img->width / scale, img->height / scale ), 8, 3 );
    CvPoint pt1, pt2;

    cvClearMemStorage( storage );

    if( cascade ) {
        // There can be more than one face in an image. So create a growable sequence of faces.
        // Detect the objects and store them in the sequence
        CvSeq* faces = cvHaarDetectObjects( img, cascade, storage,
                                            1.1, 2, CV_HAAR_DO_CANNY_PRUNING,
                                            cvSize( 40, 40 ) );

        // Loop the number of faces found.
        for( int i = 0; i < ( faces ? faces->total : 0 ); i++ ) {
            // Create a new rectangle for drawing the face
            CvRect* r = ( CvRect* )cvGetSeqElem( faces, i );

            // Find the dimensions of the face,and scale it if necessary
            pt1.x = r->x * scale;
            pt2.x = ( r->x + r->width ) * scale;
            pt1.y = r->y * scale;
            pt2.y = ( r->y + r->height ) * scale;

            // Draw the rectangle in the input image
            cvRectangle( img, pt1, pt2, CV_RGB( 255, 0, 0 ), 3, 8, 0 );
	
	// code for changing the motor position with respect to face Detected
		ofstream outfile;
		int a=0;
		if(r->x){
		//cout<<"face!!"<<endl;
		outfile.open("motor.txt",std::ios::trunc);
		outfile<<1<<endl;
		//exit(EXIT_FAILURE);
		//outfile.flush();		
		}
		//motor.start();

        }

    }

    cvReleaseImage( &temp );
}


// Main function, defines the entry point for the program.
int main( int argc, char** argv ) {
    if( argc > 1 ) {
	ofstream outfile;
	outfile.open("motor.txt",std::ios::trunc);
	outfile.flush();
        string imageIn;
        string imageOut;
        string cascade_file = argv[1];

        IplImage* image = NULL;
        bool in = true;

        DEBUG = false;
	imageIn=argv[2];
	/*
        // set options
        for( int i = 1; i < argc; i++ ) {
            const char *sw = argv[i];

            if( !strcmp( sw, "-h" ) || !strcmp( argv[i], "--help" ) ) {
                usage();
                return 0;

            } else if( !strcmp( sw, "-d" ) || !strcmp( sw, "--debug" ) ) {
                DEBUG = true;

            } else if( !strcmp( sw, "-c" ) || !strcmp( sw, "--cascade" ) ) {
                if( i + 1 >= argc ) {
                    usage();
                    return 1;
                }

                cascade_file = argv[++i];

            } else {
                if( in ) {
                    imageIn += sw;
                    in = false;
                } else {
                    imageOut += sw;
                }l
            }
        }
	*/

		// commond for running the code will be entering 0 in image destination
        if( imageIn=="0" ) {

            cout << "imageIn:  " << imageIn << endl;
            cout << "cascade:  " << cascade_file << endl;

            // Load the HaarClassifierCascade
            cascade = ( CvHaarClassifierCascade* )cvLoad( cascade_file.c_str(), 0, 0, 0 );
	//out.open("out.avi", CV_FOURCC('M', 'J', 'P', 'G'), 15,cvSize(640, 480),true);
            if( !cascade ) {
                cerr << "ERROR: Could not load classifier cascade" << endl;
                return -1;
            }
		cvNamedWindow("Camera_output",1);
		 capture =cvCaptureFromCAM(0);

		cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, 320);
		cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, 240 );

		while(1){
            storage = cvCreateMemStorage( 0 );
            //image = cvLoadImage( imageIn.c_str(), 1 );
		image=cvQueryFrame(capture);
            if( image ) {
                detect_and_draw( image );

                cvShowImage("Camera_output",image);
	//	out<<image;
		int key=cvWaitKey(10);
		if(key==27)//pressing ESC will lead to break
		{
		break;
		}

                  }
		}

                cvReleaseCapture(&capture); //Release capture.
		cvDestroyWindow("Camera_Output");
		out.release();
		return 0;

        } 

    } 
	
    
}
