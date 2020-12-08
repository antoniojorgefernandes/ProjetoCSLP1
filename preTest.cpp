#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "Preditor.cpp"
#include <iostream>

int main(int argc, char* argv[]){
    Preditor preditor;
    VideoCapture cap("../../ducks.y4m");
    if(!cap.isOpened()){
        cout << "Error opening the video" <<endl;
    return 0;
    }
    int rows=0;
    int cols=0;
    while(1){
        Mat frame;
        cap >> frame;
        if(frame.empty()){
            break;
        }
        preditor.predict(frame,4);
    }
    vector<Mat> channels;
    int i=259;
    while(i--){
        Mat rec =preditor.reconstruct(288,352,"../bitFile1.bin","../preditor1.bin",4);
        channels.push_back(rec);
    }
    for(Mat img : channels){
        imshow("img",img);
        char c =(char)waitKey(15);
        if(c==27){
            break;
        }
    }

    cap.release();
}