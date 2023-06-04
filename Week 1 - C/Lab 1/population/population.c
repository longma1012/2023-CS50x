#include <cs50.h>
#include <stdio.h>

int prompt_start_size(void);
int prompt_end_size(int startSize);
int calu_numof_years(int startSize, int endSize);
void print_numof_years(int numof_years);


int main(void)
{
    // TODO: Prompt for start size
    int startSize = prompt_start_size();

    // TODO: Prompt for end size
    int endSize = prompt_end_size(startSize);

    // TODO: Calculate number of years until we reach threshold
    int numofYears = calu_numof_years(startSize, endSize);

    // TODO: Print number of years
    print_numof_years(numofYears);
}


int prompt_start_size(void)
{
    int startSize;
    do
    {
        startSize = get_int("Start size: ");
    }
    while (startSize < 9);

    return startSize;
}


int prompt_end_size(int startSize)
{
    int endSize;
    do
    {
        endSize = get_int("End size: ");
    }
    while (endSize < startSize);

    return endSize;
}


int calu_numof_years(int startSize, int endSize)
{
    int numofYears = 0;
    int curSize = startSize;
    int bornSize;
    int paSize;

    while (curSize < endSize)
    {
        bornSize = curSize / 3;
        paSize = curSize / 4;
        curSize = curSize + bornSize - paSize;

        numofYears += 1;
    }

    return numofYears;
}


void print_numof_years(int numof_years)
{
    printf("Years: %i\n", numof_years);
}
