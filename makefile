#! Para compilacion en linux
# CC = g++
# CFLAGS = -Wall
# OPENCV = `pkg-config opencv4 --cflags --libs`
# TARGET = main

# all: $(TARGET)

# $(TARGET): $(TARGET).cpp
# 	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(OPENCV)

# clean:
# 	rm -f $(TARGET)

#! Para compilacion en windows 
# @echo off
# set CC=g++
# set CFLAGS=-Wall
# set OPENCV=-lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs
# set TARGET=main.exe

# all: %TARGET%

# %TARGET%: %TARGET%.cpp
# 	%CC% %CFLAGS% -o %TARGET% %TARGET%.cpp %OPENCV%

# clean:
# 	del %TARGET%

