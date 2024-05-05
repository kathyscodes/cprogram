#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
/* declare global variables including a table structure to hold scheduling 
information */
int num_process;  


struct node{
    int id;
    int arrival;
    int total_cpu;
    int done;  //flag
    int already_started;  //flag
    int start_time;
    int end_time;
    int turnaround_time;
    int total_remaining;
    int waiting;
    //int remaining_time;
}*table=NULL;
typedef struct node table_type;

int max (int a, int b) {
if (a>b)
return a;
else
return b;
}
/***************************************************************/
void PrintScheduling() {

    printf("ID\tARRIVAL\tTOTAL\tSTART\tEND\tTURNAROUND\n");
    printf("--------------------------------------------------\n");
    for(int i = 0; i < num_process; i++) {
        printf("%d\t%d\t%d\t", table[i].id, table[i].arrival, table[i].total_cpu);
        if(table[i].done == 1) {
            printf("%d\t%d\t%d", table[i].start_time, table[i].end_time, table[i].turnaround_time);
        }
        printf("\n");
    }
   

return;
}
/***************************************************************/
void OPTION1() {
  printf("ENTER TOTAL NUMBER OF PROCESSES : ");
    scanf("%d", &num_process);
    table = (table_type *)malloc(num_process * sizeof(table_type));
    for(int i = 0; i < num_process; i++) {
        printf("ENTER PROCESS ID : ");
        scanf("%d", &table[i].id);
        printf("ENTER ARRIVAL CYCLE FOR PROCESS P[%d] : ", i + 1);
        scanf("%d", &table[i].arrival);
        printf("ENTER TOTAL CYCLES FOR PROCESS P[%d] : ", i + 1);
        scanf("%d", &table[i].total_cpu);
    }
    printf("\n");
    PrintScheduling();
    printf("\n");
    return;
}
/***************************************************************/
void OPTION2() {
              
int local_num = num_process;
    int early_arrival;
    int current_process;
    int current_cycle = 0;
    for(int i = 0; i < num_process; i++) {
        table[i].done = 0;
    }
    while(local_num != 0) {
        early_arrival = INT_MAX;
        for(int i = 0; i < num_process; i++) {
            if(table[i].done == 0) {
                if(early_arrival > table[i].arrival) {
                    early_arrival = table[i].arrival;
                    current_process = i;
                }
            }
        }
        table[current_process].start_time = max(current_cycle, early_arrival);
        table[current_process].end_time = table[current_process].start_time + table[current_process].total_cpu;
        table[current_process].turnaround_time = table[current_process].end_time - table[current_process].arrival;
        table[current_process].done = 1;
        current_cycle = table[current_process].end_time;
        local_num--;
    }
    printf("\n");
    PrintScheduling();
    printf("\n");
    return;



}
/***************************************************************/
void OPTION3() {
int local_num = num_process;
    int lowest_cpu;
    int current_process;
    int current_cycle = 0;
    for(int i = 0; i < num_process; i++) {
        table[i].done = 0;
    }
    while(local_num != 0) {
        lowest_cpu = INT_MAX;
        for(int i = 0; i < num_process; i++) {
            if(table[i].done == 0) {
                if((lowest_cpu > table[i].total_cpu) && (table[i].arrival <= current_cycle)) {
                    lowest_cpu = table[i].total_cpu;
                    current_process = i;
                }
            }
        }
        table[current_process].start_time = current_cycle;
        table[current_process].end_time = table[current_process].start_time + table[current_process].total_cpu;
        table[current_process].turnaround_time = table[current_process].end_time - table[current_process].arrival;
        table[current_process].done = 1;
        current_cycle = table[current_process].end_time;
        local_num--;
    }
    printf("\n");
    PrintScheduling();
    printf("\n");

return;
}
/***************************************************************/
void OPTION4() {
int local_num = num_process;
    int lowest_remaining;
    int current_process;
    int start_process;
    int current_cycle = 0;
    for(int i = 0; i < num_process; i++) {
        table[i].done = 0;
        table[i].total_remaining = table[i].total_cpu;
        table[i].already_started = 0;
    }
    while(local_num != 0) {
        lowest_remaining = INT_MAX;
        for(int i = 0; i < num_process; i++) {
            if(table[i].done == 0) {
                if((lowest_remaining > table[i].total_remaining) && (table[i].arrival <= current_cycle)) {
                    lowest_remaining = table[i].total_remaining;
                    current_process = i;
                }
            }
        }
        if(table[current_process].already_started == 0) {
            table[current_process].start_time = current_cycle;
            table[current_process].already_started = 1;
        }
        table[current_process].end_time = current_cycle + 1;
        table[current_process].turnaround_time = table[current_process].end_time - table[current_process].arrival;
        current_cycle++;
        table[current_process].total_remaining--;
        if(table[current_process].total_remaining == 0) {
            table[current_process].done = 1;
            local_num--;
        }
    }
    printf("\n");
    PrintScheduling();
    printf("\n");

return;
}
/***************************************************************/
void OPTION5() {
/* free the schedule table if not NULL */
if(table != NULL)
{
free(table);
printf("Quiting program...");
}
return;
}
/***************************************************************/
int main() {
int choice;
    while(choice != 5) {
        printf("\nBatch Scheduling \n");
        printf("--------------------- \n"); 
        printf("1) Enter parameters \n");
        printf("2) Schedule processes with FIFO algorithm \n");
        printf("3) Schedule processes with SJF algorithm \n"); 
        printf("4) Schedule processes with SRT algorithm \n");
        printf("5) Quit and free memory \n");
        printf("\n ENTER SELECTION: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: OPTION1(); break;
            case 2: OPTION2(); break;
            case 3: OPTION3(); break;
            case 4: OPTION4(); break;
            case 5: OPTION5(); break;
           
        }
    }
    return 1;
} 
  /* indicates success */
 /* end of procedure */
















