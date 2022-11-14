#include <ctime>
#include <iostream>
#include <opencv2/opencv.hpp>

#define ESC 27

using namespace std;
using namespace cv;

string xml_path = "/home/acer/NSU_Computer_And_Peripherals/lab5/config/haarcascade_frontalface_alt2.xml";
string window_name = "Web camera";
string trackbar_name = "Brightness";
Mat frame;

// detect and highlight faces
void DetectAndHighlightFaces(CascadeClassifier face_cascade);

// change brightness
void ChangeBrightness();

// print information about fps
void PrintFPS();

// print information about times
void PrintTimes();

// class for measuring time
class Clock
{
public:
    void Start()
    {
        clock_gettime(CLOCK_MONOTONIC_RAW,
                      &start_);
    }

    void Finish()
    {
        clock_gettime(CLOCK_MONOTONIC_RAW,
                      &finish_);

        interval_time_ = (double)finish_.tv_sec - (double)start_.tv_sec +
            1e-9 * ((double)finish_.tv_nsec - (double)start_.tv_nsec);
        total_time_ += interval_time_;
    }

    double GetIntervalTime() const
    {
        return interval_time_;
    }

    double GetTotalTime() const
    {
        return total_time_;
    }

private:
    timespec start_ = {
        0,
        0
    };
    timespec finish_ = {
        0,
        0
    };
    double interval_time_ = 0.0;
    double total_time_ = 0.0;
} input_time, process_time, output_time;

int main()
{
    // Open a capturing device
    VideoCapture video_capture(0);

    // Load face cascade
    CascadeClassifier face_cascade(xml_path);

    // create window
    namedWindow(window_name);

    // create trackbar
    createTrackbar(trackbar_name,
                   window_name,
                   nullptr,
                   200);
    setTrackbarPos(trackbar_name,
                   window_name,
                   100);

    Mat frame;
    long long start,
        interval,
        input_time = 0,
        process_time = 0,
        output_time = 0,
        frame_time;
    long long frame_count = 0;
    while (true)
    {
        start = getTickCount();
        // get frame
        video_capture.read(frame);
        // check that frame is empty and window is closed
        if (frame.empty()) break;
        ++frame_count;
        interval = getTickCount() - start;

        frame_time = interval;
        input_time += interval;

        start = getTickCount();
        // mirror the frame horizontally
        flip(frame,
             frame,
             1);

        // get brightness value from trackbar
        int brightness = getTrackbarPos(trackbar_name,
                                        window_name);
        // change frame brightness
        frame.convertTo(frame,
                        -1,
                        1,
                        double(brightness - 100) * 255 / 100);
        // detect faces in frame
        std::vector<Rect> faces;
        face_cascade.detectMultiScale(frame,
                                      faces);
        // draw ellipse around faces
        for (auto & face : faces)
        {
            Point center(int(face.x + face.width * 0.5),
                         int(face.y + face.height * 0.5));
            ellipse(frame,
                    center,
                    Size(int(face.width * 0.5), int(face.height * 0.5)),
                    0,
                    0,
                    360,
                    Scalar(255, 255, 255),
                    3);
        }
        interval = getTickCount() - start;

        frame_time += interval;
        process_time += interval;

        start = getTickCount();
        // display frame in window
        imshow(window_name,
               frame);
        // wait for pressed key ESC or closed window
        if (waitKey(1) == ESC) break;
        if (getWindowProperty(window_name,
                              WND_PROP_AUTOSIZE) == -1) break;
        interval = getTickCount() - start;

        frame_time += interval;
        output_time += interval;

        // print FPS
        cout << frame_count << ") FPS: " << 1.0 * getTickFrequency() / double(frame_time) << endl;
    }

    long long total_time = input_time + process_time + output_time;
    cout << "Average FPS: " << double(frame_count) * getTickFrequency() / double(total_time) << endl;
    cout << "Input time: " << double(input_time) / getTickFrequency()
         << " (" << 100.0 * double(input_time) / double(total_time) << "%)" << endl;
    cout << "Process time: " << double(process_time) / getTickFrequency()
         << " (" << 100.0 * double(process_time) / double(total_time) << "%)" << endl;
    cout << "Output time: " << double(output_time) / getTickFrequency()
         << " (" << 100.0 * double(output_time) / double(total_time) << "%)" << endl;

    return EXIT_SUCCESS;
}