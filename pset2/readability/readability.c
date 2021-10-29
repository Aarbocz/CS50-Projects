#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int grade_level(string text);

int main(void)
{
    //Get text from the user
    string text;
    do
    {
        text = get_string("Text: ");
    }
    while (strlen(text) <= 0);

    //Print counts
    //printf("%i letter(s)\n", count_letters(text));
    //printf("%i word(s)\n", count_words(text));
    //printf("%i sentence(s)\n", count_sentences(text));
    
    //Print grade level
    if (grade_level(text) >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade_level(text) < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade_level(text));
    }
}

//Count total letter in text
int count_letters(string text)
{
    int letters = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
    }

    return letters;
}

//Count total words in text
int count_words(string text)
{
    int words = 1;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            words += 1;
        }

    }

    return words;
}

//Count total sentences in text
int count_sentences(string text)
{
    int sentences = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
        {
            sentences += 1;
        }
    }

    return sentences;
}

//Calculate grade level using Coleman-Liau index
int grade_level(string text)
{
    //Calculate average number of letters per 100 words
    float l = ((100 * (float) count_letters(text)) / (float) count_words(text));
    //Calculate average number of sentences per 100 words
    float s = ((100 * (float) count_sentences(text)) / (float) count_words(text));
    
    //Calculate Coleman-Liau index
    int index = round((0.0588 * l) - (0.296 * s) - 15.8);
    return index;
}
