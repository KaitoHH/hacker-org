#include <iostream>
#include <algorithm>
#include <ctime>
#include <set>
using namespace std;
const int MAXN = 100;
using unit = pair<char, char>;
int m, n, cnt;
unit mp[MAXN][MAXN];

vector<int> g[MAXN*MAXN];
set<pair<int, int>>link;
bool vis[MAXN*MAXN] {0};

bool hasPath(const unit &x, const unit &y)
{
    return x.first == y.first || x.second == y.second;
}

void addLink(int x, int y)
{
    if(link.emplace(x, y).second) {
        link.emplace(y, x);
        g[x].push_back(y);
        g[y].push_back(x);
    }
}

void printMap()
{
    for(int i = 0 ; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << mp[i][j].first << mp[i][j].second << " ";
        }
        cout << endl;
    }
}

int getIndex(int x, int y)
{
    return x * m + y;
}

int getRand(int maxv)
{
    return rand() % maxv;
}

int main()
{
    srand(time(NULL));
    cin >> n >> m;
    cnt = m * n;
    string str;
    cin >> str;
    for(int i = 0, cur = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            mp[i][j].first = str[cur++];
            mp[i][j].second = str[cur++];
        }
    }
    for(int i = 0; i < n ; i++) {
        for(int j = 0 ; j < m; j++) {
            for(int ii = 0; ii < n; ii++) {
                if(ii == i)   continue;
                if(hasPath(mp[i][j], mp[ii][j])) {
                    addLink(getIndex(i, j), getIndex(ii, j));
                }
            }
            for(int jj = 0; jj < m; jj++) {
                if(jj == j)   continue;
                if(hasPath(mp[i][j], mp[i][jj])) {
                    addLink(getIndex(i, j), getIndex(i, jj));
                }
            }
        }
    }
#ifdef DEBUG
    printMap();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cout << "[" << i << ", " << j << "]: ";
            for(auto x : g[getIndex(i, j)]) {
                int xx = x / m;
                int yy = x % m;
                cout << "(" << x / m << ", " << x % m << ") = " << mp[xx][yy].first << mp[xx][yy].second << " ";
            }
            cout << endl;
        }
    }
#endif
    vector<int>path;
    int starting = getRand(cnt);
    path.push_back(starting);
    vis[starting] = true;
    while(path.size() != cnt) {
        int cur = path.back();
        vector<int>unvis;
        for(auto x : g[cur]) {
            if(!vis[x]) {
                unvis.push_back(x);
            }
        }
        if(!unvis.empty()) {
            int next = getRand(unvis.size());
            path.push_back(unvis[next]);
            vis[unvis[next]] = true;
        } else {
            int next = getRand(g[cur].size());
            for(auto it = path.begin(); it != path.end(); it++) {
                if(*it == g[cur][next]) {
                    reverse(it + 1, path.end());
                    if(it + 2 == path.end()) {
                        reverse(path.begin(), path.end());
                    }
                    break;
                }
            }
        }
#ifdef DEBUG
        cout << "path:" << endl;
        for(auto x : path) cout << x << " ";
        cout << endl;
#endif
    }

    bool first = true;
    for(auto x : path) {
        int xx = x / m;
        int yy = x % m;
        if(first) {
            first = false;
        } else {
            cout << "_";
        }
        cout << hex << yy << "," << xx;
    }
    cout << endl;
    return 0;
}

