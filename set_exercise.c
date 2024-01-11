#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHMAP_SIZE 4
#define HASHMAP_SIZE_LIST 3

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

typedef struct set_item
{
    const char* key;
    size_t key_len;
}
set_item; 

typedef struct set_item_pokemon
{
    const pokemon* key;
    size_t key_len;
}
set_item_pokemon;

typedef struct aiv_set
{
    set_item map[HASHMAP_SIZE][HASHMAP_SIZE_LIST];
}
aiv_set;

typedef struct aiv_set_pokemon
{
    set_item_pokemon map[HASHMAP_SIZE][HASHMAP_SIZE_LIST];
}
aiv_set_pokemon;

size_t djb33x_hash(const char *key, const size_t key_len)
{
    size_t hash = 5381;

    for (size_t i = 0; i < key_len; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

// EXERCISE SEARCH
set_item* aiv_find_set(struct aiv_set *set, const char* string)
{
    const size_t key_len = strlen(string);
    const size_t hash = djb33x_hash(string, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (int i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if ( set->map[index][i].key_len == key_len && strcmp(set->map[index][i].key, string) == 0)
        {
            return &(set->map[index][i]);
        }
    }

    
    return NULL;
};

// INSERT AND UNIQUE KEYS
void aiv_set_insert(struct aiv_set *set, const char *key)
{
    if (aiv_find_set(set,key) != NULL)
    {
        printf("{%s} already exists\n",key);
        return;
    }

    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->map[index][i].key_len == 0)
        {
            set->map[index][i].key = key;
            set->map[index][i].key_len = key_len;
           //printf("Added %s at index %llu slot %llu \n", key, index, i);
            return;
        }
    }
    printf("COLLISION! for %s (index = %llu)\n", key, index);     
}

#pragma region test insert_pokemon
// void aiv_set_insert_pokemon(struct aiv_set *set, const pokemon *key)
// {
//     const size_t key_len = strlen(key);
//     const size_t hash = djb33x_hash(key->name, key_len);

//     const size_t index = hash % HASHMAP_SIZE;

//     for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
//     {
//         if (set->map[index][i].key_len == 0)
//         {
//             set->map[index][i].key = key;
//             set->map[index][i].key_len = key_len;
//             printf("Added %s at index %llu slot %llu \n", key->name, index, i);
//             return;
//         }
//     }
//     printf("COLLISION! for %s (index = %llu)\n", key, index);     
// }
#pragma endregion

void print_set(aiv_set *set)
{

    for (int i = 0; i < HASHMAP_SIZE; i++)
    {
        for (int x = 0; x < HASHMAP_SIZE_LIST; x++)
        {
            if (set->map[i][x].key != NULL)
            {
                printf("[%s]", set->map[i][x].key);
            }
            else
            {
                printf("[]");
            }
            
        }
        printf("\n");
    }
}

void print_set_pokemon(aiv_set_pokemon *set)
{

    for (int i = 0; i < HASHMAP_SIZE; i++)
    {
        for (int x = 0; x < HASHMAP_SIZE_LIST; x++)
        {
            if (set->map[i][x].key != NULL)
            {
                printf("[%s]", set->map[i][x].key->name);
            }
            else
            {
                printf("[]");
            }
            
        }
        printf("\n");
    }
}

int main_pokemon()
{

    aiv_set_pokemon first_set;
    memset(&first_set, 0, sizeof(aiv_set));

    pokemon *pikachu = NULL; 
    pokemon *bulbasaur = NULL; 
    pokemon *charmender = NULL; 
    pokemon *squirtle = NULL; 
    //
    pikachu = malloc(sizeof(pokemon));
    pikachu->name = "Pikachu";
    pikachu->type=ELECTRIC;
    pikachu->number=25;
    pikachu->height=.4f;

    bulbasaur = malloc(sizeof(pokemon));
    bulbasaur->name = "Bulbasaur";
    bulbasaur->type = GRASS;
    bulbasaur->number = 1;
    bulbasaur->height = .7f;

    charmender = malloc(sizeof(pokemon));
    charmender->name = "Charmender";
    charmender->type = FIRE;
    charmender->number = 4;
    charmender->height = .6f;

    squirtle = malloc(sizeof(pokemon));
    squirtle->name = "Squirtle";
    squirtle->type = WATER;
    squirtle->number = 7;
    squirtle->height = .5f;



    // aiv_set_insert_pokemon(&first_set, pikachu);
    // aiv_set_insert_pokemon(&first_set, bulbasaur);
    // aiv_set_insert_pokemon(&first_set, charmender);
    // aiv_set_insert_pokemon(&first_set, squirtle);
    

    print_set_pokemon(&first_set);

    return 0;
}

void main_string()
{
    aiv_set first_set;
    memset(&first_set, 0, sizeof(aiv_set));
    char* test_find = "Pikachu";

    aiv_set_insert(&first_set,"Chikorita");
    aiv_set_insert(&first_set,"Cindaquil");
    aiv_set_insert(&first_set,"Totodile");
    aiv_set_insert(&first_set,"Feraligator");
    aiv_set_insert(&first_set,"Megagnum");
    aiv_set_insert(&first_set,"Shaukle");
    aiv_set_insert(&first_set,"Shaukle");

    set_item* temp = aiv_find_set(&first_set,test_find);
    if(temp)
    {
        printf("{%s} FOUND!\n", temp->key);
    }else
    {
        printf("Item %s not found\n", test_find);
    }
    print_set(&first_set);
}

int main()
{
    main_string();

    return 0;
}