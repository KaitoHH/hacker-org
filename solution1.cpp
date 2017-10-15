// brote-force approch for crossflip solution O(2^(n^2)) 
#include <iostream>
#include <algorithm>
#include <set>
#include <bitset>
#define ALL(iterable) begin(iterable),end(iterable)
using namespace std;

vector<vector<int>>mp;
int mapping[] = {1, 0, -1};
int n, m;

bool crossFlip(int &state)
{
    if(state == 0) {
        state = 1;
    } else if(state == 1) {
        state = 0;
    } else {
        return false;
    }
    return true;
}

bool check(vector<vector<int>>vec)
{
    for(auto i : vec) {
        for(auto j : i) {
            if(!j) {
                return false;
            }
        }
    }
    return true;
}

void flip(int index, vector<vector<int>>&vec)
{
    int line = index / m;
    int col = index % m;
    for(int i = line; i >= 0 && crossFlip(vec[i][col]); i--);
    for(int i = line + 1; i < n && crossFlip(vec[i][col]); i++);
    for(int i = col; col >= 0 && crossFlip(vec[line][i]); i--);
    for(int i = col + 1; i < m && crossFlip(vec[line][i]); i++);
    crossFlip(vec[line][col]);
}

int main()
{
    set<int>wall;
    cin >> n;
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        int len = s.length();
        vector<int>cur;
        for(int j = 0; j < len; j++, cnt++) {
            int temp = mapping[s[j] - '0'];
            cur.push_back(temp);
            if(!~temp) {
                wall.insert(cnt);
            }
        }
        mp.push_back(cur);
    }
    m = mp[0].size();
    unsigned long long final = (1ull << cnt) - 1;
    unsigned long long answer = -1;
    set<unsigned long long>vis;
    for(unsigned long long i = 0; i < final; i++) {
        auto temp = mp;
        auto state = i;
        for(auto x : wall) {
            state &= ~(1ull << x);
        }
        int counter = 0;
        if(!vis.insert(state).second)	continue; // optimize out
        while(state) {
            if(state & 1) {
                flip(counter, temp);
            }
            counter++;
            state >>= 1;
        }
        if(check(temp)) {
            answer = i;
            break;
        }
    }
    auto ans = std::bitset<64>(answer).to_string();
    std::reverse(ALL(ans));
    cout << string(ans.begin(), ans.begin() + cnt) << endl;
    return 0;
}

