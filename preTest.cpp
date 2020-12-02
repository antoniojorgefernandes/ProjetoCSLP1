#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "Preditor.cpp"
#include <iostream>

int main(int argc, char* argv[]){
    vector<Mat> vid;
    Preditor preditor;
    VideoCapture cap("../../ducks.y4m");
    if(!cap.isOpened()){
        cout << "Error opening the video" <<endl;
    return 0;
    }
    while(1){
        Mat frame;
        cap >> frame;
        if(frame.empty()){
            break;
        }
        Mat coded=preditor.predict(frame);
        Mat fr=preditor.reconstruct(coded);
        vid.push_back(fr);
    }
    for (Mat img :vid){
        imshow("frame",img);
        char c =(char)waitKey(15);
    }
    cap.release();
}