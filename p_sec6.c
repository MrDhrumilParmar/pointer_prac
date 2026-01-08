#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>


#define P_FAIL  (printf("Failed\n"))

int main () {
    //gcc -Wall -Wextra -Werror -Wpedantic -fmax-errors=1 -O0 p.c -o p && ./p

    freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);



    // Section 6: Advanced Pointer Scenarios (Level 6)

    // goal : 57.	Implement a small dynamic memory manager using pointer arithmetic in a static array.


    // goal : 58.	Write code to find misaligned pointer addresses and align them to 4 - byte boundaries.


    // goal : 59.	Simulate DMA buffer access using double pointer (pointer to buffer pointer).


    // goal : 60.	Write a pointer - based implementation of a circular queue.


    // goal : 61.	Show pointer casting issues : cast int* to char* and print byte - level view.


    // goal : 62.	Demonstrate undefined behavior of incrementing a pointer beyond array bounds.


    // goal : 63.	Create function to reverse bytes of an integer using a char* pointer (endianness check).


    // goal : 64.	Implement simple memmove () using pointer arithmetic that works for overlapping buffers.


    // goal : 65.	Create uint8_t * ptr = (uint8_t*)&some_uint32; and access individual bytes to simulate register byte access.


    // goal : 66.	Use pointers to simulate ISR (Interrupt Service Routine) vector table (array of function pointers).


    return 0;
}