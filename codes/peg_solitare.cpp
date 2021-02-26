#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> start = {{-1, -1, 1, 1, 1, -1, -1},
                             {-1, -1, 1, 1, 1, -1, -1},
                             {1, 1, 1, 1, 1, 1, 1},
                             {1, 1, 1, 0, 1, 1, 1},
                             {1, 1, 1, 1, 1, 1, 1},
                             {-1, -1, 1, 1, 1, -1, -1},
                             {-1, -1, 1, 1, 1, -1, -1}};

vector<vector<int>> goal = {{-1, -1, 0, 0, 0, -1, -1},
                            {-1, -1, 0, 0, 0, -1, -1},
                            {0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 1, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0},
                            {-1, -1, 0, 0, 0, -1, -1},
                            {-1, -1, 0, 0, 0, -1, -1}};

vector<vector<int>> test_strt = {{-1, -1, 1, 1, 1, -1, -1},
                                 {-1, -1, 1, 1, 1, -1, -1},
                                 {1, 1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 0, 1, 1},
                                 {1, 1, 1, 1, 1, 0, 1},
                                 {-1, -1, 1, 0, 0, -1, -1},
                                 {-1, -1, 0, 0, 0, -1, -1}};

class State
{
public:
    vector<vector<int>> st;
    int m = 7;
    vector<State> transitions;

    State(vector<vector<int>> state)
    {
        st.assign(state.begin(), state.end());
        transitions = vector<State>();
    }

    State()
    {
        st.assign(start.begin(), start.end());
        transitions = vector<State>();
    }

    // Define the comparison operator. It doesn't make any sense so just assign random truth values to it.
    bool operator<(const State &obj) const
    {
        return true;
    }

    bool operator<=(const State &obj) const
    {
        return true;
    }

    bool operator>(const State &obj) const
    {
        return false;
    }

    bool operator>=(const State &obj) const
    {
        return false;
    }

    bool operator==(const State &obj) const
    {
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                if (st[i][j] != obj.st[i][j])
                {
                    return false;
                }

        return true;
    }

    void print()
    {
        cout << "----------------------------------------------"
             << "\n";

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
                cout << st[i][j] << "\t";
            cout << endl;
        }

        cout << "----------------------------------------------"
             << "\n";
    }

    void find_transitions()
    {
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < m; j++)
            {
                //top
                if (i - 2 >= 0)
                {
                    if (st[i][j] == 1 && st[i - 1][j] == 1 && st[i - 2][j] == 0)
                    {
                        st[i][j] = 0;
                        st[i - 1][j] = 0;
                        st[i - 2][j] = 1;
                        transitions.push_back(State(st));
                        st[i][j] = 1;
                        st[i - 1][j] = 1;
                        st[i - 2][j] = 0;
                    }
                }
                //right
                if (j + 2 < 7)
                {
                    if (st[i][j] == 1 && st[i][j + 1] == 1 && st[i][j + 2] == 0)
                    {
                        st[i][j] = 0;
                        st[i][j + 1] = 0;
                        st[i][j + 2] = 1;
                        transitions.push_back(State(st));
                        st[i][j] = 1;
                        st[i][j + 1] = 1;
                        st[i][j + 2] = 0;
                    }
                }
                //bottom
                if (i + 2 < 7)
                {
                    if (st[i][j] == 1 && st[i + 1][j] == 1 && st[i + 2][j] == 0)
                    {
                        st[i][j] = 0;
                        st[i + 1][j] = 0;
                        st[i + 2][j] = 1;
                        transitions.push_back(State(st));
                        st[i][j] = 1;
                        st[i + 1][j] = 1;
                        st[i + 2][j] = 0;
                    }
                }

                //left
                if (j - 2 >= 0)
                {
                    if (st[i][j] == 1 && st[i][j - 1] == 1 && st[i][j - 2] == 0)
                    {
                        st[i][j] = 0;
                        st[i][j - 1] = 0;
                        st[i][j - 2] = 1;
                        transitions.push_back(State(st));
                        st[i][j] = 1;
                        st[i][j - 1] = 1;
                        st[i][j - 2] = 0;
                    }
                }
            }
        }
    }

} initial, temp;

struct comp
{
    constexpr bool operator()(
        pair<int, State> const &a,
        pair<int, State> const &b)
        const noexcept
    {
        return a.first >= b.first;
    }
};

