#include <cs50.h>
#include <stdio.h>

long prompt_cardnum();
bool checksum(long cardNumber);
int get_ith_num(long cardNumber, int i);

int main(void)
{
    const long thirteen = 1000000000000;
    const long fourteen = 10000000000000;
    const long fifteen = 100000000000000;
    const long sixteen = 1000000000000000;
    const long seventeen = 10000000000000000;

    bool flag = true;

    long cardNumber = prompt_cardnum();

    long divideThirteen = cardNumber / thirteen;
    long divideFourteen = cardNumber / fourteen;
    long divideFifteen = cardNumber / fifteen;
    long divideSixteen = cardNumber / sixteen;
    long divideSeventeen = cardNumber / seventeen;

    // long modThirteen = cardNumber % thirteen;
    // long modFourteen = cardNumber % fourteen;
    // long modFifteen = cardNumber % fifteen;
    // long modSixteen = cardNumber % sixteen;
    // long modSeventeen = cardNumber % seventeen;


    if (divideSeventeen == 0 && divideThirteen != 0)
    {
        if (divideFifteen != 0 && divideSixteen == 0)
        {
            if (divideFourteen == 34 || divideFourteen == 37)
            {
                if (checksum(cardNumber))
                {
                    printf("AMEX\n");
                    flag = false;
                }
            }
        }

        if (divideSixteen != 0 && divideSeventeen == 0)
        {
            if (divideFifteen > 50 && divideFifteen < 56)
            {
                if (checksum(cardNumber))
                {
                    printf("MASTERCARD\n");
                    flag = false;
                }
            }
        }

        if (divideThirteen != 0 && divideFourteen == 0)
        {
            if (divideThirteen == 4)
            {
                if (checksum(cardNumber))
                {
                    printf("VISA\n");
                    flag = false;
                }
            }
        }

        if (divideSixteen != 0 && divideSeventeen == 0)
        {
            if (divideSixteen == 4)
            {
                if (checksum(cardNumber))
                {
                    printf("VISA\n");
                    flag = false;
                }
            }
        }
    }

    if (flag)
    {
        printf("INVALID\n");
    }
}

long prompt_cardnum()
{
    long cardNumber;
    do
    {
        cardNumber = get_long("Number: ");
    }
    while (cardNumber < 1);

    return cardNumber;
}

bool checksum(long cardNumber)
{
    int ithNum;
    int index;
    bool ret;

    int sum = 0;

    for (int i = 0; i < 8; i++)
    {
        index = (i + 1) * 2;
        ithNum = get_ith_num(cardNumber, index);
        ithNum *= 2;
        // printf("i: %i, ithnum: %i\n", index, ithNum);
        if (ithNum < 10)
        {
            sum += ithNum;
        }
        else
        {
            sum += (ithNum % 10);
            sum += (ithNum / 10);
        }
    }

    for (int i = 0; i < 8; i++)
    {
        index = 2 * i + 1;
        ithNum = get_ith_num(cardNumber, index);
        // printf("i: %i, ithnum: %i\n", index, ithNum);
        sum += ithNum;
    }

    // printf("%i\n", sum);

    if (sum % 10 == 0)
    {
        ret = true;
    }
    else
    {
        ret = false;
    }

    return ret;

}

int get_ith_num(long cardNumber, int i)
{
    long result;

    long first = 1;
    long second = 1;

    for (int j = 0; j < i - 1; j++)
    {
        first *= 10;
        second *= 10;
    }
    first *= 10;

    result = (cardNumber % first) / second;
    return result;
}