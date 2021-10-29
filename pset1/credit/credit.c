#include <cs50.h>
#include <stdio.h>


bool check_validity(long long CCN);
int find_length(long long CCN);
bool checksum(long long CCN);
void print_credit_card_brand(long long CCN);


int main(void)
{
    //Get credit card number from user
    long long credit_card_number; 
    do
    {
        credit_card_number = get_long_long("Number: ");
    }
    while (credit_card_number < 0);
    
    //Checks if conditions are met
    if (check_validity(credit_card_number)) 
    {
        print_credit_card_brand(credit_card_number);
    }
    else
    {
        printf("INVALID\n");
    }
}


//Check if length and Luhn's algorithm are true
bool check_validity(long long CCN)
{
    int len = find_length(CCN);
    
    return (len == 13 || len == 15 || len == 16) && checksum(CCN);
}


//Finds out the length of the card
int find_length(long long CCN)
{
    int len;
    for (len = 0; CCN != 0; CCN /= 10, len++);
    return len;
}

//Calculate Luhn's algorithm
bool checksum(long long CCN)
{
    int sum = 0;
    for (int i = 0; CCN != 0; i++, CCN /= 10)
    {
        if (i % 2 == 0)
        {
            sum = sum + CCN % 10;
        }
        else 
        {
            int digit = 2 * (CCN % 10);
            sum = sum + digit / 10 + digit % 10;
        }
    }
    return (sum % 10) == 0;
}

//Finds out the card's brand
void print_credit_card_brand(long long CCN)
{
    if ((CCN >= 34e13 && CCN < 35e13) || (CCN >= 37e13 && CCN < 38e13))
    {
        printf("AMEX\n");
    }
    else if (CCN >= 51e14 && CCN < 56e14)
    {
        printf("MASTERCARD\n");
    }
    else if ((CCN >= 4e12 && CCN < 5e12) || (CCN >= 4e15 && CCN < 5e15))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}