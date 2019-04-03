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

////Don't touch this
//typedef struct OS_Memory {
//    void* data;
//    size_t size_of_data;
//
//    size_t size_of_stack;
//    void* stack_pointer;
//    void* start_of_stack;
//
//} OS_Memory;


/* Initialize a memory object passed to the structure, retuns 0 if success 1 if failure.
 * *Note*: All data must be the multiple of overhead_size (16 bytes on 64bit systems). If it is less, than it will be rounded up */
int initialize_memory(OS_Memory* memory, size_t stack_size){
    size_t temp;
    if (stack_size%overhead_size != 0) {
        temp = ((stack_size/overhead_size) + 1)*overhead_size;
    }
    else{
        temp = stack_size;
    }
    
    memory->data = (void*)malloc(temp);
    memory->size_of_data = temp;
    memory->size_of_stack = temp;
    memory->start_of_stack = memory->data;
    memory->stack_pointer = memory->data;
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
    size_t temp;
    if (size%overhead_size != 0) {
        temp = ((size/overhead_size) + 1)*overhead_size;
    }
    else{
        temp = size;
    }
    // THIS IS (sorta) WRONG!!!!!!!
    if((temp + overhead_size) > memory->size_of_stack){
        return 0;
    } else{
        memory->size_of_stack -= (temp + overhead_size);
    }
    
    if(memory->stack_pointer == memory->start_of_stack){
        add_element(memory->stack_pointer, temp, 0);
    }
    else{
        void* temp_ptr = memory->stack_pointer;
        temp_ptr -= overhead_size;
        add_element(temp_ptr, temp, temp_ptr);
    }
    //memory->stack_pointer += (temp + overhead_size);
    
    
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
    
    return 0;
}

void add_element(void* stack_ptr, size_t size, void* ptr){
    // You start at the end of the assigned data
    
    // Add size to data at current point
    size_t* temp_int = (size_t*)stack_ptr;
    *temp_int = size;
    
    // Move forward by size of size_t
    void* temp_ptr = (void*)(stack_ptr + sizet_size);
    
    // Add ptr to data at current point
    memcpy(temp_ptr, ptr, sizeof(void*));
    
    // Done?
    // or add return to return new stack_ptr??? (I dont think this is best)
    
}


void remove_element(void* stack_ptr){
    
}
