#include <curses.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
 
//создание связного списка
typedef struct node{
    int value;
    struct node *next;
    struct node *prev;
} node_t;
 
//распечатка связного списка
void print_list(node_t *head, int index)
{
    node_t * current = head;
    for (int i = 0; i < index-1; ++i)
    {
        current = current->next;
    }
    printf("%d\n", current->value);
}
 
//добавление элемента в конец списка
void append(node_t *head, int num)
{
    node_t *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
 
    current->next = malloc(sizeof(node_t));
    current->next->value=num;
    current->next->next=NULL;
    current->next->prev=current;
}
 
//добавление элемента в начало спичка
void push(node_t *head, int num)
{
    node_t *current = head;
    node_t *node = head;
    node_t *first_node = head;
    node_t *second_node=head;
 
    int i = 0;
    while(current->next != NULL)
    {
        current = current->next;
        i += 1;
    }
   
    if (i < 1)
    {
        node->next = malloc(sizeof(node_t));
        node->next->value=num;
        node->next->next=NULL;
        node->next->prev=node;
    }
    else
    {
        second_node=second_node->next;
        node->next = malloc(sizeof(node_t));
        node->next->value=num;
        first_node->next = node->next;// предыдущий узел указывает на создаваемый
        second_node->prev = node->next;
        node->next->next=second_node;// созданный узел указывает на следующий элемент
        node->next->prev=first_node;
    }
   
}
 
//определение длины списка, считает количество узлов
int length(node_t *head)
{
    node_t *current = head;
    int i = 0;
    while (current != NULL)
    {
        current = current->next;
        i += 1;
    }
    return i;
}
 
//удаление узла
int delete(node_t *head, int index)
{
    if (head == NULL)
    {
       return 0;
    }
    node_t *node;
    node_t *prev_node;

   //указатель на первый элемент
    node_t * current = head;
    for (int i = 0; i < index-1; ++i)
    {
        current = current->next;
    }
    node = current->next;
    prev_node = current;
    prev_node->next=node->next;
    free(node);
    return 0;
}
 
//Вставка элемента на определенную позицию в списке
void insert(node_t * head, int index, int num)
{
    if (head == NULL)
        append(head, num);
    else
    {
        //указатель на первый элемент
        node_t * current = head;
        for (int i = 0; i < index-1; ++i)
        {
            current = current->next;
        }
        push(current, num);
    }
}
 
//обновление value списка
void update_node(node_t *head, int index, int num)
{
    if (head == NULL)
        append(head, num);
    else
    {
        //указатель на первый элемент
        node_t * current = head;
        for (int i = 0; i < index-1; ++i)
        {
            current = current->next;
        }
        current->value=num;
    }
}
 
int main()
{
    // пример использования этой функции
    node_t *head = NULL;
    head = malloc(sizeof(node_t));
 
    srand(time(NULL));
    int creates = 0;
    int deletes = 0;
    for (int i = 0; i < 10000; ++i)
    {
        int operation = rand()%6;
        operation += 1;
        int quantity = rand()%100;
     
     //Добавление элемента в начало списка
        if (operation == 1)
            for (int i = 0; i < quantity; ++i)
            {
                int x = rand()%10000-5000;
                append(head, x);
                creates += 1;
            }

        //Добавление элемента по индексу
        if (operation == 2)
            for (int i = 1; i <= quantity; ++i)
            {
                int x = rand()%10000-5000;
                int index = i;
                insert(head, index, x);
                creates += 1;
            }
            
        //Добавление элемента в начало списка
        if (operation == 3)
            for (int i = 0; i < quantity; ++i)
            {
                int x = rand()%10000-5000;
                push(head, x);
                creates += 1;
            }
     
        //delete
        if (operation == 4)
            for (int i = 0; i < quantity; ++i)
            {
              int len = length(head);
              uint index = rand()%len-5000;
         
              if (len != 1)
              {
                     delete(head, index);
                  deletes+=1;
                }
            }

        //read
         if (operation == 5)
          for (int i = 0; i < quantity; ++i)
          {
            int len = length(head);
              uint index = rand()%len-5000;
                print_list(head, index);
          }
 
        //update
        if (operation == 6)
            for (int i = 0; i < quantity; ++i)
            {
                int len = length(head);
              uint index = rand()%len-5000;
                int value = rand()%10000-5000;
                update_node(head, index, value);
            }
    }
    printf("creates %d\n", creates);
    printf("deletes %d\n", deletes);
    return 0;
 
}
