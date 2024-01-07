#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

struct AIV_node
{
    struct AIV_node *prev;
    struct AIV_node *next;
};
typedef struct AIV_node aiv_node;

struct int_node
{
    aiv_node node;
    int value;
};
typedef struct int_node int_node;

typedef enum pokemon_type
{
    FIRE,
    WATER,
    GRASS,
    ELECTRIC
}
pokemon_type;

typedef struct pokemon
{
    char* name;
    pokemon_type type;
    int number;
    float height;
}
pokemon;

typedef struct pkmn_node
{
    aiv_node node; 
    pokemon pokemon;
}
pokemon_node;

struct head_pointer
{
    struct AIV_node *node;
    char *description;
    int counter;
};

aiv_node *list_get_tail(struct head_pointer *head)
{
    aiv_node *current_node = head->node;
    aiv_node *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}

aiv_node *list_append(struct head_pointer *head, aiv_node *item)
{
    aiv_node *tail = list_get_tail(head);
    if (!tail)
    {
        head->node = item;
        
    }
    else
    {
        tail->next = item;
    }
    head->counter +=1;
    item->prev = tail;
    item->next = NULL;
    return item;
}

#pragma region PRINT_FUNCTION
//PRINT FUNCTIOTN

void print_int_list(struct head_pointer *head)
{
    aiv_node *curr_item = head->node;
    printf("name: %s\n", head->description);
    printf("count: %d\n", head->counter);
    while (curr_item)
    {
        printf("[%d]", ((int_node*)curr_item)->value);
        curr_item = curr_item->next;
    }
    printf("\n");
    
}


void print_pokemon_list(struct head_pointer *head)
{
    aiv_node *curr_node = head->node;
    printf("name: %s\n", head->description);
    printf("count: %d\n", head->counter);
    while (curr_node)
    {
        pokemon *curr_pokemon = &(((pokemon_node*)curr_node)->pokemon);
        printf("[%d] %s \n", curr_pokemon->number, curr_pokemon->name);
        curr_node = curr_node->next;
    }
    printf("\n");
}

#pragma endregion 

aiv_node *get_item_list(struct head_pointer *head, const int number)
{
    
    if (number<0 || number>= head->counter)
    {
        printf("Error: number not valid \n");
        return NULL;
    }
    
    aiv_node *item_to_return = head->node;
    for (int i = 0; i < number; i++)
    {
        item_to_return = item_to_return->next;
    }

    return item_to_return;

}

aiv_node *remove_item(struct head_pointer* head, const int number)
{
    aiv_node *item_to_remove = NULL;
    if (number < 0 || number >= head->counter)
    {
        printf("Error\n ");
        return NULL;
    }
    if (number==0)
    {
        item_to_remove = head->node;
        head->node = item_to_remove->next;
        head->node->prev = NULL;
        item_to_remove->next = NULL;
    }
    else
    {
        item_to_remove = get_item_list(head, number);

        item_to_remove->prev->next = item_to_remove->next;
        if (item_to_remove->next)
        {
            item_to_remove->next->prev = item_to_remove->prev;
        }
        
    }
    
    head->counter--;
    return item_to_remove;
}

aiv_node *insert_after(struct head_pointer *head, aiv_node *node_to_add, const int number)
{
     if (number < 0 || number >= head->counter)
    {
        printf("Error\n ");
        return NULL;
    }

    // aiv_node *item_before = get_item_list(head, number);
    aiv_node *item_before = get_item_list(head, number); 
    
    node_to_add->next = item_before->next;
    node_to_add->prev = item_before;
    
    item_before->next = node_to_add;

    if (node_to_add->next)
    {
        node_to_add->next->prev = node_to_add;
    }

    head->counter ++;
    return node_to_add;
    
}

