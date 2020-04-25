#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

typedef struct cellMemory
{
    char* name;
    int data;
} cellMemory;

cellMemory* cM = NULL;
int size = 0;


int compare(cellMemory* a, cellMemory* b)
{
    char* aPtr = a->name;
    char* bPtr = b->name;
    for (int i = 0; i < strlen(a->name); ++i)
    {
        if (*aPtr > *bPtr) return 1;
        if (*aPtr < *bPtr) return -1;
        aPtr++;
        bPtr++;
    }
    if (strlen(a->name) < strlen(b->name)) return -1;
    return 0;
}

int cmpChar(char* a, char* b)
{
    char* aPtr = a;
    char* bPtr = b;
    for (int i = 0; i < strlen(a); ++i)
    {
        if (*aPtr > *bPtr) return 1;
        if (*aPtr < *bPtr) return -1;
        aPtr++;
        bPtr++;
    }
    if (strlen(a) < strlen(b)) return -1;
    return 0;
}

void setCellMemory(char* name, int data)
{
    for (int i = 0; i < size; ++i)//вставка нового значения, если уже существует переменная с таким именем
    {
        if (strcmp(name, cM[i].name) == 0)
        {
            cM[i].data = data;
            return;
        }
    }
    //если переменная с таким именем отсутствует
    size++;
    cM = (cellMemory*)realloc(cM, sizeof(cellMemory) * size);
    cM[size - 1].name = name;
    cM[size - 1].data = data;
    //массив всегда должен быть в отсортированном состоянии
    qsort(cM, size, sizeof(cellMemory), (int (*)(const void *, const void *)) compare);
}

cellMemory getCellMemory(char* name)///////мммм здесь что-то не так?
{
    int l = 0;
    int r = size;
    int c = 0;

    while (l != r)
    {
        c = (l + r) / 2;
        if (cmpChar(cM[c].name, name) == 1)
        {
            r = c;
        }
        else if (cmpChar(cM[c].name, name) == -1)
        {
            l = c;
        }
        else
        {
            return cM[c];
        }
    }
    if (strcmp(cM[c].name, name) == 0 )
    {
        return cM[c];
    }
    else
    {
        printf("Error\n");
        exit(3);
    }
}

void clearBuf(char* buf)
{
    char* b = buf;
    while (*b)
    {
        *b++ = 0;
    }
}

int main(int argc, char* argv[])
{
    FILE* file;
    char c;
    char buf[20];
    char* b = buf;
    if (!(file = fopen("data.txt", "r")))
    {
        printf("Ошибка при открытии файла\n");
        exit(-1);
    }

    while (!feof(file))
    {
        c = fgetc(file);
        if (c == ' ' || c == '\n')//если пустая строка
        {
            continue;
        }
        if (c != ';')
        {
            *b++ = c;
        }
        else if (c == ';')//ставим конец строки и переходим в начало буфера и обрабатываем полученную строку
        {
            *b++ = c;
            *b = 0;
            b = buf;

            //обрабатываем печать
            if (strstr(buf, "print"))//если в строке есть print
            {
                b += strlen("print");//здесь захватывается и пробел
                if (*b == ';')//если пустой принт -> печатаем все переменные
                {
                    for (int i = 0; i < size; ++i)
                    {
                        printf("%s %d\n", cM[i].name, cM[i].data);
                    }
                }
                else
                {
                    char nameBuf[250];
                    char* ptr = nameBuf;
                    while (*b != ';')//считываем в буфер все до точки с запятой
                    {
                        *ptr++ = *b++;
                    }
                    cellMemory tempCell = getCellMemory(nameBuf);
                    printf("%s %d\n", tempCell.name, tempCell.data);
                }
            }
            //так теперь рассмотрим ситуацию, когда у нас нет "print" в строке
            else
            {
                char nameBuf[250];// строка 128
                char* nameBufPtr = nameBuf;
                for (int i = 0; *b != '='; ++i)//записываем все до знака =
                {
                    *nameBufPtr++ = *b++;
                }
                *nameBufPtr = 0;
                b++;//уходим на след символ после =
                char* name = (char*)malloc(sizeof(char) * (strlen(nameBuf) + 1));
                strcpy(name, nameBuf);
                if (isdigit(*b)) //если не цифра, то нас ждет арифметическая операция с двумя переменными
                {
                    int num = 0;
                    while (*b != ';')
                    {
                        num = num * 10 + (*b - '0');
                        b++;
                    }
                    setCellMemory(name, num);
                }
                else
                {
                    char first[250] = {0}, *aPtr = first;
                    char second[250] = {0}, *bPtr = second;
                    while (isalpha(*b))
                    {
                        *aPtr++ = *b++;
                    }
                    char op = *b++;
                    while (isalpha(*b))
                    {
                        *bPtr++ = *b++;
                    }
                    int l = getCellMemory(first).data;
                    int r = getCellMemory(second).data;

                    switch (op) {
                        case '+':
                            setCellMemory(name, l + r);
                            break;

                        case '*':
                            setCellMemory(name, l * r);
                            break;

                        case '-':
                            setCellMemory(name, l - r);
                            break;

                        case '/':
                            setCellMemory(name, l / r);
                            break;

                        case '%':
                            setCellMemory(name, l % r);
                            break;
                    }
                }
                b = buf;

            }
            b = buf;
            clearBuf(buf);
        }
    }
    for (int j = 0; j < size; ++j)
    {
        free(cM[j].name);
    }
    free(cM);
    fclose(file);
    return 0;
}




















