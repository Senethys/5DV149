
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void print_ints(const void *data)
{
	printf("[%d]", *(int*)data);
}


/*

Ax 1 Isempty (Empty)

Ax 2 !(Isempty(Enqueue(v,q)))

Ax 3 Isempty(q) -> Dequeue(Enqueue(v, q)) = q

Ax 4 !(Isempty(q)) -> Dequeue (Enqueue(v, q)) = Enqueue(v, Dequeue(q))

Ax 5 Isempty(q) -> Fron(Enqueue(v,q)) = v

Ax 6 !(Isempty(q)) -> Front(Enqueue(v, q)) = Front(q)

Ax 7 Length(Empty) = 0

Ax 8 Length (Enqueue(v, q)) = Lenght(q) + 1


*/



int main(void)
{
	// Create the queue.
	queue *q = queue_empty(free);
	for (int i=1; i<=3; i++) {
		// Allocate memory for one int.
		int *v = malloc(sizeof(*v));
		// Set value.
		*v=i;
		// Push value on stack.
		q=queue_enqueue(q,v);
  }


  printf("QUEUE before dequeuing:\n");
	queue_print(q, print_ints);

	queue_dequeue(q);

	printf("QUEUE after dequeuing:\n");
	queue_print(q, print_ints);

	queue_kill(q);





/*
    //queue
    *queue_empty(free_function free_func);

    //bool
    queue_is_empty(const queue *q);

    //queue
    *queue_enqueue(queue *q, void *v);

    //queue
    *queue_dequeue(queue *q);

    //void
    *queue_front(const queue *q);

     //void
    queue_kill(queue *q);


*/
}



















}
