//
//  MemoryTests.c
//  Lab02
//
//  Created by Aaron David Block on 1/29/19.
//  Copyright © 2019 Aaron David Block. All rights reserved.
//

#include "MemoryTests.h"
#include "ACMemory.h"
#include <assert.h>
#include <stdio.h>


// Code to include Macro for printing debug code. So, we can unclutter our test.
#ifndef DEBUGGER_PRINTER
#define DEBUGGER_PRINTER

//DEBUG_LEVEL 0 means no comments
//DEBUG_LEVEL 1 means no Start and stop defined
//DEBUG_LEVEL 2 means All comments are on
#define DEBUG_LEVEL 1


#if DEBUG_LEVEL <= 0
    #define DEBUG_PRINT(fmt, args...)
    #define TEST_NAME
    #define TEST_PASSED
#else
    // __func__ is part of C that gets the method name that we're currently in. 
    #define TEST_START printf("\\/ \\/ \\/ \\/ \t Running %s \t\\/ \\/ \\/ \\/\n", __func__);
    #define TEST_PASSED printf("/\\ /\\ /\\ /\\ \t %s passed! \t/\\ /\\ /\\ /\\\n\n", __func__);
    #if DEBUG_LEVEL >= 2
        #define DEBUG_PRINT(fmt, args...) fprintf(stderr, fmt, ##args)
    #else
        #define DEBUG_PRINT(fmt, args...)
    #endif
#endif

#endif


enum Month {
    Jan, Feb, March, April, May, June, July, Aug, Sep, Nov, Dec
};

struct date {
    int year;
    enum Month month;
    int day;
};

int date_eq(struct date d1, struct date d2){
    if (d1.year==d2.year && d1.month==d2.month && d1.year == d2.year){
        return 1;
    } else {
        return 0;
    }
}


void basic_stack_test(){
    TEST_START
    OS_Memory memory;
    
    initialize_memory(&memory, 100);
    char a = 'a';
    char b = 'b';
    char c = 'c';
    char d = 'd';
    
    char* rtnData;
    
    push_bytes(&memory, &a, sizeof(char));
    rtnData = get_bytes(&memory);
    DEBUG_PRINT("The value is %c\n", *rtnData);
    assert(*rtnData == 'a'&& "Cannot push data\n");
    
    push_bytes(&memory,&b, sizeof(char));
    rtnData = get_bytes(&memory);
    DEBUG_PRINT("The value is %c\n", *rtnData);
    assert(*rtnData == 'b'&& "Cannot push data\n");
    
    push_bytes(&memory,&c, sizeof(char));
    rtnData = get_bytes(&memory);
    DEBUG_PRINT("The value is %c\n", *rtnData);
    assert(*rtnData == 'c'&& "Cannot push data\n");
    
    rtnData = (char*)pop_bytes(&memory);
    DEBUG_PRINT("The value is %c\n", *rtnData);
    assert(*rtnData == 'c' && "Cannot pop data\n");
    
    rtnData = (char*)get_bytes(&memory);
    DEBUG_PRINT("The value is %c\n", *rtnData);
    assert(*rtnData == 'b' && "Cannot pop data\n");
    
    push_bytes(&memory,&d, sizeof(char));
    rtnData = get_bytes(&memory);
    DEBUG_PRINT("The value is %c\n", *rtnData);
    assert(*rtnData== 'd' && "Cannot push after pop\n");
    
    rtnData = pop_bytes(&memory);
    DEBUG_PRINT("The value is %c\n", *rtnData);
    assert(*rtnData == 'd'  && "Cannot pop\n");
    
    rtnData = get_bytes(&memory);
    DEBUG_PRINT("The value is %c\n", *rtnData);
    assert(*rtnData == 'b'  && "Cannot get after pop\n");
    
    rtnData = pop_bytes(&memory);
    DEBUG_PRINT("The value is %c\n", *rtnData);
    assert(*rtnData == 'b'  && "Cannot multiple pop\n");
    
    rtnData = get_bytes(&memory);
    DEBUG_PRINT("The value is %c\n", *rtnData);
    assert(*rtnData == 'a'  && "Cannot multiple pop\n");
    
    rtnData = pop_bytes(&memory);
    DEBUG_PRINT("The value is %c\n", *rtnData);
    assert(*rtnData == 'a' && "Cannot pop to bottom\n");
    
    rtnData = get_bytes(&memory);
    DEBUG_PRINT("Pointer value is %p\n", rtnData);
    assert(rtnData == 0  && "Cannot get when empty\n");
    
    rtnData = pop_bytes(&memory);
    DEBUG_PRINT("Pointer value is %p\n", rtnData);
    assert(rtnData == 0  && "Cannot pop when empty\n");
    
    
    free_memory(&memory);
    TEST_PASSED
    
}

