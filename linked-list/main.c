#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 
#include <omp.h>
#include <unistd.h>

typedef struct Node {
   int data;
   struct Node *next;
} node_t;

typedef struct Queue {
   node_t * head;
   node_t * tail;
} queue_t;

node_t * create(int data) {
   node_t * node = NULL;
   node = (node_t *)malloc(sizeof(node_t));
   node->data = data;

   return node;
};

queue_t * append_node(queue_t * queue, node_t * node) {
   #pragma omp critical
   {
      if (queue->head == NULL){
         queue->head = node;
         queue->tail = node;
      } else {
         queue->tail->next = node;
         queue->tail = node;
      }
   }
   return queue;
};

 node_t * remove_node(queue_t * queue) {
   node_t * node;
   #pragma omp critical
   {
      node = queue->head;
      if (queue->head != NULL)
            queue->head = queue->head->next;
   }
   return node;
};

void processNode();

int main() {
   srand(12);
   queue_t queue = {.head = NULL,.tail = NULL};
   queue_t * queuePointer = &queue;

   #pragma omp parallel for
   for (int i = 0; i < 100; ++i) {
      append_node(queuePointer, create(i));
   } 

   size_t totalProcessedCounter = 0;
    double timer_started = omp_get_wtime();
    omp_set_num_threads(5);

    #pragma omp parallel
    {
      node_t * n;
      size_t processedCounter = 0;
      double started = omp_get_wtime();
      
      while ((remove_node(queuePointer)) != NULL) {
         processNode();
         processedCounter++;
      }

        double elapsed = omp_get_wtime() - started;
        printf("Thread id: %d,  processed: %ld nodes, took: %f seconds \n", omp_get_thread_num(), processedCounter, elapsed);
        #pragma omp atomic
        totalProcessedCounter += processedCounter;
    }

    double elapsed = omp_get_wtime() - timer_started;
    printf("End. Processed %ld nodes. Took %f in total\n", totalProcessedCounter, elapsed);

   return 0;
}

void processNode() {
    int r = rand() % 9 + 1;
    usleep(r * 10000);
}
