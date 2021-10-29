#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Calculate shade
            int average = round(((float)image[i][j].rgbtRed + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtBlue) / 3);

            //Assign new valor to pixel
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Calculate sepia based on formula
            int sepiaRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            int sepiaGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            int sepiaBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));

            //Handle limit
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            //Assign new valor to pixel
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            //Temporary hold value
            RGBTRIPLE temp  = image[i][j];

            //Switch values
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Make copy of image
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            RGBTRIPLE a = temp[m - 1][n - 1];
            RGBTRIPLE b = temp[m - 1][n];
            RGBTRIPLE c = temp[m - 1][n + 1];
            RGBTRIPLE d = temp[m][n - 1];
            RGBTRIPLE e = temp[m][n];
            RGBTRIPLE f = temp[m][n + 1];
            RGBTRIPLE g = temp[m + 1][n - 1];
            RGBTRIPLE h = temp[m + 1][n];
            RGBTRIPLE i = temp[m + 1][n + 1];
            
            //Handle top left corner
            if ((m == 0) && (n == 0))
            {
                image[m][n].rgbtRed = round(((float)e.rgbtRed + f.rgbtRed + h.rgbtRed + i.rgbtRed) / 4);
                image[m][n].rgbtBlue = round(((float)e.rgbtBlue + f.rgbtBlue + h.rgbtBlue + i.rgbtBlue) / 4);
                image[m][n].rgbtGreen = round(((float)e.rgbtGreen + f.rgbtGreen + h.rgbtGreen + i.rgbtGreen) / 4);
            }
            //Handle top right corner
            else if ((m == 0) && (n == width - 1))
            {
                image[m][n].rgbtRed = round(((float)d.rgbtRed + e.rgbtRed + g.rgbtRed + h.rgbtRed) / 4);
                image[m][n].rgbtBlue = round(((float)d.rgbtBlue + e.rgbtBlue + g.rgbtBlue + h.rgbtBlue) / 4);
                image[m][n].rgbtGreen = round(((float)d.rgbtGreen + e.rgbtGreen + g.rgbtGreen + h.rgbtGreen) / 4);
            }
            //Handle bottom left corner
            else if ((m == height - 1) && (n == 0))
            {
                image[m][n].rgbtRed = round(((float)b.rgbtRed + c.rgbtRed + e.rgbtRed + f.rgbtRed) / 4);
                image[m][n].rgbtBlue = round(((float)b.rgbtBlue + c.rgbtBlue + e.rgbtBlue + f.rgbtBlue) / 4);
                image[m][n].rgbtGreen = round(((float)b.rgbtGreen + c.rgbtGreen + e.rgbtGreen + f.rgbtGreen) / 4);
            }
            //Handle bottom right corner
            else if ((m == height - 1) && (n == width - 1))
            {
                image[m][n].rgbtRed = round(((float)a.rgbtRed + b.rgbtRed + d.rgbtRed + e.rgbtRed) / 4);
                image[m][n].rgbtBlue = round(((float)a.rgbtBlue + b.rgbtBlue + d.rgbtBlue + e.rgbtBlue) / 4);
                image[m][n].rgbtGreen = round(((float)a.rgbtGreen + b.rgbtGreen + d.rgbtGreen + e.rgbtGreen) / 4);
            }
            //Handle first line
            else if (m == 0)
            {
                image[m][n].rgbtRed = round(((float)d.rgbtRed + e.rgbtRed + f.rgbtRed + g.rgbtRed + h.rgbtRed + i.rgbtRed) / 6);
                image[m][n].rgbtBlue = round(((float)d.rgbtBlue + e.rgbtBlue + f.rgbtBlue + g.rgbtBlue + h.rgbtBlue + i.rgbtBlue) / 6);
                image[m][n].rgbtGreen = round(((float)d.rgbtGreen + e.rgbtGreen + f.rgbtGreen + g.rgbtGreen + h.rgbtGreen + i.rgbtGreen) / 6);
            }
            //Handle last line
            else if (m == height - 1)
            {
                image[m][n].rgbtRed = round(((float)a.rgbtRed + b.rgbtRed + c.rgbtRed + d.rgbtRed + e.rgbtRed + f.rgbtRed) / 6);
                image[m][n].rgbtBlue = round(((float)a.rgbtBlue + b.rgbtBlue + c.rgbtBlue + d.rgbtBlue + e.rgbtBlue + f.rgbtBlue) / 6);
                image[m][n].rgbtGreen = round(((float)a.rgbtGreen + b.rgbtGreen + c.rgbtGreen + d.rgbtGreen + e.rgbtGreen + f.rgbtGreen) / 6);
            }
            //Handle first column
            else if (n == 0)
            {
                image[m][n].rgbtRed = round(((float)b.rgbtRed + c.rgbtRed + e.rgbtRed + f.rgbtRed + h.rgbtRed + i.rgbtRed) / 6);
                image[m][n].rgbtBlue = round(((float)b.rgbtBlue + c.rgbtBlue + e.rgbtBlue + f.rgbtBlue + h.rgbtBlue + i.rgbtBlue) / 6);
                image[m][n].rgbtGreen = round(((float)b.rgbtGreen + c.rgbtGreen + e.rgbtGreen + f.rgbtGreen + h.rgbtGreen + i.rgbtGreen) / 6);
            }
            //Handle last column
            else if (n == width - 1)
            {
                image[m][n].rgbtRed = round(((float)a.rgbtRed + b.rgbtRed + d.rgbtRed + e.rgbtRed + g.rgbtRed + h.rgbtRed) / 6);
                image[m][n].rgbtBlue = round(((float)a.rgbtBlue + b.rgbtBlue + d.rgbtBlue + e.rgbtBlue + g.rgbtBlue + h.rgbtBlue) / 6);
                image[m][n].rgbtGreen = round(((float)a.rgbtGreen + b.rgbtGreen + d.rgbtGreen + e.rgbtGreen + g.rgbtGreen + h.rgbtGreen) / 6);
            }
            //Handle middle pixels
            else
            {
                image[m][n].rgbtRed = round(((float)a.rgbtRed + b.rgbtRed + c.rgbtRed + d.rgbtRed + e.rgbtRed + f.rgbtRed + g.rgbtRed +
                                             h.rgbtRed + i.rgbtRed) / 9);
                image[m][n].rgbtBlue = round(((float)a.rgbtBlue + b.rgbtBlue + c.rgbtBlue + d.rgbtBlue + e.rgbtBlue + f.rgbtBlue + g.rgbtBlue +
                                              h.rgbtBlue + i.rgbtBlue) / 9);
                image[m][n].rgbtGreen = round(((float)a.rgbtGreen + b.rgbtGreen + c.rgbtGreen + d.rgbtGreen + e.rgbtGreen + f.rgbtGreen +
                                               g.rgbtGreen + h.rgbtGreen + i.rgbtGreen) / 9);
            }
        }
    }
    return;
}