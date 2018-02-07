#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "list.h"
#include <string.h>
#include <math.h>

/*
* Datastrkturer och algoritmer
* Spring 18
* Assignment 2

* File:         queuetest.c
* Description:  A test program for a list implementation.
* Author:       Svitri Magnusson
* CS username:  kv13smn
* Date:         2018-02-07
* Input:        void
* Output:       console prints
* Limitations:  Does not test every combination of elements in different order.
*/
//Den verifierar att listan bara är tom en gång. Dv.s


typedef struct{
  int *intField;
  char *charField;
} testStruct;

/******************************/

void print_ints(const void *data)
{
	printf("[%d]", *(int*)data);
}

/******************************/

queue *add_all_types(queue *q)
{

	char *c =  malloc(sizeof(*c));
	double *d =  malloc(sizeof(*d));
	long *l =  malloc(sizeof(*l));
	bool *b =  malloc(sizeof(*b));
	int *v = malloc(sizeof(*v));

	 c="test letters";
	*d=3.14;
	*l=1234567;
	*b=false;
	*v=42;

	q = queue_enqueue(q, c);
	q = queue_enqueue(q, d);
	q = queue_enqueue(q, l);
	q = queue_enqueue(q, b);
	q = queue_enqueue(q, v);

	return q;
}

/******************************/

