#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Get number of columns
    int columns;
    do
    {
        columns = get_int("Height: ");
    }
    while (columns < 1 || columns > 8);
    
    //Make pyramid
    for (int i = 0; i < columns; i++)
    {
        // Print space before
        for (int k = 1; k < columns - i; k++)
        {
            printf(" ");
        }
      
        // Print first lines of #
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
      
      
        // Print new line
        printf("\n");
    }

}
