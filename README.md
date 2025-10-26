# HelloCV
仓库
2025210498 AI+先进技术 赵奕博

```cpp
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgHSV, mask;
int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;

int main() {
    string path = "TrafficLight.mp4";
    VideoCapture cap(path);
    Mat img;
    int f = 1;
    while(true){
        cap.read(img);
        if(f){
            cout << img.rows << endl << img.cols << endl;
        }
        if(img.empty()){
            cout << "视频读取完毕" << endl;
            break;
        }
        else{
            imshow("视频播放", img);
            waitKey(20);
        }
        
        cvtColor(img, imgHSV, COLOR_BGR2HSV);
        namedWindow("Trackbars", (640, 200));
        createTrackbar("Hue Min", "Trackbars", &hmin, 179);
        createTrackbar("Hue Max", "Trackbars", &hmax, 179);
        createTrackbar("Sat Min", "Trackbars", &smin, 255);
        createTrackbar("Sat Max", "Trackbars", &smax, 255);
        createTrackbar("Val Min", "Trackbars", &vmin, 255);
        createTrackbar("Val Max", "Trackbars", &vmax, 255);

        while(true){
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);
        imshow("Mask", mask);
        waitKey(1);
        }
    }
    return 0;
}
```


