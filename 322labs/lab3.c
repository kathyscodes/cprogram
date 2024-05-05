#include <stdio.h>

#include <stdlib.h>

// Declare dynamic arrays as global variables

int *resource = NULL; // Resource vector

int *available = NULL; // Available vector

int *maxclaim = NULL; // Max claims array

int *allocation = NULL; // Allocation array

int *need = NULL; // Need array

int num_processes; // stores number of processes

int num_resources; // stores number of resources

// Function to print items of resource vector

void print_resources() {

printf("\tUnits \tAvailable \n");
printf("--------------------------------\n");



for (int i = 0; i < num_resources; i++)
{
printf("r%d\t%d\t%d", i,resource[i],available[i]);

printf("\n");
}


}


void printmatrix() {

printf("\tMax claim\t\tCurrent\t\tPotential \n");


for (int c = 0; c < num_resources; c++)
{
printf("\tr%d", c); // print r0, r1, ...


}
for (int c = 0; c < num_resources; c++)
{
printf("\tr%d", c); // print r0, r1, ...


}
for (int c = 0; c < num_resources; c++)
{
printf("\tr%d", c); // print r0, r1, ...


}
printf("\n-------------------------------------------------------------------\n");
for (int i = 0; i < num_processes; i++) {

printf("\np%d\t", i); // print p0, p2, ...

// Iterate through number of resources

for (int j = 0; j < num_resources; j++)
{
printf("%d\t", maxclaim[i * num_resources + j]); // print (i*num_resources+j)th value

}

for (int j = 0; j < num_resources; j++)
{
    
printf("%d\t", allocation[i * num_resources + j]);
}

for (int j = 0; j < num_resources; j++)
{
printf("%d\t", need[i * num_resources + j]);
}
}
}


void option1() {

printf("Enter number of processes: ");

scanf("%d", &num_processes);

printf("Enter number of resources: ");

scanf("%d", &num_resources);

// memory allocation for all vectors and arrays

resource = (int *) malloc(num_resources * sizeof(int)); // allocate memory to resource vector

available = (int *) malloc(num_resources * sizeof(int)); // allocate memory to available vector

maxclaim = (int *) malloc(num_processes * num_resources * sizeof(int)); // allocate memory to maxclaim array

allocation = (int *) malloc(num_processes * num_resources * sizeof(int)); // allocate memory to allocation array

need = (int *) malloc(num_processes * num_resources * sizeof(int)); // allocate memory to need array

int units;

// Prompt for the number of units for each resource, then set the resource and available arrays indices

printf("Enter number of units for resources (r%d to r%d): ", 0, num_resources - 1);

for (int i = 0; i < num_resources; i++) { // for each process

scanf("%d", &units); // read input

resource[i] = units; // set resource array value

available[i] = units; // set available array value

}

// Prompt for the maximum amount of units sought by the process for each process and resource.

// maxclaim and need arrays will be updated.

for (int i = 0; i < num_processes; i++) { // for each process

// prompt user

printf("Enter maximum number of units process p%d will request from each resource (r%d to r%d): ", i, 0, num_resources - 1);

for (int j = 0; j < num_resources; j++) { // for each resource

scanf("%d", & units); // read user input

// update maxclaim and need arrays

maxclaim[i * num_resources + j] = units;

need[i * num_resources + j] = units;

}

}

  

// Prompt for the quantity of resource units allocated to each process and resource for each process.

for (int i = 0; i < num_processes; i++) { // for each process

printf("Enter number of units of each resource (r%d to r%d) allocated to process p%d: ", 0, num_resources - 1, i);

for (int j = 0; j < num_resources; j++) { // for each resource

scanf("%d", & units); // read user input

// update allocation, need, and available arrays

allocation[i * num_resources + j] = units;

need[i * num_resources + j] -= units;

available[j] -= units;

}

}

  



print_resources(); 

printmatrix(); 

printf("\n"); // print new line

}

// Function to perform Banker's algorithm and determine safe sequence

void option2() {

// declare variables

int count_sequenced = 0;

int less_than;

  

// create a vector that stores if process is safely sequenced

int *sequenced = (int *) calloc(num_processes, sizeof(int)); // allocate memory and initialize with zero

// run loop until all processes are sequenced

while (count_sequenced < num_processes) {

for (int i = 0; i < num_processes; i++) { // for each process

less_than = 1;

if (sequenced[i] == 0) { // if the process hasn't been sequenced in a safe manner

printf("Checking: < ");

for (int j = 0; j < num_resources; j++) // for each resource

printf(" %d", need[i * num_resources + j]); // print need array

printf(" > <= < ");

// print available array

for (int j = 0; j < num_resources; j++)

printf(" %d", available[j]);

printf(" > ");

// By comparing the need vector to the available vector,

// we can ensure that the sequence is safe.

for (int j = 0; j < num_resources; j++) {

less_than &= (need[i * num_resources + j] <= available[j]);

}

// Update the number of resource units available if each resource is available

if (less_than == 1) {

  

// display processes that has been safely sequenced

printf(" :p%d safely sequenced", i);

sequenced[i] = 1;

count_sequenced++;

// for each resource

for (int j = 0; j < num_resources; j++) {

// free all the resources allocated to the process

available[j] += allocation[i * num_resources + j];

allocation[i *num_resources + j] = 0;

need[i *num_resources + j] = maxclaim[i *num_resources + j];

}

  

}
else
printf(" :p%d could not be sequenced", i);
printf("\n");

}

}

}

printf("\n");

free(sequenced);

}

// Function deallocate all allocated memory

void option3() {

// free memory for all arrays

if (maxclaim != NULL)

free(maxclaim);

}

// Driver function

int main() {

int ch; // for storing user choice/option

// run loop until user choose to quit the program

do {

// display menu

printf("\nBanker's Algorithm\n");

printf("--------------------------------\n");

printf("1) Enter parameters\n");

printf("2) Determine safe sequence\n");

printf("3) Quit program and free memory\n");

// ask user to enter an option

printf("\nEnter selection: ");

scanf("%d", & ch);

// do as per user choice

switch (ch) {

case 1: // 1) Enter parameters

option1();

break;

case 2: // 2) Determine safe sequence

option2();

break;

case 3: // 3) Quit program and free memory

printf("Quitting program...\n");

option3();

break;



}

} while (ch != 3);

return 0;

}