void basic_int_test(){
    TEST_START
    OS_Memory memory;
    
    initialize_memory(&memory, 100);
    int a = 11;
    int b = 22;
    int c = 33;
    int rtnInt = -1;
    int* rtnData;
    
    push_bytes(&memory, &a, sizeof(int));
    rtnData = get_bytes(&memory);
    rtnInt = *(int*)rtnData;
    DEBUG_PRINT("The value is %d \n", rtnInt);
    assert(rtnInt == a  && "Cannot push data\n");
    
    push_bytes(&memory,&b, sizeof(int));
    rtnData = get_bytes(&memory);
    rtnInt = *(int*)rtnData;
    DEBUG_PRINT("The value is %d \n", rtnInt);
    assert(rtnInt == b  && "Cannot push data\n");
    
    push_bytes(&memory,&c, sizeof(int));
    rtnData = get_bytes(&memory);
    rtnInt = *(int*)rtnData;
    DEBUG_PRINT("The value is %d \n", rtnInt);
    assert(rtnInt == c  && "Cannot push data\n");
    
    
    rtnData = pop_bytes(&memory);
    rtnInt = *(int*)rtnData;
    DEBUG_PRINT("The value is %d \n", rtnInt);
    assert(rtnInt == c  && "Cannot pop data\n");
    
    rtnData = get_bytes(&memory);
    rtnInt = *(int*)rtnData;
    DEBUG_PRINT("The value is %d \n", rtnInt);
    assert(rtnInt == b  && "Cannot pop data\n");
    
    
    rtnData = pop_bytes(&memory);
    rtnInt = *(int*)rtnData;
    DEBUG_PRINT("The value is %d \n", rtnInt);
    assert(rtnInt == b  && "Cannot pop data\n");
    
    rtnData = get_bytes(&memory);
    rtnInt = *(int*)rtnData;
    DEBUG_PRINT("The value is %d \n", rtnInt);
    assert(rtnInt == a  && "Cannot pop data\n");
    
    free_memory(&memory);
    TEST_PASSED
}

void basic_double_test(){
    TEST_START
    OS_Memory memory;
    
    initialize_memory(&memory, 100);
    double a = 2.0;
    double b = 12.4;
    double c = -35.2;
    double rtn_double = -1;
    double* rtnData;
    
    

    push_bytes(&memory, &a, sizeof(double));
    rtnData = get_bytes(&memory);
    rtn_double = *(double*)rtnData;
    DEBUG_PRINT("The value is %f \n", rtn_double);
    
    //Normally, we shouldn't compare doubles for equality; however, since we are storing the same bits
    //this should be fine.
    assert(rtn_double == a  && "Cannot push data\n");
    
    
    push_bytes(&memory,&b, sizeof(double));
    rtnData = get_bytes(&memory);
    rtn_double = *(double*)rtnData;
    DEBUG_PRINT("The value is %f \n", rtn_double);
    assert(rtn_double == b  && "Cannot push data\n");
    
    
    push_bytes(&memory,&c, sizeof(double));
    rtnData = get_bytes(&memory);
    rtn_double = *(double*)rtnData;
    DEBUG_PRINT("The value is %f \n", rtn_double);
    assert(rtn_double == c  && "Cannot push data\n");
    
    
    rtnData = pop_bytes(&memory);
    rtn_double = *(double*)rtnData;
    DEBUG_PRINT("The value is %f \n", rtn_double);
    assert(rtn_double == c  && "Cannot pop data\n");
    
    rtnData = get_bytes(&memory);
    rtn_double = *(double*)rtnData;
    DEBUG_PRINT("The value is %f \n", rtn_double);
    assert(rtn_double == b  && "Cannot pop data\n");
    
    
    rtnData = pop_bytes(&memory);
    rtn_double = *(double*)rtnData;
    DEBUG_PRINT("The value is %f \n", rtn_double);
    assert(rtn_double == b  && "Cannot pop data\n");
    
    rtnData = get_bytes(&memory);
    rtn_double = *(double*)rtnData;
    DEBUG_PRINT("The value is %f \n", rtn_double);
    assert(rtn_double == a  && "Cannot pop data\n");
    
    free_memory(&memory);
    TEST_PASSED
}

