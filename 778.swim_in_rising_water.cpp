#include<vector>
#include<iostream>
#include<deque>

using namespace std;

class Solution {
public:
    int swimInWater(vector<vector<int> >& grid) {
        // N^2, once t is big enough, swim to destination in no time
        // binary search (min number equal or greater than t_threshold)
        
        // Given a T, can you tell whether it is feasible
        // Tricky part is that the route can twist in any way (not strickly right-down)
        // BFS
        // DFS
        int n = grid.size(), t = 0;
        int low = 0, high = n*n - 1;

        while (low < high) {
            t = (low + high) / 2;
            vector<vector<bool> > reached(n, vector<bool>(n, false));
            //test(grid, reached, t, 0, 0);
            testBFS(grid, reached, t);
            if (reached[n-1][n-1]) {
                high = t;
            } else {
                low = t + 1;
            }
        }
        if (low > high) return -1;
        return low;
    }


    // DFS
    void test(vector<vector<int> >& grid, vector<vector<bool> >& reached, int t, int i, int j) {
        int n = grid.size();
        if (grid[i][j] > t) {
            return;
        } else {
            reached[i][j] = true;
            if (i-1 >=0 && !reached[i-1][j]) {
                test(grid, reached, t, i-1, j);
            } 
            if (i+1 <= n-1 && !reached[i+1][j]) {
                test(grid, reached, t, i+1, j);
            }
            if (j-1 >= 0 && !reached[i][j-1]) {
                test(grid, reached, t, i, j-1);
            }
            if (j+1 <= n-1 && !reached[i][j+1]) {
                test(grid, reached, t, i, j+1);
            }
        } 
    }
    
    // BFS 
    void testBFS(vector<vector<int> >&grid, vector<vector<bool> >& reached, int t) {
        int n = grid.size(), i, j;
        deque<pair<int, int>> deq;
        if (grid[0][0] <= t) {
            reached[0][0] = true;
            deq.emplace_back(0, 0);
        }
        
        while (!deq.empty()) {
            auto p = deq.front();
            deq.pop_front();
            i = p.first;
            j = p.second;
            
            if (i-1 >=0 && !reached[i-1][j] && grid[i-1][j]<=t) {
                reached[i-1][j] = true;
                deq.emplace_back(i-1, j);
            } 
            if (i+1 <= n-1 && !reached[i+1][j] && grid[i+1][j]<=t) {
                reached[i+1][j] = true;
                deq.emplace_back(i+1, j);
            }
            if (j-1 >= 0 && !reached[i][j-1] && grid[i][j-1]<=t) {
                reached[i][j-1] = true;
                deq.emplace_back(i, j-1);
            }
            if (j+1 <= n-1 && !reached[i][j+1] && grid[i][j+1]<=t) {
                reached[i][j+1] = true;
                deq.emplace_back(i, j+1);
            }
        }
    }
};

int main() {
    Solution solu;
    vector<vector<int> > grid(2, vector<int>(2));
    grid[0][0] = 2;
    grid[0][1] = 0;
    grid[1][0] = 1;
    grid[1][1] = 3;
    solu.swimInWater(grid);

    return 0;
}
