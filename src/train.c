#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train.h"

Train* create_train(const char *train_id) {
    Train *train = (Train *)malloc(sizeof(Train));
    if (!train) {
        fprintf(stderr, "Memory allocation failed for train\n");
        return NULL;
    }
    strcpy(train->train_id, train_id);
    train->first_wagon = NULL;
    train->wagon_count = 0;
    return train;
}

void add_wagon(Train *train) {
    Wagon *new_wagon = create_wagon(train->wagon_count + 1);
    if (!train->first_wagon) {
        train->first_wagon = new_wagon;
    } else {
        Wagon *last = train->first_wagon;
        while (last->next) last = last->next;
        last->next = new_wagon;
        new_wagon->prev = last;
    }
    train->wagon_count++;
}

void remove_empty_wagon(Train *train, Wagon *wagon) {
    if (!wagon) return;

    if (wagon->prev) wagon->prev->next = wagon->next;
    if (wagon->next) wagon->next->prev = wagon->prev;
    if (wagon == train->first_wagon) train->first_wagon = wagon->next;

    free_wagon(wagon);
    train->wagon_count--;
}

void display_train_status(const Train *train) {
    printf("Train ID: %s\n", train->train_id);
    printf("Wagons: %d\n", train->wagon_count);
    Wagon *current = train->first_wagon;
    while (current) {
        display_wagon_status(current);
        current = current->next;
    }
}

void free_train(Train *train) {
    Wagon *current = train->first_wagon;
    while (current) {
        Wagon *next = current->next;
        free_wagon(current);
        current = next;
    }
    free(train);
}
