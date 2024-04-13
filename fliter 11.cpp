#include <iostream>
#include "Image_Class.h"
#include <cstdlib>

using namespace std;

int main() {
    string filename;
    cout << "Please enter the image you want to resize: ";
    cin >> filename;

    Image image(filename);

    // Get input for the new dimensions
    int newWidth, newHeight;
    cout << "Enter the new width of the image: ";
    cin >> newWidth;
    cout << "Enter the new height of the image: ";
    cin >> newHeight;

    // Calculate scaling ratios
    double widthRatio = (double)newWidth / image.width;
    double heightRatio = (double)newHeight / image.height;

    // Perform resizing with bi-linear interpolation
    Image resizedImage(newWidth, newHeight);
    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            double srcX = (double)i / widthRatio;
            double srcY = (double)j / heightRatio;

            int x1 = (int)srcX;
            int y1 = (int)srcY;
            int x2 = min(x1 + 1, image.width - 1);
            int y2 = min(y1 + 1, image.height - 1);

            double xWeight = srcX - x1;
            double yWeight = srcY - y1;

            for (int k = 0; k < image.channels; ++k) {
                double interpolatedValue = (1 - xWeight) * (1 - yWeight) * image(x1, y1, k) +
                                           xWeight * (1 - yWeight) * image(x2, y1, k) +
                                           (1 - xWeight) * yWeight * image(x1, y2, k) +
                                           xWeight * yWeight * image(x2, y2, k);

                resizedImage(i, j, k) = (unsigned int)interpolatedValue;
            }
        }
    }

    cout << "Please enter the image name to store the new image\n";
    cout << "and specify the extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;
    resizedImage.saveImage(filename);
    system(filename.c_str());

    return 0;
}
