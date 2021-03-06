 /************************************************************
 *		file for recognizing gesture in a given image
 *		Developed by - Kumar Shubham
 ************************************************************/

#ifndef _REC_GESTURE_
#define _REC_GESTURE_


#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "main.hpp"
#include "myImage.hpp"
#include "handGesture.hpp"
#include <fstream>
#include<cmath>
#include<iostream>
#include<opencv2/ml/ml.hpp>

using namespace cv;
using namespace std;

class rec_gesture{
			public:
				MyImage m;
				Mat 	train_data;
				Mat	test_data;
				Mat 	train_labels;
				Mat	test_labels;	
				double *hu_matrix;
				double norm_matrix[7];
	        		string to_string(double num);
			void	text_feature(double *hu_matrix);
			void 	machine_learning_1( Mat *train_data, Mat *train_labels);
			int 	frame_number;
			int 	prev_gesture;
			int  old_gesture;
			void 	initialize();
			ofstream outfile;
			void	mat_generator();
			bool run;
			bool check(int number, int index);
			void signal_handler(int sign);	
			void normalize(const double *hu_matrix,double *norm_matrix);
			double	std_dev( const double *hu_matrix);
			double mean( const double *hu_matrix);
			int mostFrequentgestureNumber;

			int prediction_frame();
			void frequent_gesture();
			void computeGestureNumber();
			void getGestureNumber(MyImage *m,HandGesture *hg);
			void addNumberToImg(MyImage *m);
			void speak(int text);//function for converting gesture into speech
			Scalar numberColor;
			private :
			void logistic_prediction(double *hu_matrix,int * labels);	
			vector<int> gestureNumbers;
			vector<int> gestures2Display;
			Moments hu;
			double  mom[7];
			int _arr[5];

			bool button_1=true;
			bool button_2=true;
			bool button_3=true;
			bool button_4=true;
			bool button_5=true;// for recognizing namaste
			bool button_6= true;// for recognizing aap kaise hai
			bool cont_gest=false;
				 };
			
#endif
