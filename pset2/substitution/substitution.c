#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool check_two_arguments(int argc);
bool check_all_letters(string argv);
void argv_encoded(string text, string argv);
bool check_26_char(string argv);
bool check_all_different(string argv);

int main(int argc, string argv[])
{
    //Check if conditions of the argument line is met
    if (check_two_arguments(argc))
    {
        if ((check_26_char(argv[1])) && (check_all_letters(argv[1])) && (check_all_different(argv[1])))
        {

            //Get text from user
            string text = get_string("plaintext: ");

            //Print encrypted text
            printf("ciphertext: ");
            argv_encoded(text, argv[1]);

            return 0;
        }
        //Handle error
        else
        {
            printf("Key must contain 26 different characters from a - z.\n");
            return 1;
        }
    }
    //Handle error
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
bool check_all_letters(string argv)
{
    bool check_letter;
    for (int i = 0; i < strlen(argv); i++)
    {
        if (((argv[i] >= 'A') && (argv[i] <= 'Z')) || ((argv[i] >= 'a') && (argv[i] <= 'z')))
        {
            check_letter = true;
        }
        else
        {
            check_letter = false;
            return check_letter;
        }
    }
    return check_letter;
}

//Check if argv[1] has 26 characters
bool check_26_char(string argv)
{
    bool check_26;
    if (strlen(argv) == 26)
    {
        check_26 = true;
    }
    else
    {
        check_26 = false;
        return check_26;
    }
    return check_26;
}

//Check if argv[1] are all different
bool check_all_different(string argv)
{
    bool check_dif = true;
    int count = 0;

    for (int i = 0; i < strlen(argv); i++)
    {
        argv[i] = tolower(argv[i]);

        for (int n = 0; n < strlen(argv); n++)
        {
            if (argv[i] == argv[n])
            {
                count++;
            }
        }
    }
    if (count == 26)
    {
        check_dif = true;
    }
    else
    {
        check_dif = false;
        return check_dif;
    }
    return check_dif;
}

//Encodes text based on argv[1] and print results
void argv_encoded(string text, string argv)
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    //Loop over every character in text
    for (int i = 0; i < strlen(text); i++)
    {
        //Handle lower case characters in text
        if (islower(text[i]))
        {
            for (int n = 0; n < strlen(alphabet); n++)
            {
                if (text[i] == alphabet[n])
                {
                    printf("%c", argv[n]);

                }
            }
        }
        //Handles uppercase characters in text
        else if (isupper(text[i]))
        {
            for (int n = 0; n < strlen(alphabet); n++)
            {
                if (text[i] == toupper(alphabet[n]))
                {
                    printf("%c", toupper(argv[n]));
                }
            }
        }
        //Handle non alphabetical characters
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}