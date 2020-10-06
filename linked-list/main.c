#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 
#include <omp.h>
#include <unistd.h>

//Segmentation fault (core dumped)

struct Node {
   int data;
   int key;
   struct Node *next;
};

struct Queue {
   struct Node *head;
   struct Node *tail;
};

struct Node* create(int data) {
   struct Node *node;
   node->data = data;
   return node;
};

struct Queue* append_node(struct Queue *queue, struct Node *node) {
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

struct Queue* add(struct Queue *queue, int data) {
   return append_node(queue, create(data));
}

struct Node* remove_node(struct Queue *queue) {
   struct Node *node;
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
   struct Queue *queue;

   #pragma omp parallel for
   for (int i = 0; i < 10; ++i) {
      add(queue, i);
   } 

   size_t totalProcessedCounter = 0;
    double timer_started = omp_get_wtime();
    omp_set_num_threads(5);
    #pragma omp parallel
    {
      struct Node *n;
      size_t processedCounter = 0;
      double started = omp_get_wtime();
      
      while ((remove_node(queue)) != NULL) {
         processNode();
         processedCounter++;
      }

        double elapsed = omp_get_wtime() - started;
        printf("Thread id: %d,  processed: %ld nodes, took: %f seconds \n",
               omp_get_thread_num(), processedCounter, elapsed);
        #pragma omp atomic
        totalProcessedCounter += processedCounter;
    }

    double elapsed = omp_get_wtime() - timer_started;
    printf("End. Processed %ld nodes. Took %f in total", totalProcessedCounter, elapsed);
//    Thread id: 4,  processed: 100 nodes, took: 5.114557 seconds
//    Thread id: 0,  processed: 111 nodes, took: 5.118820 seconds
//    Thread id: 2,  processed: 102 nodes, took: 5.125992 seconds
//    Thread id: 3,  processed: 95 nodes, took: 5.158186 seconds
//    Thread id: 1,  processed: 92 nodes, took: 5.173112 seconds
//    end. processed 500 nodes. took 5.17337 in total
   return 0;
}

void processNode() {
    int r = rand() % 9 + 1; // between 1 and 9
    usleep(r * 10000); // sleeps 0.001 or 0.090 second
}
