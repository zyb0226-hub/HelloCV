# HelloCV
仓库
2025210498 AI+先进技术 赵奕博

先将红绿灯的颜色的HSV值提取出来，便于下面图形提取时直接确定颜色范围

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
bool paused = false;

int main() {
    string path = "TrafficLight.mp4";
    VideoCapture cap(path);
    Mat img, currentFrame;
    
    // 创建滑动条窗口（只需要一次）
    namedWindow("Trackbars", WINDOW_NORMAL);
    resizeWindow("Trackbars", 640, 200);
    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);
    
    cout << "空格键: 暂停/继续" << endl;
    cout << "ESC键: 退出" << endl;
    
    while(true){
        if (!paused) {
            if (!cap.read(img)) {
                cout << "视频读取完毕" << endl;
                break;
            }
            currentFrame = img.clone(); // 保存当前帧
        }
        
        // 显示原始视频（当前帧或暂停帧）
        imshow("视频播放", currentFrame);
        
        // 处理当前帧
        cvtColor(currentFrame, imgHSV, COLOR_BGR2HSV);
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);
        
        // 显示掩膜
        imshow("Mask", mask);
        
        // 显示当前HSV范围
        if (paused) {
            putText(currentFrame, "PAUSED - Adjust HSV Trackbars", Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 255), 2);
            imshow("视频播放", currentFrame);
        }
        
        char key = waitKey(30);
        if(key == 27) break; // ESC退出
        if(key == ' ') {
            paused = !paused; // 空格键切换暂停/继续
            cout << (paused ? "已暂停 - 调整HSV滑动条" : "继续播放") << endl;
        }
    }
    
    return 0;
}
```
最终结果



红：H[173,179],S[128,255],V[61,255]

绿：H[82,90],S[128,255],V[133,207]

```
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//已确定好颜色HSV范围
Scalar redlower(173,128,61);
Scalar redupper(179,255,255);
Scalar greenlower(82,128,133);
Scalar greenupper(90,255,207);

void detect(Mat &frame){
    Mat imgHSV, redMask, greenMask;
    cvtColor(frame, imgHSV, COLOR_BGR2HSV);

    //直接生成处理好的掩膜
    inRange(imgHSV, redlower, redupper, redMask);
    inRange(imgHSV, greenlower, greenupper, greenMask);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

    morphologyEx(redMask, redMask, MORPH_CLOSE, kernel);
    morphologyEx(greenMask, greenMask, MORPH_CLOSE, kernel);

    vector<vector<Point>> contours;
    string lightColor = "?";
    Rect largestRect;

    findContours(redMask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    for(auto &contour : contours){
        if(contourArea(contour) > 10000){
            Rect rect = boundingRect(contour);
            if(rect.area() > largestRect.area()){
                largestRect = rect;
                lightColor = "red";
            }
        }
    }

    //这里要取所有色块中最大的，否则数字也可能被框出来
    findContours(greenMask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    for(auto &contour : contours){
        if(contourArea(contour) > 10000){
            Rect rect = boundingRect(contour);
            if(rect.area() > largestRect.area()){
                largestRect = rect;
                lightColor = "green";
            }
        }
    }

    //用和灯相同颜色的框（doge）
    if(lightColor != "?"){
        Scalar color;
        if(lightColor == "red"){
            color = Scalar(0,0,255);
        }
        else{
            color = Scalar(0,255,0);
        }
        rectangle(frame, largestRect, color, 2);
        putText(frame, lightColor, Point(120,160), FONT_HERSHEY_SIMPLEX, 2, Scalar(255,255,255), 4);
    }
}

int main(){
    string path = "TrafficLight.mp4";
    VideoCapture cap(path);
    VideoWriter output("result.avi", VideoWriter::fourcc('X','2','6','4'), 30, Size(1920, 1080));

    Mat frame;
    while(cap.read(frame)){
        detect(frame);
        output.write(frame);
        imshow("Traffic Light Detector",frame);
        if(waitKey(1) == 27) break;
    }
    cap.release();
    output.release();
    return 0;
}
//不知道为什么，视频只显示了4秒，DS说可能是编码器兼容性的原因，有点无奈。
```
