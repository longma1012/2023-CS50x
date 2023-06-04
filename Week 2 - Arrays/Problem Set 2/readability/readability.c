#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const float HUNDRED = 100.0;

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
void print_result(float index);

int main(void)
{
    string text = get_string("Text: ");
    int numLetters = count_letters(text);
    int numWords = count_words(text);
    int numSentences = count_sentences(text);

    // printf("number of letters: %i\n", numLetters);
    // printf("number of words: %i\n", numWords);
    // printf("number of sentences: %i\n", numSentences);

    float L = numLetters / (numWords / HUNDRED);
    float S = numSentences / (numWords / HUNDRED);
    float indexF = 0.0588 * L - 0.296 * S - 15.8;

    // printf("%f\n", indexF);

    print_result(indexF);
}

int count_letters(string text)
{
    int numLetters = 0;
    int textLength = strlen(text);
    for (int i = 0; i < textLength; i++)
    {
        if (isalpha(text[i]))
        {
            numLetters += 1;
        }
    }
    return numLetters;
}

int count_words(string text)
{
    int numWords = 1;
    int textLength = strlen(text);
    for (int i = 0; i < textLength; i++)
    {
        if (text[i] == ' ')
        {
            numWords += 1;
        }
    }
    return numWords;
}

int count_sentences(string text)
{
    int numSentences = 0;
    int textLength = strlen(text);
    for (int i = 0; i < textLength; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            numSentences += 1;
        }
    }
    return numSentences;
}

void print_result(float index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        int indexI = (int) index;
        float modOne = index - indexI;
        if (modOne >= 0.5)
        {
            printf("Grade %i\n", (indexI + 1));
        }
        else
        {
            printf("Grade %i\n", indexI);
        }
    }
}