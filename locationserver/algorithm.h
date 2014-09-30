#include <map>
#include <vector>
#include <set>
using namespace std;

struct SLServer;

extern "C"
{
    int findDisk(int id, int n, map<int, int> &_map, map<int, set<int> > &bucket);
    int addDisk(int id, int capacity, int &n, map<int, int> &_map, map<int, set<int> > &bucket, vector<SLServer> &server);
    int deleteDisk(int id, int n, map<int, int> &_map, map<int, set<int> > &bucket, vector<SLServer> &server);
    int addNode(int n, map<int, int> &_map, vector<SLServer> &server);
    int deleteNode(int n, map<int, int> &_map, vector<SLServer> &server);
};
