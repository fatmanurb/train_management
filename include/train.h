#ifndef TRAIN_H
#define TRAIN_H

#include "wagon.h"

typedef struct Train {
    char train_id[20];
    Wagon *first_wagon;
    int wagon_count;
} Train;

Train* create_train(const char *train_id);
void add_wagon(Train *train);
void remove_empty_wagon(Train *train, Wagon *wagon);
void display_train_status(const Train *train);
void free_train(Train *train);

#endif


