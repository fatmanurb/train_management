#ifndef WAGON_H
#define WAGON_H

#include "material.h"

typedef struct Wagon {
    int wagon_id;
    float max_weight;
    float current_weight;
    LoadedMaterial *loaded_materials;
    struct Wagon *next, *prev;
} Wagon;

Wagon* create_wagon(int wagon_id);
void load_material_to_wagon(Wagon *wagon, MaterialType *material, int quantity);
void unload_material_from_wagon(Wagon *wagon, MaterialType *material, int quantity);
void display_wagon_status(const Wagon *wagon);
void free_wagon(Wagon *wagon);

#endif
