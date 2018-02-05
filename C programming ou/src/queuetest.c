//The real one.
//Den verifierar att listan bara är tom en gång. Dv.s
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "list.h"

/******************************/

void print_ints(const void *data)
{
	printf("[%d]", *(int*)data);
}

/******************************/

void empty_queue_test()
{
	queue *q=queue_empty(NULL);

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
	int *v = malloc(sizeof(*v));
	*v=1;

	q = queue_enqueue(q, v);
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

	if (!queue_is_empty(q)) {
		fprintf(stderr, "FAIL. New queue is not empty after enqueue and deqeue!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}
	q = queue_dequeue(queue_enqueue(queue_enqueue(q, v), v2));

	if (queue_is_empty(q)) {
		fprintf(stderr, "FAIL. New queue is empty after enqueue-deqeue-enqueue!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	q = queue_enqueue(queue_dequeue(q), v2);

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
	t = queue_front(queue_enqueue(q, v));

	if (queue_is_empty(q) || (!(*t == *v))) {
		fprintf(stderr, "FAIL. Queue is empty after enqueue and front or\n");
		fprintf(stderr, "latest value added is not the same as front.\n");
		fprintf(stderr, "Value 1: %d - Value 2: %d", *t, *v);
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	v = queue_front(queue_enqueue(q, v2));
	t = queue_front(q);

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

void capacity_test()
{
	// Create empty list.

	int *checkSum1 = calloc(1, sizeof(*checkSum1));
	int *checkSum2 = calloc(1, sizeof(*checkSum2));
	queue *q=queue_empty(NULL);

	for(int i = 0; i <= 100; i++) {
		int *number = malloc(sizeof(*number));
		*number = i;
		q = queue_enqueue(q, number);

		*checkSum1 += i;
	}

	if (queue_is_empty(q)) {
		fprintf(stderr, "FAIL. Empty queue is not empty after 10000 values!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	for(int i = 100; i >= 0; i--) {
		q = queue_dequeue(q);
		*checkSum2 += i;
	}

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

void type_test()
{
	queue *q = queue_empty(NULL);

	char *c =  malloc(sizeof(*c));
	double *d =  malloc(sizeof(*d));
	long *l =  malloc(sizeof(*l));
	bool *b =  malloc(sizeof(*b));
	int *v = malloc(sizeof(*v));


	c="t";
	*d=3.14;
	*l=12345667;
	*b=true;
	*v=1;

	q = queue_enqueue(q, c);
	q = queue_enqueue(q, d);
	q = queue_enqueue(q, l);
	q = queue_enqueue(q, b);
	q = queue_enqueue(q, v);

	if (queue_is_empty(q)) {
		fprintf(stderr, "FAIL. New queue is empty after enqueue!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}



	queue_kill(q);
	printf("PASSED.\n\n");

}

/******************************/

queue *add_all_types(queue *q)
{

	char *c =  malloc(sizeof(*c));
	double *d =  malloc(sizeof(*d));
	long *l =  malloc(sizeof(*l));
	bool *b =  malloc(sizeof(*b));
	int *v = malloc(sizeof(*v));

	 c="t";
	*d=3.14;
	*l=12345667;
	*b=true;
	*v=1;

	q = queue_enqueue(q, c);
	q = queue_enqueue(q, d);
	q = queue_enqueue(q, l);
	q = queue_enqueue(q, b);
	q = queue_enqueue(q, v);

//type av q är que pekare
	return q;
}

/******************************/

void order_test()
{
	queue *q = queue_empty(NULL);
	q = add_all_types(q);

	if (queue_is_empty(q)) {
		fprintf(stderr, "FAIL. New queue is empty after enqueue!\n");
		queue_kill(q);
		exit(EXIT_FAILURE);
	}

	queue_kill(q);
	printf("PASSED.\n\n");

}

/******************************/




//									------------------------------------------
/****************************************MAIN**********************************/
//									--------------------_____-----------------


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

	printf("Testing 10000 values:\n");
	capacity_test();

	printf("Testing adding different types:\n");
	type_test();

	printf("Testing if any function affects list element order:\n");
	order_test();

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
