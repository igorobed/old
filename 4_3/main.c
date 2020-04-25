#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <memory.h>

#define BUF_SIZE 300

typedef struct Data
{
    int priority;
    char* text;
} Data;

typedef struct QueueNode
{
    struct QueueNode* next;
    Data data;
} QueueNode;

QueueNode* tail;
QueueNode* head;

QueueNode* createNode(char* text, int priority)
{
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    node->data.text = text;
    node->data.priority = priority;
    node->next = NULL;
    return node;
}

//засовыаем в очередь
void Enqueue(QueueNode* node)
{
    if (tail == NULL)
    {
        tail = head = node;
    }
    else
    {
        tail->next = node;
        tail = node;
    }
}

//вытаскиваем из очереди
QueueNode* Dequeue()
{
    if (head == NULL)
    {
        return NULL;
    }
    QueueNode* result = head;
    head = head->next;
    result->next = NULL;
    return result;
}

void EnqueuePriority(QueueNode* node)
{
    QueueNode* curNode = head;
    if (head != NULL)
    {
        if (curNode->data.priority > node->data.priority)
        {
            node->next = curNode;
            head = node;
        }
        else
        {
            while (curNode->next && (curNode->next->data.priority <= node->data.priority))
            {
                curNode = curNode->next;
            }
            node->next = curNode->next;
            curNode->next = node;
        }
    }
    else
    {
        Enqueue(node);
    }
}

int main()
{
    system("chcp 65001");
    FILE* file;
    char c;
    int n;
    printf("Введите число входных файлов:\n");
    scanf("%d", &n);
    char buf[BUF_SIZE];
    char* b = buf;
    char nameBuf[BUF_SIZE] = {0};
    char* nameBufPtr = nameBuf;
    char fileName[BUF_SIZE];
    for (int i = 0; i < n; i++)
    {
        printf("Введите имя очередного файла:\n");
        scanf("%s", fileName);
        if (!(file = fopen(fileName, "r")))
        {
            printf("Не может быть открытым %s\n", fileName);
            continue;
        }
        while (!feof(file))
        {
            c = fgetc(file);
            if (c != '\n' && c != EOF)//считываем очередную строку файла
            {
                *b++ = c;
            }
            //обрабатываем считанную строку
            else
            {
                *b = 0;
                b = buf;
               while (isalpha(*b))//идем, пока не встретим знак равно
                {
                    b++;
                }
                b++;//сделали шаг и мы уже на цифре
                int num = 0;//сюда запишем приоритет очередного сообщения
                while (*b != ' ')
                {
                    num = num * 10 + (*b - '0');
                    b++;
                }
                b++;
                while (*b != '"')
                {
                    b++;
                }
                b++;
                while (*b != '"')//между кавычек имя, так что пока не дошли до второй -->> считываем имя
                {
                    *nameBufPtr++ = *b++;
                }

                //выделяем память для строки в Data
                char* name = (char*)malloc(sizeof(char) * (strlen(nameBuf) + 1));
                strcpy(name, nameBuf);
                
                b = buf;
                while(*b)//обнуляем
                {
                    *b++ = 0;
                }
                b = buf;
                nameBufPtr = nameBuf;//тут тож зануляем
                while (*nameBufPtr)
                {
                    *nameBufPtr++ = 0;
                }
                nameBufPtr = nameBuf;

                QueueNode*  queueNode = createNode(name, num);
                EnqueuePriority(queueNode);
            }
            

        }
    }
    //печатаем очередь, попутно очищая ее
    QueueNode* queueNode1 = Dequeue();
    while (queueNode1 != NULL)
    {
        printf("%d %s\n", queueNode1->data.priority, queueNode1->data.text);
        free(queueNode1->data.text);
        free(queueNode1);
        queueNode1 = Dequeue();
    }

    return 0;
}











