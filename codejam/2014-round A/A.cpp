#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
    int T;
    scanf("%d", &T);
    vector< vector<int> > m = { 
    { 0, 2, 3, 5, 6, 7, 8, 9 },
    { 0, 1, 2, 3, 4, 7, 8, 9 },
    { 0, 1, 3, 4, 5, 6, 7, 8, 9 },
    { 0, 2, 3, 5, 6, 8, 9 },
    { 0, 2, 6, 8 },
    { 0, 4, 5, 6, 8, 9 },
    { 2, 3, 4, 5, 6, 8, 9 }
    };

    map<int, string> key;
    key[0] = "1111110";
    key[1] = "0110000";
    key[2] = "1101101";
    key[3] = "1111001";
    key[4] = "0110011";
    key[5] = "1011011";
    key[6] = "1011111";
    key[7] = "1110000";
    key[8] = "1111111";
    key[9] = "1111011";

    for (int cas = 1; cas <= T; ++cas)
    {
        int n;
        scanf("%d", &n);
        char str[110][10];
        memset(str, 0, sizeof(str));
        for (int i = 0; i < n; ++i)
            scanf("%s", str[i]);

        int a[10];
        vector<int> ans;
        for (int i = 0; i < n; ++i)
        {
            memset(a, 0, sizeof(a));
            if (strcmp(str[i], "0000000") == 0)
                continue;
            for (int j = 0; j < 7; ++j)
            {
                if (str[i][j] == '1')
                {
                    for (int k = 0; k < m[j].size(); ++k)
                        a[m[j][k]]++;
                }
            }

            int maxn = 0;
            for (int l = 0; l < 10; ++l)
            {
                if (a[l] > maxn)
                    maxn = a[l];
            }

            if (ans.size() == 0)
            {
                for (int l = 0; l < 10; ++l)
                if (a[l] == maxn)
                    ans.push_back(l);
            }
            else
            {
                vector<int>::iterator it;
                for (it = ans.begin(); it != ans.end(); ++it)
                {
                    if ((*it) != - 1 && a[(*it) - i] != maxn)
                        *it = -1;
                }
            }
        }

        int cnt = 0, val = 0;
        for (int i = 0; i < ans.size(); i++)
        {
            if (ans[i] != -1)
            {
                val = ans[i];
                cnt++;
            }
        }

        if (cnt != 1)
        {
            printf("Case #%d: ERROR!\n", cas);
            continue;
        }
        int flag[10];
        memset(flag, 0, sizeof(flag));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < 7; ++j)
            {
                if (str[i][j] != key[val][j])
                    flag[j] = 1;
            }

            if (val == 0)
                val = 9;
            else
                val--;
        }

        printf("Case #%d: ", cas);
        for (int i = 0; i < 7; ++i)
        {
            if (flag[i])
                printf("0");
            else
                printf("%c", key[val][i]);
        }
        printf("\n");
    }

    return 0;
}
