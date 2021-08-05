/**
 * CS 2110 - Summer 2021 - Homework 9
 *
 * @author Kelsi Fulton
 *
 * list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return FAILURE if
 * the function returns an int).
 */

// Do not add ANY additional includes!!!
#include "list.h"

/* You should NOT have any global variables. */

/* These are static helper functions not intended to be called anywhere outside this file. */
static Student *create_student(char *name, int id, ContentQuestion question);
static Node *create_node(char *name, int id, ContentQuestion question);
static int student_equal(const Student *student1, const Student *student2);

/** create_student
 *
 * Helper function that creates a student by allocating memory for it on the heap
 * and initializing with the passed in data. You MUST create a deep copy of
 * the name by malloc'ing space for it on the heap.
 *
 * If malloc returns NULL, you should free everything you've allocated and
 * return NULL.
 *
 * @param the fields of the student struct
 * @return a student struct, return NULL if malloc returns NULL
 */
static Student *create_student(char *name, int id, ContentQuestion question)
{
    Student *s1 = (Student*) malloc(sizeof(Student));
    if (!s1) return NULL;
    if (name == NULL){
        s1->name=name;
    }
    else{
    char *name_copy = (char*) malloc((strlen(name)+1)*(sizeof(char)));
    if(!name_copy) {
        free(s1); 
        return NULL;
    }
    strcpy(name_copy,name);
    s1->name = name_copy;
    }
    s1->question = question;
    s1->id = id;
    return s1;
}


/** create_node
 *
 * Helper function that creates a struct node by allocating memory for it on
 * the heap. Be sure to set its next pointer to NULL.
 *
 * Remember that you need to malloc both the node itself and the student that's
 * contained in the struct. You might want to call create_student instead of
 * malloc'ing again.
 *
 * If malloc returns NULL for either of them, you should return NULL to
 * indicate failure. In the case that you successfully malloc one of them but
 * fail to malloc the other one, you should free the one you successfully
 * malloc'd.
 *
 * @param the fields of the student struct
 * @return a linked list node
 */
static Node *create_node(char *name, int id, ContentQuestion question)
{
    Node *n1 = (Node*) malloc(sizeof(Node));
    if (!n1){
        return NULL;
    }
    n1->data = create_student(name, id, question);
    if (!n1->data){
        free(n1);
        return NULL;
    }
    n1->next = NULL;

    return n1;
}


/** student_equal
 * Helper function to help you compare two student structs.
 *
 * If the name and id are both equal, you should return 1.
 * Otherwise, return 0.
 *
 * NOTE: struct members that are pointers may be null! If two student both have
 * null for a certain pointer, the pointers are considered equal. However, if
 * either of the input students is NULL, you should return 0.
 *
 * Make sure you're using the right function when comparing the name.
 * Remember that you are allowed to use functions from string.h
 *
 * This is meant to be used as a helper function in 'contains'; it is not tested
 * by the autograder.
 *
 * @param the two student structs to be compared
 * @return 1 if equal, 0 otherwise
 */
static int student_equal(const Student *student1, const Student *student2){
// {   UNUSED(student1);
//     UNUSED(student2);

//     return 0;
    if (student1==NULL|| student2 == NULL) return 0;
    const char name1 = *student1->name;
    const char name2 = *student2->name;
    int id1 = student1->id;
    int id2 = student2->id;

    if (name1 == name2){
        if (id1 == id2){
            return 1;
        }
        else{return 0;}
    }

    else{

    return 0;
    }
}

/** create_list
 *
 * Creates a 'struct linked_list' by allocating memory for it on the heap.
 * Be sure to initialize size to zero and head to NULL.
 *
 * If malloc returns NULL, you should return NULL to indicate failure.
 *
 * @return a pointer to a new list or NULL on failure
 */
