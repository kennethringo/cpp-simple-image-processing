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
		friend class iterator;
	private:
		int width, height;
		std::unique_ptr<unsigned char[]> data;

//		size_t size;
	public:

		int sizeOfImage;
		Image(int w,int h);
		~Image();
		int getWidth() const;
		int getHeight() const;
		void setWidth(int w);
		void setHeight(int h);
		void reset(int w, int h);
		bool loadImage(std::string imageName);
		void saveImage(std::string outputName);

		Image & operator+(Image& rhs);



//		Image & operator+(Image & rhs);
		class iterator

		{
			friend class Image;

			private:
				unsigned char *ptr;
				// construct only via Image class (begin/end)


			public://copy construct is public

				iterator(unsigned char *p);
				~iterator();
				// define overloaded ops: *, ++, --, =

				iterator& operator=(const iterator & rhs);


				unsigned char & operator*(void);
				iterator& operator++(void);
				iterator& operator--(void);
				bool operator==(const iterator & rhs);
				bool operator!=(const iterator & rhs);

				// other methods for iterator
		};
		iterator begin(void);
		iterator end(void);
	};
}




#endif /* IMAGE_H_ */
