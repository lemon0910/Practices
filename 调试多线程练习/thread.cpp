#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <iostream>
using namespace std;

void *func(void *arg)
{
    cout << "new thread" << endl;
}

int main(int argc, char *argv[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, &func, NULL);
    pthread_join(tid, NULL);

    return 0;
}
