all: *.cpp ; g++ *.cpp -o serial `pkg-config --cflags --libs opencv`

parallel: *.cu ; nvcc -I/usr/local/include -I/usr/local/include/opencv -L/usr/local/lib *.cu -o parallel -lopencv_core -lopencv_features2d -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_video
