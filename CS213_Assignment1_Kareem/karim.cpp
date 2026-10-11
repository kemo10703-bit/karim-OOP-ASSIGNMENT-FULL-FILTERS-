#include <iostream>
#include <algorithm>
#include "Image_class.h"

using namespace std;

Image DarkenAndLighten(Image &input, bool darken)
{
    Image output(input.width, input.height);

    for (int y = 0; y < input.height; y++)
    {
        for (int x = 0; x < input.width; x++)
        {
            unsigned char r = input(x, y, 0);
            unsigned char g = input(x, y, 1);
            unsigned char b = input(x, y, 2);

            unsigned char R_new;
            unsigned char G_new;
            unsigned char B_new;

            if (darken)
            {
                R_new = r * 0.5;
                G_new = g * 0.5;
                B_new = b * 0.5;
            }
            else
            {
                R_new = r * 1.5 > 255 ? 255 : r * 1.5;
                G_new = g * 1.5 > 255 ? 255 : g * 1.5;
                B_new = b * 1.5 > 255 ? 255 : b * 1.5;
            }

            output(x, y, 0) = R_new;
            output(x, y, 1) = G_new;
            output(x, y, 2) = B_new;
        }
    }

    return output;
}

void Crop(Image &work_on)
{
    int width = 600;
    int height = 600;

    if (work_on.width < width)
        width = work_on.width;

    if (work_on.height < height)
        height = work_on.height;

    int x = (work_on.width - width) / 2;
    int y = (work_on.height - height) / 2;

    Image newImage(width, height);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            for (int k = 0; k < work_on.channels; k++)
            {
                newImage(i, j, k) = work_on(x + i, y + j, k);
            }
        }
    }

    work_on = newImage;
}

void Purple(Image &work_on)
{
    for (int i = 0; i < work_on.width; i++)
    {
        for (int j = 0; j < work_on.height; j++)
        {
            unsigned char r = work_on(i, j, 0);
            unsigned char g = work_on(i, j, 1);
            unsigned char b = work_on(i, j, 2);

            work_on(i, j, 0) = min(255, (int)(r * 0.7 + 80));
            work_on(i, j, 1) = g * 0.5;
            work_on(i, j, 2) = min(255, (int)(b * 0.7 + 80));
        }
    }
}

Image Invert(Image &input)
{
    for (int y = 0; y < input.height; y++)
    {
        for (int x = 0; x < input.width; x++)
        {
            unsigned char R_new = 255 - input(x, y, 0);
            unsigned char G_new = 255 - input(x, y, 1);
            unsigned char B_new = 255 - input(x, y, 2);

            input(x, y, 0) = R_new;
            input(x, y, 1) = G_new;
            input(x, y, 2) = B_new;
        }
    }

    return input;
}

int main()
{
    string filename = "spider man 8k ultra, image or wallpaper.jpeg";

    Image img(filename);

    Image dark = DarkenAndLighten(img, true);
    dark.saveImage("spiderman_darken.jpeg");

    Image light = DarkenAndLighten(img, false);
    light.saveImage("spiderman_lighten.jpeg");

    Image cropped = img;
    Crop(cropped);
    cropped.saveImage("spiderman_crop.jpeg");

    Image purple = img;
    Purple(purple);
    purple.saveImage("spiderman_purple.jpeg");

    Image inverted = img;
    Invert(inverted);
    inverted.saveImage("spiderman_invert.jpeg");

    cout << "All filters applied successfully!" << endl;

    return 0;
}