bool cell_visited[7][7];
int bfs(State S1, pair<int, int> cell)
{
    queue<pair<int, int>> fifo;
    // map<pair<int, int>, bool> cell_visited;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            cell_visited[i][j] = false;
        }
    }

    cell_visited[cell.first][cell.second] = true;
    // cell_visited[cell] = true;
    cell_visited[0][0] = true;
    cell_visited[1][0] = true;
    cell_visited[0][1] = true;
    cell_visited[1][1] = true;
    cell_visited[0][5] = true;
    cell_visited[1][5] = true;
    cell_visited[0][6] = true;
    cell_visited[1][6] = true;
    cell_visited[5][0] = true;
    cell_visited[6][0] = true;
    cell_visited[5][1] = true;
    cell_visited[6][1] = true;
    cell_visited[5][5] = true;
    cell_visited[6][5] = true;
    cell_visited[5][6] = true;
    cell_visited[6][6] = true;

    // around the root node
    if (cell.first - 1 >= 0)
    {
        if (!cell_visited[cell.first - 1][cell.second])
        {
            fifo.push({cell.first - 1, cell.second});
        }
    }
    if (cell.second + 1 < 7)
    {
        if (!cell_visited[cell.first][cell.second + 1])
        {
            fifo.push({cell.first, cell.second + 1});
        }
    }
    if (cell.first + 1 < 7)
    {
        if (!cell_visited[cell.first + 1][cell.second])
        {
            fifo.push({cell.first + 1, cell.second});
        }
    }
    if (cell.second - 1 >= 0)
    {
        if (!cell_visited[cell.first][cell.second - 1])
        {
            fifo.push({cell.first, cell.second - 1});
        }
    }
    while (!fifo.empty())
    {
        pair<int, int> pt = fifo.front();
        fifo.pop();
        cell_visited[pt.first][pt.second] = true;
        int isodd = abs(cell.first - pt.first) + abs(cell.second - pt.second);
        if (S1.st[pt.first][pt.second] == 1) // && (isodd % 2)
        {
            return isodd;
        }
        if (pt.first - 1 >= 0)
        {
            if (!cell_visited[pt.first - 1][pt.second])
            {
                fifo.push({pt.first - 1, pt.second});
            }
        }
        if (pt.second + 1 < 7)
        {
            if (!cell_visited[pt.first][pt.second + 1])
            {
                fifo.push({pt.first, pt.second + 1});
            }
        }
        if (pt.first + 1 < 7)
        {
            if (!cell_visited[pt.first + 1][pt.second])
            {
                fifo.push({pt.first + 1, pt.second});
            }
        }
        if (pt.second - 1 >= 0)
        {
            if (!cell_visited[pt.first][pt.second - 1])
            {
                fifo.push({pt.first, pt.second - 1});
            }
        }
    }
    return 0;
}

int heuristic(State S1)
{
    int Hcost = 0;
    if (S1.st == goal)
    {
        return 0;
    }
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (S1.st[i][j] == 1)
            {
                // pair<int,int> nearest_cell = bfs(S1,{i,j});
                // if(bfs(S1, {i, j})>0){
                //     Hcost +=(100);
                // }
                Hcost += bfs(S1, {i, j});
            }
        }
    }
    return Hcost;
}

int heuristic2(State S)
{
    int Hcost=0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if(S.st[i][j]==0){
                //top
                if(i-1>=0){
                    if(S.st[i-1][j]==1){
                        Hcost++;
                    }
                }
                //right
                if(j+1<7){
                    if(S.st[i][j+1]==1){
                        Hcost++;
                    }
                }
                //bottom
                if(i+1<7){
                    if(S.st[i+1][j]==1){
                        Hcost++;
                    }
                }
                //left
                if(j-1>=0){
                    if(S.st[i][j-1]==1){
                        Hcost++;
                    }
                }
            }
        }
    }
    return Hcost;
}
int closetogoal(State curr)
{
    int cost = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (curr.st[i][j] == 1)
            {
                cost += (abs(i - 3) + abs(j - 3));
            }
        }
    }
    return cost;
}

void best_first_search()
{
    priority_queue<pair<int, State>, vector<pair<int, State>>, comp> frontier;
    map<State, bool> visited;
    State strt(start), goal_state(goal);
    // Initialize the frontier with the start state.
    frontier.push(make_pair(0, test_strt));
    while (!frontier.empty())
    {
        // Pop the state with highest priority (lowest cost)
        auto it = frontier.top();

        // if (visited[it.second] == true){
        //     frontier.pop();
        // }
        // cout <<"Heuristic cost : "<<it.first<<endl;
        it.second.print();

        frontier.pop();

        if (it.second == goal_state)
        {
            cout << "Congratulations!!!! Goal State reached";
            break;
        }

        if (!visited[it.second])
        {
            it.second.find_transitions();

            visited[it.second] = true;

            for (auto tem : it.second.transitions)
            {
                if (visited[tem] == false)
                {
                    // int Hcost = -1*(heuristic(tem)*abs(closetogoal(it.second)-closetogoal(tem)));
                    int Hcost = heuristic2(tem) + closetogoal(tem)+heuristic(tem); //closetogoal(tem); //+ heuristic(tem);
                    frontier.push(make_pair(Hcost, tem));
                }
            }
        }
    }
}

int main()
{
    best_first_search();
    return 0;
}