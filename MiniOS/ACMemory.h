//
//  Memory420.h
//  Lab02
//
//  Created by Aaron David Block on 1/28/19.
//  Copyright © 2019 Aaron David Block. All rights reserved.
//

#ifndef ACMemory_h
#define ACMemory_h
//Chars and bytes are interchangable in C, but this will make our code read easier



#include <stdlib.h>

#define byte char

/* To declare a global variable you need to declare it in the header using extern
 * then in the implementation file you need to include it's acutal declearation
 */
extern const size_t sizet_size; //Defined to be sizeof(size_t) in implementation file
extern const size_t overhead_size; //Defined to be sizeof(void*) + sizet_size in implementation file

//Don't touch this
typedef struct OS_Memory {
    void* data;
    size_t size_of_data;
    
    size_t size_of_stack;
    void* stack_pointer;
    void* start_of_stack;
    
} OS_Memory;




/* Initialize a memory object passed to the structure, retuns 0 if success 1 if failure.
 * *Note*: All data must be the multiple of overhead_size (16 bytes on 64bit systems). If it is less, than it will be rounded up */
int initialize_memory(OS_Memory* memory, size_t stack_size);


/* frees the memory allocated */
void free_memory(OS_Memory* memory);


/* Pushes the data in bytes onto the stack and returns a pointer to the data's location
 * returns 0 if there is a failure.
 */
void* push_bytes(OS_Memory* memory, void* data, size_t size);



/* Returns a pointer to the top element on the stack, 0 if there is a failure */

void* get_bytes(OS_Memory* memory);


/* Pops off top value from stack.
 * Returns pointer to the popped element, 0 if there is an error.
 * While Pointer is *removed* from the stack, it still lives in memory for a short time. Therefore, if you want to use this data you should immediatly copy it to a more persistant data location since the next push will destroy the data.
 */
void* pop_bytes(OS_Memory* memory);

/* Adds the overhead information to the list
 * stack_ptr is the location to put the information
 * size is the size of the new data
 * ptr is the pointer to the last element of the stack
 */
void add_element(void* stack_ptr, size_t size, void** ptr);



#endif /* Memory420_h */
