#include "PCN.h"

int main()
{
    PCN detector("model/PCN.caffemodel",
                 "model/PCN-1.prototxt", "model/PCN-2.prototxt", "model/PCN-3.prototxt");
    detector.SetMinFaceSize(45);
    detector.SetScoreThresh(0.37, 0.43, 0.95);
    detector.SetImagePyramidScaleFactor(1.414);
    detector.SetVideoSmooth(false);

    for (int i = 1; i <= 26; i++)
    {
        cv::Mat img =
            cv::imread("../imgs/" + std::to_string(i) + ".jpg");
        cv::TickMeter tm;
        tm.reset();
        tm.start();
        std::vector<Window> faces = detector.DetectFace(img);
        tm.stop();
        std::cout << "Image: " << i << std::endl;
        std::cout << "Time Cost: "<<
                  tm.getTimeMilli() << " ms" << std::endl;
        cv::Mat faceImg;
        for (int j = 0; j < faces.size(); j++)
        {
            cv::Mat tmpFaceImg = CropFace(img, faces[j], 200);
            faceImg.push_back(tmpFaceImg);
        }
        cv::imshow("Faces", faceImg);
        for (int j = 0; j < faces.size(); j++)
        {
            DrawFace(img, faces[j]);
        }
        cv::imshow("PCN", img);
        cv::waitKey();
    }

    cv::destroyAllWindows();

    return 0;
}