aiv_node *insert_before(struct head_pointer *head, aiv_node *node_to_add, const int number)
{
    aiv_node *item_after = get_item_list(head, number); 
     if (!item_after)
    {
        printf("Error\n ");
        return NULL;
    }
   
    node_to_add->next = item_after;
    node_to_add->prev = item_after->prev;
    
    item_after->prev = node_to_add;

    if (node_to_add->prev)
    {
        node_to_add->prev->next = node_to_add;
    }else
    {
        head->node = node_to_add;
    }

    head->counter ++;
    return node_to_add;
    
}


int main()
{
    int_node *first_element = NULL;
    int_node *second_element = NULL;
    int_node *third_element = NULL;

    first_element = malloc(sizeof(int_node));
    second_element = malloc(sizeof(int_node));
    third_element = malloc(sizeof(int_node));

    // first_element->next = second_element; // HEAP firsty element si trova nell'heap perchè malloc lo crea li
    // second_element->next = third_element;
    // third_element->next = NULL;

    // first_element->prev = NULL;
    // second_element->prev = first_element;
    // third_element->prev = second_element;

    // head_list_node = first_element;
    // head_list_node->counter = 3;

    struct head_pointer head;
    //head.node = first_element; // STACK perchè head è crata nello stack
    head.node = NULL;
    head.counter = 0;
    head.description = "Number List";
    first_element->value = 100;
    second_element->value = 200;
    third_element->value = 300;

    list_append(&head,(aiv_node*)first_element);
    list_append(&head,(aiv_node*)second_element);
    list_append(&head,(aiv_node*)third_element);

    print_int_list(&head);

    //POKEMON LIST
    pokemon_node *pikachu = NULL; 
    pokemon_node *bulbasaur = NULL; 
    pokemon_node *charmender = NULL; 
    pokemon_node *squirtle = NULL; 

    pikachu = malloc(sizeof(pokemon_node));
    pikachu->pokemon.name = "Pikachu";
    pikachu->pokemon.type=ELECTRIC;
    pikachu->pokemon.number=25;
    pikachu->pokemon.height=.4f;

    bulbasaur = malloc(sizeof(pokemon_node));
    bulbasaur->pokemon.name = "Bulbasaur";
    bulbasaur->pokemon.type = GRASS;
    bulbasaur->pokemon.number = 1;
    bulbasaur->pokemon.height = .7f;

    charmender = malloc(sizeof(pokemon_node));
    charmender->pokemon.name = "Charmender";
    charmender->pokemon.type = FIRE;
    charmender->pokemon.number = 4;
    charmender->pokemon.height = .6f;

    squirtle = malloc(sizeof(pokemon_node));
    squirtle->pokemon.name = "Squirtle";
    squirtle->pokemon.type = WATER;
    squirtle->pokemon.number = 7;
    squirtle->pokemon.height = .5f;

    // head pointer for pokemon list
    struct head_pointer pokemon_head_list;
    //head.node = first_element; // STACK perchè head è crata nello stack
    pokemon_head_list.node = NULL;
    pokemon_head_list.counter = 0;
    pokemon_head_list.description = "Pokemon List";

    list_append(&pokemon_head_list,(aiv_node*)pikachu);
    list_append(&pokemon_head_list,(aiv_node*)bulbasaur);
    list_append(&pokemon_head_list,(aiv_node*)squirtle);
    list_append(&pokemon_head_list,(aiv_node*)charmender);
    print_pokemon_list(&pokemon_head_list);

    //REMOVE ITEM IN POKEMON LIST
    remove_item(&pokemon_head_list, 1);
    remove_item(&pokemon_head_list, 2);
    // remove_item(&pokemon_head_list, 25);
    print_pokemon_list(&pokemon_head_list);

    // INSERT AFTER
    insert_after(&pokemon_head_list,(aiv_node*)bulbasaur,1);
    print_pokemon_list(&pokemon_head_list);

    //INSERT BEFORE
    insert_before(&pokemon_head_list,(aiv_node*)charmender,0);
    print_pokemon_list(&pokemon_head_list);

    return 0;
}