void empty_queue_test()
{
	queue *q=queue_empty(NULL);
	queue_print(q, print_ints);
	if (!queue_is_empty(q)) {
		fprintf(stderr, "FAIL. New queue is not empty!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	queue_kill(q);
	printf("PASSED.\n\n");
}

/******************************/

void empty_enque_test()
{
	queue *q=queue_empty(NULL);
	queue_print(q, print_ints);
	int *v = malloc(sizeof(*v));
	*v=1;
	q = queue_enqueue(q, v);
	queue_print(q, print_ints);
	if (queue_is_empty(q)) {
		fprintf(stderr, "FAIL. New queue is empty after enqueue!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	queue_kill(q);
	printf("PASSED.\n\n");

}

/******************************/

void empty_enque_deque_test()
{
	queue *q=queue_empty(NULL);
	int *v = malloc(sizeof(*v));
	int *v2 = malloc(sizeof(*v2));

	*v=1;
	*v2=2;

	q = queue_dequeue(queue_enqueue(q, v));
	queue_print(q, print_ints);
	if (!queue_is_empty(q)) {
		fprintf(stderr, "FAIL. New queue is not empty after enqueue and deqeue!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}
	q = queue_dequeue(queue_enqueue(queue_enqueue(q, v), v2));
	queue_print(q, print_ints);
	if (queue_is_empty(q)) {
		fprintf(stderr, "FAIL. New queue is empty after enqueue-deqeue-enqueue!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	q = queue_enqueue(queue_dequeue(q), v2);
	queue_print(q, print_ints);
	if (queue_is_empty(q)) {
		fprintf(stderr, "FAIL. New queue is empty after denqueue-enqeue!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	queue_kill(q);
	printf("PASSED.\n\n");
}

/******************************/

void queue_front_test()
{
	queue *q=queue_empty(NULL);
	int *v = malloc(sizeof(*v));
	int *v2 = malloc(sizeof(*v2));
	int *t = malloc(sizeof(*t));
	int *t2 = malloc(sizeof(*t2));

	*v = 1;
	*v2 = 2;

	queue_print(q, print_ints);
	t = queue_front(queue_enqueue(q, v));
	queue_print(q, print_ints);


	if (queue_is_empty(q) || (!(*t == *v))) {
		fprintf(stderr, "FAIL. Queue is empty after enqueue and front or\n");
		fprintf(stderr, "latest value added is not the same as front.\n");
		fprintf(stderr, "Value 1: %d - Value 2: %d", *t, *v);
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	v = queue_front(queue_enqueue(q, v2));
	t = queue_front(q);
	queue_print(q, print_ints);

	if (queue_is_empty(q) || (!(*t == *v))) {
		fprintf(stderr, "FAIL. New queue is empty after enqueue and front or\n");
		fprintf(stderr, "latest value added is not the same as front.\n");
		fprintf(stderr, "Value 1: %d - Value 2: %d", *t2, *v2);
		queue_kill(q);
		exit(EXIT_FAILURE);
	}
	queue_kill(q);
	printf("PASSED.\n\n");
}

/******************************/

void type_test()
{
	queue *q = queue_empty(NULL);
	q = add_all_types(q);
	queue_print(q, print_ints);

	if (queue_is_empty(q)) {
		fprintf(stderr, "FAIL. New queue is empty after enqueue!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	queue_kill(q);
	printf("PASSED.\n\n");

}

/******************************/


void capacity_test()
{
	// Create empty list.

	int *checkSum1 = calloc(1, sizeof(*checkSum1));
	int *checkSum2 = calloc(1, sizeof(*checkSum2));

	queue *q=queue_empty(NULL);
	q = add_all_types(q);

	for(int i = 0; i <= 100; i++) {
		int *number = malloc(sizeof(*number));
		*number = i;
		q = queue_enqueue(q, number);

		*checkSum1 += i;
	}
	queue_print(q, print_ints);
	if (queue_is_empty(q)) {
		fprintf(stderr, "FAIL. Empty queue is not empty after 10000 values!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	for(int i = 100; i >= 0; i--) {
		q = queue_dequeue(q);
		*checkSum2 += i;
	}
	queue_print(q, print_ints);
	if(*checkSum1 != *checkSum2) {
		fprintf(stderr, "FAIL. Total value added is not the same removed: %d  %d\n\n", *checkSum1, *checkSum2);
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	free(checkSum1);
	free(checkSum2);
	queue_kill(q);
	printf("PASSED.\n\n");

}

/******************************/

void order_type_test()
{
	queue *q = queue_empty(NULL);
	q = add_all_types(q);
	char *ch = malloc(sizeof(*ch));
	*ch = 'B';

	double precision = 0.000001;


	char *front_str = queue_front(q);
	queue_print(q, print_ints);
	if((strcmp(front_str, "test letters") != 0)) {
		fprintf(stderr, "FAIL. The queue got modified after dequeue!\n");
		fprintf(stderr, "Value: %s. Should be: \"test letters\"", front_str);
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	queue_dequeue(q);

	double *front_double = queue_front(q);
	queue_print(q, print_ints);
	if(fabs(*front_double - 3.140000) > precision) {
		fprintf(stderr, "FAIL. The queue got modified after dequeue!\n");
		fprintf(stderr, "Value: %lf. Should be: 0.000, with precision: %lf", *front_double, precision);
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	queue_dequeue(q);

	long *front_long = queue_front(q);
	queue_print(q, print_ints);
	if(*front_long != 1234567) {
		fprintf(stderr, "FAIL. The queue got modified after dequeue!\n");
		fprintf(stderr, "Value: %lu. Should be: 1234567", *front_long);
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	queue_dequeue(q);

	bool *front_bool = queue_front(q);
	queue_print(q, print_ints);
	if(*front_bool != 0) {
		fprintf(stderr, "FAIL. The queue got modified after dequeue!\n");
		fprintf(stderr, "Value: %d. Should be: 0", *front_bool);
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	queue_dequeue(q);

	int *front_digit = queue_front(q);
	queue_print(q, print_ints);
	if(*front_digit != 42) {
		fprintf(stderr, "FAIL. The queue got modified after dequeue!\n");
		fprintf(stderr, "Value: %d. Should be: 42", *front_digit);
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	queue_dequeue(q);
	queue_print(q, print_ints);

	if (!(queue_is_empty(q))) {
		fprintf(stderr, "FAIL. New queue is not empty!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	q = queue_enqueue(q, ch);
	char *front_char = queue_front(q);
	queue_print(q, print_ints);
	if(*front_char != *ch) {
		printf("%c - ", *front_char);
		fprintf(stderr, "FAIL. The queue got modified after dequeue or enqueue!\n");
		fprintf(stderr, "Value: %c. Should be: %c", *front_char, *ch);
		queue_kill(q);
		exit(EXIT_FAILURE);
	}
	queue_dequeue(q);
	queue_print(q, print_ints);


	if (!(queue_is_empty(q))) {
		fprintf(stderr, "FAIL. New queue is not empty!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	queue_kill(q);
	printf("PASSED.\n\n");
}

/******************************/

void test_queue_structs()
{
	testStruct *tstruct = malloc(sizeof(*tstruct));
	testStruct *tstructs[10][10] = calloc(10 * 10, sizeof(struct));

	for(int i = 0; i < 11; i++) {
		for(int j = 0; j < 11; j++) {
			*tstruct->intField = j + i;
			tstruct->charField = "String";
		}
	}

	*tstruct->intField = 24;
	tstruct->charField = "Twenty Four";

	queue *q=queue_empty(NULL);
	queue_enqueue(q, tstruct);
	queue_enqueue(q, tstructs);

	queue_print(q, print_ints);


	if (!queue_is_empty(q)) {
		fprintf(stderr, "FAIL. New queue is not empty!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	queue_kill(q);
	printf("PASSED.\n\n");
}





//						------------------------------------------
/****************************************MAIN**********************************/
//					--------------------_____-----------------


int main(void)
{
	printf("Initiating Queue Testing...\n\n");



	printf("***Axiomatic tests:***\n\n");

	printf("AX 1 - Empty test: \n");
	empty_queue_test();

	printf("AX 2 - Enqueue test: \n");
	empty_enque_test();

	printf("AX 3 & 4 - Enqueue dequeue test: \n");
	empty_enque_deque_test();

	printf("AX 5 & 6 - Empty & Nonempty queue Front test: \n");
	queue_front_test();



	printf("**Limit and type tests:***\n\n");

	printf("Testing adding different types:\n");
	type_test();

	printf("Testing 10000 values:\n");
	capacity_test();

	printf("Testing if any function affects list element order:\n");
	order_type_test();

	printf("Testing structs:\n");
	test_queue_structs();

}




/*
void empty_deque_test()
{

	queue *q=queue_empty(NULL);

	q = queue_dequeue(q);

	if (!queue_is_empty(q)) {
		fprintf(stderr, "FAIL. Empty queue is not empty after dequeue!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
		printf("FAILED.\n\n");
	}

	queue_kill(q);
	printf("PASSED.\n\n");

}

void empty_front_test()
{
	// Create empty list.
	queue *q=queue_empty(NULL);
	q = queue_front(q);

	if (!queue_is_empty(q)) {
		fprintf(stderr, "FAIL. Empty queue is not empty after dequeue!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	queue_kill(q);
	printf("PASSED.\n\n");

}
*/


/*
	char *c =  malloc(sizeof(*c));
	double *d =  malloc(sizeof(*d));
	long *l =  malloc(sizeof(*l));
	bool *b =  malloc(sizeof(*b));
	int *v = malloc(sizeof(*v));


	c="Svitri";
	*d=3.1478;
	*l=1234567;
	*b=true;
	*v=1;

	q = queue_enqueue(q, c);
	char *front_char = queue_front(q);
	printf("Queue: %s - ", front_char);
	queue_dequeue(q);

	q = queue_enqueue(q, d);
	double *front_double = queue_front(q);
	printf("%lf - ", *front_double);
	queue_dequeue(q);

	q = queue_enqueue(q, l);
	long *front_long = queue_front(q);
	printf(" %lu - ", *front_long);
	queue_dequeue(q);

	q = queue_enqueue(q, b);
	bool *front_bool = queue_front(q);
	printf(" %d - ", *front_bool);
	queue_dequeue(q);

	q = queue_enqueue(q, v);
	int *front_digit = queue_front(q);
	printf("%d\n", *front_digit);
	queue_dequeue(q);

*/



/*




*/
