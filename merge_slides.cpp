#include <iostream>
#include <vector>
#include <sstream>
#include <climits>

using namespace std;

vector<string> tokenize(const string& data) {
    vector<string> result;
    string token;
    stringstream ss(data);

    while (ss >> token) {
        result.push_back(token);
    }
    return result;
}

int str2int (const string &str) {
    stringstream ss(str);
    int num;
    if((ss >> num).fail())
    {
        return -1;
    }
    return num;
}

int merge_slides(const vector<int>& cost){
    int N = cost.size()-1;
    if(N == 1)
        return 0;

    vector<int> sum(N+1, 0);
    vector< vector<int> > dp(N+1, vector<int>(N+1,0));
    vector< vector<int> > num(N+1, vector<int>(N+1,0));

    for(int i=1; i<=N; i++)
        sum[i] = sum[i-1] + cost[i];

    for (int i=1; i <= N; i++)
        sum[i] = sum[i-1] + cost[i];

    for (int i=1; i <= N; i++)
        num[i-1][i] = i;

    for (int d=2; d <= N; d++) {
        for (int i=0; i+d <= N; i++) {
            int j = i + d;
            dp[i][j] = INT_MAX;

            for (int k = num[i][j-1]; k <= num[i+1][j]; k++) {
                int minimum = dp[i][k] + dp[k][j] + sum[j] - sum[i];
                if (dp[i][j] > minimum){
                    dp[i][j] = minimum;
                    num[i][j] = k;
                }
            }
        }
    }
    return dp[0][N];
}

int main() {
    string input;

    while(true){
        getline(cin, input);
        if(input.empty())
            return 0;

        vector<string> tokens = tokenize(input);
        vector<int> values;
        bool error = false;

        for(int i =0; i< tokens.size(); i++)
            if(str2int(tokens[i]) == -1) error = true;

        if(error) {
            cout << "Invalid Input\n";
            continue;
        }

        values.push_back(0);
        for(int i =0; i< tokens.size(); i++)
            values.push_back(str2int(tokens[i]));

        cout << merge_slides(values) << endl;
    }
}