// Author: Kenneth Shimabukuro Abrahams
// Date: Date: 23-04-2018
// Image.cpp
#include "Image.h"

#include <string>
#include <memory>
#include <iostream>
#include <fstream>



using namespace shmken002;
using namespace std;
using it = Image::iterator;
namespace shmken002
{
	//constructor
	Image::Image(int w,int h): width(w), height(h), sizeOfImage(0), data(new unsigned char[w*h]){}

	Image::~Image(){
		width = 0;
		height = 0;

	}
	int Image::getWidth() const{
		return width;
	}
	int Image::getHeight() const{
		return height;
	}
	void Image::setWidth(int w){
		width = w;

	}
	void Image::setHeight(int h){
		height = h;
	}
	void Image::reset(int w, int h) {
		width = w; height = h;
//		sizeOfImage = w*h;
		data = unique_ptr <unsigned char[]>(new unsigned char[sizeOfImage]);
	}

	bool Image::loadImage(string imageName){
			char * memblock;
			int nRows = 0;
			int nCols = 0;
			string numberOfColumns= "";
			string numberOfRows= "";
			ifstream input(imageName+".pgm",ios::in|ios::binary|ios::ate); //possibly open at the back to be able to set end of iterator

			if (!(input.is_open())){
				return false;
			}else{
				input.seekg (0, ios::beg); //get position to beginning of file

				string line="";

			while (line != "255") {
				getline(input >> std::ws,line);
				if ((line[0] == 'P' && line[1] == '5') || line[0] == '#'){	//for any line containing P5 or #comments

					// cout << "IGNORE LINE\n";
				}
				else if (line != "255"){	//for line containing nRows, nCols

					std::size_t pos = line.find(" ");
					numberOfColumns= line.substr (pos);
					numberOfRows= line.substr (0,pos);
					nCols = stoi(numberOfColumns);
					nRows = stoi(numberOfRows);

					// cout << nRows << ", " << nCols <<"\n";

					break;
				}
			}

			getline(input >> std::ws,line);

			this->sizeOfImage = nCols * nRows; 		// no header only rows and cols
			memblock = new char [sizeOfImage];

			input.read (memblock, sizeOfImage);
			width = nCols;
			height = nRows;
			reset(nCols, nRows);
			// cout << memblock[0];


			// data = unique_ptr <unsigned char[]>(new unsigned char[sizeOfImage]);
			// data = make_unique<unsigned char[]>(sizeOfImage);
			for (int i = 0; i<sizeOfImage; i++){
				data[i] = reinterpret_cast<unsigned char&>(memblock[i]);
			}

			// cout << "$$"<< data[51] <<"$$";
			input.close();


			// cout << ","<< width <<","<< height <<","<< "\n";

			delete[] memblock;
			return true;
			}
	}

	void Image::saveImage(string outputName){
			ofstream outputFile;

			outputFile.open(outputName + ".pgm", ios::out | ios::binary);
			outputFile << "P5\n";		//NB NB NB need these lines otherwise it isn't a PGM file
			outputFile << to_string(this->height) << " " << to_string(this->width) << "\n";
			outputFile << "255\n";

			for (int i = 0; i<this->sizeOfImage; i++){

					outputFile << this->data[i];
			}
			outputFile.close();
	}

	//iterator functions//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	it::iterator(unsigned char *p): ptr(p){}

	it::~iterator(){
		ptr = nullptr;
	}


	unsigned char& it::operator*(void){ //dereferencing
		return *ptr;
	}
	it& it::operator++(void){ //prefix increment
		ptr++;
		return *this;
	}
	it& it::operator--(void){ //prefix decrement
		ptr--;
		return *this;
	}

	bool it::operator==(const iterator & rhs){	//check if left ptr = right ptr

		return ptr == rhs.ptr;
	}
	bool it::operator!=(const iterator & rhs){
		return ptr != rhs.ptr;
	}

	/*	Image functions												*/
	it Image::begin(void){
		return iterator(data.get());
	}
	it Image::end(void){
		return iterator(data.get()+sizeOfImage);
	}

	Image & Image::operator+(Image & rhs){
//		cout << "lhs size: " << sizeOfImage <<endl;
//		cout << "rhs size: " << rhs.sizeOfImage <<endl;
			if (this->sizeOfImage == rhs.sizeOfImage){
				it beg = this->begin(), end = this->end();
				it inStart = rhs.begin(), inEnd = rhs.end();
				while ( beg != end) {
//					cout << "not at end";
					*beg = *inStart + *beg;

					if(*beg > 255 ){	//clamping data between range 0 and 255
						*beg = 255;
					}
					else if (*beg < 0 ){
						*beg = 0;
					}

					++beg; ++inStart;
				}
			}
			return *this;
	}
}
