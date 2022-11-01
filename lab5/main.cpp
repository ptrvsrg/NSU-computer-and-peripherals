#include <ctime>
#include <iostream>
#include <opencv2/opencv.hpp>

#define ESC 27

using namespace std;
using namespace cv;

string xml_path = "/home/acer/NSU_Computer_And_Peripherals/lab5/config/haarcascade_frontalface_alt2.xml";
string window_name = "Face detecting";
string trackbar_name = "Brightness";
Mat frame;

void DetectAndHighlightFaces(CascadeClassifier face_cascade);
void ChangeBrightness();
void PrintInfo(int fps_counter);

class Clock
{
public:
    void Start()
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start_);
    }

    void Finish()
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &finish_);
        total_time_ = (double)finish_.tv_sec - (double)start_.tv_sec +
            1e-9 * ((double)finish_.tv_nsec - (double)start_.tv_nsec);
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
    double total_time_ = 0;
} input_time, process_time, output_time, program_time;

int main()
{
    VideoCapture video_capture(0); // Open a capturing device
    if (!video_capture.isOpened())
    {
        cerr << "VideoCapture error" << endl;
        return EXIT_FAILURE;
    }

    CascadeClassifier face_cascade(xml_path); // Load face cascade
    if (face_cascade.empty())
    {
        cerr << "CascadeClassifier error" << endl;
        return EXIT_FAILURE;
    }

    namedWindow(window_name);
    createTrackbar(trackbar_name,
                   window_name,
                   nullptr,
                   200);
    setTrackbarPos(trackbar_name,
                   window_name,
                   100);

    int fps_counter = 0;
    program_time.Start();
    while (true)
    {
        ++fps_counter;

        input_time.Start();
        video_capture >> frame; // Get video frame
        if (frame.empty()) break;
        input_time.Finish();

        process_time.Start();
        flip(frame,
             frame,
             1);    // Flip horizontally

        ChangeBrightness(); // Change brightness

        DetectAndHighlightFaces(face_cascade); // Face detecting
        process_time.Finish();

        output_time.Start();
        imshow(window_name,
               frame); // Show window
        output_time.Finish();

        if (waitKey(1) == ESC) break;
    }
    program_time.Finish();

    PrintInfo(fps_counter);

    return 0;
}

void DetectAndHighlightFaces(CascadeClassifier face_cascade)
{
    // Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(frame,
                                  faces);


    // Draw circles on the detected faces
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
                Scalar(255, 255, 255));
    }
}

void ChangeBrightness()
{
    int brightness = getTrackbarPos(trackbar_name,
                                   window_name);
    frame.convertTo(frame,
                    -1,
                    1,
                    (brightness - 100) * 255 / 100);
}

void PrintInfo(int fps_counter)
{
    double time = input_time.GetTotalTime() + process_time.GetTotalTime() + output_time.GetTotalTime();
    cout << "FPS: " << fps_counter / program_time.GetTotalTime() << endl;
    cout << "Input time: "      << 100.0 * input_time.GetTotalTime() / time << "%" << endl;
    cout << "Process time: "    << 100.0 * process_time.GetTotalTime() / time << "%" << endl;
    cout << "Output time: "     << 100.0 * output_time.GetTotalTime() / time << "%" << endl;
}