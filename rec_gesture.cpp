#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "main.hpp"
#include "myImage.hpp"
#include <fstream>
#include <cmath>
#include<iostream>
#include <sys/io.h>
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include"rec_gesture.hpp"
#include <csignal>
#include<opencv2/ml/ml.hpp>
#include "handGesture.hpp"
using namespace cv;
using namespace std;
 double rec_gesture::mean( const double *hu_matrix)
	{
		double temp=0;
		for (int i=0; i<7;i++)
			{
				temp+=hu_matrix[i];
			}
		return(temp/7);
	}

	
	  double rec_gesture::std_dev( const double *hu_matrix)
	{
		double mn=mean(hu_matrix);
		double st=0;
		double result;
		for(int i=0;i<7;i++)
		{
			st+=pow(hu_matrix[i]-mn,2);
		}		
		result=sqrt(st/7);
		return result;
	}
void rec_gesture::normalize(const double *hu_matrix,double *norm_matrix)
	{	double mn,st;
			mn=mean(hu_matrix);
			st=std_dev(hu_matrix);	
		
		for (int i=0;i<7;i++)

		{	//norm_matrix[i]=0;
			norm_matrix[i]=(hu_matrix[i]-mn)/st;
		}
	}
// for calculation of various feature using hue moments
void rec_gesture::initialize()
	{
		
	outfile.open("r.txt",std::ios::trunc);
	//outfile<<flush;	
	}

string rec_gesture:: to_string(double num)
{
    ostringstream  myStream; //creates an ostringstream object
    myStream << num << flush;
    /*
    * outputs the number into the string stream and then flushes
    * the buffer (makes sure the output is put into the stream)
    */
    return(myStream.str()); //returns the string form of the stringstream object
};
void rec_gesture::text_feature( double *hu_matrix)
	{
	      int ikey=cvWaitKey(10); 
		  string text;
		int i;
		text= "";
		//cout<<ikey<<endl;
	      switch(ikey)
		{	
			case 49:
			normalize(hu_matrix,norm_matrix);
			for (i=0;i<7;i++)	//yes
			    {
				text+=to_string(norm_matrix[i])+ " ";
			    }
			text+=" " + to_string(1);
			outfile<<text<<endl;		
			break;
			case 50:
			normalize(hu_matrix,norm_matrix);
				//No
			for (i=0;i<7;i++)	
			    {
				text+=to_string(norm_matrix[i])+ " ";
			    }
			text+=" " + to_string(2);		
			outfile<<text<<endl;
			break;
			case 51:
				//bye
			normalize(hu_matrix,norm_matrix);
			for (i=0;i<7;i++)	
			    {
				text+=to_string(norm_matrix[i])+ " ";
			    }
			text+=" " + to_string(3);
			outfile<<text<<endl;		
			break;
			case 52:
				//HI
			normalize(hu_matrix,norm_matrix);
			for (i=0;i<7;i++)	
			    {
				text+=to_string(norm_matrix[i])+ " ";
			    }
			text+=" " + to_string(4);
			outfile<<text<<endl;		
			break;
			case 53:
				//thanks
			normalize(hu_matrix,norm_matrix);
			for (i=0;i<7;i++)	
			    {
				text+=to_string(norm_matrix[i])+ " ";
			    }
			text+=" " + to_string(5);
			outfile<<text<<endl;		
			break;
			case 27:
			outfile.close();
			break;			
		}
			
					
	}
void rec_gesture::mat_generator()
	{
		Mat m;
	//FileStorage fs("train_data.txt",FileStorage::READ);
	//fs["mat1"]>>m;
		int i;
		ifstream f("final.txt");
	string line;
	for (i = 0; std::getline(f, line); ++i);
		Mat A_data;
		Mat A_labels; 
	
	 A_data=Mat::zeros(i,7,CV_64FC1);
	 A_labels=Mat::zeros(i,1,CV_64FC1);

	std::fstream myfile("final.txt", std::ios_base::in);

   	 float a;
     	   for(int rows=0;rows<i;rows++)
		{
			for(int cols=0;cols<8;++cols){
					if (myfile>>a)
						{
					if (cols!=7)
				A_data.at<float>(rows,cols)=a;
					else
				A_labels.at<float>(rows,cols)=a;
						}
				else
				{rows=cols=1000;
				break;
				}
				//cout<< train_data.at<float>(0,6)<<endl;
		
				}	
		}
 		train_data=A_data;
		train_labels=A_labels;
		 
	//machine_learning_1(&A_data,&A_labels);
	}
	/*
 void rec_gesture ::machine_learning_1( Mat *train_data, Mat *train_labels)
			{cout<<train_labels->at<float>(22,1)<<endl;
		
			
			int count_1,count_2,count_3,count_4;
			count_1=count_2=count_3=count_4=0;
			for(int i=1;i<train_labels->rows;i++)

			{
				cout<<train_labels->at<float>(i,1)<<endl;
				if (train_labels->at<float>(i,1)==1)
				count_1++;
				
			}
	cout << "The value of 1 2 3 4"<<count_1<<" "<<count_2<<" "<<count_3<<" "<<count_4<<endl;					
		}
	*/

 int rec_gesture::prediction_frame()
	{
		normalize(hu_matrix,norm_matrix);
			//above code is for recognizing gesture
			 int temp=cvWaitKey(50);
			  if (temp==49){
			cont_gest=!cont_gest;
			cout << "change in the overall structure of the code"<<endl;
			}
 
			if (!cont_gest){ 
			if(abs(norm_matrix[6])>0.4086)
				return 2 ;
			else if (abs(norm_matrix[4])>=0.40835)
				return 1;
			else if (abs(norm_matrix[4])<0.40835)
				return 3;	
			else
				return 0;
			}
			else{
				//  code for recognizing continuous gesture
				
				if(abs(norm_matrix[1])>0.4060){
				return 6 ;//Namaste
				}
				else if (abs(norm_matrix[1])<0.4060 && abs(norm_matrix[1])<0.4085){
				//cout<<abs(norm_matrix[1])<<endl;
				return 5; // aap kaise hai 
				}
				else 
				return 0;

			    }
	}
