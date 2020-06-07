#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int countOf1InBinary(int num)
{
    int count = 0;
    while (num != 0)
    {
        if (num % 2 != 0)
        {
            count ++;
        }
        num /= 2;
    }
    return count;
}

bool seriesOfLExist(int num, int l)
{
    int count = 0;

    while (num != 0)
    {
        if (num % 2 != 0)
        {
            count++;
        }
        else
        {
            count = 0;
        }
        if (count == l && ((num/2)%2 == 0 || num == 0))
            return 1;
        num /= 2;
    }
    return 0;
}

void task1(int k, int l)
{
    printf("Первое задание:\n");
    int max = 1 << k;//создаем число 1000...00(k нулей)
    for (int i = 1 << (k-1); i < max; ++i)//рассматриваем все числа в промежутке [max/2 ; max)
    {
        if (countOf1InBinary(i) == l) {
            printf("%d\n", i);
        }
    }
}

void task2(int k, int l)
{
    printf("Второе задание:\n");
    int max = 1 << k;
    for (int i = 1 << (k-1); i < max; ++i)
    {
        if (seriesOfLExist(i, l))
        {
            printf("%d\n", i);
        }
    }
}

int main(int argc, char* argv[])
{
    system("chcp 65001");
    int k, l;
    printf("Введите k: ");
    scanf("%d", &k);
    printf("Введите l: ");
    scanf("%d", &l);

    task1(k, l);
    task2(k, l);

    return 0;
}
