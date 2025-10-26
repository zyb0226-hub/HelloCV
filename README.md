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

红：H[173,179],S[128,255],V[61,255]

绿：H[82,90],S[128,255],V[133,207]