void rec_gesture ::frequent_gesture()
	{	int i=0;
		i=prediction_frame();
		 gestureNumbers.push_back(i);		
	}

void rec_gesture::computeGestureNumber(){
	std::sort(gestureNumbers.begin(), gestureNumbers.end());
	int frequentNr;	
	int thisNumberFreq=1;
	int highestFreq=1;
	frequentNr=gestureNumbers[0];
	for(int i=1;i<gestureNumbers.size(); i++){
		if(gestureNumbers[i-1]!=gestureNumbers[i]){
			if(thisNumberFreq>highestFreq){
				frequentNr=gestureNumbers[i-1];	
				highestFreq=thisNumberFreq;
			}
			thisNumberFreq=0;	
		}
		thisNumberFreq++;	
	}
	if(thisNumberFreq>highestFreq){
		frequentNr=gestureNumbers[gestureNumbers.size()-1];	
	}
	mostFrequentgestureNumber=frequentNr;	
}
void rec_gesture::getGestureNumber(MyImage *m,HandGesture *hg){
		Mat Region_interest;
		Region_interest=m->bw(hg->bRect);
		imshow("Image_checking",Region_interest);
		//imshow("Image_checking",m->gesture);
		hu=moments(Region_interest);
		HuMoments(hu,mom);
		hu_matrix=mom;
		//initialize();
		text_feature(mom);
		frequent_gesture();
		if(hg->frameNumber>12){
			computeGestureNumber();	
			gestureNumbers.clear();
			if (hg->mostFrequentFingerNumber==3 && mostFrequentgestureNumber== 3 )
			gestures2Display.push_back(4);
			else
			gestures2Display.push_back(mostFrequentgestureNumber);
			
			
			
		}
	
	addNumberToImg(m);
}
void rec_gesture::addNumberToImg(MyImage *m){
	flip(m->gesture,m->gesture,1);
	int xPos=10;
	int yPos=10;
	int offset=30;
	float fontSize=1.5f;
	numberColor=Scalar(0,0,200);
	int fontFace = FONT_HERSHEY_PLAIN;
	for(int i=0;i<gestures2Display.size();i++){
		//rectangle(m->gesture,Point(xPos,yPos),Point(xPos+offset,yPos+offset),numberColor, 2);
			if((gestures2Display[i]==1)&&button_1){
		//putText(m->gesture, "A",Point(xPos+7,yPos+offset-3),fontFace,fontSize,numberColor);
		speak(11);
		button_1=!button_1;
			}
			if((gestures2Display[i]==2)&&button_2){
				
		//putText(m->gesture, "B",Point(xPos+7,yPos+offset-3),fontFace,fontSize,numberColor);
		speak(12);
		button_2=!button_2;
			}
			if((gestures2Display[i]==3)&&button_3){
				
		//putText(m->gesture, "C",Point(xPos+7,yPos+offset-3),fontFace,fontSize,numberColor);
		speak(13);
		button_3=!button_3;
				}
			if(gestures2Display[i]==4){
				
		//putText(m->gesture, "D",Point(xPos+7,yPos+offset-3),fontFace,fontSize,numberColor);
			speak(14);
	       		}
		/*
		xPos+=40;
		if(xPos>(m->src.cols-m->src.cols/3.2)){
			yPos+=40;
			xPos=10;
			*/
	if((gestures2Display[i]==6)&&button_5){
				
		//putText(m->gesture, "A",Point(xPos+7,yPos+offset-3),fontFace,fontSize,numberColor);
		speak(15);
		//cout<<"Namaste"<<endl;
		button_5=false;
		}
			

	if((gestures2Display[i]==5)&&button_6){
				
		//putText(m->gesture, "A",Point(xPos+7,yPos+offset-3),fontFace,fontSize,numberColor);
		speak(16);
		//cout<<"aap kaise hai"<<endl;
		button_6=false;
			}
	

		}
	}
	
//imshow("result",m->gesture);

	//function for speech in hand gesture 
	void rec_gesture::speak(int text)
	{	int n=0;
		ofstream outfile;
		outfile.open("gesture.txt",std::ios::trunc);
		if((old_gesture!=text)&&(prev_gesture!=text) && (text==11||(text==12)||(text==13)||text==14 ||(text==15)||(text==16))){	++n;
		outfile<<text<<endl;
		cout<<text<<endl;
		outfile.close();
		if(n%2==0)
		prev_gesture=old_gesture;

		old_gesture=text;
			
	}
		/*
		for (int i=0;i<gestures2Display.size();i++)
		{
			if((old_gesture!=gestures2Display[i]) && (gestures2Display[i]==1||(gestures2Display[i]==2)||(gestures2Display[i]==3)||gestures2Display[i]==4))
				{
					outfile<<(gestures2Display[i]+5)<<endl;
					outfile.close();
					cout<<gestures2Display[i]<<endl;
					//_arr[n]=gestures2Display[i];
					//++n;
				
				}
				old_gesture=gestures2Display[i];
				//cvWaitKey(20);
				//outfile.flush();
		}*/
			
						
	}

  bool rec_gesture::check(int number, int index)
	{
		for (int i=index ; i>=0; i--)
		{
			if (number==_arr[i])
				return false;
			else 
			continue;
		}
			return true;
	}

