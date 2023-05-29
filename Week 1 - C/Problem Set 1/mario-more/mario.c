#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_pyramids(int height);

int main(void)
{
    int height = get_height();
    print_pyramids(height);
}

int get_height(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    return height;
}

void print_pyramids(int height)
{
    char hash = '#';
    int numofHashes;
    int i;
    int j;

    for (i = 0; i < height; i++)
    {
        numofHashes = i + 1;

        for (j = 0; j < height - numofHashes; j++)
        {
            printf(" ");
        }

        for (j = 0; j < numofHashes; j++)
        {
            printf("%c", hash);
        }

        printf("  ");

        for (j = 0; j < numofHashes; j++)
        {
            printf("%c", hash);
        }

        printf("\n");

    }
}