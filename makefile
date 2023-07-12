# !For linux, tested in Debian based distros
# CC=g++
# CFLAGS=-I. -std=c++14
# LIBS=-lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui

# all: main

# main: main.o imageloading.o
# 	$(CC) -o main main.o imageloading.o $(CFLAGS) $(LIBS)

# main.o: main.cpp imageloading.h
# 	$(CC) -c main.cpp $(CFLAGS)

# imageloading.o: imageloading.cpp imageloading.h
# 	$(CC) -c imageloading.cpp $(CFLAGS)

# .PHONY: clean
# clean:
# 	rm -f *.o main

# !For Windows

# CC=g++
# CFLAGS=-I. -std=c++14 
# OPENCV_PATH = C:/opencv #!change this to your opencv path
# LIBS=-L$(OPENCV_PATH)/build/x64/vc15/lib -lopencv_core430 -lopencv_imgcodecs430 -lopencv_imgproc430 -lopencv_highgui430

# # Default target
# all: main

# main: main.o imageloading.o
# 	$(CC) -o main main.o imageloading.o $(CFLAGS) $(LIBS)

# main.o: main.cpp imageloading.h
# 	$(CC) -c main.cpp $(CFLAGS)

# imageloading.o: imageloading.cpp imageloading.h
# 	$(CC) -c imageloading.cpp $(CFLAGS)

# .PHONY: clean
# clean:
# 	del *.o main.exe
