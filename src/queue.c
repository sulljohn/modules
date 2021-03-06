/**
1;95;0c * Created by John Sullivan on 10/5/18.
 *
 * Consulted: https://www.geeksforgeeks.org/queue-set-2-linked-list-implementation/
 */

#include "queue.h"

struct Node {
    void *next;
    void *data;
};

struct queue {
    struct Node *head;
    struct Node *tail;
};

/* create an empty queue */
queue_t* qopen(void) {
    struct queue *q;

    // Allocating memory, returning if fails
    if (!(q = (struct queue*)malloc(sizeof(struct queue)))) {
        printf("[Error: malloc failed allocating car]\n");
        return NULL;
    }

    q->head = NULL;
    q->tail = NULL;

    return q;
}

/* deallocate a queue, frees everything in it */
void qclose(queue_t *qp) {
    struct queue* q = (struct queue*)qp;
    struct Node *curr = q->head;
    struct Node *prev = NULL;

    // Freeing each element
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;

        free(prev->data);   // Free the data
        free(prev);         // Free the node
    }

    // Freeing the entire queue
    free(q);    // Free the queue
}

/* put element at the end of the queue
 * returns 0 is successful; nonzero otherwise
 */
int32_t qput(queue_t *qp, void *elementp) {
    struct queue* q = (struct queue*)qp;

    struct Node *node;

    // Allocating memory, returning if fails
    if (!(node = (struct Node*)malloc(sizeof(struct Node)))) {
        printf("[Error: malloc failed allocating car]\n");
        return 1;
    }

    node->next=NULL;
    node->data=elementp;

    // If nothing in the queue yet
    if (q->tail == NULL) {
        q->head = node;
        q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }

    return 0;
}

/* get the first first element from queue, removing it from the queue */
void* qget(queue_t *qp) {
    struct queue* q = (struct queue*)qp;

    // If queue is empty
    if (q->head == NULL) {
        return NULL;
    }

    // Rest is for if the queue is NOT empty
    struct Node *node = q->head;
    void* data = node->data;
    q->head = q->head->next;

    // If head becomes null, tail should also become null
    if (q->head == NULL) q->tail = NULL;

    // Removing associate node and returning data
    free(node);
    return data;
}

/* apply a function to every element of the queue */
void qapply(queue_t *qp, void (*fn)(void* elementp)) {
    struct queue* q = (struct queue*)qp;
    struct Node *curr = q->head;

    while (curr != NULL) {
        (*fn)(curr->data); // Applies function to data instead
        curr = curr->next;
    }
}

/* search a queue using a supplied boolean function
 * skeyp -- a key to search for
 * searchfn -- a function applied to every element of the queue
 *          -- elementp - a pointer to an element
 *          -- keyp - the key being searched for (i.e. will be
 *             set to skey at each step of the search
 *          -- returns TRUE or FALSE as defined in bool.h
 * returns a pointer to an element, or NULL if not found
 */
void* qsearch(queue_t *qp,
              bool (*searchfn)(void* elementp,const void* keyp),
              const void* skeyp) {
    struct queue* q = (struct queue*)qp;
    struct Node *curr = q->head;

    while (curr != NULL) {
        if ((searchfn)(curr->data,skeyp)) {  // Applies function to data instead
            return curr->data;
        }
        curr = curr->next;
    }

    return NULL;
}

/* search a queue using a supplied boolean function (as in qsearch),
 * removes the element from the queue and returns a pointer to it or
 * NULL if not found
 */
void* qremove(queue_t *qp,
              bool (*searchfn)(void* elementp,const void* keyp),
              const void* skeyp) {
    struct queue* q = (struct queue*)qp;

    struct Node *prev = NULL;
    struct Node *curr = q->head;
    void* data; // For holding data that is dereferenced

    if (q->head == NULL) return NULL;

    // Case if at front of list
    if (searchfn(curr->data, skeyp)) {
        q->head = curr->next;

        // Delinking curr's next ptr
        data = curr->data;
        free(curr); // Need to free the node that holds the data
        return data;
    }

    // Searching rest of list
    while (curr != NULL) {

        if (searchfn(curr->data, skeyp)) {
            prev->next = curr->next;

            // Delinking curr's next ptr
            data = curr->data;
            free(curr); // Need to free the node that holds the data
            return data;
        }

        prev = curr;
        curr = curr->next;
    }

    return NULL;
}

/* concatenatenates elements of q2 into q1
 * q2 is dealocated, closed, and unusable upon completion
 */
void qconcat(queue_t *q1p, queue_t *q2p) {
    void* elem;

    while ((elem = qget(q2p)) != NULL) qput(q1p, elem);

    qclose(q2p);

    return;
}

