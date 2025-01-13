#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_ops.h"
#include "train.h"
#include "wagon.h"
#include "material.h"



void save_train_status_to_file(const Train *train, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Failed to open file for writing: %s\n", filename);
        return;
    }

    fprintf(file, "TRAIN:%s:%d\n", train->train_id, train->wagon_count);

    Wagon *current = train->first_wagon;
    while (current) {
        fprintf(file, "WAGON:%d:%.2f:%.2f\n", current->wagon_id, current->max_weight, current->current_weight);

        LoadedMaterial *mat = current->loaded_materials;
        while (mat) {
            fprintf(file, "L:%s:%d\n", mat->type->name, mat->quantity);
            mat = mat->next;
        }

        current = current->next;
    }

    fclose(file);
    printf("Train status saved to file: %s\n", filename);
}

Train* load_train_status_from_file(const char *filename, MaterialType *materials[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return NULL;
    }

    Train *train = NULL;
    char buffer[256];
    Wagon *current_wagon = NULL;

    while (fgets(buffer, sizeof(buffer), file)) {
        if (strncmp(buffer, "TRAIN:", 6) == 0) {
            char train_id[20];
            int wagon_count;
            sscanf(buffer, "TRAIN:%[^:]:%d", train_id, &wagon_count);
            train = create_train(train_id);
        }
        else if (strncmp(buffer, "WAGON:", 6) == 0) {
            int wagon_id;
            float max_weight, current_weight;
            sscanf(buffer, "WAGON:%d:%f:%f", &wagon_id, &max_weight, &current_weight);

            add_wagon(train);
            current_wagon = train->first_wagon;
            while (current_wagon->next) current_wagon = current_wagon->next; 
            current_wagon->current_weight = current_weight;
        }
        else if (strncmp(buffer, "L:", 2) == 0) {
            char material_name[50];
            int quantity;
            sscanf(buffer, "L:%[^:]:%d", material_name, &quantity);

            MaterialType *material = NULL;
            for (int i = 0; i < 3; i++) {
                if (strcmp(materials[i]->name, material_name) == 0) {
                    material = materials[i];
                    break;
                }
            }

            if (material && current_wagon) {
                LoadedMaterial *new_material = (LoadedMaterial *)malloc(sizeof(LoadedMaterial));
                if (!new_material) {
                    fprintf(stderr, "Memory allocation failed for loaded material\n");
                    fclose(file);
                    return train;
                }
                new_material->type = material;
                new_material->quantity = quantity;
                new_material->next = current_wagon->loaded_materials;
                if (current_wagon->loaded_materials) {
                    current_wagon->loaded_materials->prev = new_material;
                }
                new_material->prev = NULL;
                current_wagon->loaded_materials = new_material;

                material->loaded += quantity;
                material->quantity -= quantity;
            }
        }
    }

    fclose(file);
    return train;
}