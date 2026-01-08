#include <stdio.h>
#include <climits>


#define SIZE 100
static unsigned char buff[SIZE];
static int used_byte = 0;
void* my_malloc (const int size) {
    if (used_byte + size > SIZE)
        return NULL;
    void* ret = &buff[used_byte];
    used_byte += size;
    return ret;
}


int calAvg (const int* pa, const int size, int* avg) {
    if (pa == NULL || avg == NULL || size <= 0)return -1;

    int sum = 0, si = size;
    while (si--) {
        if (sum >= INT_MAX - *pa)return -2;
        sum += *pa++;
    }
    *avg = (sum / size);
    return 0;
}
int swapptr (int** p1, int** p2) {
    if (p1 == NULL || p2 == NULL || *p1 == NULL || *p2 == NULL)return -1;
    int* tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
    return 0;
}
int add_by_val (int v1, int v2) {
    return v1 + v2;
}
int add_by_ref (int* p1, int* p2, int* sum) {
    if (p1 == NULL || p2 == NULL || sum == NULL)return -1;
    *sum = *p1 + *p2;
    return 0;
}
int fx (int** p2) {
    if (p2 == NULL || *p2 == NULL)return -1;
    **p2 = 5;
    return 0;
}
void my_hw (void) {
    printf ("Hello World");
}
void fx1 (void) { printf ("hello 1\n"); }
void fx2 (void) { printf ("hello 2\n"); }
void fx3 (void) { printf ("hello 3\n"); }

int fx4 (void (*fx)(void)) {
    if (fx == NULL)return -1;
    (*fx)();
    return 0;
}

void scheduler (void (*fxn)(void)) {
    //do scheduler stuff;

    fxn ();
}
void blick_led (void) {
    printf ("LED is Blinking");
    int i = 100;
    while (i--)printf (".");
    return;
}
int my_memcpy (void* dest, const void* src, const int size) {

    if (dest == NULL || src == NULL || size <= 0)return-1;
    unsigned char* d = (unsigned char*)dest;
    unsigned char* s = (unsigned char*)src;
    int si = size;
    while (si--) {
        *d++ = *s++;
    }

    return 0;
}
int main () {
    //gcc -Wall -Wextra -Werror -Wpedantic -fmax-errors=1 -O0 p.c -o p && ./p

    freopen ("input.txt", "r", stdin);
    freopen ("output.txt", "w", stdout);


    //goal:26.	Pass an array to a function using a pointer and calculate average.

    // int a[10] = { 5,9,8,6,4,7,3,2,1,21 };
    // int* pa = &a[0];
    // int avg = 0;
    // int flag = calAvg (pa, 10, &avg);
    // printf ("%d \n", avg);

    //goal:27.	Implement a function to swap two pointers (swap pointer values, not data).

    // int v1 = 93;
    // int v2 = -5;
    // int* p1 = &v1;
    // int* p2 = &v2;
    // printf ("%d %d \n", *p1, *p2);
    // int flag = swapptr (&p1, &p2);
    // if (flag >= 0) {
    //     printf ("%d %d \n", *p1, *p2);
    // }
    //goal:28.	Demonstrate difference between “passing by pointer” and “passing by value”.

    // int v1 = 93;
    // int v2 = -5;
    // int addval = add_by_val (v1, v2);
    // int addref = 0;
    // int flag = add_by_ref (&v1, &v2, &addref);
    // if (flag >= 0) {
    //     printf ("%d %d \n", addval, addref);
    // } else {
    //     printf ("Failed");
    // }

    //goal:29.	Write a function that takes a pointer to a pointer to modify the caller pointer.

    // int v = 50;
    // int* p1 = &v;
    // int** p2 = &p1;

    // printf ("%d \n", v);
    // fx (p2);
    // printf ("%d \n", v);

    //goal:30.	Write code to simulate malloc behavior using static arrays and pointer arithmetic.
    // int* p1 = (int*)my_malloc (sizeof (int));
    // float* p2 = (float*)my_malloc (sizeof (float));
    // *p1 = 5;
    // *p2 = 2.5f;
    // printf ("%d %f \n", *p1, *p2);

    //goal:31.	Demonstrate function pointer declaration, assignment, and calling a function through it.

    // void (*fxn_ptr)(void);
    // fxn_ptr = my_hw;
    // (*fxn_ptr) (); //or fxn_ptr();

    //goal:32.	Write a program where you store multiple function addresses in an array of function pointers.

    // int i = 3;
    // void (*pt[i])(void);

    // pt[0] = fx1;
    // pt[1] = fx2;
    // pt[2] = fx3;

    // while (i--) {
    //     pt[i] ();
    // }

    //goal:33.	Pass a function pointer as an argument to another function.

    void (*fxn) (void) = fx3;
    int flag = fx4 (fxn);
    if (flag < 0) { printf ("Failed"); }

    //goal:34.	Write a small callback example (e.g., pass pointer to blink_led () to a scheduler).

    // void (*pblick_led)(void) = blick_led;
    // scheduler (pblick_led);

    //goal:35.	Implement your own memcpy () using pointer arithmetic.

    // int src[10] = { 8,3,2,10,1,5,9,4,7,4 };
    // int dest[10] = { 0 };
    // int flag = my_memcpy (dest, src, 4 * sizeof (int));
    // if (flag >= 0) {
    //     int* ptr = dest;
    //     for (int i = 0; i < (sizeof (dest) / sizeof (dest[0])); i++) {
    //         printf ("%d ", *ptr++);
    //     }
    //     printf ("\n");
    // } else {
    //     printf ("Failed");
    // }

    return 0;
}