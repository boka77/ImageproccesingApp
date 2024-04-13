#include <cstdlib>
#include <iostream>
using namespace std;
#include "Image_Class.h"

int main() {
    string filename;
    cout << "Please enter the colored image name to turn into a purple filter: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0 ; i < image.width  ; ++i) {
        for (int j = 0; j < image.height ; ++j) {
            unsigned int red = image(i, j, 0);   // Red channel value
            unsigned int green = image(i, j, 1); // Green channel value
            unsigned int blue = image(i, j, 2);  // Blue channel value

            // Calculate the new pixel values for the purple filter
            red = (red + blue) / 2;     // Red channel contributes to purple
            green = red / 2;            // Green channel also contributes to purple
            blue = (blue + red) / 2;   // Blue channel contributes to purple

            // Set the new pixel values
            image(i, j, 0) = red;
            image(i, j, 1) = green;
            image(i, j, 2) = blue;
        }
    }

    cout << "Please enter the image name to store the new image\n";
    cout << "and specify the extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);
    system(filename.c_str());

    return 0;
}