void basic_mixed_test(){
    TEST_START
    OS_Memory memory;
    void* rtnData;
    
    initialize_memory(&memory, 100);
    int a = 11;
    char b = 'd';
    double c = -15.5;
    int rtnInt = 0;
    char rtnChar = 0;
    double rtnDouble = 0;
    
    

    push_bytes(&memory,&a, sizeof(int));
    rtnData = get_bytes(&memory);
    rtnInt = *(int*)rtnData;
    DEBUG_PRINT("The value is %d \n", rtnInt);
    assert(rtnInt == a  && "Cannot push data\n");
    
    

    push_bytes(&memory,&b, sizeof(char));
    rtnData = get_bytes(&memory);
    rtnChar = *(char*)rtnData;
    DEBUG_PRINT("The value is %c \n", rtnChar);
    assert(rtnChar == b  && "Cannot push data\n");
    
    

    push_bytes(&memory,&c, sizeof(double));
    rtnData = get_bytes(&memory);
    rtnDouble = *(double*)rtnData;
    DEBUG_PRINT("The value is %f \n", rtnDouble);
    assert(rtnDouble == c  && "Cannot push data\n");
    
    
    rtnData = pop_bytes(&memory);
    rtnDouble = *(double*)rtnData;
    DEBUG_PRINT("The value is %f \n", rtnDouble);
    assert(rtnDouble == c  && "Cannot pop data\n");
    
    rtnData = get_bytes(&memory);
    rtnChar = *(char*)rtnData;
    DEBUG_PRINT("The value is %c \n", rtnChar);
    assert(rtnChar == b  && "Cannot pop data\n");
    
    
    rtnData = pop_bytes(&memory);
    rtnChar = *(char*)rtnData;
    DEBUG_PRINT("The value is %c \n", rtnChar);
    assert(rtnChar == b  && "Cannot pop data\n");
    
    rtnData = get_bytes(&memory);
    rtnInt = *(int*)rtnData;
    DEBUG_PRINT("The value is %d \n", rtnInt);
    assert(rtnInt == a  && "Cannot pop data\n");
    
    free_memory(&memory);
    TEST_PASSED
}

void basic_struct_test(){
    TEST_START
    OS_Memory memory;
    void* rtnData;
    
    initialize_memory(&memory, 100);
    struct date a;
    a.day = 20;
    a.month = April;
    a.year = 2019;
    
    struct date b;
    b.day = 1;
    b.month = Jan;
    b.year = 2;
    
    struct date c;
    c.day = 31;
    c.month = Dec;
    c.year = 1980;
    
    struct date rtdStruct;
    
    push_bytes(&memory,&a, sizeof(struct date));
    rtnData = get_bytes(&memory);
    rtdStruct = *(struct date*)rtnData;
    assert(date_eq(rtdStruct, a) && "Cannot push data\n");
    
    
    push_bytes(&memory,&b, sizeof(struct date));
    rtnData = get_bytes(&memory);
    rtdStruct = *(struct date*)rtnData;
    assert(date_eq(rtdStruct, b) && "Cannot push data\n");
    

    push_bytes(&memory,&c, sizeof(struct date));
    rtnData = get_bytes(&memory);
    rtdStruct = *(struct date*)rtnData;
    assert(date_eq(rtdStruct, c) && "Cannot push data\n");
    
    
    rtnData = pop_bytes(&memory);
    rtdStruct = *(struct date*)rtnData;
    assert(date_eq(rtdStruct, c) && "Cannot pop data\n");
    
    rtnData = get_bytes(&memory);
    rtdStruct = *(struct date*)rtnData;
    assert(date_eq(rtdStruct, b) && "Cannot pop data\n");
    
    
    rtnData = pop_bytes(&memory);
    rtdStruct = *(struct date*)rtnData;
    assert(date_eq(rtdStruct, b) && "Cannot pop data\n");
    
    rtnData = get_bytes(&memory);
    rtdStruct = *(struct date*)rtnData;
    assert(date_eq(rtdStruct, a) && "Cannot pop data\n");
    
    free_memory(&memory);
    DEBUG_PRINT("Passed basic_struct_test \n");
    TEST_PASSED
}
