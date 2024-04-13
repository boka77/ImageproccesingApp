#include <cstdlib>
#include <iostream>
#include "Image_Class.h"

using namespace std;

int main() {
    string filename;
    cout << "Please enter the colored image name to turn it into warm filter: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0 ; i < image.width ; ++i) {
        for (int j = 0; j < image.height; ++j) {
            int red = image(i, j, 0);
            int green = image(i, j, 1);
            int blue = image(i, j, 2);

            // Apply warm filter by increasing red and green channels more
            red += 30;
            green += 60;


            // Ensure values stay within [0, 255] range
            red = min(255, max(0, red));
            green = min(255, max(0, green));

            // Set the adjusted RGB values
            image(i, j, 0) = red;
            image(i, j, 1) = green;

            // Blue channel remains unchanged
        }
    }

    cout << "Please enter the image name to store the new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;

    image.saveImage(filename);
    system(filename.c_str());

    return 0;
}
