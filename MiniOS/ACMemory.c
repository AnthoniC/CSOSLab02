//
//  Memory420.c
//  Lab02
//
//  Created by Aaron David Block on 1/28/19.
//  Copyright © 2019 Aaron David Block. All rights reserved.
//

#include "ACMemory.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

const size_t sizet_size = sizeof(size_t);
const size_t overhead_size = sizeof(void*) + sizet_size;


/* Initialize a memory object passed to the structure, retuns 0 if success 1 if failure.
 * *Note*: All data must be the multiple of overhead_size (16 bytes on 64bit systems). If it is less, than it will be rounded up */
int initialize_memory(OS_Memory* memory, size_t stack_size){
    // Checks to see if size is a multiple of overhead_size
    // If it is then temp is set to size, if it isn't size is rounded up and assigned to temp
    size_t temp;
    if (stack_size%overhead_size != 0) {
        temp = ((stack_size/overhead_size) + 1)*overhead_size;
    }
    else{
        temp = stack_size;
    }
    
    // Allocate memory for data and set memory's variables
    memory->data = (void*)malloc(temp);
    memory->size_of_data = temp;
    memory->size_of_stack = temp;
    memory->start_of_stack = memory->data;
    memory->stack_pointer = memory->data;
    
    // Check to see if memort->stack_pointer exists
    if (memory->stack_pointer != NULL) {
        return 0;
    }
    else{
        return 1;
    }
}


/* frees the memory allocated */
void free_memory(OS_Memory* memory){
    free(memory->data);
}


/* Pushes the data in bytes onto the stack and returns a pointer to the data's location
 * returns 0 if there is a failure.
 */
void* push_bytes(OS_Memory* memory, void* data, size_t size){
    // Checks to see if size is a multiple of overhead_size
    // If it is then temp is set to size, if it isn't size is rounded up and assigned to temp
    size_t temp;
    if (size%overhead_size != 0) {
        temp = ((size/overhead_size) + 1)*overhead_size;
    }
    else{
        temp = size;
    }

    // Check to see if there is enough room for data, if not return 0
    if((temp + overhead_size) > memory->size_of_stack){
        return 0;
    } else{
        // If there is enough room change the size_of_stack to match
        memory->size_of_stack -= (temp + overhead_size);
    }
    
    // Add the overhead information for the new data
    if(memory->stack_pointer == memory->start_of_stack){
        add_element(memory->stack_pointer, temp, &memory->start_of_stack);
        memory->stack_pointer += overhead_size;
    }
    else{
        void* temp_ptr = memory->stack_pointer;
        temp_ptr -= overhead_size;
        size_t* last_element_size = (size_t*)temp_ptr;
        temp_ptr += overhead_size;
        add_element((temp_ptr + *last_element_size), temp, &temp_ptr);
        temp_ptr += *last_element_size;
        temp_ptr += overhead_size;
        memcpy(temp_ptr, data, size);
        memory->stack_pointer = temp_ptr;
    }
    // Copy the data from data into the stack
    memcpy(memory->stack_pointer, data, size);
    
    return memory->stack_pointer;
}



/* Returns a pointer to the top element on the stack, 0 if there is a failure */
void* get_bytes(OS_Memory* memory){
    if(memory->stack_pointer == memory->start_of_stack){
        return 0;
    }
    return memory->stack_pointer;
}


/* Pops off top value from stack.
 * Returns pointer to the popped element, 0 if there is an error.
 * While Pointer is *removed* from the stack, it still lives in memory for a short time. Therefore, if you want to use this data you should immediatly copy it to a more persistant data location since the next push will destroy the data.
 */
void* pop_bytes(OS_Memory* memory){
    // Check to see if the list is empty, if it is return 0
    if(memory->stack_pointer == memory->start_of_stack){
        return 0;
    }
    
    // set return value
    void* to_return = memory->stack_pointer;
    
    // Set memory->stack_pointer to the previous data point on the stack
    void** last_ptr = (void**)malloc(sizeof(void*));
    void* temp = memory->stack_pointer;
    temp -= sizeof(void*);
    memcpy(last_ptr, temp, sizeof(void*));
    memory->stack_pointer = *last_ptr;
    
    // Add the size back into memory->size_of_stack
    temp -= sizet_size;
    int* size = (int*)temp;
    memory->size_of_stack += (*size + overhead_size);
    
    return to_return;
}

/* Adds the overhead information to the list
 * stack_ptr is the location to put the information
 * size is the size of the new data
 * ptr is the pointer to the last element of the stack
 */
void add_element(void* stack_ptr, size_t size, void** ptr){
    
    size_t* temp_int = (size_t*)stack_ptr;
    *temp_int = size;
    void* temp_ptr = (void*)(stack_ptr + sizet_size);
    memcpy(temp_ptr, ptr, sizeof(void*));
    
    void** thingy = (void**)malloc(sizeof(void*));
    memcpy(thingy, temp_ptr, sizeof(void*));
}

