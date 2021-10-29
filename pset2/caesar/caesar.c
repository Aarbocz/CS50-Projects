#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool check_two_arguments(int argc);
bool check_argv_number(string argv);
string argv_encoded(string text, int steps);

int main(int argc, string argv[])
{
    //Check if conditions of the argument line is met
    if ((check_two_arguments(argc)) && (check_argv_number(argv[1])))
    {
        //Transform string argv to int argv
        int steps = atoi(argv[1]);

        //Get text from user
        string text = get_string("plaintext: ");

        //Print encrypted text
        printf("ciphertext: %s\n", argv_encoded(text, steps));

        return 0;
    }
    else
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
}


//Check if command line has two arguments
bool check_two_arguments(int argc)
{
    if (argc == 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Check if argv[1] is all numbers
bool check_argv_number(string argv)
{
    bool check;
    for (int i = 0; i < strlen(argv); i++)
    {
        if ((argv[i] >= '0') && (argv[i] <= '9'))
        {
            check = true;
        }
        else
        {
            check = false;
            return check;
        }
    }
    return check;
}

//Encodes text based on argv[1]
string argv_encoded(string text, int steps)
{
    //Loop over every character in text
    for (int i = 0; i < strlen(text); i++)
    {
        //Handle A - Z
        if ((text[i] >= 'A') && (text[i] <= 'Z'))
        {
            text[i] += (steps % 26);
            if (text[i] > 'Z')
            {
                text[i] = text[i] - 26;
            }
        }

        //Handle a - z
        if ((text[i] >= 'a') && (text[i] <= 'z'))
        {
            text[i] -= 'a';
            text[i] += (steps % 26);
            if (text[i] >= 26)
            {
                text[i] = text[i] - 26;
            }
            text[i] += 'a';
        }
    }
    return text;
}