/* File:     p2_1.c
 * Author:   Ray Wang
 *
 * Purpose:  Create functions that can find the union, intersection, and
 *           difference of two sets.
 *
 * Input:    ints to be inserted into two linked lists
 * Output:   the union, intersection, or difference of two sets
 *
 * Compile:  gcc -g -Wall -o p2_1 p2_1.c
 * Run:      ./p2_1
 *
 */
#include <stdio.h>
#include <stdlib.h>

struct list_node_s {
    int data;
    struct list_node_s* next_p;
};

struct list_node_s* Insert(struct list_node_s* tail_p, int val);
struct list_node_s* Build(struct list_node_s* head_p);
void Print(struct list_node_s* head_p);
struct list_node_s* Union(struct list_node_s* head_p1,
                          struct list_node_s* head_p2);
struct list_node_s* Intersect(struct list_node_s* head_p1,
                              struct list_node_s* head_p2);
struct list_node_s* Difference(struct list_node_s* head_p1,
                               struct list_node_s* head_p2);
struct list_node_s* Free_list(struct list_node_s* head_p);
char Get_command(void);
int Get_value(void);
void Print_node(char node_name[], struct list_node_s* node_p);

/*-----------------------------------------------------------------*/
int main(void)
{
    char command;
    struct list_node_s* head_p1 = NULL;
    struct list_node_s* head_p2 = NULL;
    struct list_node_s* head_p3 = NULL;
    /* start with empty list */
    
    command = Get_command();
    while (command != 'q' && command != 'Q') {
        
        head_p1 = Build(head_p1);
        head_p2 = Build(head_p2);
        
        switch (command) {
            case 'u':
            case 'U':
                head_p3 = Union(head_p1, head_p2);
                printf("The union between the two sets is: ");
                Print(head_p3);
                break;
                
            case 'i':
            case 'I':
                head_p3 = Intersect(head_p1, head_p2);
                printf("The intersection of the two sets is: ");
                Print(head_p3);
                break;
                
            case 'd':
            case 'D':
                head_p3 = Difference(head_p1, head_p2);
                printf("The difference between the two sets is: ");
                Print(head_p3);
                break;
                
            default:
                printf("There is no %c command\n", command);
                printf("Please try again\n");
        }
        
        head_p1 = Free_list(head_p1);
        head_p2 = Free_list(head_p2);
        head_p3 = Free_list(head_p3);
        
        command = Get_command();
    }
    
    return 0;
} /* main */

/*-----------------------------------------------------------------
 * Function:    Union
 * Purpose:     Finds the union of two sets
 * Input args:  head_p1: pointer to head of list 1
 *              head_p2: pointer to head of list 2
 * Return val:  head_p3: pointer to head of list 3 (union of list 1 and 2)
 */
struct list_node_s* Union(struct list_node_s* head_p1,
                          struct list_node_s* head_p2)
{
    struct list_node_s* curr_p1 = head_p1;
    struct list_node_s* curr_p2 = head_p2;
    struct list_node_s* head_p3 = NULL;
    struct list_node_s* tail_p3 = NULL;
    
    int val;
    
    while (curr_p1 != NULL && curr_p2 != NULL) {
        if (curr_p1->data < curr_p2->data) {
            val = curr_p1->data;
            curr_p1 = curr_p1->next_p;
        }
        else if (curr_p1->data > curr_p2->data) {
            val = curr_p2->data;
            curr_p2 = curr_p2->next_p;
        }
        else {
            val = curr_p1->data;
            curr_p1 = curr_p1->next_p;
            curr_p2 = curr_p2->next_p;
        }
        
        if (head_p3 == NULL) {
            head_p3 = Insert(head_p3, val);
            tail_p3 = head_p3;
        }
        else {
            tail_p3 = Insert(tail_p3, val);
        }
    }
    
    if (curr_p1 != NULL) {
        while (curr_p1 != NULL) {
            val = curr_p1->data;
            
            if (head_p3 == NULL) {
                head_p3 = Insert(head_p3, val);
                tail_p3 = head_p3;
            }
            else {
                tail_p3 = Insert(tail_p3, val);
            }
            
            curr_p1 = curr_p1->next_p;
        }
    }
    else {
        while (curr_p2 != NULL) {
            val = curr_p2->data;
            
            if (head_p3 == NULL) {
                head_p3 = Insert(head_p3, val);
                tail_p3 = head_p3;
            }
            else {
                tail_p3 = Insert(tail_p3, val);
            }
            
            curr_p2 = curr_p2->next_p;
        }
    }
    
    return head_p3;
    
} /* Union */

/*-----------------------------------------------------------------
 * Function:    Intersection
 * Purpose:     Find intersection of two lists
 * Input args:  head_p1: pointer to head of list 1
 *              head_p2: pointer to head of list 2
 * Return val:  head_p3: pointer to head of list 3 (intersection of list 1 and 2)
 */
struct list_node_s* Intersect(struct list_node_s* head_p1,
                              struct list_node_s* head_p2)
{
    struct list_node_s* curr_p1 = head_p1;
    struct list_node_s* curr_p2 = head_p2;
    struct list_node_s* head_p3 = NULL;
    struct list_node_s* tail_p3 = NULL;
    
    int val;
    
    while (curr_p1 != NULL && curr_p2 != NULL) {
        if (curr_p1->data < curr_p2->data) {
            curr_p1 = curr_p1->next_p;
        }
        else if (curr_p1->data > curr_p2->data) {
            curr_p2 = curr_p2->next_p;
        }
        else if (curr_p1->data == curr_p2->data) {
            val = curr_p1->data;
            
            if (head_p3 == NULL) {
                head_p3 = Insert(head_p3, val);
                tail_p3 = head_p3;
            }
            else {
                tail_p3 = Insert(tail_p3, val);
            }
            
            curr_p1 = curr_p1->next_p;
            curr_p2 = curr_p2->next_p;
        }
    }
    
