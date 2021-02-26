#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class pair_cust {
    public:
    string first;
    int second;
    pair_cust(string first, int second) {
        this->first = first;
        this->second = second;
    }
};

bool win_check(string st) {
    if (st[0] == st[3] && st[3] == st[6] && st[0] != '_')
        return true;
    if (st[1] == st[4] && st[4] == st[7] && st[1] != '_')
        return true;
    if (st[2] == st[5] && st[5] == st[8] && st[2] != '_')
        return true;

    if (st[0] == st[1] && st[1] == st[2] && st[0] != '_')
        return true;
    if (st[3] == st[4] && st[4] == st[5] && st[3] != '_')
        return true;
    if (st[6] == st[7] && st[7] == st[8] && st[6] != '_')
        return true;

    if (st[0] == st[4] && st[4] == st[8] && st[0] != '_')
        return true;
    
    if (st[2] == st[4] && st[4] == st[6] && st[2] != '_')
        return true;
    
    return false;
}

bool is_filled(string st) {
    for (int i = 0; i < 9; i++)
        if (st[i] == '_') return false;
    return true;
}

void print(string st) {
    cout << st.substr(0, 3) << "\n";
    cout << st.substr(3, 3) << "\n";
    cout << st.substr(6, 3) << "\n";
}

map<pair<string, int>, int> scores;
string val = "OX";
string test_state = "_________";

int count_m_m = 0, count_abp = 0;

// Min-Max algorithm. Generates all the possible states and find out what is the min-max value of each node.
int recursive(string states, int turn) {
    count_m_m++;
    if (turn == 0) {
        int mn = 2;
        for (int i = 0; i < 9; i++) {
            if (states[i] != '_') continue;
            states[i] = val[turn];
            if (win_check(states)) {
                states[i] = '_';
                scores[make_pair(states, turn)] = -1;
                // print(states);
                // cout << -1 << "\n";
                return -1;
            }
            mn = min(recursive(states, turn ^ 1), mn);
            states[i] = '_';
        }
        if (mn == 2)
            mn = 0;
        
        scores[make_pair(states, turn)] = mn;
        // print(states);
        // cout << mn << "\n";
        // cout << states << " " << mn << "\n";
        return mn;
    }

    int mx = -2;
    for (int i = 0; i < 9; i++) {
        if (states[i] != '_') continue;
        states[i] = val[turn];
        if (win_check(states)) {
            states[i] = '_';
            scores[make_pair(states, turn)] = 1;
            // print(states);
            // cout << 1 << "\n";
            return 1;
        }
        mx = max(recursive(states, turn ^ 1), mx);
        states[i] = '_';
    }

    if (mx == -2)
        mx = 0;
    scores[make_pair(states, turn)] = mx;
    // print(states);
    // cout << mx << "\n";
    // cout << states << " " << mx << "\n";
    return mx;
}

// We can take infinity = 2 in this case because 2 will never be achieved in naughts and crosses.
pair_cust alpha_beta_pruning(string state, int alpha, int beta, int turn) {
    // Everything almost remains same as the min-max except the condition that stops the algorithm from exploring the nodes further
    count_abp++;
    if (turn) {
        int ans = -2;
        string m_state = state;
        for (int i = 0; i < 9; i++) {
            if (state[i] != '_') continue;
            state[i] = 'X';
            if (win_check(state)) return pair_cust(state, 1);
            if (is_filled(state)) return pair_cust(state, 0);

            auto it = alpha_beta_pruning(state, alpha, beta, turn ^ 1);
            if (it.second > ans) {
                ans = it.second;
                m_state = state;
            }

            alpha = max(alpha, ans);

            if (alpha >= beta) return pair_cust(state, ans);
            state[i] = '_';
        }
        return pair_cust(m_state, ans);
    }

    int ans = 2;
    string m_state = state;
    for (int i = 0; i < 9; i++) {
        if (state[i] != '_') continue;
        state[i] = 'O';
        if(win_check(state)) return pair_cust(state, -1);
        if(is_filled(state)) return pair_cust(state, 0);

        auto it = alpha_beta_pruning(state, alpha, beta, turn ^ 1);
        if (ans > it.second) {
            ans = it.second;
            m_state = state;
        }

        beta = min(beta, ans);
        if (beta <= alpha) return pair_cust(state, ans);
        state[i] = '_';
    }
    return pair_cust(m_state, ans);
}

int min_max_playing() {
    // Who will play first??
    cout << "This game will be played using min-max search.\n";
    cout << "Who will play first (0 for O and 1 for X. You are O.): ";
    int play;
    cin >> play;

    string start = "_________";
    recursive(start, play);

    while (true) {
        if (is_filled(start)) {
            cout << "Game drawn!!\n";
            return 0;
        }

        if (play == 0) {
            int a, b;
            cout << "Enter zero based co-ordinates of the position of new O: ";
            cin >> a >> b;
            while (start[a * 3 + b] != '_') {
                cout << "Invalid Co-ordinates. Enter new ones: ";
                cin >> a >> b;
            }
            start[a * 3 + b] = 'O';
            cout << "The game state is now:\n";
            print(start);
            if (win_check(start)) {
                cout << "Congrats!!! You won\n";
                return 0;
            }
            play ^= 1;
        }
        else {
            int mx = -2;
            string ns = "";
            for (int i = 0; i < 9; i++) {
                if (start[i] == '_') {
                    start[i] = 'X';
                    int curr = scores[make_pair(start, play ^ 1)];
                    if (win_check(start)) {
                        cout << "My move is:\n";
                        print(start);
                        cout << "I won!!!\n";
                        return 0;
                    }
                    if (curr >= mx) {
                        ns = start;
                        mx = curr;
                    }
                    start[i] = '_';
                }
            }
            start = ns;

            cout << "My move is:\n";
            print(ns);
            play ^= 1;
        }

    }
}

int abp_play() {
    cout << "This game will be played using Alpha-Beta pruning\n";
    // Who will play first??
    cout << "Who will play first (0 for O and 1 for X. You are O.): ";
    int play;
    cin >> play;

    string start = "_________";

    while (true) {
        if (is_filled(start)) {
            cout << "Game drawn!!\n";
            return 0;
        }

        if (play == 0) {
            int a, b;
            cout << "Enter zero based co-ordinates of the position of new O: ";
            cin >> a >> b;
            while (start[a * 3 + b] != '_') {
                cout << "Invalid Co-ordinates. Enter new ones: ";
                cin >> a >> b;
            }
            start[a * 3 + b] = 'O';
            cout << "The game state is now:\n";
            print(start);
            if (win_check(start)) {
                cout << "Congrats!!! You won\n";
                return 0;
            }
            play ^= 1;
        }
        else {
            auto curr = alpha_beta_pruning(start, -2, 2, play);
            cout << "My move is:\n";
            print(curr.first);
            start = curr.first;
            if (win_check(start)) {
                cout << "I won!!!";
                return 0;
            }

            play ^= 1;
        }

    }
}

int main () {
    alpha_beta_pruning(test_state, -2, 2, 0);
    recursive(test_state, 0);

    cout << "Number of explored nodes in min-max is: " << count_m_m << endl;
    cout << "Number of explored nodes in alpha-beta pruning is: " << count_abp << endl;

    abp_play();
    // auto it = alpha_beta_pruning(test_state, -2, 2, 1);
    // cout << it.first << " " << it.second << endl;
    return 0;
}