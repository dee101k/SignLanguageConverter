#ifndef _VOICE_
#define _VOICE_


#include<iostream>
#include<fstream>

using namespace std;


class speak {

		public:
		int speech;
		void initialize();
		void voice();
		int gesture;
		private:

		ofstream outfile;
		
		
		
	    };

#endif
	
