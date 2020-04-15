#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFSIZE 50

typedef struct _Address
{
    //char city[BUFFSIZE];
    //char street[BUFFSIZE];
    char* city;
    char* street;
    unsigned int num_house;
    unsigned int num_flat;
    unsigned int index;
} Address;

typedef struct _Mail
{
    Address address;
    unsigned int post_id;
    unsigned int weight;
} Mail;

typedef struct _Post
{
    Address address;
    Mail * mails;

} Post;
int compare_index(const void *a, const void *b)
{
    const Mail *x = a;
    const Mail *y = b;

    int comp = x->address.index - y->address.index;

    if (comp < 0)
        return -1;

    if (comp > 0)
        return 1;
    return comp;
}
int compare_post_id(const void *a, const void *b)
{
    const Mail *x = a;
    const Mail *y = b;

    int comp = x->post_id - y->post_id;

    if (comp < 0)
        return -1;

    if (comp > 0)
        return 1;
    return comp;
}


int main(int argc, char * argv[])
{
    system("chcp 65001");
    Post post;
    printf("Введите адрес(Post) в следующем формате: город улица дом квартира индекс\n");
    char city_buf[BUFFSIZE];
    char street_buf[BUFFSIZE];
    unsigned int num_house, num_flat, index;
    scanf("%s %s %d %d %d", city_buf, street_buf, &num_house, &num_flat, &index);
    //добавление
    post.address.city = (char*)malloc(sizeof(char)*strlen(city_buf) + 1);
    post.address.street = (char*)malloc(sizeof(char)*strlen(street_buf) + 1);
    strcpy(post.address.city, city_buf);
    strcpy(post.address.street, street_buf);
    //добавление
    //strcpy(post.address.city, city_buf);
    //strcpy(post.address.street, street_buf);
    post.address.num_house = num_house;
    post.address.num_flat = num_flat;
    post.address.index = index;

    int size_mails = 3;
    int cur_size_mails = 0;
    int post_id = 0;
    int weight = 0;
    int temp;

    post.mails = malloc(sizeof(Mail) * size_mails);

    int flag = 0;
    printf("1 - Добавление\n"
           "2 - Удаление\n"
           "3 - Поиск по post_id(номеру сообщения)\n"
           "4 - Просмотр mail\n"
           "5 - Сортировать по почтовому индексу\n"
           "6 - Сортировать по post_id(номер сообщения)\n"
           "-1 - Выход\n");


    while(flag != -1)
    {
        printf("Введите комманду: ");
        scanf("%d", &flag);
        switch(flag)
        {
            case 1:
                if (cur_size_mails == size_mails)
                {
                    size_mails *= 2;
                    post.mails = realloc(post.mails, sizeof(Mail) * size_mails);
                }
                printf("Введите адрес(Mail) в следующем формате: город улица дом квартира индекс\n");
                scanf("%s %s %d %d %d", city_buf, street_buf, &num_house, &num_flat, &index);
                //добавление
                post.mails[cur_size_mails].address.city = (char*)malloc(sizeof(char)*strlen(city_buf) + 1);
                post.mails[cur_size_mails].address.street = (char*)malloc(sizeof(char)*strlen(street_buf) + 1);
                strcpy(post.mails[cur_size_mails].address.city, city_buf);
                strcpy(post.mails[cur_size_mails].address.street, street_buf);

                //добавление
                //strcpy(post.mails[cur_size_mails].address.city, city_buf);
                //strcpy(post.mails[cur_size_mails].address.street, street_buf);
                post.mails[cur_size_mails].address.num_house = num_house;
                post.mails[cur_size_mails].address.num_flat = num_flat;
                post.mails[cur_size_mails].address.index = index;
                post.mails[cur_size_mails].post_id = post_id++;
                printf("Введите вес посылки: ");
                scanf("%d", &weight);
                while (weight <= 0)
                {
                    printf("Введите вес посылки: ");
                    scanf("%d", &weight);
                }
                post.mails[cur_size_mails].weight = weight;
                cur_size_mails++;

                break;
            case 2:
                printf("Введите номер сообщения(post_id): ");//нумерация начинается с нуля
                scanf("%d", &temp);
                if (temp < 0 || temp >= cur_size_mails)
                {
                    printf("Такое сообщение отсутствует\n");
                }
                else
                {
                    for (int i = 0; i < cur_size_mails; i++)//все это делается в такоем виде, если, например, post_id не номер сообщения, а что-то другое
                    {
                        if (post.mails[i].post_id == temp)
                        {
                            for (int j = i; j < cur_size_mails - 1; j++)
                            {
                                post.mails[j] = post.mails[j + 1];
                            }
                            cur_size_mails--;
                        }
                    }
                }
                break;
            case 3:
                printf("Введите номер сообщения(post_id): ");//нумерация начинается с нуля
                scanf("%d", &temp);
                if (temp < 0 || temp >= cur_size_mails)
                {
                    printf("Такое сообщение отсутствует\n");
                }
                else
                {
                    for (int i = 0; i < cur_size_mails; i++)
                    {
                        if (post.mails[i].post_id == temp)
                        {
                            printf("post_id | weight | city | street | house | flat | index\n");
                            printf("%d | %d | %s | %s | %d | %d | %d\n", post.mails[i].post_id, post.mails[i].weight,
                                   post.mails[i].address.city, post.mails[i].address. street, post.mails[i].address.num_house,
                                   post.mails[i].address.num_flat, post.mails[i].address.index);
                            break;
                        }
                    }
                }
                break;
            case 4:
                printf("post_id | weight | city | street | house | flat | index\n");
                for (int i = 0; i < cur_size_mails; i++)
                {
                    printf("%d | %d | %s | %s | %d | %d | %d\n", post.mails[i].post_id, post.mails[i].weight,
                           post.mails[i].address.city, post.mails[i].address. street, post.mails[i].address.num_house,
                           post.mails[i].address.num_flat, post.mails[i].address.index);
                }
                break;
            case 5:

                qsort(post.mails, cur_size_mails, sizeof(Mail), compare_index);
                break;
            case 6:
                qsort(post.mails, cur_size_mails, sizeof(Mail), compare_post_id);

                break;
            case -1:
                //сделать очистку памяти
                for (int i = 0; i < cur_size_mails; i++)
                {
                    //free(&post.mails[i].address);
                    free(post.mails[i].address.city);
                    free(post.mails[i].address.street);
                }
                //
                free(post.mails);
                //free(&post.address);
                free(post.address.city);
                free(post.address.street);
                return 0;
        }
    }
    //сделать очистку памяти
    //.......
    return 0;
}
