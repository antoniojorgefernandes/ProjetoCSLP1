#include "BitStreamW.cpp"
#include "BitStreamR.cpp"
#include "GolombEncode.cpp"
#include "GolombDecode.cpp"
#include <boost/dynamic_bitset.hpp> 
#include <math.h>
#include <stdint.h>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace boost;
using namespace cv;


class Preditor{

    public:
    GolombEncode ge;
    BitStreamW bsw;
    GolombDecode gd;
    BitStreamR bsr;
    Mat predict(Mat frame){
        vector<Mat> rgbChannels(3); //Mat rgbchannel[3];
	    split(frame, rgbChannels);
        vector<Mat> channels;
        int framePixel, tmpPixel,error;
        Mat res;
        dynamic_bitset<> code;
        int m=2;
        for (int ch=0;ch<3;ch++){
            frame=rgbChannels[ch];
            Mat tmp = Mat::zeros(Size(frame.cols, frame.rows), CV_8UC1);
            for (int rows = 0; rows < frame.rows; rows++) {
                for (int cols = 1; cols <= frame.cols; cols++) {
                    framePixel = frame.at<u_char>(rows, cols-1);
                    error=framePixel-int(tmp.at<u_char>(rows, cols-1));
                    tmp.at<u_char>(rows,cols)=frame.at<u_char>(rows, cols-1);
                    code=ge.encode(error,2);
                    bsw.writeNBits(code,code.size());
                    
                }
            }
            channels.push_back(tmp);
        }
        merge(channels,res);
        bsw.close();
        return res;
    }




    Mat reconstruct(Mat frame){
        vector<Mat> rgbChannels(3); //Mat rgbchannel[3];
	    split(frame, rgbChannels);
        vector<Mat> channels;
        int error, aux;
        Mat tmp,res;
        dynamic_bitset<> code;
        int m=2;
        for (int ch=0;ch<3;ch++){
            frame=rgbChannels[ch];
            Mat tmp = Mat::zeros(Size(frame.cols, frame.rows), CV_8UC1);
            for (int rows = 0; rows < frame.rows; rows++) {
                for (int cols = 0; cols <= frame.cols; cols++) {
                    code.clear();
                    code.push_back(bsr.readOneBit());
                    aux=bsr.readOneBit();
                    
                    while(1){
                        code.push_back(aux);
                        aux=bsr.readOneBit();
                        if(aux==0){
                            break;
                        }
                    }
                    dynamic_bitset<>resto=bsr.readNBits(log2(m));
                    for (int i=0; i<resto.size();i++){
                        code.push_back(resto[i]);

                    }

                    error=gd.decode(code,m);
                    aux=int(frame.at<u_char>(rows, cols))+error;
                    tmp.at<u_char>(rows,cols)=u_char(aux);
                }
            }
            channels.push_back(tmp);
        }
        bsr.close();
        merge(channels,res);
        return res;
    }
};