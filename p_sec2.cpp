#include <stdio.h>
#include <climits>
/*
// goal : 1.	Declare a pointer to an integer, assign it the address of a variable, and print the value using dereferencing.
// int var = 24;
// int* ptr = &var;
// printf ("%d\n", *ptr);
//goal : 2.	What happens if you dereference a NULL pointer? Write code and observe the result.

// int* ptr2 = NULL;
// printf ("%d", *ptr2);

// goal : 3.	Create an integer array and access its elements using pointers (no [] operator).
// int arr[] = { 1,2,55,6,74,11 };
// int* arrptr = &arr[0];
// for (int i = 0; i < (sizeof (arr) / sizeof (arr[0])); i++) {
    //     printf ("%d\n", *arrptr);
//     arrptr++;
// }

// goal: 3.	Create an integer array and access its elements using pointers (no[] operator).
// int arr[] = { 1,2,55,6,74,11 };
// int* arrptr = &arr[0];
// swap (&arr[1], &arr[5]);
// for (int i = 0; i < (sizeof (arr) / sizeof (arr[0])); i++) {
//     printf ("%d\n", *arrptr);
//     arrptr++;
// }

//goal: 5.	Declare a pointer to a pointer (int **p) and print values at each level. 🧩 Section 1: Pointer Basics (Level 1)

// int var = 69;
// int* ptr = &var;
// int** ptr2 = &ptr;

// printf ("%X\n", ptr2);
// printf ("%X\n", *ptr2);
// printf ("%d\n", **ptr2);

//goal: 11.	Use const int *p, int *const p, and const int *const p — show which one allows modifying data or address.

// const int var1 = 69;
// int var2 = 852;

// const int* ptr = &var1;
// int* ptr2 = (int*)&var1;
// printf ("%d\n", *ptr);
// *ptr2 = 52;
// printf ("%d\n", *ptr2);

//goal:12.	Write code to print the size of a pointer for int, char, float, and struct.

// int a = 2;
// float b = 4.5;
// double c = 9.6;
// char d = 'a';

// int* ptra = &a;
// float* ptrb = &b;
// double* ptrc = &c;
// char* ptrd = &d;


// printf ("%d %d %d %d", sizeof (ptra), sizeof (ptrb), sizeof (ptrc), sizeof (ptrd));

//goal : 13.	Show that incrementing a pointer moves by the size of the data type.

// int a = 2;
// float b = 4.5;
// double c = 9.6;
// char d = 'a';

// int* ptra = &a;
// float* ptrb = &b;
// double* ptrc = &c;
// char* ptrd = &d;

// printf ("%d %d %d %d\n", (ptra), (ptrb), (ptrc), (ptrd));
// ptra++;
// ptrb++;
// ptrc++;
// ptrd++;
// printf ("%d %d %d %d\n", (ptra), (ptrb), (ptrc), (ptrd));

//goal:14.	Print the difference between two pointers pointing into the same array.

// int arr[] = { 4,85,2,4,9,3,1,4 };
// int* pt1 = &arr[0];
// int* pt2 = &arr[5];
// printf ("%d\n", pt2);
// printf ("%d\n", pt1);
// printf ("%d\n", pt2 - pt1);

// goal: 15.	Demonstrate pointer aliasing (two pointers pointing to the same variable).


// const int var1 = 69;
// int var2 = 852;

// const int* ptr = &var1;
// int* ptr2 = (int*)&var1;
// printf ("%d\n", *ptr);
// *ptr2 = 52;
// printf ("%d\n", *ptr2);

void swap (int* p1, int* p2) {
    int var = *p1;
    *p1 = *p2;
    *p2 = var;
}
*/

typedef struct {
    int classroom;
    int bus;
    int teachers;
    int admin;
}school_t;

int reverse (int* pstart, int* pend) {
    if (pstart == NULL || pend == NULL)return -1;

    while (pstart < pend) {
        int tmp = *(pstart);
        *(pstart++) = *(pend);
        *(pend--) = tmp;
    }
    return 0;
}
int  sumarr (const int* ptr, int size, long long* osum) {
    if (size <= 0)return -1;
    if (ptr == NULL)return -1;
    long long sum = 0LL;
    while (size--) {
        if (sum >= LLONG_MAX - *ptr)return -2;
        sum += *ptr++;
    }
    *osum = sum;
    return 0;

}

