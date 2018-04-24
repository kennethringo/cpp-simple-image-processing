// Author: Kenneth Shimabukuro Abrahams
// Date: 23-04-2018
// driver.cpp
#include "Image.h"

#include <string>
#include <iostream>
#include <cstring>


int main (int argc, char** argv){
	using namespace std; //never use "using namespace" outside a scope...
	using namespace shmken002;
	Image i1(0,0);		//initialise values to zero to be reset later in loadImage method
	Image i2(0,0);
	Image out(0,0);;

	string operation;
	string firstFileName;
	string secondFileName;
	string outputFileName;

	int frequency;
	bool firstFileIsCorrect;
	bool secondFileIsCorrect;
	operation = string(argv[1]);


	if (argc == 5){

		if (operation == "-a"){
			firstFileName = string(argv[2]);
			secondFileName = string(argv[3]);
			outputFileName = string (argv[4]);
			if (i1->loadImage(firstFileName) && i2->loadImage(secondFileName) ){

				cout << "adding values in " << firstFileName << ", to values in " << secondFileName << "\n";
				(*i1)+(*i2); //must dereference pointers to get to underlying objects
				i1->saveImage(outputFileName);

				cout << "saved to output: "<< outputFileName << "\n";
			}else{
				cout << "Incorrect file names specified";
			}

		}
		if (operation == "-s"){
			firstFileName = string(argv[2]);
			secondFileName = string(argv[3]);
			outputFileName = string (argv[4]);
			if (i1->loadImage(firstFileName) && i2->loadImage(secondFileName) ){
				cout << "subtracting values in " << firstFileName << ", by values in " << secondFileName << "\n";
				(*i1)-(*i2);
				i1->saveImage(outputFileName);
				cout << "saved to output: "<< outputFileName << "\n";

			}
			else{
				cout << "Incorrect file names specified";
			}
		}

		
	}

	return 0;
}

