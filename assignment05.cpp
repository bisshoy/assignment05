/*****************************************************************************/
/* Skeleton provided by S. Bassil (Spring 2023)                              */
/*                                                                           */
/* Programmer: Bisshoy Anwar                                                 */
/*                                                                           */
/* Program: assignment05                                                     */
/*                                                                           */
/* Approximate Completion Time: 2 days                                       */
/*****************************************************************************/

/*
   This program builds a linked list and traverses it iteratively.
*/

#include <iostream>

using namespace std;

/* declaration of structure */
struct node{
	int data;
	node *next;
};

/* functions prototypes */
node* insert_node(node *ptr, node *new_ptr);
node* find_node(node *ptr, int n);
node* delete_node(node *ptr, int n, bool &success_flag);
void print_backward(node *ptr);
void printMenu();

int main()
{
    int num;
    int choice;
    node* p;        // First finder pointer 
    bool success_flag;
    
    node* head = nullptr;
    node* create = nullptr;

    printMenu();
    cin >> choice;

    // Input validation 
    while (choice < 1 || choice > 5) {
        cout << "\nInvalid choice. Retry.\n" << endl;
        printMenu();
        cin >> choice;
    }

    do {
        switch(choice)
        {
            case 1:
                // Allocate space for new node 
                create = new node;

                // Get user's desired data value 
                cout << "\nEnter an integer to be inserted ";
                cout << "into linked list: ";
                cin >> num;
                cout << endl;
                
                // Set up node with data value and nullptr, then
                // call insert function 
                create->data = num;
                create->next = nullptr;
                head = insert_node(head, create);

                if (head->data == num) {
                    cout << num << " has been inserted "
                         << "successfully" << endl << endl;
                }

                else {
                    cout << "ERROR: Could not insert node." << endl << endl;
                }

                printMenu();
                cin >> choice;
                break;

            case 2:
                int findValue;

                cout << "\nEnter an integer to be found in linked list: ";
                cin >> findValue;
                cout << endl;

                p = head;

                if (find_node(p, findValue)) {
                    cout << findValue << " has been found "
                         << "in linked list.\n" << endl;
                }

                else {
                    cout << findValue << " has not been found " 
                         << "in linked list.\n" << endl;
                }

                printMenu();
                cin >> choice;
                break;

            case 3:
                int deleteValue;
                success_flag = false;

                cout << "\nEnter an integer to be deleted from linked list: ";
                cin >> deleteValue; 
                cout << endl;

                p = head; 

                // In case value not in linked list 
                if (find_node(p, deleteValue) == nullptr) {
                    success_flag = false;
                    cout << "Number is not in linked list.\n" << endl;
                    printMenu();
                    cin >> choice;
                    break;
                }

                else {
                    // In case head holds the deleteValue 
                    if (p->data == deleteValue) {
                        head = head->next;
                        delete p;
                        success_flag = true;
                    }

                    // Otherwise, proceed through linked list 
                    else {
                        head = delete_node(head, deleteValue, success_flag);
                    }

                }

                // Print messages 
                if (success_flag) {
                    cout << deleteValue << " has been found and "
                    << "deleted from linked list.\n" << endl;
                }

                else {
                    cout << "ERROR: Value found "
                         << "but was not deleted.\n" << endl;
                }

                printMenu();
                cin >> choice;
                break;

            case 4:
                cout << "\nHere are the integers in the order they were entered: ";
                print_backward(head);
                cout << endl;

                printMenu();
                cin >> choice;
                break;
            case 5:
                break; 

            default:
                // Cycled input validation 
                cout << "\nInvalid choice. Retry.\n" << endl;
                printMenu();
                cin >> choice;       
        }
    } while (choice != 5);

    cout << "\nThank you for using the system!" << endl;
	return 0;

}

/******************************************************************************/
/* Function: insert_node                                                      */
/*                                                                            */
/* Description: Inserts node to head of linked list (creates new head)        */
/*                                                                            */
/* Data in: ptr to first node in linked list, ptr to the node to be inserted  */
/*                                                                            */
/* Data out: ptr to the first node in new linked list                         */
/******************************************************************************/

node* insert_node(node *ptr, node* new_ptr)
{    
    new_ptr->next = ptr;
    return new_ptr;	
}


/******************************************************************************/
/* Function: find_node                                                        */
/*                                                                            */
/* Description: Write a brief description of what the function does           */
/*                                                                            */
/* Data in: ptr to first node in linked list, the integer searching for       */
/*                                                                            */
/* Data out: ptr to the node with data equals to integer searched for,        */
/*           nullptr if integer searched for was not found                    */
/******************************************************************************/

node* find_node(node *ptr, int n)
{
    // Simple enough; iterate through, if you find the 
    // desired value, then you stop and return that 
    // pointer 
    while (ptr != nullptr && ptr->data != n) {
        ptr = ptr->next;
    }

    if (ptr != nullptr) {
        return ptr;
    }

    // In case the value is not in the array 
    else {
        return nullptr;
    }
}

/******************************************************************************/
/* Function: delete_node                                                      */
/*                                                                            */
/* Description: Write a brief description of what the function does           */
/*                                                                            */
/* Data in: ptr to first node in linked list, the integer searching for,      */
/*          flag to be set to:                                                */
/*            - true if integer was found and corresponding node deleted      */
/*            - false otherwise                                               */
/*                                                                            */
/* Data out: ptr to the first node in new linked list                         */
/******************************************************************************/

node* delete_node(node *ptr, int n, bool &success_flag)
{
    node* current = ptr;
    node* future = current->next;

    // Loops through while stopping future from going 
    // past nullptr
    while (future->data != n && future->next != nullptr) {
        current = current->next;
        future = current->next;
    }

    // If the data in the next-from-current is the desired 
    // value, then we make current point to whatever is 
    // two steps ahead, then delete the pointer pointing to 
    // the node with the value we want to delete 
    if (future->data == n) {
        current->next = current->next->next;
        delete future;
        success_flag = true;
    }

    return ptr;

}

/******************************************************************************/
/* Function: print_backward                                                   */
/*                                                                            */
/* Description: Prints out the linked list in order of user entry             */
/*                                                                            */
/* Data in: ptr to first node in linked list                                  */
/*                                                                            */
/* Data out: none                                                             */
/******************************************************************************/

void print_backward(node *ptr)
{
    // Set current to the head and last to the end 
	node* current = ptr;
    node* last = nullptr;

    while (last != ptr) {

        // Go to last element in array 
        while(current->next != last) {
            current = current->next;
        }

        // Set the current-final element as the new final,
        // so that loop iterates again and stops at it
        // (sort of like a new nullptr)
        last = current;

        // Print out that "last" element 
        cout << last->data << " ";

        // Reset for fresh loop 
        current = ptr;

    }

    cout << endl;

}

/******************************************************************************/
/* Function: printMenu                                                        */
/*                                                                            */
/* Description: Prints out the menu                                           */
/*                                                                            */
/* Data in: none                                                              */
/*                                                                            */
/* Data out: none                                                             */
/******************************************************************************/

void printMenu()
{
    cout << "1    Insert integer into linked list" << endl;
    cout << "2    Find integer in linked list" << endl;
    cout << "3    Delete integer from linked list" << endl;
    cout << "4    Print out integers" << endl;
    cout << "5    Quit" << endl << endl;

    cout << "Enter 1, 2, 3, 4, or 5: ";
}

