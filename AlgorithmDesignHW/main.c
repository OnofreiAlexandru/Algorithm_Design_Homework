#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

 //Function that returns the bigger number out of 2 given numbers.

long max(long a , long b){
    if(a>=b){
       return a;
    }else{
        return b;
    }
}


// Function that generates and prints lobsters and their specific attributes randomly.
// The maximum size and value a lobster can have is given by the user.
void generate_and_print_lobsters(long sizes[], long values[], long no_lobsters) {
    long max_size, max_value;

    printf("Input maximum size range: \n");
    scanf("%ld", &max_size);
    printf("Input maximum value range: \n");
    scanf("%ld", &max_value);
    printf("*** Lobsters ***\n");

    for (long i = 0; i < no_lobsters; i++) {
        sizes[i] = rand() % (max_size + 1);
        values[i] = rand() % (max_value + 1);
        printf("Lobster no.%ld: size %ld, value %ld\n", i + 1, sizes[i], values[i]);
    }
}

// Function that calculates the maximum value that can be obtained in the net
// and prints the maximum value.

void dp_lobsters(long net_capacity, long sizes[], long values[], long no_lobsters, long* dp[]) {

    for (long i = 0; i <= no_lobsters; i++) {        //This line searches for every lobster.
        for (long s = 0; s <= net_capacity; s++) {      //This line searches for all the possible sizes until it reaches the current lobster's size.
            if (i == 0 || s == 0) {                 //If either the size or the lobster has no value , then the respective cell will be null.
                dp[i][s] = 0;
            } else if (sizes[i - 1] <= s) {         //If the size iterator reaches the current lobster's size , we verify if the lobster can be added
                dp[i][s] = max(values[i - 1] + dp[i - 1][s - sizes[i - 1]], dp[i - 1][s]);             //and if it is worth being added comparing it with
            } else {                                                                                   //the elements already existing in the net.
                dp[i][s] = dp[i - 1][s];            //If the iterator has not reached the current lobster's size , the same row from the previous column
            }                                       //is copied.
        }
    }

    printf("Maximum value in net = %ld\n", dp[no_lobsters][net_capacity]);
}

main() {
    long no_lobsters, net_capacity;

    printf("Input the size of the net: \n");            //Input of the net's capacity and the number of lobsters.
    scanf("%d", &net_capacity);
    printf("Input the number of lobsters: \n");
    scanf("%d", &no_lobsters);

    long *sizes = (long *)malloc(no_lobsters * sizeof(long));          //Memory allocation.
    long *values = (long *)malloc(no_lobsters * sizeof(long));
    long *dp[no_lobsters+1];
    for(int i = 0; i <= no_lobsters; i++){
        dp[i] = (long *)malloc(net_capacity * sizeof(long));
    }

    if (sizes == NULL || values == NULL) {          //Verifies if the memory allocation was done.
        printf("Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));  // Initialize random seed

    generate_and_print_lobsters(sizes, values, no_lobsters);               //Generation and printing of the lobsters using the random seed.
    dp_lobsters(net_capacity, sizes, values, no_lobsters, dp);                 //Calculation of the maximum value that can be obtained in the net.

    free(sizes);                //Memory deallocation.
    free(values);
    free(dp);

    return 0;
}
