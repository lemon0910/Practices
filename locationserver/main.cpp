#include <isotream>
#include <string>
#include <fstream>
#include <dlfcn.h>
#include <map>
#include <set>
#include <vector>
using namespace std;

struct SLServer
{
    int id;
    int capacity;
};

void getnum(int &a[], int n, char *str)
{
    int temp = 0;
    int index = 0;
    int i = 0;
    while(i != n)
    {
        if(str[index] == " " || str[index] == "\n")
        {
            a[i++] = temp;
            index++;
            temp = 0;
        }
        else
        {
            temp = temp * 10 + str[index++] - '0';
        }
    }
}

void init(int &n, int &m, map<int, int> &_map, map<int, set<int> > &bucket, vector<SLServer> &server)
{
    ifstream infile;
    infile.open("info", ifstream::in);

    if(!infile.is_open())
    {
        cerr << "file open error" << endl;
        return;
    }

    char str[256];
    memset(str, 0, sizeof(str));
    infile.getline(str, 256);
    int a[2];
    getnum(a, 2, str);
    n = a[0];
    m = a[1];

    for(int i = 0; i < m; ++i)
    {
        int temp[2];
        memset(str, 0, sizeof(str));
        infile.getline(str, 256);
        getnum(temp, 2, str);
        SLServer s;
        s.id = temp[0];
        s.capacity = temp[1];
        server.push_back(s);
    }

    for(int i = 0; i < n; ++i)
    {
        int temp[3];
        memset(str, 0, sizeof(str));
        infile.getline(str, 256);
        getnum(temp, 3, str);
        _map[temp[0]] = temp[2];
        bucket[temp[0]].insert(temp[1]);
    }

    infile.close();
}

int main()
{
    void *handle = dlopen("./libalgorithm.so", RTLD_LAZY);
    if(0 == handle)
    {
        cout << "dlopen error" << endl;
        return 0;
    }

    int n, m;
    map<int, int> _map;
    map<int, set<int> > bucket;
    vector<SLServer> server;
    init(n, m, _map, bucket, server);

    //typedef void (*Fun)();
    //Fun f1 = (Fun)dlsym(handle, "f");
    
    dlclose(handle);
    return 0;
}
