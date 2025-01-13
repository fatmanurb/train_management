#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/train.h"
#include "wagon.h"
#include "material.h"
#include "file_ops.h"
#include "utils.h"

void display_menu() {
    printf("\n=== Train Loading Management System ===\n");
    printf("1. Load train status from file\n");
    printf("2. Load material, starting from head of Train\n");
    printf("3. Load material to specific wagon\n");
    printf("4. Unload material, starting from tail\n");
    printf("5. Unload material from specific wagon\n");
    printf("6. Display train status\n");
    printf("7. Display materials status\n");
    printf("8. Empty train\n");
    printf("9. Save train status to file\n");
    printf("10. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Train *train = create_train("T123");
    MaterialType *materials[3] = {
        create_material("Large Box", 200.0, 50),
        create_material("Medium Box", 150.0, 50),
        create_material("Small Box", 100.0, 50)
    };

    int choice;
    do {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
          
            case 1: {
                char filename[100];
                printf("Enter filename to load train status: ");
                scanf("%s", filename);
                Train *loaded_train = load_train_status_from_file(filename, materials);
                if (loaded_train) {
                    free_train(train); // Clean up the current train
                    train = loaded_train;
                    printf("Train status loaded from file successfully.\n");
                } else {
                    printf("Failed to load train status.\n");
                }
                break;
            }
           
            case 2: {
                int material_index, quantity;
                printf("Select material (0: Large, 1: Medium, 2: Small): ");
                scanf("%d", &material_index);
                if (material_index < 0 || material_index > 2) {
                    printf("Invalid material choice.\n");
                    break;
                }
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                MaterialType *material = materials[material_index];

                Wagon *wagon = train->first_wagon;
                while (quantity > 0 && wagon) {
                    float remaining_capacity = wagon->max_weight - wagon->current_weight;

                    int loadable_quantity = (int)(remaining_capacity / material->weight);

                    if (loadable_quantity > 0) {
                        int to_load = (quantity < loadable_quantity) ? quantity : loadable_quantity;
                        load_material_to_wagon(wagon, material, to_load);
                        quantity -= to_load;
                    }

                    wagon = wagon->next;
                }

                while (quantity > 0) {
                    add_wagon(train);
                    Wagon *new_wagon = train->first_wagon;
                    while (new_wagon->next) new_wagon = new_wagon->next; 

                    float remaining_capacity = new_wagon->max_weight - new_wagon->current_weight;
                    int loadable_quantity = (int)(remaining_capacity / material->weight);

                    if (loadable_quantity > 0) {
                        int to_load = (quantity < loadable_quantity) ? quantity : loadable_quantity;
                        load_material_to_wagon(new_wagon, material, to_load);
                        quantity -= to_load;
                    }
                }

                break;
            }
            case 3: {
                int material_index, quantity, wagon_id;
                printf("Enter Wagon ID: ");
                scanf("%d", &wagon_id);
                Wagon *wagon = train->first_wagon;
                while (wagon && wagon->wagon_id != wagon_id) {
                    wagon = wagon->next;
                }
                if (!wagon) {
                    printf("Wagon not found.\n");
                    break;
                }
                printf("Select material (0: Large, 1: Medium, 2: Small): ");
                scanf("%d", &material_index);
                if (material_index < 0 || material_index > 2) {
                    printf("Invalid material choice.\n");
                    break;
                }
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                load_material_to_wagon(wagon, materials[material_index], quantity);
                break;
            }
            case 4: {
                    int material_index, quantity;
                    printf("Select material to unload (0: Large, 1: Medium, 2: Small): ");
                    scanf("%d", &material_index);
                    if (material_index < 0 || material_index > 2) {
                        printf("Invalid material choice.\n");
                        break;
                    }
                    printf("Enter quantity to unload: ");
                    scanf("%d", &quantity);

                    MaterialType *material = materials[material_index];
                    Wagon *wagon = train->first_wagon;

                    while (wagon && wagon->next) {
                        wagon = wagon->next;
                    }

                    while (wagon && quantity > 0) {
                        int unloadable_quantity = 0;
                        LoadedMaterial *current = wagon->loaded_materials;
                        while (current) {
                            if (current->type == material) {
                                unloadable_quantity = (current->quantity < quantity) ? current->quantity : quantity;
                                unload_material_from_wagon(wagon, material, unloadable_quantity);
                                quantity -= unloadable_quantity;
                                break;
                            }
                            current = current->next;
                        }

                        if (wagon->current_weight == 0) {
                            Wagon *to_remove = wagon;
                            wagon = wagon->prev; 
                            remove_empty_wagon(train, to_remove);
                        } else {
                            wagon = wagon->prev; 
                        }
                    }

                    if (quantity > 0) {
                        printf("Could not unload %d units. Not enough material.\n", quantity);
                    } else {
                        printf("Material unloaded successfully.\n");
                    }
                    break;
                }


            case 5: {
                int material_index, quantity, wagon_id;
                printf("Enter Wagon ID: ");
                scanf("%d", &wagon_id);
                Wagon *wagon = train->first_wagon;
                while (wagon && wagon->wagon_id != wagon_id) {
                    wagon = wagon->next;
                }
                if (!wagon) {
                    printf("Wagon not found.\n");
                    break;
                }
                printf("Select material (0: Large, 1: Medium, 2: Small): ");
                scanf("%d", &material_index);
                if (material_index < 0 || material_index > 2) {
                    printf("Invalid material choice.\n");
                    break;
                }
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                unload_material_from_wagon(wagon, materials[material_index], quantity);
                break;
            }
            case 6: {
                display_train_status(train);
                break;
            }
            case 7: {
                for (int i = 0; i < 3; i++) {
                    display_material_status(materials[i]);
                }
                break;
            }
            case 8: {
                free_train(train);
                train = create_train("T123");
                printf("Train emptied.\n");
                break;
            }
            case 9: {
                char filename[100];
                printf("Enter filename to save train status: ");
                scanf("%s", filename);
                save_train_status_to_file(train, filename);
                break;
            }
            case 10: {
                printf("Exiting program...\n");
                break;
            }
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 10);

    for (int i = 0; i < 3; i++) {
        free_material(materials[i]);
    }
    free_train(train);
    return 0;
}
