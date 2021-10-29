#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //Get amount of change from user
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);
    
    //Convet dollars into cents
    int cents = round(change * 100);
    
    //Figure out how many coins are needed for change
    int coins = 0;
    
    // Handle quarters
    while (cents >= 25)
    {
        cents = cents - 25;
        coins++;
    }
    
    // Handle dimes
    while (cents >= 10)
    {
        cents = cents - 10;
        coins++;
    }
    
    // Handle nickles
    while (cents >= 5)
    {
        cents = cents - 5;
        coins++;
    }
    
    // Handle pennies
    while (cents >= 1)
    {
        cents = cents - 1;
        coins++;
    }
    
    
    //Print minium amont of coins for change
    printf("%i", coins);
    
    //Print new line
    printf("\n");
}