#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float greysc;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width;  j++)
        {

            //Let's find out the arithmetic mean of 3 color components
            greysc = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            greysc = round(greysc);

            //Set Values to each pixel of the image
            image[i][j].rgbtBlue = greysc;
            image[i][j].rgbtGreen = greysc;
            image[i][j].rgbtRed = greysc;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiared;
    float sepiagreen;
    float sepiablue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width;  j++)
        {

            // Calculating new color values using the sepia algorithm
            sepiared = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiagreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiablue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiared > 255)
            {
                sepiared = 255;
            }
            if (sepiagreen > 255)
            {
                sepiagreen = 255;
            }
            if (sepiablue > 255)
            {
                sepiablue = 255;
            }

            if (sepiared < 0)
            {
                sepiared = 0;
            }
            if (sepiagreen < 0)
            {
                sepiagreen = 0;
            }
            if (sepiablue < 0)
            {
                sepiablue = 0;
            }

            // Set modified pixels to image
            image[i][j].rgbtBlue = sepiablue;
            image[i][j].rgbtGreen = sepiagreen;
            image[i][j].rgbtRed = sepiared;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    RGBTRIPLE temp2;
    int tmpwidth;

    // Go through each line of the image
    for (int i = 0; i < height; i++)
    {

        // Swapping pixels from the beginning and from the end
        for (int j = 0; j < (width / 2);  j++)
        {
            temp = image[i][(width - 1) - j];
            temp2 = image[i][j];
            image[i][j] =  temp;
            image[i][(width - 1) - j] = temp2;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float   blur_red;
    float   blur_green;
    float   blur_blue;
    int     items;

    RGBTRIPLE image_tmp[height][width];

    // Go through each pixel of the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width;  j++)
        {
            blur_red = 0;
            blur_green = 0;
            blur_blue = 0;
            items = 0;

            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    //add up the color values of the surrounding pixels only. The loop skips in extreme positions (corners and edges). )
                    if ((i + h > -1) && (i + h < height) && (j + w > -1) && (j + w < width))
                    {
                        blur_blue += image[i + h][j + w].rgbtBlue;
                        blur_green += image[i + h][j + w].rgbtGreen;
                        blur_red += image[i + h][j + w].rgbtRed;
                        items++;
                    }
                }
            }
            // Divide the sum by the number of pixels
            blur_blue = blur_blue / items;
            blur_green = blur_green / items;
            blur_red = blur_red / items;

            //Assign values to each pixel of the temporary image
            image_tmp[i][j].rgbtBlue = round(blur_blue);
            image_tmp[i][j].rgbtGreen = round(blur_green);
            image_tmp[i][j].rgbtRed = round(blur_red);
        }
    }

// Copy pixels from tempriary image to target image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_tmp[i][j];
        }
    }

    return;
}

