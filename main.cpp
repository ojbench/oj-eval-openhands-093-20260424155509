#include <iostream>
#include <vector>
#include <set>
#include <tuple>
using namespace std;

// Direction: 0=North(up), 1=East(right), 2=South(down), 3=West(left)
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int main() {
    vector<vector<int>> grid(10, vector<int>(10));
    int startX = -1, startY = -1;
    
    // Read input
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 4) {
                startX = i;
                startY = j;
            }
        }
    }
    
    int x = startX, y = startY;
    int dir = 0; // Start facing north (up)
    int score = 0;
    
    // Track visited states (position + direction) to detect loops
    set<tuple<int, int, int>> visited;
    
    // Mark starting position as empty
    grid[x][y] = 1;
    
    while (true) {
        // Check for loop
        if (visited.count({x, y, dir})) {
            cout << "Silly Pacman" << endl;
            return 0;
        }
        visited.insert({x, y, dir});
        
        // Try to move following right-hand rule: right > straight > left > back
        bool moved = false;
        for (int turn = 0; turn < 4; turn++) {
            // turn: 0=right, 1=straight, 2=left, 3=back
            int newDir;
            if (turn == 0) newDir = (dir + 1) % 4; // right
            else if (turn == 1) newDir = dir; // straight
            else if (turn == 2) newDir = (dir + 3) % 4; // left
            else newDir = (dir + 2) % 4; // back
            
            int nx = x + dx[newDir];
            int ny = y + dy[newDir];
            
            // Check bounds
            if (nx < 0 || nx >= 10 || ny < 0 || ny >= 10) continue;
            
            // Check if not wall
            if (grid[nx][ny] != 0) {
                // Valid move
                x = nx;
                y = ny;
                dir = newDir;
                
                // Check what's at this position
                if (grid[x][y] == 2) {
                    // Eat bean
                    score += 2;
                    grid[x][y] = 1; // Bean consumed
                } else if (grid[x][y] == 3) {
                    // Hit ghost
                    score -= 500;
                    cout << score << endl;
                    return 0;
                }
                
                moved = true;
                break;
            }
        }
        
        // If no valid move found, we're stuck (shouldn't happen with valid input)
        if (!moved) {
            cout << score << endl;
            return 0;
        }
    }
    
    return 0;
}