int copyarr (const int* pa, int* pb, int size) {
    if (pa == NULL || pb == NULL || size <= 0)return -1;

    while (size--) {
        *pb++ = *pa++;
    }
    return 0;
}
int main () {
    //gcc -Wall -Wextra -Werror -Wpedantic -fmax-errors=1 -O0 p.c -o p && ./p

    freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);
    /*
    //goal: 16.	Write code to print the 3rd element of an array using *(arr + 2) syntax.
    // int arr[] = { 5,98,6,5,42,6,3 };
    // int* ptr = arr;
    // printf ("%d\n", *(ptr + 2));

    //goal:17.	Use pointer arithmetic to traverse a character array (string).
    // char st[] = "Pointer Practice";
    // char* ptr = st;

    // // for (int i = 0; i < (sizeof (st) / sizeof (st[0])); i++) {
    // //     printf ("%c ", *ptr++);
    // // }
    // while (*ptr) {
    //     printf ("%c", *ptr++);
    // }
    // printf ("\n");

    //goal:18.	Reverse an integer array using pointer arithmetic (no indexing).

    // int arr[10] = { 5,8,6,1,2,7,8,3,9,11 };
    // int flag = reverse (&arr[0], &arr[5]);
    // int* ptr = arr;
    // for (int i = 0; i < (sizeof (arr) / sizeof (arr[0])); i++) {
    //     printf ("%d ", *ptr++);
    // }
    // printf ("\n");
    // flag < 0 ? printf ("Failed") : printf ("Done");

    //goal:19.	Create a function that takes a pointer to array and its size, and returns the sum of elements.
    // int arr[10] = { 5,8,6,1,2,7,8,3,9,11 };
    // long long osum = 0;
    // int flag = sumarr (&arr[0], 10, &osum);
    // printf ("\n");
    // flag < 0LL ? printf ("Failed") : printf ("%lld", osum);

    //goal: 20.	Write code to compare addresses of consecutive array elements using pointer increment.

    // int arr[10] = { 5,8,6,1,2,7,8,3,9,11 };
    // int* ptr = arr;
    // int* prev = ptr;
    // for (int i = 0; i < (sizeof (arr) / sizeof (arr[0])); i++) {
        //     printf ("%p  ", ptr++);
        //     i != 0 ? printf ("%td ", ptr - prev) : printf ("0 ");
        //     prev = ptr;
    // }
    // printf ("\n");

    */

    // goal:21.	Use pointer subtraction to find how many elements apart two pointers are.

    // int arr[10] = { 5,8,6,1,2,7,8,3,9,11 };
    // int* ps = &arr[5], * pd = &arr[8];
    // printf ("%td \n", (pd - ps));


    // goal:22.	Write code to increment a pointer to structure and access next structure in array.

    // school_t uv[5];
    // uv[0].admin = 3;
    // uv[1].admin = -5;
    // uv[2].admin = 10;
    // uv[3].admin = 69;
    // uv[4].admin = -1;

    // school_t* sptr = &uv[0];
    // // printf ("%d \n", (*sptr++).admin);
    // // printf ("%d \n", (*sptr++).admin);
    // // printf ("%d \n", (*sptr++).admin);
    // // printf ("%d \n", (*sptr++).admin);
    // // printf ("%d \n", (*sptr).admin);

    // printf ("%d \n", (sptr++)->admin);
    // printf ("%d \n", (sptr++)->admin);
    // printf ("%d \n", (sptr++)->admin);
    // printf ("%d \n", (sptr++)->admin);
    // printf ("%d \n", (sptr)->admin);


    // goal:23.	Demonstrate how pointer arithmetic behaves differently for char* and int*.

    // int var[2] = { 29,-2 };
    // char c[2] = { 43, -9 };

    // int* pint = &var[0];
    // char* pchar = &c[0];
    // printf ("%p ", pint);
    // printf ("%p\n", pchar);
    // pint += 1;
    // pchar += 1;
    // printf ("%p ", pint);
    // printf ("%p\n", pchar);

    //goal:24.	Create a function that copies one array into another using pointers only.

    // int a[10] = { 8,4,6,2,1,3,5,7,9,5 }, b[10];
    // int* pa = &a[0], * pb = &b[0];
    // int flag = copyarr (pa, pb, 10);
    // if (flag != -1) {
    //     int* ptr = b;
    //     for (int i = 0; i < (sizeof (b) / sizeof (b[0])); i++) {
    //         printf ("%d ", *ptr++);
    //     }
    // } else {
    //     printf ("Failed");
    // }


    //goal:25.	Write code to traverse a 2D array using a single pointer.

    // int i = 10, j = 10;
    // int arr[i][j] = {
    //     {1,2,3,4,5,6,7,8,9,10},
    //     {11,12,13,14,15,16,17,18,19,20},
    //     {21,22,23,24,25,26,27,28,29,30},
    //     {31,32,33,34,35,36,37,38,39,40},
    //     {41,42,43,44,45,46,47,48,49,50},
    //     {51,52,53,54,55,56,57,58,59,60},
    //     {61,62,63,64,65,66,67,68,69,70},
    //     {71,72,73,74,75,76,77,78,79,80},
    //     {81,82,83,84,85,86,87,88,89,90},
    //     {91,92,93,94,95,96,97,98,99,100},
    // };
    // int* ptr = &arr[0][0];
    // for (int a = 0; a < (i); a++) {
    //     for (int b = 0; b < (j); b++) {
    //         printf ("%d ", *ptr++);
    //     }
    //     printf ("\n");
    // }


    return 0;
}