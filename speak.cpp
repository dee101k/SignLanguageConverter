 
 #include<iostream>
 #include<fstream>
 #include "speak.hpp"
// #include<stdio.h>



using namespace std;

int prev_speech=0;
void speak::initialize()
	{
		outfile.open("gesture.txt",std::ios::trunc);
		outfile.flush();
		//gesture=0;
		//outfile.close();
	}
void speak::voice() //i iss the id of the number which will be used to speak
	{
		outfile.open("gesture.txt",std::ios::trunc);
		
		if (prev_speech!=speech)
		{
			gesture=12;
			outfile<<speech<<endl;
			//cout<<speech<<endl;
			prev_speech=speech;
			outfile.flush();
			

			

		 //cout<<gesture<<endl;
		}	
		outfile.close();
	}
