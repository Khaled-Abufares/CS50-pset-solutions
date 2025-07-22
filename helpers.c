#include <stdio.h>
#include <math.h>
#include <stdlib.h>
typedef unsigned char BYTE;
typedef struct
{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

        int average = round ((red + green + blue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
           image[i][j].rgbtBlue = average;
       }
    }

}
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (sepiaRed > 255) sepiaRed = 255;
            if (sepiaGreen > 255) sepiaGreen = 255;
            if (sepiaBlue > 255) sepiaBlue = 255;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

void reflect (int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red_sum = 0;
            int green_sum = 0;
            int blue_sum = 0;
            int count = 0;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        red_sum += image[ni][nj].rgbtRed;
                        green_sum += image[ni][nj].rgbtGreen;
                        blue_sum += image[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }
            temp[i][j].rgbtRed = round(red_sum / (float)count);
            temp[i][j].rgbtGreen = round(green_sum / (float)count);
            temp[i][j].rgbtBlue = round(blue_sum / (float)count);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
     int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red_x = 0, red_y = 0;
            int green_x = 0, green_y = 0;
            int blue_x = 0, blue_y = 0;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        red_x += image[ni][nj].rgbtRed * Gx[di + 1][dj + 1];
                        red_y += image[ni][nj].rgbtRed * Gy[di + 1][dj + 1];
                        green_x += image[ni][nj].rgbtGreen * Gx[di + 1][dj + 1];
                        green_y += image[ni][nj].rgbtGreen * Gy[di + 1][dj + 1];
                        blue_x += image[ni][nj].rgbtBlue * Gx[di + 1][dj + 1];
                        blue_y += image[ni][nj].rgbtBlue * Gy[di + 1][dj + 1];
                    }
                }
            }
            int red = round(sqrt(red_x * red_x + red_y * red_y));
            int green = round(sqrt(green_x * green_x + green_y * green_y));
            int blue = round(sqrt(blue_x * blue_x + blue_y * blue_y));
            temp[i][j].rgbtRed = (red > 255) ? 255 : red;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            temp[i][j].rgbtBlue = (blue > 255) ? 255    : blue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}
