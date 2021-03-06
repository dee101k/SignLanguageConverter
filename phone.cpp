 #include <opencv2/imgproc/imgproc.hpp>
 #include<opencv2/opencv.hpp>
 #include <opencv2/highgui/highgui.hpp>
 #include <stdio.h>
 #include <stdlib.h>
 #include <iostream>
 #include<string>
#include<fstream>

 using namespace cv;

 using namespace std;

  string int2str(int number)
	{
		stringstream ss;
		ss << number;
		string str = ss.str();
		return str;
	}

 int main()

	{	setNumThreads(2);
		int thread =getNumThreads();
		int fontFace = FONT_HERSHEY_PLAIN;
		Scalar fColor(0,0,0);
		float fontSize= 3.7f;
		int thickness=7;
		Mat Image,Image_Copy;
		Image=imread("mobile.png");
		namedWindow("Phone",CV_WINDOW_KEEPRATIO);
		int count=0;
		int ypos=Image.rows/6.2;
		int xpos=Image.cols/1.00001;
                int a;
		cout<<thread<<endl;
               while(1)
		{	
			ifstream infile("gesture.txt");
			infile>>a;
			count++;
			//cvCopy(Image, Image_Copy);
			Image.copyTo(Image_Copy);
			if (a<20 && a>0){
				if (a<10)
			putText(Image_Copy,string(int2str(a)),Point(ypos,xpos),fontFace,fontSize  ,fColor,thickness);
				else if (a==11)
			putText(Image_Copy,string("HI"),Point(ypos,xpos),fontFace,fontSize  ,fColor,thickness);
			
				else if (a==12)
			putText(Image_Copy,string("alwida"),Point(ypos,xpos),fontFace,fontSize  ,fColor,thickness);
			
				else if (a==13)
			putText(Image_Copy,string("haan"),Point(ypos,xpos),fontFace,fontSize  ,fColor,thickness);
			
				else if (a==14)
			putText(Image_Copy,string("soonder"),Point(ypos,xpos),fontFace,fontSize  ,fColor,thickness);
				else if (a==15)
			putText(Image_Copy,string("namaste"),Point(ypos,xpos),fontFace,fontSize  ,fColor,thickness);
				
			else if (a==16)
			putText(Image_Copy,string(". . . "),Point(ypos,xpos),fontFace,fontSize  ,fColor,thickness);
				
						
		}
			cvWaitKey(10);
			imshow("Phone",Image_Copy);
		}

		
	}
