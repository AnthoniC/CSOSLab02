//
//  main.c
//  MiniOS
//
//  Created by Aaron David Block on 1/31/19.
//  Copyright © 2019 Austin College. All rights reserved.
//

#include <stdio.h>
#include "MemoryTests.h"


int main(int argc, const char * argv[]) {
    
    printf("Starting Tests!\n");


    /* Stack Tests */
    basic_stack_test();
    basic_int_test();
    basic_double_test();
    basic_mixed_test();
    basic_struct_test();

    printf("All Tests passed!\n");
    return 0;
}
