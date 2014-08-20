#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
    int T, cas;
    int len;
    char dir[10];
    scanf("%d", &T);
    for (cas = 1; cas <= T; ++cas)
    {
        memset(dir, 0, sizeof(dir));
        scanf("%d %s", &len, dir);
        vector < vector<int> > m;
        vector < vector<bool> > used;
        for (int i = 0; i < len; ++i)
        {
            vector<int> v;
            vector<bool> flag;
            for (int j = 0; j < len; ++j)
            {
                int temp;
                scanf("%d", &temp);
                v.push_back(temp);
                flag.push_back(false);
            }
            m.push_back(v);
            used.push_back(flag);
        }

        if (strcmp(dir, "right") == 0)
        {
            for (int i = 0; i < len; ++i)
            {
                for (int j = len - 2; j >= 0; --j)
                {
                    if (m[i][j] == 0)
                        continue;
                    int val = m[i][j];
                    int pos = j;
                    if (pos + 1 < len && m[i][pos + 1] == 0)
                    {
                        pos++;
                        while (pos + 1 < len && m[i][pos + 1] == 0)
                            pos++;
                    }
                    m[i][j] = 0;
                    m[i][pos] = val;
                    if (pos + 1 < len && m[i][pos] == m[i][pos + 1] && !used[i][pos + 1])
                    {
                        used[i][pos + 1] = true;
                        m[i][pos + 1] *= 2;
                        m[i][pos] = 0;
                    }
                }
            }
        }

        if (strcmp(dir, "left") == 0)
        {
            for (int i = 0; i < len; ++i)
            {
                for (int j = 1; j < len; ++j)
                {
                    if (m[i][j] == 0)
                        continue;
                    int val = m[i][j];
                    int pos = j;
                    if (pos - 1 >= 0 && m[i][pos - 1] == 0)
                    {
                        pos--;
                        while (pos - 1 >= 0 && m[i][pos - 1] == 0)
                            pos--;
                    }
                    m[i][j] = 0;
                    m[i][pos] = val;
                    if (pos - 1 >= 0 && m[i][pos] == m[i][pos - 1] && !used[i][pos - 1])
                    {
                        used[i][pos - 1] = true;
                        m[i][pos - 1] *= 2;
                        m[i][pos] = 0;
                    }
                }
            }
        }

        if (strcmp(dir, "up") == 0)
        {
            for (int j = 0; j < len; ++j)
            {
                for (int i = 1; i < len; ++i)
                {
                    if (m[i][j] == 0)
                        continue;
                    int val = m[i][j];
                    int pos = i;
                    if (pos - 1 >= 0 && m[pos - 1][j] == 0)
                    {
                        pos--;
                        while (pos - 1 >= 0 && m[pos - 1][j] == 0)
                            pos--;
                    }
                    m[i][j] = 0;
                    m[pos][j] = val;
                    if (pos - 1 >= 0 && m[pos][j] == m[pos - 1][j] && !used[pos - 1][j])
                    {
                        used[pos - 1][j] = true;
                        m[pos - 1][j] *= 2;
                        m[pos][j] = 0;
                    }
                }
            }
        }

        if (strcmp(dir, "down") == 0)
        {
            for (int j = 0; j < len; ++j)
            {
                for (int i = len - 2; i >= 0; --i)
                {
                    if (m[i][j] == 0)
                        continue;
                    int val = m[i][j];
                    int pos = i;
                    if (pos + 1 < len && m[pos + 1][j] == 0)
                    {
                        pos++;
                        while (pos + 1 < len && m[pos + 1][j] == 0)
                            pos++;
                    }
                    m[i][j] = 0;
                    m[pos][j] = val;
                    if (pos + 1 < len && m[pos][j] == m[pos + 1][j] && !used[pos + 1][j])
                    {
                        used[pos + 1][j] = true;
                        m[pos + 1][j] *= 2;
                        m[pos][j] = 0;
                    }
                }
            }
        }

        printf("Case #%d:\n", cas);
        for (int i = 0; i < len; ++i)
        {
            for (int j = 0; j < len; ++j)
            {
                printf("%d", m[i][j]);
                if (j == len - 1)
                    printf("\n");
                else
                    printf(" ");
            }
        }
    }

    return 0;
}
