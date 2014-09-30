#include "algorithm.h"
#include <iostream>
using namespace std;

struct SLServer
{
    int id;
    int capacity;
};

int findDisk(int id, int n, map<int, int> &_map, map<int, set<int> > &bucket)
{
    int temp = id % n;
    if(_map.end() == _map.find(temp))
    {
        return -1;
    }

    if(bucket[temp].end() == bucket[temp].find(id))
    {
        return -1;
    }

    return _map[temp];
}

int addDisk(int id, int capacity, int &n, map<int, int> &_map, map<int, set<int> > &bucket, vector<SLServer> &server)
{
    int temp = id % n;

    if(bucket[temp].end() != bucket[temp].find(id))
    {
        return -1;
    }

    int machine = _map[temp];
    bool success = false;

    for(int i = 0; i < server.size(); ++i)
    {
        if(server[i].id == machine)
        {
            if(server[i].capacity > capacity)
                success = true;

            break;
        }
    }

    if(success)
    {
        bucket[temp].insert(id);
        cout << "notify storage node to save disk" << endl;
        return 0;
    }
    else
    {
        //进行扩容
        
    }
}

int deleteDisk(int id, int n, map<int, int> &_map, map<int, set<int> > &bucket, vector<SLServer> &server)
{
    int temp = id % n;
    if(bucket[temp].end() == bucket[temp].find(id))
    {
        return -1;
    }

    bucket[temp].erase(id);
    cout << "notify storage node to delete disk" << endl;
    return 0;
}

int addNode(int n, map<int, int> &_map, vector<SLServer> &server)
{
    return 0;
}

int deleteNode(int n, map<int, int> &_map, vector<SLServer> &server)
{
    return 0;
}
