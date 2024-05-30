#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>


 //Function that returns the bigger number out of 2 given numbers.

int max_number(int a , int b){
    if(a>=b){
       return a;
    }else{
        return b;
    }
}


// Function that generates and prints lobsters and their specific attributes randomly.
// The maximum size and value a lobster can have is given by the user.
void generate_and_print_lobsters(int sizes[], int values[], int no_lobsters) {
    int max_size, max_value;

    printf("Input maximum size range: \n");
    scanf("%d", &max_size);
    printf("Input maximum value range: \n");
    scanf("%d", &max_value);
    printf("*** Lobsters ***\n");

    for (int i = 0; i < no_lobsters; i++) {
        sizes[i] = rand() % (max_size + 1);
        values[i] = rand() % (max_value + 1);
        printf("Lobster no.%d: size %d, value %d\n", i + 1, sizes[i], values[i]);
    }
}

// Function that calculates the maximum value that can be obtained in the net
// and prints the maximum value.

void dp_lobsters(int net_capacity, int sizes[], int values[], int no_lobsters, int* dp[]) {

    for (int i = 0; i <= no_lobsters; i++) {        //This line searches for every lobster.
        for (int s = 0; s <= net_capacity; s++) {      //This line searches for all the possible sizes until it reaches the current lobster's size.
            if (i == 0 || s == 0) {                 //If either the size or the lobster has no value , then the respective cell will be null.
                dp[i][s] = 0;
            } else if (sizes[i - 1] <= s) {         //If the size iterator reaches the current lobster's size , we verify if the lobster can be added
                dp[i][s] = max_number(values[i - 1] + dp[i - 1][s - sizes[i - 1]], dp[i - 1][s]);             //and if it is worth being added comparing it with
            } else {                                                                                   //the elements already existing in the net.
                dp[i][s] = dp[i - 1][s];            //If the iterator has not reached the current lobster's size , the same row from the previous column
            }                                       //is copied.
        }
    }

    printf("Maximum value in net = %d\n", dp[no_lobsters][net_capacity]);
}

main() {
    int no_lobsters, net_capacity;
    clock_t start,end;

    printf("Input the size of the net: \n");            //Input of the net's capacity and the number of lobsters.
    scanf("%d", &net_capacity);
    printf("Input the number of lobsters: \n");
    scanf("%d", &no_lobsters);

    int *sizes = (int *)malloc(no_lobsters * sizeof(int));          //Memory allocation.
    int *values = (int *)malloc(no_lobsters * sizeof(int));
    int *dp[no_lobsters+1];
    for(int i = 0; i <= no_lobsters; i++){
        dp[i] = (int *)malloc(net_capacity * sizeof(int));
    }

    if (sizes == NULL || values == NULL) {          //Verifies if the memory allocation was done.
        printf("Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));  // Initialize random seed

    generate_and_print_lobsters(sizes, values, no_lobsters);            //Generation and printing of the lobsters using the random seed.
    start = clock();
    dp_lobsters(net_capacity, sizes, values, no_lobsters, dp);                 //Calculation of the maximum value that can be obtained in the net.
    end = clock();
    double cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC;      //Calculation of run time.
    printf("\nRun time: %lf",cpu_time_used);                                      //Prints the run time.

    free(sizes);                //Memory deallocation.
    free(values);
    free(dp);

    return 0;
}
