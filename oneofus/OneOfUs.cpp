#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
const int MAXN = 100;
using unit = pair<char, char>;
int m, n, cnt;
unit mp[MAXN][MAXN];

set<int> g[MAXN*MAXN];
vector<int>ans;

bool hasPath(const unit &x, const unit &y)
{
    return x.first == y.first || x.second == y.second;
}

void addLink(int x, int y)
{
    g[x].insert(y);
    g[y].insert(x);
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

void dfs(vector<int>&path, vector<bool>&vis, bool &flag)
{
    if(flag)    return;
    if(path.size() == cnt) {
        flag = true;
        ans = path;
        return;
    }
    int cur = path.back();

    vector<pair<int, int>>vec;
    for(auto x : g[cur]) {
        vec.emplace_back(g[x].size(), x);
    }
    sort(vec.begin(), vec.end());

    for(int i = 0; i < g[cur].size(); i++) {
        int x = vec[i].second;
        if(!vis[x]) {
            vis[x] = true;
            path.push_back(x);
            dfs(path, vis, flag);
            vis[x] = false;
            path.pop_back();
        }
    }
}

int main()
{
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

    pair<int, int>pr[MAXN * MAXN];
    for(int i = 0; i < cnt; i++) {
        pr[i].first = g[i].size();
        pr[i].second = i;
    }
    sort(pr, pr + cnt);

    for(int i = 0; i < cnt; i++) {
        vector<int>temp;
        vector<bool>vis;
        bool flag = false;
        vis.resize(cnt, false);
        int target = pr[i].second;
        temp.push_back(target);
        vis[target] = true;
        dfs(temp, vis, flag);
        if(flag) {
            break;
        }
    }

    bool first = true;
    for(auto x : ans) {
        int xx = x / m;
        int yy = x % m;
        if(first) {
            first = false;
        } else {
            cout << "_";
        }
        cout << yy << "," << xx;
    }
    cout << endl;
    return 0;
}

