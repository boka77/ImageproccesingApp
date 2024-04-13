#include <iostream>
#include "Image_Class.h"
#include <cstdlib>

using namespace std;

int main() {
    string filename;
    cout << "Please enter the image you want to crop: ";
    cin >> filename;

    Image image(filename);

    // Get input for the cropping region
    int x, y, width, height;
    cout << "Enter the coordinates of the top-left corner (x, y): ";
    cin >> x >> y;
    cout << "Enter the width and height of the new image: ";
    cin >> width >> height;

    // Perform cropping
    Image croppedImage(width, height);
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                croppedImage(i, j, k) = image(x + i, y + j, k);
            }
        }
    }


    cout << "Please enter the image name to store the new image\n";
    cout << "and specify the extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;
    croppedImage.saveImage(filename);
    system(filename.c_str());

    return 0;
}
