#ifndef MATERIAL_H
#define MATERIAL_H

typedef struct MaterialType {
    char name[50];
    float weight;
    int quantity;
    int loaded;
} MaterialType;

typedef struct LoadedMaterial {
    MaterialType *type;
    int quantity;
    struct LoadedMaterial *next, *prev;
} LoadedMaterial;

MaterialType* create_material(const char *name, float weight, int quantity);
void display_material_status(const MaterialType *material);
void free_material(MaterialType *material);

#endif
