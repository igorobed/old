#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 200

typedef struct Node
{
    char* data;
    struct Node* next;
} Node;

Node* createNode(char* data)
{
    Node* node = malloc(sizeof(Node));
    char* d = malloc(sizeof(char) * (strlen(data) + 1));
    strcpy(d, data);
    node->data = d;
    node->next = NULL;
}

void LIST_NodePush(Node* node, Node** tail)//передаю указатель на указатель, чтобы работать с исходной переменной
{                                          // а не с временной копией
    if (*tail == NULL)
    {
        *tail = node;
        return;
    }
    Node* cur = *tail;
    cur->next = node;
    *tail = node;
    return;
}

Node* STACK_NodePop(Node** top, Node* predTop)
{
    Node* result = *top;
    if (predTop == *top)
    {
        (*top)->next = NULL;
        return result;
    }

    while (predTop->next != *top)//ищем предпоследний элемент
        predTop = predTop->next;
    if ((*top != NULL) && (predTop->next != NULL))
    {
        *top = predTop;
        (*top)->next = NULL;
    }
    return result;
}

Node* QUEUE_NodeDequeue(Node** head)
{
    Node* result = *head;
    if (*head == NULL)
        return NULL;
    if ((*head)->next != NULL)
    {
        *head = (*head)->next;
    }
    else
    {
        *head = NULL;
    }
    result->next = NULL;
    return result;
}

void nodeFree(Node* r)
{
    free(r->data);
    free(r);
}

int main()
{
    FILE* file;
    if (!(file = fopen("output4_6.txt", "w")))
    {
        printf("Error 1");
        exit(-1);
    }
    char str[LEN];
    int n;
    int i = 1;
    printf("Set n:\n");
    scanf("%d", &n);
    if (n < 1)
    {
        printf("Incorrect input data\n");
        exit(-2);
    }
    printf("Input str:\n");
    scanf("%s", str);
    Node* head = NULL;
    Node* Tail_Top = NULL;

    while (strcmp(str, "stop") != 0)
    {
        if (strcmp(str, "rm") == 0)//удаляем последние n/2 записи
        {
            for (int j = 0; j < n/2; j++)
            {
                if (head == NULL && Tail_Top == NULL)
                    break;
                Node* remove = STACK_NodePop(&Tail_Top, head);

                if (remove != NULL)
                {
                    nodeFree(remove);
                    i -= 1;
                    if (i == 0)
                    {
                        Tail_Top = NULL;//когда мы ввели меньше n/2  и захотели все удалить
                        break;
                    }
                }
                else
                    break;
            }
            if (i + (n/2) <= (n/2))//чтобы учитывать исходное i до удаления
                head = NULL;

        }
        else
        {

            Node *node = createNode(str);
            if (head == NULL)//начинаем очередь для хранения
                head = node;
            LIST_NodePush(node, &Tail_Top);//хвост списка
            if (i == n)//когда у нас набралось n строк, производим запись в файл
            {
                Node* dequeue = QUEUE_NodeDequeue(&head);
                while (dequeue != NULL)
                {
                    fprintf(file, "%s\n", dequeue->data);
                    nodeFree(dequeue);
                    dequeue = QUEUE_NodeDequeue(&head);

                }
                Tail_Top = NULL;
                i = 0;//для следующей итерации n строк
            }
            //i += 1;
        }
        scanf("%s", str);
        if ((strcmp(str, "stop") != 0) && (strcmp(str, "rm") != 0))
            i++;
        if (strcmp(str, "stop") == 0)
        {
            Node* dequeue = QUEUE_NodeDequeue(&head);
            while (dequeue != NULL)
            {
                fprintf(file, "%s\n", dequeue->data);
                nodeFree(dequeue);
                dequeue = QUEUE_NodeDequeue(&head);

            }
            Tail_Top = NULL;
        }

    }
    fclose(file);
    return 0;
}
