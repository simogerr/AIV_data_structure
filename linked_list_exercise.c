#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define LIST_APPEND(list, d) list_append((struct list_node **)&list, (struct list_node *)int_item_new(d)); 

struct list_node
{
    struct list_node *next;
};

struct list_node *list_get_tail(struct list_node *head)
{
    struct list_node *current_node = head;
    struct list_node *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}

struct list_node *list_append(struct list_node **head, struct list_node *item)
{
    struct list_node *tail = list_get_tail(*head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->next = NULL;
    return item;
}

struct list_node *list_pop(struct list_node **head)
{
    struct list_node *current_head = *head;
    if (!current_head)
    {
        return NULL;
    }
    *head = (*head)->next;
    current_head->next = NULL;
    return current_head;
}

struct string_item
{
    struct list_node node;
    const char *string;
};

struct string_item *string_item_new(const char *string)
{
    struct string_item *item = malloc(sizeof(struct string_item));
    if (!item)
    {
        return NULL;
    }
    item->string = string;
    return item;
}

struct int_item
{
    struct list_node node;
    int number;
};

struct int_item *int_item_new(const int number)
{
    struct int_item *item = malloc(sizeof(struct int_item));
    if(!item)
    {
        return NULL;
    }
    item->number = number;
    return item;
}

struct list_node *remove_node(struct list_node **head, const int number)
{
    /*
    EXERCISE REMOVE NODE:

    */

    if (number == 0)
    {
        return (list_pop(head));
    }
    struct list_node *current_node = (*head)->next;
    struct list_node *prev_node = *head;

    for(int i = 1; i < number; i++ )
    {
        prev_node = current_node;
        current_node = current_node->next;

        if (!current_node)
        {
            printf("Number out of range\n");
            return NULL;
        }
    }
    
    prev_node->next = current_node->next;
    return current_node;
 
};

#define TEST(a,b) a->b // use of extera macro

int main()
{
    struct int_item *my_int_list = NULL;
    // list_append((struct list_node **)&my_int_list, (struct list_node *)int_item_new(1));
    // list_append((struct list_node **)&my_int_list, (struct list_node *)int_item_new(2));
    // list_append((struct list_node **)&my_int_list, (struct list_node *)int_item_new(3));
    // list_append((struct list_node **)&my_int_list, (struct list_node *)int_item_new(4));
    // list_append((struct list_node **)&my_int_list, (struct list_node *)int_item_new(5));

    /*
        EXERCISE:
        Use macros to reduce verbose code
    */
    LIST_APPEND(my_int_list,1)
    LIST_APPEND(my_int_list,2)
    LIST_APPEND(my_int_list,3)
    LIST_APPEND(my_int_list,4)
    LIST_APPEND(my_int_list,5)
    struct int_item *int_item = my_int_list;
    
    while (int_item)
    {
        printf("%d\n", TEST(int_item,number));
        int_item = (struct int_item *)int_item->node.next;
    }

    // list_pop((struct list_node **)&(my_int_list->node.next));
    remove_node((struct list_node **)&(my_int_list),4);
    int_item = my_int_list;

    while (int_item)
    {
        printf("%d\n", int_item->number);
        int_item = (struct int_item *)int_item->node.next;
    }

    return 0;
}
