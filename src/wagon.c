#include <stdio.h>
#include <stdlib.h>
#include "wagon.h"

Wagon* create_wagon(int wagon_id) {
    Wagon *wagon = (Wagon *)malloc(sizeof(Wagon));
    if (!wagon) {
        fprintf(stderr, "Memory allocation failed for wagon\n");
        return NULL;
    }
    wagon->wagon_id = wagon_id;
    wagon->max_weight = 1000.0;
    wagon->current_weight = 0.0;
    wagon->loaded_materials = NULL;
    wagon->next = NULL;
    wagon->prev = NULL;
    return wagon;
}

void load_material_to_wagon(Wagon *wagon, MaterialType *material, int quantity) {
    if (!wagon || !material || quantity <= 0) return;

    float total_weight = material->weight * quantity;
    if (wagon->current_weight + total_weight > wagon->max_weight) {
        printf("Cannot load material: Exceeds wagon capacity\n");
        return;
    }

    LoadedMaterial *new_material = (LoadedMaterial *)malloc(sizeof(LoadedMaterial));
    if (!new_material) {
        fprintf(stderr, "Memory allocation failed for loaded material\n");
        return;
    }
    new_material->type = material;
    new_material->quantity = quantity;
    new_material->next = wagon->loaded_materials;
    if (wagon->loaded_materials) wagon->loaded_materials->prev = new_material;
    new_material->prev = NULL;
    wagon->loaded_materials = new_material;

    wagon->current_weight += total_weight;
    material->loaded += quantity;
    material->quantity -= quantity;

    printf("Loaded %d %s into Wagon %d\n", quantity, material->name, wagon->wagon_id);
}

void unload_material_from_wagon(Wagon *wagon, MaterialType *material, int quantity) {
    if (!wagon || !material || quantity <= 0) return;

    LoadedMaterial *current = wagon->loaded_materials;
    while (current) {
        if (current->type == material) {
            if (current->quantity < quantity) {
                printf("Cannot unload material: Not enough quantity in Wagon %d\n", wagon->wagon_id);
                return;
            }

            current->quantity -= quantity;
            wagon->current_weight -= material->weight * quantity;
            material->loaded -= quantity;
            material->quantity += quantity;

            printf("Unloaded %d %s from Wagon %d\n", quantity, material->name, wagon->wagon_id);

            if (current->quantity == 0) {
                if (current->prev) current->prev->next = current->next;
                if (current->next) current->next->prev = current->prev;
                if (wagon->loaded_materials == current) wagon->loaded_materials = current->next;
                free(current);
            }
            return;
        }
        current = current->next;
    }
    printf("Material not found in Wagon %d\n", wagon->wagon_id);
}

void display_wagon_status(const Wagon *wagon) {
    printf("Wagon ID: %d\n", wagon->wagon_id);
    printf("Capacity: %.2f / %.2f kg\n", wagon->current_weight, wagon->max_weight);
    LoadedMaterial *current = wagon->loaded_materials;
    while (current) {
        printf(" - %s: %d units\n", current->type->name, current->quantity);
        current = current->next;
    }
}

void free_wagon(Wagon *wagon) {
    if (!wagon) return;

    LoadedMaterial *current = wagon->loaded_materials;
    while (current) {
        LoadedMaterial *next = current->next;
        free(current);
        current = next;
    }
    free(wagon);
}
