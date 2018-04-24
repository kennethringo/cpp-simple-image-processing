/*
 * Image.h
 *
 *  Created on: 29 Apr 2018
 *      Author: Ringo
 */

#ifndef IMAGE_H_
#define IMAGE_H_
#include <memory>
#include <string>

namespace shmken002{
	class Image{
	private:
		int width, height;
		std::unique_ptr<unsigned char[]> data;
		int sizeOfImage;
//		size_t size;
	public:
		int nRows;
		int nCols;

		Image(int w,int h);
		~Image();
		int getWidth() const;
		int getHeight() const;
		void setWidth(int w);
		void setHeight(int h);
		void reset(int w, int h);
		bool loadImage(std::string imageName);
		void saveImage(std::string outputName);
	};
}




#endif /* IMAGE_H_ */