    return head_p3;
    
} /* Intersect */

/*-----------------------------------------------------------------
 * Function:    Difference
 * Purpose:     Finds the difference between two lists
 * Input args:  head_p1: pointer to head of list 1
 *              head_p2: pointer to head of list 2
 * Return val:  head_p3: pointer to head of list 3 (difference of list 1 and 2)
 */
struct list_node_s* Difference(struct list_node_s* head_p1,
                               struct list_node_s* head_p2)
{
    struct list_node_s* curr_p1 = head_p1;
    struct list_node_s* curr_p2 = head_p2;
    struct list_node_s* head_p3 = NULL;
    struct list_node_s* tail_p3 = NULL;
    
    int val;
    
    while(curr_p1 != NULL && curr_p2 != NULL) {
        if(curr_p1->data < curr_p2->data) {
            val = curr_p1->data;
            
            if (head_p3 == NULL) {
                head_p3 = Insert(head_p3, val);
                tail_p3 = head_p3;
            }
            else {
                tail_p3 = Insert(tail_p3, val);
            }
            
            curr_p1 = curr_p1->next_p;
        } else if (curr_p1->data > curr_p2->data) {
            curr_p2 = curr_p2->next_p;
        } else if(curr_p1->data == curr_p2->data) { //if they are equal
            curr_p1 = curr_p1->next_p;
            curr_p2 = curr_p2->next_p;
        }
        
    }
    
    if(curr_p1 != NULL) {
        while (curr_p1 != NULL) {
            val = curr_p1->data;
            
            if (head_p3 == NULL) {
                head_p3 = Insert(head_p3, val);
                tail_p3 = head_p3;
            }
            else {
                tail_p3 = Insert(tail_p3, val);
            }
            
            curr_p1 = curr_p1->next_p;
        }
    }
    
    
    return head_p3;
    
} /* Difference */

/*-----------------------------------------------------------------
 * Function:   Build
 * Purpose:    Inserts nodes into a linked list in the order that the numbers
 *             are entered
 * In/out arg:  head_p: pointer to head of list being built
 */
struct list_node_s* Build(struct list_node_s* head_p)
{
    struct list_node_s* tail_p = NULL;
    int val;
    
    printf("Please enter the numbers to be added to a Linked List. ");
    printf("Enter -1 to end.\n");
    
    scanf("%d", &val);
    
    while (val >= 0) {
        if (head_p == NULL) {
            head_p = Insert(head_p, val);
            tail_p = head_p;
        }
        else {
            tail_p = Insert(tail_p, val);
        }
        scanf("%d", &val);
    }
    
    Print(head_p);
    
    return head_p;
}

/*-----------------------------------------------------------------
 * Function:   Insert
 * Purpose:    Insert val at the end of the list
 * Input arg:  val: value to be inserted into the list
 * In/out arg: tail_p: pointer to end of the list
 */
struct list_node_s* Insert(struct list_node_s* tail_p, int val)
{
    struct list_node_s* temp;
    temp = malloc(sizeof(struct list_node_s));
    temp->next_p = NULL;
    temp->data = val;
    //    temp->next_p = NULL;
    
    if (tail_p == NULL) {
        tail_p = temp;
    }
    else {
        tail_p->next_p = temp;
        tail_p = tail_p->next_p;
    }
    
    return tail_p;
    
} /* Insert */

/*-----------------------------------------------------------------
 * Function:   Print
 * Purpose:    Print list on a single line of stdout
 * Input arg:  head_p
 */
void Print(struct list_node_s* head_p)
{
    struct list_node_s* curr_p = head_p;
    
    printf("list = ");
    while (curr_p != NULL) {
        printf("%d ", curr_p->data);
        curr_p = curr_p->next_p;
    }
    printf("\n");
} /* Print */

/*-----------------------------------------------------------------
 * Function:    Free_list
 * Purpose:     free each node in the list
 * Input arg:   head_p:  pointer to head of list
 * Return val:  NULL pointer
 * Note:        head_p is set to NULL on completion, indicating
 *              list is empty.
 */
struct list_node_s* Free_list(struct list_node_s* head_p)
{
    struct list_node_s* curr_p;
    struct list_node_s* temp_p;
    
    curr_p = head_p;
    while (curr_p != NULL) {
        temp_p = curr_p;
        curr_p = curr_p->next_p;
        free(temp_p);
    }
    
    head_p = NULL;
    return head_p;
    
} /* Free_list */

/*-----------------------------------------------------------------
 * Function:      Get_command
 * Purpose:       Get a single character command from stdin
 * Return value:  the first non-whitespace character from stdin
 */
char Get_command(void)
{
    char c;
    
    printf("Please enter a command Union (u), Intersect (i), Difference (d), ");
    printf("Quit(q): ");
    /* Put the space before the %c so scanf will skip white space */
    scanf(" %c", &c);
    return c;
} /* Get_command */

/*-----------------------------------------------------------------
 * Function:   Print_node
 * Purpose:    Print the value referred to by a node or NULL.
 *             Only used in DEBUG mode
 * Input args: node_name: Name of node pointer
 *             node_p: pointer to node
 */
void Print_node(char node_name[], struct list_node_s* node_p)
{
    if (node_p != NULL)
        printf("%s = %d\n", node_name, node_p->data);
    else
        printf("%s = NULL\n", node_name);
} /* Print_node */