#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) 
{
    if(map == NULL || key == NULL) return;  
    long posicion_inicial = hash(key, map->capacity);
    
    for(int i = 0; i < map->capacity; i++)
    {
        long posicion_actual = (posicion_inicial + i) % map->capacity;
        Pair * pair_actual = map->buckets[posicion_actual];

        if(pair_actual == NULL) break;
        if (pair_actual->key != NULL && is_equal(pair_actual->key, key)) 
        {
            return;
        }
    }

    for(int i = 0; i < map->capacity; i++)
    {
        long posicion_actual = (posicion_inicial + i) % map->capacity;
        Pair * pair_actual = map->buckets[posicion_actual];
        
        if (pair_actual == NULL || pair_actual->key == NULL) 
        {
            Pair * nuevo_pair = createPair(strdup(key), value);
            map->buckets[posicion_actual] = nuevo_pair;
            map->size++;
            map->current = posicion_actual;
            return;
        }
    }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) 
{
    HashMap *map = (HashMap *) malloc (sizeof(HashMap));
    if(!map) return NULL;
    map->size = 0;
    map->capacity = capacity;
    map->current = -1;

    map->buckets = (Pair **) malloc(sizeof(Pair *) * capacity);
    for (long i = 0; i < capacity; i++)
    {
        map->buckets[i] = NULL;
    }

    return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) 
{   
    if (map == NULL || key == NULL) return NULL;
    long posicion_inicial = hash(key, map->capacity);
    for (int i = 0; i < map->capacity; i++)
    {
        long posicion_actual = (posicion_inicial + i) % map ->capacity;
        Pair * pair_actual = map->buckets[posicion_actual];
        if (pair_actual == NULL) return NULL;
        if (pair_actual->key != NULL && is_equal(pair_actual->key, key))
        {
            map->current = posicion_actual;
            return pair_actual;
        }
    }
    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
