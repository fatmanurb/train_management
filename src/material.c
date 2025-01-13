#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "material.h"

MaterialType* create_material(const char *name, float weight, int quantity) {
    MaterialType *material = (MaterialType *)malloc(sizeof(MaterialType));
    if (!material) {
        fprintf(stderr, "Memory allocation failed for material\n");
        return NULL;
    }
    strcpy(material->name, name);
    material->weight = weight;
    material->quantity = quantity;
    material->loaded = 0;
    return material;
}

void display_material_status(const MaterialType *material) {
    printf("Material: %s\n", material->name);
    printf("Weight: %.2f kg\n", material->weight);
    printf("Available: %d units\n", material->quantity);
    printf("Loaded: %d units\n", material->loaded);
}

void free_material(MaterialType *material) {
    if (material) free(material);
}
