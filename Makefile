CC=g++

imageops: Image.o driver.o 
	$(CC) -std=c++11 Image.o driver.o -o imageops

Image.o: Image.cpp Image.h
	$(CC) -std=c++11 Image.cpp Image.h -c -g

driver.o: driver.cpp
	$(CC) -std=c++11 driver.cpp -c -g


clean:
	rm -f imageops
	rm -f *.o
	

