#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define numberOfDoctors 3
#define numberOfPatients 10
#define timeLimit 10

struct doctor
{
	pthread_mutex_t doctorMutex;
	int doctorID;
};

pthread_mutex_t mutexQueue;

struct doctor doctors[numberOfDoctors];
pthread_cond_t doctorCondition;
int doctorsCount;

pthread_t patients[numberOfPatients];

void finishConsultation(struct doctor _doctor, int patientID, int consultationTime, int waitingTime)
{
	printf("\nDoctor %d finished consulting patient %d. \n--> Consultation time: %d \n--> Waiting time: %d \n", _doctor.doctorID + 1, patientID + 1, consultationTime, waitingTime);
	
	//printf("\nDoctor %d finished consulting patient %d. \n", _doctor.doctorID + 1, patientID + 1);
	//printf("--> Consultation time: %d \n", consultationTime);
	//printf("--> Waiting time: %d \n", waitingTime);

	pthread_mutex_lock(&mutexQueue);
	doctors[doctorsCount] = _doctor;
	doctorsCount++;
	pthread_mutex_unlock(&mutexQueue);
	
	pthread_cond_signal(&doctorCondition);
}

void consultation(struct doctor *_doctor, int patientID, int waitingTime)
{
	int consultationTime = 1 + rand() % timeLimit;

	pthread_mutex_lock(&_doctor->doctorMutex);
	sleep(consultationTime);
	pthread_mutex_unlock(&_doctor->doctorMutex);

	finishConsultation(*_doctor, patientID, consultationTime, waitingTime);
}

void *goToConsultation(void *args)
{
	int patientID = *(int*) args;
	int startWaiting, stopWaiting, i;
	struct doctor _doctor;

	pthread_mutex_lock(&mutexQueue);

	startWaiting = time(NULL);

	while (doctorsCount == 0)
	{
		printf("\nPatient %d arrived and is waiting for a doctor. He is drinking a coffee while waiting. \n", patientID + 1);
		pthread_cond_wait(&doctorCondition, &mutexQueue);
	}

	stopWaiting = time(NULL);

	if (stopWaiting - startWaiting == 0)
	{
		printf("\nPacient %d arrived and did not wait for a doctor. \n", patientID + 1);
	}
	else
	{
		printf("\nDoctor %d is available. Patient %d can visit him now. \n", doctors[0].doctorID + 1, patientID + 1);
	}
	_doctor = doctors[0];

	for (i = 0; i < doctorsCount - 1; i++)
	{
		doctors[i] = doctors[i + 1];
	}
	doctorsCount--;

	pthread_mutex_unlock(&mutexQueue);

	consultation(&_doctor, patientID, stopWaiting - startWaiting);
}

int main(int argc, char *argv[])
{
	int i;

	if (pthread_mutex_init(&mutexQueue, NULL))
	{
		printf("ERROR: The queue mutex couldn't be initialized.");
		return errno;
	}

	if (pthread_cond_init(&doctorCondition, NULL))
	{
		printf("ERROR: The condition variable couldn't be initialized.");
		return errno;
	}

	for (i = 0; i < numberOfDoctors; i++)
	{
		struct doctor _doctor;

		_doctor.doctorID = i;

		if (pthread_mutex_init(&_doctor.doctorMutex, NULL))
		{
			printf("ERROR: The doctor mutex couldn't be initialized.");
			return errno;
		}

		doctors[doctorsCount] = _doctor;
		doctorsCount++;
	}

	for (i = 0; i < numberOfPatients; i++)
	{
		sleep(2);

		int patientID;
		patientID = i;

		if (pthread_create(&patients[i], NULL, &goToConsultation, &patientID))
		{
			printf("ERROR: The pacient thread couldn't be created.");
			return errno;
		}
	}

	for (i = 0; i < numberOfPatients; i++)
	{
		if (pthread_join(patients[i], NULL))
		{
			printf("ERROR: Failed to join thread %d", i);
			return errno;
		}
	}

	for (i = 0; i < numberOfDoctors; i++)
	{
		pthread_mutex_destroy(&doctors[i].doctorMutex);
	}

	pthread_mutex_destroy(&mutexQueue);
	pthread_cond_destroy(&doctorCondition);

	return 0;
}