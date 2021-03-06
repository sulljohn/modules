//
// Created by John Sullivan on 10/5/18.
//
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "list.h"

car_t *make_car(char *plate, double price, int year) {
    car_t *pp;

    // Allocating memory, returning if fails
    if (!(pp = (car_t *) malloc(sizeof(car_t)))) {
        printf("[Error: malloc failed allocating car]\n");
        exit(EXIT_FAILURE);
    }

    // Setting parts of object based on criteria
    pp->next = NULL;
    pp->price = price;
    pp->year = year;
    strcpy(pp->plate, plate);
    return pp;
}

bool searchfn(void *elementp, const void *keyp) {
    car_t *carp = (car_t *) elementp;

    return strcmp(carp->plate, keyp) == 0;
}

void print_plate(car_t *cp) {
    printf("%s\n", cp->plate);
}

int main(int argc, char **argv) {
    if (argc != 2) exit(EXIT_FAILURE);

    int in = atoi(argv[1]);

    queue_t *queue = qopen();

    car_t *p1;
    car_t *p2;
    car_t *p3;
    car_t *p4;

    switch (in) {
        case 1:
            printf("Putting to an empty list...\n");

            p1 = make_car("123456789", 20000, 2016);

            if (qput(queue, p1) == 0) {
                printf("Good\n");
                qclose(queue);
                exit(EXIT_SUCCESS);
            } else {
                printf("Bad\n");
                qclose(queue);
                exit(EXIT_FAILURE);
            }
        case 2:
            printf("Putting to a non-empty list...\n");

            p1 = make_car("123456789", 20000, 2016);
            p2 = make_car("098765432", 15000, 2015);

            qput(queue, p1);

            if (qput(queue, p2) == 0) {
                printf("Good\n");
                qclose(queue);
                exit(EXIT_SUCCESS);
            } else {
                printf("Bad\n");
                qclose(queue);
                exit(EXIT_FAILURE);
            }
        case 3:
            printf("Getting from an empty list...\n");

            car_t *tmp1 = qget(queue);
            free(tmp1);

            if (tmp1 == NULL) {
                printf("Good\n");
                qclose(queue);
                exit(EXIT_SUCCESS);
            } else {
                printf("Bad\n");
                qclose(queue);
                exit(EXIT_FAILURE);
            }
        case 4:
            printf("Getting from a non-empty list...\n");

            p1 = make_car("123456789", 20000, 2016);
            p2 = make_car("098765432", 15000, 2015);

            qput(queue, p1);
            qput(queue, p2);

            car_t *tmp2 = qget(queue);

            if (tmp2 != NULL) {
                printf("Got plate: \n");
                printf("%s\n", tmp2->plate);
                free(tmp2);

                printf("Good\n");
                qclose(queue);
                exit(EXIT_SUCCESS);
            } else {
                printf("Bad\n");
                qclose(queue);
                exit(EXIT_FAILURE);
            }
        case 5:
            printf("Printing an empty list...\n");

            qapply(queue, (void (*)(void *)) print_plate);

            printf("Good\n");
            qclose(queue);
            exit(EXIT_SUCCESS);
        case 6:
            printf("Printing from a non-empty queue...\n");

            p1 = make_car("123456789", 20000, 2016);
            p2 = make_car("098765432", 15000, 2015);
            p3 = make_car("543216789", 17000, 2017);
            p4 = make_car("678905432", 12000, 2012);

            qput(queue, p1);
            qput(queue, p2);
            qput(queue, p3);
            qput(queue, p4);

            qapply(queue, (void (*)(void *)) print_plate);

            printf("Good\n");
            qclose(queue);
            exit(EXIT_SUCCESS);
        case 7:
            printf("Removing from empty list...\n");

            car_t *tmp3 = qremove(queue, searchfn, "123456789");

            if (tmp3 == NULL) {
                free(tmp3);

                printf("Good\n");
                qclose(queue);
                exit(EXIT_SUCCESS);
            } else {
                free(tmp3);

                printf("Bad\n");
                qclose(queue);
                exit(EXIT_FAILURE);
            }
        case 8:
            printf("Removing last element (tail) in hashtable...\n");

            p1 = make_car("123456789", 20000, 2016);
            p2 = make_car("098765432", 15000, 2015);
            p3 = make_car("543216789", 17000, 2017);
            p4 = make_car("678905432", 12000, 2012);

            qput(queue, p1);
            qput(queue, p2);
            qput(queue, p3);
            qput(queue, p4);

            printf("Printing all plates\n");
            qapply(queue, (void (*)(void *)) print_plate);

            free(qremove(queue, searchfn, "678905432"));

            printf("Printing all plates with last one removed...\n");
            qapply(queue, (void (*)(void *)) print_plate);

            printf("Good\n");
            qclose(queue);
            exit(EXIT_SUCCESS);
        case 9:
            printf("Removing first element (head) of the queue...\n");

            p1 = make_car("123456789", 20000, 2016);
            p2 = make_car("098765432", 15000, 2015);
            p3 = make_car("543216789", 17000, 2017);
            p4 = make_car("678905432", 12000, 2012);

            qput(queue, p1);
            qput(queue, p2);
            qput(queue, p3);
            qput(queue, p4);

            printf("Printing all plates\n");
            qapply(queue, (void (*)(void *)) print_plate);

            free(qremove(queue, searchfn, "123456789"));

            printf("Printing all plates with first one removed...\n");
            qapply(queue, (void (*)(void *)) print_plate);

            printf("Good\n");
            qclose(queue);
            exit(EXIT_SUCCESS);
        case 10:
            printf("Removing a middle element of the queue...\n");

            p1 = make_car("123456789", 20000, 2016);
            p2 = make_car("098765432", 15000, 2015);
            p3 = make_car("543216789", 17000, 2017);
            p4 = make_car("678905432", 12000, 2012);

            qput(queue, p1);
            qput(queue, p2);
            qput(queue, p3);
            qput(queue, p4);

            printf("Printing all plates\n");
            qapply(queue, (void (*)(void *)) print_plate);

            free(qremove(queue, searchfn, "543216789"));

            printf("Printing all plates with 543... removed\n");
            qapply(queue, (void (*)(void *)) print_plate);

            printf("Good\n");
            qclose(queue);
            exit(EXIT_SUCCESS);
        case 11:
            printf("Searching empty queue...\n");

            car_t *tmp4 = qsearch(queue, searchfn, "123456789");

            if (tmp4 == NULL) {
                printf("Good\n");
                qclose(queue);
                exit(EXIT_SUCCESS);
            } else {
                printf("Bad\n");
                qclose(queue);
                exit(EXIT_FAILURE);
            }
        case 12:
            printf("Searching non-empty queue...\n");

            p1 = make_car("123456789", 20000, 2016);
            p2 = make_car("098765432", 15000, 2015);

            qput(queue, p1);
            qput(queue, p2);

            car_t *tmp5 = qsearch(queue, searchfn, "123456789");

            if (tmp5 != NULL) {
                printf("Got plate: \n");
                printf("%s\n", tmp5->plate);

                printf("Good\n");
                qclose(queue);
                exit(EXIT_SUCCESS);
            } else {
                printf("Bad\n");
                qclose(queue);
                exit(EXIT_FAILURE);
            }
        case 13:
            printf("Concatenating two queues...");

            p1 = make_car("123456789", 20000, 2016);
            p2 = make_car("098765432", 15000, 2015);
            p3 = make_car("543216789", 17000, 2017);
            p4 = make_car("678905432", 12000, 2012);

            queue_t *queue2 = qopen();

            qput(queue, p1);
            qput(queue, p2);

            qput(queue2, p3);
            qput(queue2, p4);

            printf("Printing queue 1\n");
            qapply(queue, (void (*)(void *)) print_plate);

            printf("Printing queue 2\n");
            qapply(queue2, (void (*)(void *)) print_plate);

            printf("Concatenating...\n");
            qconcat(queue, queue2);

            printf("Printing concatenated queue\n");
            qapply(queue, (void (*)(void *)) print_plate);

            printf("Good\n");
            qclose(queue);
            exit(EXIT_SUCCESS);
        case 14:
            printf("Removing all elements of queue...\n");

            p1 = make_car("123456789", 20000, 2016);
            p2 = make_car("098765432", 15000, 2015);
            p3 = make_car("543216789", 17000, 2017);
            p4 = make_car("678905432", 12000, 2012);

            qput(queue, p1);
            qput(queue, p2);
            qput(queue, p3);
            qput(queue, p4);

            printf("Printing all plates\n");
            qapply(queue, (void (*)(void *)) print_plate);

            free(qremove(queue, searchfn, "123456789"));
            free(qremove(queue, searchfn, "098765432"));
            free(qremove(queue, searchfn, "543216789"));
            free(qremove(queue, searchfn, "678905432"));

            printf("Printing queue with all removed...\n");
            qapply(queue, (void (*)(void *)) print_plate);

            printf("Good\n");
            qclose(queue);
            exit(EXIT_SUCCESS);
        default:
            printf("Bad\n");
            qclose(queue);
            exit(EXIT_FAILURE);
    }
}
