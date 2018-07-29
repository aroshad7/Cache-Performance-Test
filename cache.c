#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//L1 cache size = 32K
//L2 cache size = 256K
//L3 cache size = 3072K
//b1, b2 = 64


void random_assign(char *bytes, int len){

    for (int i=0; i<len; i++){
        bytes[i] = (u_int8_t)((clock()+i));        //assigning random values based on sys clock
    }

}

void subroutine_a(long test_iterations){
     //Subroutine A
    
    char *bytes_L1;
      
    bytes_L1 = (char *) malloc(2*32*1024);  

    if (!bytes_L1) {
            fprintf(stderr, "Memory allocation failed\n");
            abort();
    }

    random_assign(bytes_L1, 65536);

    double time_used_a = 0;
    clock_t start_a = clock();

    for (int j=0; j<test_iterations; j++){                             //Loop for increasing number of experiments. j was adjusted so that the execution time > 1s
        for (int i=0; i<65536; i++){
            bytes_L1[i] = bytes_L1[i] + 1;
        }
    }

    clock_t end_a = clock();
    time_used_a = ((double)(end_a - start_a));
    time_used_a = time_used_a/CLOCKS_PER_SEC;
    printf("Time taken by Subroutine A: %lf\n", time_used_a);
    float bandWidth_a = (64*test_iterations)/(time_used_a*1024);

    int sum = 0;
    for (int i=0; i<65536; i++){                           
        sum = sum + bytes_L1[i];
    }
    printf("Calculated sum: %d\n\n", sum);


    free(bytes_L1);
}

void subroutine_b(long test_iterations){
    //Subroutine B

    char *bytes_L1;
      
    bytes_L1 = (char *) malloc(2*32*1024);  

    if (!bytes_L1) {
            fprintf(stderr, "Memory allocation failed\n");
            abort();
    }

    random_assign(bytes_L1, 65536);

    double time_used_b = 0;
    clock_t start_b = clock();
    
    for (int j=0; j<test_iterations; j++){                         //Loop for increasing number of experiments. j was adjusted so that the execution time > 1s  
        for (int i=63; i<65536; i=i+64){
            bytes_L1[i] = bytes_L1[i] + 1;
        }
    }

    clock_t end_b = clock();
    time_used_b = ((double)(end_b - start_b));
    time_used_b = time_used_b/CLOCKS_PER_SEC;
    printf("Time taken by Subroutine B: %lf\n", time_used_b);
    float bandWidth_b = (64*test_iterations)/(time_used_b*1024);

    int sum = 0;
    for (int i=0; i<65536; i++){
        sum = sum + bytes_L1[i];
    } 
    printf("Calculated sum: %d\n\n", sum);


    free(bytes_L1);
}

void subroutine_c(long test_iterations){
    //Subroutine C

    char *bytes_L2;
          
    bytes_L2 = (char *) malloc(2*256*1024);  

    if (!bytes_L2) {
            fprintf(stderr, "Memory allocation failed\n");
            abort();
    }

    random_assign(bytes_L2, 524288);

    double time_used_c = 0;
    clock_t start_c = clock();
    
    for (int j=0; j<test_iterations; j++){                          //Loop for increasing number of experiments. j was adjusted so that the execution time > 1s
        for (int i=63; i<524288; i=i+64){
            bytes_L2[i] = bytes_L2[i] + 1;
        }
    }

    clock_t end_c = clock();
    time_used_c = ((double)(end_c - start_c));
    time_used_c = time_used_c/CLOCKS_PER_SEC;
    printf("Time taken by Subroutine C: %lf\n", time_used_c);
    float bandWidth_c = (0.5 * test_iterations)/time_used_c;

    int sum = 0;
    for (int i=0; i<524288; i++){
        sum = sum + bytes_L2[i];
    }
    printf("Calculated sum: %d\n\n", sum);


    free(bytes_L2);
}



int main() {

    subroutine_a(200000);

    subroutine_b(200000*64);

    subroutine_c(200000*8);

    return(0);
}
