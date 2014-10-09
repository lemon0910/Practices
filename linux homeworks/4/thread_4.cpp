#include <cstring>
#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <signal.h>
using namespace std;

#define BUFFERLENGTH 1000
#define BLOCKSIZE 16

struct SLResource
{
    long type;
    char *address;
    long len;
};

struct SLBuffer
{
    long readPosition;
    long writePosition;
    SLResource item[BUFFERLENGTH];
    bool isNULL[BUFFERLENGTH];
    long bufferLength;
}buffer;

void *blkProducer(void *);
void *blkConsumer(void *);

pthread_mutex_t stderrMutex = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t stdoutMutex = PTHREAD_MUTEX_INITIALIZER; 

pthread_mutex_t bufferMutex = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t bufferReadCond = PTHREAD_COND_INITIALIZER; 
pthread_cond_t bufferWriteCond = PTHREAD_COND_INITIALIZER; 

static void sigExit(int signo)
{
    cout << "the process is exited" << endl;
    exit(0);
}

int main(int argc, char *argv[])
{
	pthread_t *tids;
	int cnt = 0;
    int nProducers, nConsumers;
    if (argc != 3)
    {
        cerr << "usage: " << argv[0]
            << " nProducers nConsumers" << endl;
        return -1;
    }

    if(signal(SIGINT, sigExit) == SIG_ERR)
    {
        cout << "can't catch SIGINT" << endl;
    }

	nProducers = atoi(argv[1]);
	nConsumers = atoi(argv[2]);

	tids = (pthread_t *) malloc((nProducers + nConsumers) * sizeof(pthread_t));

    for(int i = 0; i < buffer.bufferLength; ++i)
    {
        buffer.item[i].address = 0;
        buffer.isNULL[i] = true;
    }
    buffer.writePosition = buffer.readPosition = 0;


    for (int i = 0; i < nProducers; ++i)
    {
       if(pthread_create(&tids[cnt++], NULL, blkProducer, NULL) == -1)
           perror("create producer failed");
    }

    for (int i = 0; i < nConsumers; ++i)
    {
       if(pthread_create(&tids[cnt++], NULL, blkConsumer, NULL) == -1)
           perror("create consumer failed");
    }

    pthread_mutex_lock(&stdoutMutex);
    cout << "init success!" << endl;
    pthread_mutex_unlock(&stdoutMutex);

	for (int i = 0; i < nProducers; ++i )
	{
		pthread_join(tids[i], NULL);
		pthread_mutex_lock(&stdoutMutex);
		cout << "producers " << i << " exit" << endl;
		pthread_mutex_unlock(&stdoutMutex);
	}


	for (int i = 0; i < nConsumers; ++i )
	{
		pthread_join(tids[nProducers + i], NULL);
		pthread_mutex_lock(&stdoutMutex);
		cout << "consumer " << i << " exit" << endl;
		pthread_mutex_unlock(&stdoutMutex);
	}
    return 0;
}


void *blkProducer(void *arg)
{ 
    char *ptr;
    for (;;)
    {
        pthread_mutex_lock(&bufferMutex);
        if(buffer.isNULL[buffer.writePosition] == true)
        {
            if ((ptr = (char *)(malloc(BLOCKSIZE))) == NULL)
            {
                pthread_mutex_unlock(&bufferMutex);
                continue;
            }
            else
            {
                memset(ptr, '1', BLOCKSIZE);
                buffer.item[buffer.writePosition].address = ptr;
                buffer.isNULL[buffer.writePosition] = false;
                buffer.writePosition = (buffer.writePosition + 1) % BUFFERLENGTH;
                pthread_cond_signal(&bufferReadCond);
                pthread_mutex_lock(&stdoutMutex);
                cout << "the block " << (long)ptr << " is produced" << endl;
                pthread_mutex_unlock(&stdoutMutex);
            }
        }
        else
        {
            while(buffer.isNULL[buffer.writePosition] == false)
                pthread_cond_wait(&bufferWriteCond, &bufferMutex);
            pthread_mutex_unlock(&bufferMutex);
            continue;
        }
        pthread_mutex_unlock(&bufferMutex);

    }

    return NULL;
}

void *blkConsumer(void *arg)
{
    SLResource block;

    for (;;)
    {
        pthread_mutex_lock(&bufferMutex);
        if(buffer.isNULL[buffer.readPosition] == false)
        {
            block = buffer.item[buffer.readPosition];
            buffer.isNULL[buffer.readPosition] = true;
            buffer.readPosition = (buffer.readPosition + 1) % BUFFERLENGTH;
            pthread_cond_signal(&bufferWriteCond);
        }
        else
        {
            while(buffer.isNULL[buffer.readPosition] == true)
                pthread_cond_wait(&bufferReadCond, &bufferMutex);
            pthread_mutex_unlock(&bufferMutex);
            continue;
        }
        
        pthread_mutex_unlock(&bufferMutex);


        pthread_mutex_lock(&stdoutMutex);
        cout << "the block " << (long)block.address << " is consumed" << endl;
        pthread_mutex_unlock(&stdoutMutex);

        free((void*)block.address);

    }
    return NULL;
}
