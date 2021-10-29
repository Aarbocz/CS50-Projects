#include "helpers.h"
#include "math.h"

int calculate(int Gx, int Gy);

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


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
        //Calculate red pixels
        for (int n = 0; n < width; n++)
        {
            //Gx 9 pixel grid
            int a = (float)temp[m - 1][n - 1].rgbtRed * -1;
            int b = (float)temp[m - 1][n].rgbtRed * 0;
            int c = (float)temp[m - 1][n + 1].rgbtRed * 1;
            int d = (float)temp[m][n - 1].rgbtRed * -2;
            int e = (float)temp[m][n].rgbtRed * 0;
            int f = (float)temp[m][n + 1].rgbtRed * 2;
            int g = (float)temp[m + 1][n - 1].rgbtRed * -1 ;
            int h = (float)temp[m + 1][n].rgbtRed * 0;
            int i = (float)temp[m + 1][n + 1].rgbtRed * 1;

            //gx 9 pixel grid
            int r = (float)temp[m - 1][n - 1].rgbtRed * -1;
            int s = (float)temp[m - 1][n].rgbtRed * -2;
            int t = (float)temp[m - 1][n + 1].rgbtRed * -1;
            int u = (float)temp[m][n - 1].rgbtRed * 0;
            int v = (float)temp[m][n].rgbtRed * 0;
            int w = (float)temp[m][n + 1].rgbtRed * 0;
            int x = (float)temp[m + 1][n - 1].rgbtRed * 1;
            int y = (float)temp[m + 1][n].rgbtRed * 2;
            int z = (float)temp[m + 1][n + 1].rgbtRed * 1;

            //Handle top left corner
            if ((m == 0) && (n == 0))
            {
                image[m][n].rgbtRed = calculate(e + f + h + i, v + w + y + z);
            }
            //Handle top right corner
            else if ((m == 0) && (n == width - 1))
            {
                image[m][n].rgbtRed = calculate(d + e + g + h, u + v + x + y);
            }
            //Handle bottom left corner
            else if ((m == height - 1) && (n == 0))
            {
                image[m][n].rgbtRed = calculate(b + c + e + f, s + t + v + w);
            }
            //Handle bottom right corner
            else if ((m == height - 1) && (n == width - 1))
            {
                image[m][n].rgbtRed = calculate(a + b + d + e, r + s + u + v);
            }
            //Handle first line
            else if (m == 0)
            {
                image[m][n].rgbtRed = calculate(d + e + f + g + h + i, u + v + w + x + y + z);
            }
            //Handle last line
            else if (m == height - 1)
            {
                image[m][n].rgbtRed = calculate(a + b + c + d + e + f, r + s + t + u + v + w);
            }
            //Handle first column
            else if (n == 0)
            {
                image[m][n].rgbtRed = calculate(b + c + e + f + h + i, s + t + v + w + y + z);
            }
            //Handle last column
            else if (n == width - 1)
            {
                image[m][n].rgbtRed = calculate(a + b + d + e + g + h, r + s + u + v + x + y);
            }
            //Handle middle pixels
            else
            {
                image[m][n].rgbtRed = calculate(a + b + c + d + e + f + g + h + i, r + s + t + u + v + w + x + y + z);
            }
        }

        //Calculate blue pixels
        for (int n = 0; n < width; n++)
        {
            //Gx 9 pixel grid
            int a = (float)temp[m - 1][n - 1].rgbtBlue * -1;
            int b = (float)temp[m - 1][n].rgbtBlue * 0;
            int c = (float)temp[m - 1][n + 1].rgbtBlue * 1;
            int d = (float)temp[m][n - 1].rgbtBlue * -2;
            int e = (float)temp[m][n].rgbtBlue * 0;
            int f = (float)temp[m][n + 1].rgbtBlue * 2;
            int g = (float)temp[m + 1][n - 1].rgbtBlue * -1 ;
            int h = (float)temp[m + 1][n].rgbtBlue * 0;
            int i = (float)temp[m + 1][n + 1].rgbtBlue * 1;

            //gx 9 pixel grid
            int r = (float)temp[m - 1][n - 1].rgbtBlue * -1;
            int s = (float)temp[m - 1][n].rgbtBlue * -2;
            int t = (float)temp[m - 1][n + 1].rgbtBlue * -1;
            int u = (float)temp[m][n - 1].rgbtBlue * 0;
            int v = (float)temp[m][n].rgbtBlue * 0;
            int w = (float)temp[m][n + 1].rgbtBlue * 0;
            int x = (float)temp[m + 1][n - 1].rgbtBlue * 1;
            int y = (float)temp[m + 1][n].rgbtBlue * 2;
            int z = (float)temp[m + 1][n + 1].rgbtBlue * 1;

            //Handle top left corner
            if ((m == 0) && (n == 0))
            {
                image[m][n].rgbtBlue = calculate(e + f + h + i, v + w + y + z);
            }
            //Handle top right corner
            else if ((m == 0) && (n == width - 1))
            {
                image[m][n].rgbtBlue = calculate(d + e + g + h, u + v + x + y);
            }
            //Handle bottom left corner
            else if ((m == height - 1) && (n == 0))
            {
                image[m][n].rgbtBlue = calculate(b + c + e + f, s + t + v + w);
            }
            //Handle bottom right corner
            else if ((m == height - 1) && (n == width - 1))
            {
                image[m][n].rgbtBlue = calculate(a + b + d + e, r + s + u + v);
            }
            //Handle first line
            else if (m == 0)
            {
                image[m][n].rgbtBlue = calculate(d + e + f + g + h + i, u + v + w + x + y + z);
            }
            //Handle last line
            else if (m == height - 1)
            {
                image[m][n].rgbtBlue = calculate(a + b + c + d + e + f, r + s + t + u + v + w);
            }
            //Handle first column
            else if (n == 0)
            {
                image[m][n].rgbtBlue = calculate(b + c + e + f + h + i, s + t + v + w + y + z);
            }
            //Handle last column
            else if (n == width - 1)
            {
                image[m][n].rgbtBlue = calculate(a + b + d + e + g + h, r + s + u + v + x + y);
            }
            //Handle middle pixels
            else
            {
                image[m][n].rgbtBlue = calculate(a + b + c + d + e + f + g + h + i, r + s + t + u + v + w + x + y + z);
            }
        }

        //Calculate green pixels
        for (int n = 0; n < width; n++)
        {
            //Gx 9 pixel grid
            int a = (float)temp[m - 1][n - 1].rgbtGreen * -1;
            int b = (float)temp[m - 1][n].rgbtGreen * 0;
            int c = (float)temp[m - 1][n + 1].rgbtGreen * 1;
            int d = (float)temp[m][n - 1].rgbtGreen * -2;
            int e = (float)temp[m][n].rgbtGreen * 0;
            int f = (float)temp[m][n + 1].rgbtGreen * 2;
            int g = (float)temp[m + 1][n - 1].rgbtGreen * -1 ;
            int h = (float)temp[m + 1][n].rgbtGreen * 0;
            int i = (float)temp[m + 1][n + 1].rgbtGreen * 1;

            //gx 9 pixel grid
            int r = (float)temp[m - 1][n - 1].rgbtGreen * -1;
            int s = (float)temp[m - 1][n].rgbtGreen * -2;
            int t = (float)temp[m - 1][n + 1].rgbtGreen * -1;
            int u = (float)temp[m][n - 1].rgbtGreen * 0;
            int v = (float)temp[m][n].rgbtGreen * 0;
            int w = (float)temp[m][n + 1].rgbtGreen * 0;
            int x = (float)temp[m + 1][n - 1].rgbtGreen * 1;
            int y = (float)temp[m + 1][n].rgbtGreen * 2;
            int z = (float)temp[m + 1][n + 1].rgbtGreen * 1;

            //Handle top left corner
            if ((m == 0) && (n == 0))
            {
                image[m][n].rgbtGreen = calculate(e + f + h + i, v + w + y + z);
            }
            //Handle top right corner
            else if ((m == 0) && (n == width - 1))
            {
                image[m][n].rgbtGreen = calculate(d + e + g + h, u + v + x + y);
            }
            //Handle bottom left corner
            else if ((m == height - 1) && (n == 0))
            {
                image[m][n].rgbtGreen = calculate(b + c + e + f, s + t + v + w);
            }
            //Handle bottom right corner
            else if ((m == height - 1) && (n == width - 1))
            {
                image[m][n].rgbtGreen = calculate(a + b + d + e, r + s + u + v);
            }
            //Handle first line
            else if (m == 0)
            {
                image[m][n].rgbtGreen = calculate(d + e + f + g + h + i, u + v + w + x + y + z);
            }
            //Handle last line
            else if (m == height - 1)
            {
                image[m][n].rgbtGreen = calculate(a + b + c + d + e + f, r + s + t + u + v + w);
            }
            //Handle first column
            else if (n == 0)
            {
                image[m][n].rgbtGreen = calculate(b + c + e + f + h + i, s + t + v + w + y + z);
            }
            //Handle last column
            else if (n == width - 1)
            {
                image[m][n].rgbtGreen = calculate(a + b + d + e + g + h, r + s + u + v + x + y);
            }
            //Handle middle pixels
            else
            {
                image[m][n].rgbtGreen = calculate(a + b + c + d + e + f + g + h + i, r + s + t + u + v + w + x + y + z);
            }
        }
    }
    return;
}

int calculate(int Gx, int Gy)
{
    //Get sqaure root of Gx and Gy. Round number.
    int i = round(sqrt(pow(Gx, 2) + pow(Gy, 2)));

    //Check if goes over 255
    if (i > 255)
    {
        i = 255;
    }
    return i;
}
