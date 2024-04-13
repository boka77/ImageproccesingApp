#include <iostream>
#include "Image_Class.h"

int main() {
    std::string photo1, photo2, mergedFileName;
    std::cout << "Enter the name of the first file: ";
    std::cin >> photo1;
    std::cout << "Enter the name of the second file: ";
    std::cin >> photo2;

    Image image1(photo1);
    Image image2(photo2);

    // Check which image has the larger dimensions
    Image* largerImage;
    Image* smallerImage;
    if (image1.width * image1.height > image2.width * image2.height) {
        largerImage = &image1;
        smallerImage = &image2;
    }
    else {
        largerImage = &image2;
        smallerImage = &image1;
    }

    // Crop the larger image to match the dimensions of the smaller one
    Image croppedImage(smallerImage->width, smallerImage->height);
    for (int i = 0; i < smallerImage->width; ++i) {
        for (int j = 0; j < smallerImage->height; ++j) {
            for (int k = 0; k < smallerImage->channels; ++k) {
                croppedImage(i, j, k) = (*largerImage)(i, j, k);
            }
        }
    }

    // Merge the cropped image with the smaller image
    Image mergedImage(smallerImage->width, smallerImage->height);
    for (int i = 0; i < smallerImage->width; ++i) {
        for (int j = 0; j < smallerImage->height; ++j) {
            for (int k = 0; k < smallerImage->channels; ++k) {
                // Average the pixel values from the two images
                mergedImage(i, j, k) = (croppedImage(i, j, k) + (*smallerImage)(i, j, k)) / 2;
            }
        }
    }

    std::cout << "Enter the name of the file to save the merged image and specify extension (.jpg, .bmp, .png, .tga): ";
    std::cin >> mergedFileName;
    mergedImage.saveImage(mergedFileName);

    std::cout << "Merged image saved as: " << mergedFileName << std::endl;

    return 0;
}
