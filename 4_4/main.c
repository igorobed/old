
//сделать обработку события, что элемент для удаления не найден


#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define LEN 200

typedef struct Node
{
    char* surname;
    char* name;
    char* patronymic;
    int day;
    int year;
    int month;
    int sex;
    int salary;

    struct Node* next;
} Node;

Node* first;

Node* createNode(char* name,char* surname,  char* patronymic, int day, int year, int month, int sex, int salary) {
    Node* node = malloc(sizeof(Node));
    node->name = name;
    node->surname = surname;
    node->patronymic = patronymic;
    node->day = day;
    node->year = year;
    node->month = month;
    node->sex = sex;
    node->salary = salary;
    node->next = NULL;

    return node;
}

//-1 - second старше first
// 1 - first старше second
int compareAge(Node* first, Node* second)
{
    if (first->year > second->year)
        return -1;
    if (first->year < second->year)
        return 1;
    if (first->year == second->year)
    {
        if (first->month > second->month)
            return -1;
        if (first->month < second->month)
            return 1;
        if (first->month == second->month)
        {
            if (first->day > second->day)
                return -1;
            if (first->day < second->day)
                return 1;
        }
    }
    return 1;
}

void printNodes()
{
    Node* cur = first;
    printf("%15s %15s %15s %4s %4s %4s %4s %9s", "Name", "Surname", "Patronymic", "Day", "Year",
           "Month", "Sex", "Salary\n");
    while (cur != NULL)
    {

        printf("%15s %15s %15s %4d %4d %4d %4d %9d\n", cur->name, cur->surname, cur->patronymic, cur->day,
               cur->year, cur->month, cur->sex, cur->salary);
        cur = cur->next;
    }
}

void insertNode(Node* node)
{
    Node* cur = first;
    if (cur == NULL)
    {
        first = node;
        return;
    }
    if (compareAge(first, node) > 0)// если first старше node, то он(first) уходит вниз
    {
        node->next = first;
        first = node;
        return;
    }
    Node* prev = cur;
    while (cur->next != NULL)
    {
        if (compareAge(cur, node) < 0)//если node старше cur, то идем вправо, пока не встретим
        {                             //cur старше node или null
            prev = cur;
            cur = cur->next;
        }
        else
            break;
    }
    if ((cur != NULL) && (compareAge(cur, node) < 0))//случай, когда node самый старший в итоге и ставится последним
    {
        cur->next = node;
        node->next = NULL;

        return;
    }
    node->next = prev->next; //если пришли сюда, значит нашли cur, который старше node, и node ставим перед ним
    prev->next = node;
}

int main(int argc, char* argv[])
{
    /*if (argc < 2)
    {
        printf("Invalid argument");
        exit(-2);
    }*/

    //char myArgv[LEN];
    //scanf("%s", myArgv);
    FILE* file;
    //if (!(file = fopen(argv[1], "r")))
    if (!(file = fopen("..\\input4_4.txt", "r")))
    {
        printf("Couldn't open %s", "..\\input4_4.txt");
        exit(-1);
    }
    char nameBuf[LEN];
    char surnameBuf[LEN];
    char patronymicBuf[LEN];

    int day;
    int year;
    int month;
    int sex;
    int salary;

    while (!feof(file))
    {
        fscanf(file, "%s %s %s %d %d %d %d %d\n", nameBuf, surnameBuf, patronymicBuf, &day, &year, &month, &sex, &salary);
        char* name = malloc(sizeof(char) * (strlen(nameBuf) + 1));
        char* surname = malloc(sizeof(char) * (strlen(surnameBuf) + 1));
        char* patronymic = malloc(sizeof(char) * (strlen(patronymicBuf) + 1));

        strcpy(name, nameBuf);
        strcpy(surname, surnameBuf);
        strcpy(patronymic, patronymicBuf);

        Node* node = createNode(name, surname, patronymic, day, year, month, sex, salary);
        insertNode(node);
    }

    fclose(file);

    int action = 0;
    char buf[LEN];
    while (action != 5)
    {
        printf("1.Print list\n2.Search\n3.Delete\n4.Add\n5.Exit\n");
        scanf("%d", &action);
        switch (action)
        {
            case 1:
                printNodes();
                break;
            case 2:
                printf("Enter name and date in format: Name Day Year Month\n");
                scanf("%s %d", buf, &year);
                Node* cur = first;
                char find = 0;
                while (cur != NULL)
                {
                    if ((strcmp(buf, cur->name) == 0) && (year == cur->year))
                    {
                        printf("%15s %15s %15s %4d %4d %4d %4d %9d\n", cur->name, cur->surname, cur->patronymic, cur->day,
                               cur->year, cur->month, cur->sex, cur->salary);
                        find = 1;
                        break;
                    }
                    cur = cur->next;
                }
                if (find == 0) printf("Not found\n");
                break;
            case 3://удаление
                printf("Enter name\n");
                scanf("%s", buf);
                cur = first;
                Node* prev = cur;
                Node* remove;

                while (cur != NULL)
                {
                    if (strcmp(buf, cur->name) == 0)//если мы нашли элемент на удаление
                    {
                        remove = cur;

                        if (cur == first)
                        {
                            first = cur->next;
                        }
                        else
                        {
                            prev->next = cur->next;
                        }

                        free(remove->name);
                        free(remove->patronymic);
                        free(remove->surname);
                        free(remove);

                        break;
                    }

                    if (cur->next)
                    {
                        prev = cur;
                        cur = cur->next;
                    }
                    else
                    {
                        printf("Name not found\n");
                        break;
                    }

                }

                break;
            case 4:
                printf("Enter: Name Surname Patronymic Day Year Month Sex Salary\n");
                scanf("%s %s %s %d %d %d %d %d", nameBuf, surnameBuf, patronymicBuf, &day, &year, &month, &sex, &salary);

                char* name = malloc(sizeof(char) * (strlen(nameBuf) + 1));
                char* surname = malloc(sizeof(char) * (strlen(surnameBuf) + 1));
                char* patronymic = malloc(sizeof(char) * (strlen(patronymicBuf) + 1));

                strcpy(name, nameBuf);
                strcpy(surname, surnameBuf);
                strcpy(patronymic, patronymicBuf);

                Node* node = createNode(name, surname, patronymic, day, year, month, sex, salary);
                insertNode(node);
                break;
            case 5:
                //if (!(file = fopen(argv[1], "w")))
                if (!(file = fopen("..\\input4_4.txt", "w")))
                {
                    printf("Counld't open for writing %s", "..\\input4_4.txt");
                    exit(-3);
                }
                cur = first;
                while (cur != NULL)
                {

                    fprintf(file, "%s %s %s %d %d %d %d %d\n", cur->name, cur->surname, cur->patronymic, cur->day,
                            cur->year, cur->month, cur->sex, cur->salary);
                    cur = cur->next;
                }
                break;
            default:
                break;
        }
    }
    return 0;
}

