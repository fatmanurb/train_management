# Train Loading Management System

## Overview
The Train Loading Management System is a C programming project that simulates real-world cargo train logistics. It enables efficient loading and unloading of materials onto train wagons while adhering to stacking and weight distribution rules. The system leverages data structures like doubly linked lists and dynamic memory management for practical problem-solving.

## Features
- Dynamic addition and removal of wagons based on cargo needs.
- Material stacking rules to ensure proper distribution.
- Save and load train statuses to/from files for persistence.
- Comprehensive menu-driven user interface.

## Prerequisites
- *Operating System:* Windows, Linux, or macOS
- *Compiler:* GCC (or any compatible C compiler)
- *Memory:* Minimum 2GB RAM

## Installation
1. Clone the repository:
   bash
   git clone [repository URL]
   
2. Navigate to the project directory:
   bash
   cd train-management
   
3. Compile the project using the Makefile:
   make clear
   make
   
5. Run the program:
   ./train_management
   

## Usage
Once the program is running, use the menu interface to interact with the system:

1. *Load train status from file:* Restore a previously saved train setup.
2. *Load material starting from the head:* Add materials to wagons starting from the first suitable wagon.
3. *Load material to a specific wagon:* Specify a wagon to load materials into.
4. *Unload material starting from the tail:* Remove materials from wagons, starting from the last wagon.
5. *Unload material from a specific wagon:* Specify a wagon to unload materials from.
6. *Display train status:* View details of the train and its wagons.
7. *Display materials status:* View information about available and loaded materials.
8. *Empty train:* Remove all wagons and materials to reset the train.
9. *Save train status to file:* Save the current state of the train to a file.
10. *Exit:* Save the train status and exit the program.

## File Structure

project/
├── src/
│   ├── main.c          # Main program flow
│   ├── train.c         # Train operations
│   ├── wagon.c         # Wagon management
│   ├── material.c      # Material handling
│   ├── file_ops.c      # File operations
│   └── utils.c         # Utility functions
├── include/
│   ├── train.h
│   ├── wagon.h
│   ├── material.h
│   ├── file_ops.h
│   └── utils.h
├── Makefile            # Build instructions
└── README.md           # Documentation


## Example File Format
Here’s an example of a train status file:

TRAIN:T123:3
MATERIALS:3
M:Large Box:Steel:200.00:50:13
M:Medium Box:Aluminium:150.00:50:0
M:Small Box:Wood:100.00:50:0
WAGON:1:1000.00:1000.00
L:Large Box
L:Large Box
WAGON:2:1000.00:1000.00
L:Large Box
L:Large Box
WAGON:3:1000.00:600.00
L:Large Box


## Contribution
1. Fork the repository.
2. Create a feature branch:
   bash
   git checkout -b feature-branch
   
3. Commit your changes:
   bash
   git commit -m "Add new feature"
   
4. Push to the branch:
   bash
   git push origin feature-branch
   
5. Open a pull request.

## License
This project is licensed under the [MIT License](LICENSE).

## Contact
For any questions or feedback, please contact [raydughmsh, fatmanurb].