LinkedList *create_list(void)
{
    LinkedList *list = (LinkedList*) malloc(sizeof(LinkedList));
    if (!list){
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

/** push_front
 *
 * Adds the element at the front of the linked list.
 *
 * @param list a pointer to the linked list struct.
 * @param the fields of the student struct
 * @return FAILURE if the linked_list is NULL or if allocating the new node
 *         fails, SUCCESS if successful.
 */
int push_front(LinkedList *list, char *name, int id, ContentQuestion question)
{
    if (list == NULL) return FAILURE;
    Node *new_node = create_node(name, id, question);
    if (!new_node){
        return FAILURE;
        }
    if (list->size==0){
        list->head = new_node;
        list->size++;
        }
    else{
        new_node->next=list->head;
        list->head = new_node;
        list->size++;
        }
    return SUCCESS;
}


/** push_back
 *
 * Adds the element to the back of the struct linked_list.
 *
 * @param list a pointer to the linked_list struct.
 * @param the fields of the student struct
 * @return FAILURE if the linked list is NULL or if allocating the new node
 *         fails, SUCCESS if successful.
 */
int push_back(LinkedList *list, char *name, int id, ContentQuestion question)
{
    if (list == NULL) return FAILURE;
    if (list->size==0){
        Node *new_node = create_node(name, id, question);
        if (!new_node){
            return FAILURE;
        }
        list->head = new_node;
        list->size++;
        }
    else{
        Node *current = list->head;
        while(current->next!=NULL){
            current=current->next;
        }
        Node *new_node = create_node(name, id, question);
        if (!new_node){
            return FAILURE;
        }
        current->next=new_node;
        current->next->next = NULL;
        list->size++;
        }
    return SUCCESS;
}

/** add_at_index
 *
 * Add the element at the specified index in the linked list. This index must
 * lie in the inclusive range [0,size].
 *
 * For example, if you have no elements in the linked list, you should be able
 * to add to index 0, but no less. If you have two elements in the linked list,
 * you should be able to add to index 2 but no further.
 *
 * @param list a pointer to the linked list struct
 * @param index 0-based, starting from the head in the inclusive range [0,size]
 * @param the fields of the student struct
 * @return FAILURE if the index is out of bounds or the linked list is NULL or
 *         malloc fails (do not add the data in this case) otherwise (on
 *         success) return SUCCESS
 */
int add_at_index(LinkedList *list, int index, char *name, int id, ContentQuestion question)
{
    if (list == NULL) return FAILURE;
    if (index < 0 || index > list->size) return FAILURE;
    Node *new_node = create_node(name, id, question);
    if (!new_node){
            return FAILURE;
        }
    if (index==0){
        new_node->next = list->head;
        list->head = new_node;
        list->size++;
    }
    else{
        Node *curr = list->head;
        int i = 1;
        while (index != i){
            curr=curr->next;
            i++;
        }
        new_node->next=curr->next;
        curr->next = new_node;
        list->size++;
    }
   
    return SUCCESS;
}

/** get
 *
 * Gets the data at the specified index in the linked list
 *
 * @param list a pointer to the linked list struct
 * @param index 0-based, starting from the head.
 * @param dataOut A pointer to a pointer used to return the data from the
 *        specified index in the linked list or NULL on failure.
 * @return FAILURE if dataOut is NULL or index is out of range of the linked
 *         list or the linked list is NULL, SUCCESS otherwise
 */
int get(LinkedList *list, int index, Student **dataOut)
{
    if (list == NULL) return FAILURE;
    if (index < 0 || index > list->size-1) return FAILURE;

    int tempPos = 0;
    Node *current = list->head;

    if (current != NULL){
        while (current != NULL){
            if (index== tempPos){
                *dataOut = current->data;
                return SUCCESS;
            }
            tempPos++;
            current=current->next;
        }
          
    }
    *dataOut = NULL;
    if (dataOut == NULL) {free(dataOut); return FAILURE;}
    // return SUCCESS;

    

    // UNUSED(list);
    // UNUSED(index);
    // UNUSED(dataOut);

    return SUCCESS;
}

/** contains
 *
 * Traverses the linked list, trying to see if the linked list contains some
 * data. We say the list contains some input if there exists some node with
 * equal data as the input.
 *
 * You should use 'student_equal' here to compare the data. Note that pointers are
 * allowed to be null!
 *
 * If there are multiple pieces of data in the linked list which are equal to
 * the "data" parameter, return the one at the lowest index.
 *
 *
 * @param list a pointer to the linked list struct
 * @param data The data, to see if it exists in the linked list
 * @param dataOut A pointer to a pointer used to return the data contained in
 *        the linked list or NULL on failure
 * @return 0 (false) if dataOut is NULL, the list is NULL, or the list does not
 *         contain data, else 1 (true)
 */
int contains(LinkedList *list, Student *data, Student **dataOut)
{
    if (list == NULL) {*dataOut=NULL; return 0;}
    if (list->size == 0) {*dataOut=NULL; return 0;}
    Node *current = list->head;
    if (current == NULL) {dataOut=NULL; free(current); return 0;}
    while (current !=NULL){
        if (student_equal(current->data, data)==1){
            *dataOut = current->data;
            return 1;
        }
        current = current->next;
    }
    
    *dataOut = NULL;
    if (*dataOut == NULL) return 0;
    return 0;
}

/** pop_front
 *
 * Removes the node at the front of the linked list, and returns its data to
 * the program user.
 *
 * @param list a pointer to the linked list.
 * @param dataOut A pointer to a pointer used to return the data in the first
 *        node or NULL if the linked list is NULL or empty
 * @return FAILURE if dataOut is NULL (the linked list is NULL or empty), else
 *         SUCCESS
 */
int pop_front(LinkedList *list, Student **dataOut)
{
    if (list==NULL) return FAILURE;
    Node *nextNode = NULL;
    if(list->head==NULL) return FAILURE;
    nextNode = list->head->next;
    *dataOut = list->head->data;
    free(list->head);
    list->head=nextNode;
    list->size--;
    if (dataOut==NULL) return FAILURE;
    return SUCCESS;
}

/** pop_back
 *
 * Removes the node at the back of the linked list, and returns its data to the
 * program user.
 *
 * @param list a pointer to the linked list.
 * @param dataOut A pointer to a pointer used to return the data in the last
 *        node or NULL if the linked list is NULL or empty
 * @return FAILURE if dataOut is NULL (the linked list is NULL or empty), else
 *         SUCCESS
 */
int pop_back(LinkedList *list, Student **dataOut)
{
    if (list==NULL) {dataOut=NULL; return FAILURE;}
    if (list->size==0) {dataOut=NULL; return FAILURE;}
    if (list->head == NULL) {dataOut=NULL; return FAILURE;}
    else{
        Node *delLast, *prev;
        delLast = list->head;
        prev = NULL;
        while (delLast->next != NULL)
        {
            prev =  delLast;
            delLast =  delLast->next;
        }
        if (delLast == list->head){
            *dataOut = list->head->data;
            free(list->head);
            list->size--;
            list->head=NULL;
            return SUCCESS;
        }
        else{
            *dataOut = delLast->data;
            free(delLast);
            list->size--;
            prev->next = NULL;
            return SUCCESS;
        }
        

    }
    
    if (dataOut==NULL) {return FAILURE;}
    list->size--;
    
    return SUCCESS;
}


/** remove_at_index
 *
 * Remove the element at the specified index in the linked list.
 *
 * @param list a pointer to the linked list structure
 * @param dataOut A pointer to a pointer used to return the data in the last
 *        node or NULL if the linked list is NULL or empty
 * @param index 0-based, starting from the head in the inclusive range
 *        [0,size-1]
 * @return FAILURE if the index is out of bounds, the linked list is NULL or the
 *         dataOut is NULL, otherwise return SUCCESS
 */
int remove_at_index(LinkedList *list, Student **dataOut, int index)
{
    if (list == NULL) {dataOut=NULL; return FAILURE;}
    if (list->size==0) {dataOut=NULL; return FAILURE;}
    if (index < 0 || index > (list->size)-1) {dataOut=NULL; return FAILURE;}
    if (list->head ==  NULL) {dataOut=NULL; return FAILURE;}
    Node *temp =list->head;
    Node *rmove;
    int i=0;
    if (index==0){
        *dataOut= list->head->data;
        rmove = list->head;
        list->head = temp->next;
        free(rmove);
        list->size--;
        return SUCCESS;
    }

    if (index==1){
        *dataOut = list->head->next->data;
        rmove = list->head->next;
        list->head->next = temp->next->next;
        free(rmove);
        list->size--;
        return SUCCESS;
    }

    if(index==-1){
        while (i<((list->size)-2)){
            temp = temp->next;
            i++;
        }
        *dataOut = temp->next->data;
        rmove = temp->next;
        temp->next = NULL;
        free(rmove);
        list->size--;
        return SUCCESS;

    }
    while (i < (index-1))
    {
        temp = temp->next;
        i++;
    }
    *dataOut = temp->next->data;
    rmove  = temp->next;
    temp->next = temp->next->next;
    free(rmove);
    list->size--;
    return SUCCESS;
    *dataOut = NULL;
    if (dataOut==NULL) return FAILURE;
    return SUCCESS;
}

/** empty_list
 *
 * Empties the linked list. After this is called, the linked list should be
 * empty. This does NOT free the linked list struct itself, just all nodes and
 * data within. Make sure to check that the list is not NULL before using it.
 *
 * Once again, the things that need to be freed after this function are:
 * - the nodes
 * - the Student structs within the nodes
 * - all pointers in the Student struct
 *
 * However, if you're using other functions you've written (which you should
 * be), those functions might take care of some of the freeing for you.
 *
 * You may call free on char pointers as well as struct pointers.
 *
 * If 'list' is NULL, simply return.
 *
 * @param list a pointer to the linked list struct
 */
void empty_list(LinkedList *list)
{
    if (list==NULL) return;
    if (list->head==NULL) return;
    if (list->size==0) return;
    Node *curr = list->head;
    while (curr != NULL){
        Node *temp = curr;
        curr = curr->next;
        free(temp->data->name);
        free(temp->data);
        free(temp);
        list->size--;
    }
    list->head = NULL;
    
    return;
}


/** replace_name_at_index
 *
 * Replaces the name field in the user data struct of the node at the specified
 * index with a new name
 *
 * Note that new name may be a different size than old one (hint: use realloc to
 * resize the buffer).
 *
 * If realloc or malloc fails, leave the name at the specified index unchanged.
 *
 * @param list a pointer to the linked list struct
 * @param index 0-based, starting from the head in the inclusive range
 *        [0,size-1]
 * @param newName a pointer to the new name
 * @return FAILURE if the index is out of bounds, the linked list is NULL or
 *         realloc fails otherwise return SUCCESS
 */
int replace_name_at_index(LinkedList *list, int index, char *newName)
{
    if (list == NULL) {return FAILURE;}
    if (list->size==0) {return FAILURE;}
    if (index < 0 || index > (list->size)-1) {return FAILURE;}

    int i=0;

    while(list->head != NULL){
        if (index == i){
            char* rep_name = (char*) realloc(list->head->data->name, (strlen(newName)+1*(sizeof(char))));
            if (rep_name == NULL) return FAILURE;
            strcpy(rep_name, newName);
            list->head->data->name = rep_name;
            return SUCCESS;
        }
        list->head = list->head->next;
        i++;
    }
    // UNUSED(list);
    // UNUSED(index);
    // UNUSED(newName);

    return FAILURE;
}

/** avoid_assembly
 *
 *
 * Traverse the Office Hours queue(LinkedList) as a TA and count how many students want to ask
 * you questions about assembly so you can promptly avoid them or ask another TA to help them.
 * In other words, traverse the LinkedList and count the number of students who have a ContentQuestion
 * equal to ASSEMBLY.
 *
 * @param list a pointer to the LinkedList structure
 * @param dataOut A pointer to int used to return a count of how many students have 
 *                a ContentQuestion about assembly
 *                or -1 if the LinkedList is NULL or empty
 * @return FAILURE if the LinkedList is NULL or empty, else SUCCESS
 */
int avoid_assembly(LinkedList *list, int *dataOut)
{
    enum content_question q = ASSEMBLY;
    if (list==NULL) {*dataOut= -1; return FAILURE;}
    if (list->size == 0) {*dataOut= -1; return FAILURE;}
    Node *current = list->head;
    int i;
    dataOut = 0;
    for (i=0; i<(list->size); i++){
        if (current->data->question == q){
            dataOut++;
        }
        current=current->next;
    }
    if (dataOut == 0) return SUCCESS;

    return SUCCESS;
}

