

#PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:${PKG_CONFIG_PATH}
#export PKG_CONFIG_PATH

all:
	g++ -o opencv main.cpp myImage.cpp handGesture.cpp roi.cpp rec_gesture.cpp speak.cpp `pkg-config --cflags --libs opencv` 

