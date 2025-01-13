#ifndef FILE_OPS_H
#define FILE_OPS_H

#include "train.h"
#include "material.h"

void save_train_status_to_file(const Train *train, const char *filename);
Train* load_train_status_from_file(const char *filename, MaterialType *materials[]);

#endif