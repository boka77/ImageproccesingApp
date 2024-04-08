/*
File:CS112_A3_Part1_S 20_S 20_S 19_20230332_20230234_20230163
Purpose: Image filtering 
Author:Mohamed Hussien Mohamed Ali S 20  
       Zyad Wael El-Baz S 20 
       Ezz El-Deen Amr Abd El-Monem S 20  
E-Mails: mohamedboka893@gmail.com
         zodawael54@gmail.com
         azzkandeel@gmail.com
IDs:20230332 filter (5)
    20230163 filter (4)
    20230234 fliter (1,2,3,6)
*/
#include <iostream>
#include "Image_Class.h"
using namespace std;

int main() {
    int choice;

    cout << "1. Grey\n2. Black and White\n3. Invert\n4. Merge\n5. Flip Image\n6.cloackwise rotation\n17. infrared photography filte\n8. crop\n13. warm filter\n16. purple filter";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1: {
        string photo;
        cout << "Enter the name of the file: ";
        cin >> photo;
        Image image(photo);

        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                unsigned int avg = 0;
                for (int k = 0; k < image.channels; ++k) {
                    avg += image(i, j, k);
                }
                avg /= image.channels;
                for (int k = 0; k < image.channels; ++k) {
                    image(i, j, k) = avg;
                }
            }
        }

        string newPhoto;
        cout << "Enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
        cin >> newPhoto;
        image.saveImage(newPhoto);
        break;
    }
    case 2: {
        string photo;
        cout << "Enter the name of the file: ";
        cin >> photo;
        Image image(photo);
        const int blackAndWhiteThreshold = 128;
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                unsigned int avg = 0;
                for (int k = 0; k < image.channels; ++k) {
                    avg += image(i, j, k);
                }
                avg /= image.channels;

                if (avg >= blackAndWhiteThreshold) {
                    for (int k = 0; k < image.channels; ++k) {
                        image(i, j, k) = 255;
                    }
                }
                else {
                    for (int k = 0; k < image.channels; ++k) {
                        image(i, j, k) = 0;
                    }
                }
            }
        }

        string newPhoto;
        cout << "Enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
        cin >> newPhoto;
        image.saveImage(newPhoto);
        break;
    }
    case 3: {
        string photo;
        cout << "Enter the name of the file: ";
        cin >> photo;
        Image image(photo);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    // Invert the pixel intensity
                    image(i, j, k) = 255 - image(i, j, k);
                }
            }
        }

        string newPhoto;
        cout << "Enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
        cin >> newPhoto;
        image.saveImage(newPhoto);
        break;
    }
    case 4: {
#

        
            string photo1, photo2, mergedFileName;
            cout << "Enter the name of the first file: ";
            cin >> photo1;
            cout << "Enter the name of the second file: ";
            cin >> photo2;

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

            cout << "Enter the name of the file to save the merged image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> mergedFileName;
            mergedImage.saveImage(mergedFileName);

            cout << "Merged image saved as: " << mergedFileName << endl;

            return 0;
        }

    case 5: {
        string photo;
        cout << "Enter the name of the file: ";
        cin >> photo;
        Image image(photo);

        cout << "Choose flip direction:\n";
        cout << "1. Horizontal Flip\n";
        cout << "2. Vertical Flip\n";
        int flipChoice;
        cin >> flipChoice;

        if (flipChoice == 1) {
            for (int i = 0; i < image.width / 2; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        swap(image(i, j, k), image(image.width - 1 - i, j, k));
                    }
                }
            }
        }
        else if (flipChoice == 2) {
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height / 2; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        swap(image(i, j, k), image(i, image.height - 1 - j, k));
                    }
                }
            }
        }
        else {
            cout << "Invalid choice!" << endl;
            break;
        }

        string newPhoto;
        cout << "Enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
        cin >> newPhoto;
        image.saveImage(newPhoto);
        break;
    }
    case 6: {
    string photo;
    cout << "Enter the name of the file: ";
    cin >> photo;
    Image image(photo);
    int degree;
    cout << "Choose the degree you like (90, 180, or 270): ";
    cin >> degree;

    if (degree == 90 || degree == 270) {
        // Transpose the image
        Image transposedImage(image.height, image.width);
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    transposedImage(j, i, k) = image(i, j, k);
                }
            }
        }

        // Flip the transposed image horizontally to rotate it clockwise by 90 or 270 degrees
        if (degree == 90) {
            for (int i = 0; i < transposedImage.width / 2; ++i) {
                for (int j = 0; j < transposedImage.height; ++j) {
                    for (int k = 0; k < transposedImage.channels; ++k) {
                        swap(transposedImage(i, j, k), transposedImage(transposedImage.width - 1 - i, j, k));
                    }
                }
            }
        } else if(degree == 270) { 
            for (int i = 0; i < transposedImage.width; ++i) {
                for (int j = 0; j < transposedImage.height / 2; ++j) {
                    for (int k = 0; k < transposedImage.channels; ++k) {
                        swap(transposedImage(i, j, k), transposedImage(i, transposedImage.height - 1 - j, k));
                    }
                }
            }
        }

        string newPhoto;
        cout << "Enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
        cin >> newPhoto;
        transposedImage.saveImage(newPhoto);
    } else if (degree == 180) {
        // Flip the image horizontally
        for (int i = 0; i < image.width / 2; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    swap(image(i, j, k), image(image.width - 1 - i, j, k));
                }
            }
        }

        // Flip the image vertically
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height / 2; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    swap(image(i, j, k), image(i, image.height - 1 - j, k));
                }
            }
        }

        string newPhoto;
        cout << "Enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
        cin >> newPhoto;
        image.saveImage(newPhoto);
    } else {
        cout << "Invalid choice!" << endl;
    }
    break;
}
 case 17: {
        string photo;
        cout << "Enter the name of the file: ";
        cin >> photo;
        Image image(photo);

        // Apply the infrared photography filter
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                // Swap the red and blue color channels
                unsigned char temp = image(i, j, 0); // Save red channel value
                image(i, j, 0) = image(i, j, 2);     // Set red channel to blue channel value
                image(i, j, 2) = temp;               // Set blue channel to saved red channel value
            }
        }

        // Save the filtered image
        string newPhoto;
        cout << "Enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
        cin >> newPhoto;
        image.saveImage(newPhoto);

        cout << "Infrared filter applied successfully and saved as: " << newPhoto << endl;

        break;
    }
 case 8 : {
        string filename;
    cout << "Please enter the image name u want to crop: ";
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
 }
 case 16: {
    string filename;
    cout << "Please enter the colored image name to turn into a purple filter: ";
    cin >> filename;

    Image image(filename);

    const float brightnessFactor = 0.9f; // Adjust brightness factor as needed

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int red = image(i, j, 0);   // Red channel value
            unsigned int green = image(i, j, 1); // Green channel value
            unsigned int blue = image(i, j, 2);  // Blue channel value

            // Decrease brightness of all channels
            red = static_cast<unsigned int>(red * brightnessFactor);
            green = static_cast<unsigned int>(green * brightnessFactor);
            blue = static_cast<unsigned int>(blue * brightnessFactor);

            // Adjust pixels based on overall brightness to preserve yellow tones
            unsigned int avg = (red + green + blue) / 3;
            if (avg < 200) {
                red = (10 * red + blue) / 11;         // Red channel contributes more to purple
                green = (green + 2 * blue) / 3;       // Green channel contributes to purple
                blue = (red + green + 2 * blue) / 4;  // Blue channel contributes to purple
            }

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
    break;
}
 
 case 13:  {

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

 }
    default:
        cout << "Invalid choice!" << endl;
        return 1;
    }

    return 0;
}


