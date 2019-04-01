
#include <semaphore.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define num_philosopher 5
#define num_fork 5
#define max 0.5
#define min 0.0

int request_Matrix[num_philosopher];

int alloc_Matrix[num_philosopher];

sem_t check[num_fork];
pthread_mutex_t lock;

void pick(int philosopher_Id, int fork_Id)
{
	request_Matrix[philosopher_Id] = 1;

	sem_wait(&check[fork_Id]);

	request_Matrix[philosopher_Id] = 0;
	alloc_Matrix[philosopher_Id] = 1;
}

void printMatrix()
{
	int i, j;

	pthread_mutex_lock(&lock);
	printf("\nAllocation Matrix :\n");
	for (i = 0; i < num_philosopher; i++)
	{
			printf("%d ", alloc_Matrix[i]);
	}
         printf("\n");
	printf("\nRequest Matrix :\n");

	for (i = 0; i < num_philosopher; i++)
	{
			printf("%d ", request_Matrix[i]);
	}
     printf("\n");
	pthread_mutex_unlock(&lock);
}

void *startPhilosopher(void *arg)
{
	int philosopher_Id = *((int *)arg);

	while (1)
	{
		int leftFork = philosopher_Id;
		int rightFork = (leftFork + 1) % num_philosopher;

		sleep(2);

		pick(philosopher_Id, leftFork);
		printf("\nPhilosopher %d grab fork %d (left)\n", philosopher_Id, leftFork);

		sleep(2);

		pick(philosopher_Id, rightFork);

		if (!alloc_Matrix[philosopher_Id])
		{
			pick(philosopher_Id, leftFork);
			printf("\nPhilosopher %d grab fork %d (left)\n", philosopher_Id, leftFork);
		}

		printf("\nPhilosopher %d grab fork %d (right)\n", philosopher_Id, rightFork);
		printf("\nPhilosopher %d starts eating.\n", philosopher_Id);

		sleep(2);

		printMatrix();

		sleep(2);

		printf("\nPhilosopher %d ends eating and releases forks %d (left) and %d (right)\n", philosopher_Id, leftFork, rightFork);

		alloc_Matrix[philosopher_Id] = 0;
		sem_post(&check[leftFork]);

		printf("\nPhilosopher %d starts thinking\n", philosopher_Id);

		alloc_Matrix[philosopher_Id] = 0;
		sem_post(&check[rightFork]);
	}
}

int main()
{
	pthread_t threadId[num_philosopher];
	pthread_mutex_init(&lock, NULL);
	srand(time(0));

	for (int i = 0; i < num_fork; i++)
	{
		sem_init(&check[i], 0, 1);
	}

	for (int philosopher = 0; philosopher < num_philosopher; philosopher++)
	{
		int thread = pthread_create(&threadId[philosopher], NULL, startPhilosopher, &philosopher);

		if (thread < 0)
		{
			printf("Thread creation failed for philosopher %d\n", philosopher);
		}

		printf("Philosopher %d starts thinking\n", philosopher);

		sleep(1);
	}

	while (1)
	{
		bool flag = false;
		int i;

		for (i = 0; i < num_fork; i++)
		{
			if (!alloc_Matrix[i])
			{
				flag = true;
			}
		}

		if (flag)
		{
			continue;
		}

		printf("Parent detects deadlock, going to initiate recovery\n");
		int dropFork = rand() % num_fork;
		printf("Parent preempts Philosopher %d\n", dropFork);

		alloc_Matrix[dropFork] = 0;
		sem_post(&check[dropFork]);

		printMatrix();
		sleep(2);
	}
}