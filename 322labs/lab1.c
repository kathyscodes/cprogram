#include <stdio.h>
#include <stdlib.h>


int num_process;


struct node1 {
    int process;
    struct node1 *link;
};

typedef struct node1 linked_list_type;

struct node2 {
    int parent;
    linked_list_type *children;
    
} *pcb = NULL;

typedef struct node2 pcb_type;


void printprocess() {
    linked_list_type *next;
    for(int i = 0; i < num_process; i++) {
        if ((pcb[i].parent != -1) && (pcb[i].children != NULL)) {
            printf("PCB [%d] is the parent of: ",i);
            next = pcb[i].children;
            while (next != NULL) {
                printf("PCB[%d] ", next->process);
                next = next->link;
            }
        }
        printf("\n");
    }
}

void OPTION1 () {
    printf("Enter the maximum number of processes: ");
    scanf("%d", &num_process);
    pcb = malloc(num_process *sizeof(pcb_type)); //allocate memory
     
    pcb[0].parent = 0;      //define pcb[0]
    pcb[0].children=NULL;
    for (int i = 1; i < num_process;i++) {
        pcb[i].parent = -1;
        
        
    }
  return;  //end with return
}

void OPTION2(){
    int p;
    int q = 0;
    linked_list_type  *new_child, *next;
    printf("Enter the parent process index: ");
    scanf("%d", &p);
    
    while (pcb[q].parent != -1)
    { 
        
       q++;
         }
         
         
    new_child = (linked_list_type*)malloc(sizeof(linked_list_type));
    new_child->process = q ;
    new_child->link = NULL ;
    pcb[q].parent = p;
    pcb[q].children = NULL;
    if (pcb[p].children == NULL) {            //if empty children, then fill it
        pcb[p].children = new_child;
    }
    else {
        next = pcb[p].children;
        while (next->link != NULL) {
            next = next->link;
        }
    next->link = new_child;
    }
    printprocess();
    return;
}

void destroychildren(linked_list_type *node) {
    if (node == NULL) {                 //check if end of link-list, then return
        return;
    }
    else {
        destroychildren(node->link);
        int q = node->process;
        destroychildren(pcb[q].children);
        free(node); 
        pcb[q].parent = -1;
        node = NULL;
    }
    return;
}

/* OPTION 3 */
void OPTION3() {
    int p;
    printf("Enter the index of the process whose descendants are to be destroyed: ");
    scanf("%d", &p);
    destroychildren(pcb[p].children);
    pcb[p].children = NULL;   
    printprocess();//reset to null
   return;
}

/* OPTION 4 */
void OPTION4() {
    if (pcb != NULL) {
        if (pcb[0].children != NULL) {
            destroychildren(pcb[0].children);
        }
        free(pcb);
    }
    printf("Quiting program....");
}


int main() {
    int choice;
    while(choice != 4) {
        printf("\nProcess creation and destruction \n");
        printf("------------------------------ \n"); 
        printf("1) Enter parameters \n");
        printf("2) Create a new child process \n");
        printf("3) Destroy all descendants of a process \n"); 
        printf("4) Quit program and free memory \n");
        printf("\n ENTER SELECTION: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: OPTION1(); break;
            case 2: OPTION2(); break;
            case 3: OPTION3(); break;
            case 4: OPTION4(); break;
           
        }
    }
    return 1;                //indicate success
}







