#include "BitStream.cpp"
#include <iostream>
#include "Golomb.cpp"
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/opencv.hpp>
using namespace std;
using namespace cv;


class Preditor{

    public:
    int count=0;
    void predict(Mat frame,int m){
        cout<<count++<<endl;
        BitStream bswrite_error("../bitFile1.bin","w");
        GolombEncoder g(&bswrite_error,m);
        BitStream bswrite_img("../preditor1.bin","w");
        vector<Mat> rgbChannels(3); //Mat rgbchannel[3];
	    split(frame, rgbChannels);
        int a,b,c,error,pred_value;
        for (int ch=0;ch<3;ch++){
            frame=rgbChannels[ch];
            Mat tmp = Mat::zeros(Size(frame.cols, frame.rows), CV_8UC1);
            for (int rows = 0; rows < frame.rows; rows++) {
                for (int cols = 0; cols <= frame.cols; cols++) {
                    if (rows==0 && cols==0){
                        a=0;
                        b=0;
                        c=0;
                    }
                    else if(rows==0 && cols>0){
                        a=0;
                        b=int(frame.at<u_char>(rows,cols-1));
                        c=0;
                    }
                    else if(cols==0 && rows>0){
                        a=int(frame.at<u_char>(rows-1,cols));
                        b=0;
                        c=0;
                    }
                    else{
                        a=int(frame.at<u_char>(rows,cols-1));
                        b=int(frame.at<u_char>(rows-1,cols));
                        c=int(frame.at<u_char>(rows-1,cols-1));
                    }
                    if(c<=min(a,b)){
                        pred_value=max(a,b);
                    }
                    else if(c>=max(a,b)){
                        pred_value=min(a,b);
                    }
                    else{
                        pred_value=a+b-c;
                    }
                    error=int(frame.at<u_char>(rows,cols))-pred_value;
                    tmp.at<u_char>(rows,cols)=u_char(pred_value);
                    g.encode(error);
                    bswrite_img.writeNBits(pred_value,8);

                    
                }
            }
        }
        bswrite_img.close();
        bswrite_error.close();
    }




    Mat reconstruct(int rows, int cols,string errorFile,string img_file,int m){
        BitStream bsread_error(errorFile,"r");
        GolombDecoder g(&bsread_error,m);
        BitStream bsread_img(img_file,"r");
        vector<Mat> channels;
        int error, pix;
        for (int ch=0;ch<3;ch++){
            Mat tmp = Mat::zeros(rows,cols, CV_8UC1);
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col <= cols; col++) {
                    error=g.decode();
                    pix=bsread_img.readNBits(8);
                    pix+=error;
                    tmp.at<u_char>(row,col)=u_char(pix);
                }
            }
            channels.push_back(tmp);
        }
        bsread_error.close();
        bsread_img.close();
        Mat res;
        merge(channels,res);
        return res;
    }
};