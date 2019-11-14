#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>


using namespace std;

vector<string> tokenize(const string& data, const char delimiter = ' ') {
    vector<string> result;
    string token;
    stringstream ss(data);

    while (getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

int str2int (const string &str) {
    stringstream ss(str);
    int num;
    if((ss >> num).fail())
    {
        return 0;
    }
    return num;
}

int add(int cost[], int i, int j) {
    if(i==0) return cost[j];
    else return cost[j] - cost[i-1];
}


int mergeSlides(const vector<int>& cost){
    int size = cost.size();
    int sum[size];
    vector< vector<int> > dp;

    //Calculate sum
    sum[0] = cost[0];
    for(int i = 1; i < size; i++) sum[i] += sum[i-1] + cost[i];
    //Init
    for(int i = 0; i < size-1; i++) dp[i][i+1] = cost[i] + cost[i+1];

    for(int gap = 2; gap < size; gap++){	//i와 j간 gap 3칸부터
        for(int i = 0; i+gap < size; i++){	//i인덱스
            int j = i+gap;	//j인덱스
            dp[i][j] = INT_MAX;	//MIN을 구하기 위해

            for(int k = i; k < j; k++)	//i~j 사이의 k값
                dp[i][j] = min(dp[i][k] + dp[k+1][j] + add(sum, i, j), dp[i][j]);
        }
    }
    return dp[0][cost.size()-1];
}

int main(){
    string input;
    while(true){
        getline(cin, input);
        if(input.empty())
            return 0;

        vector<string> tokens = tokenize(input);
        vector<int> values;
        vector<int> sum;
        bool error = false;

        for(int i =0; i< tokens.size(); i++)
            if(str2int(tokens[i]) == 0) error = true;

        if(error) {
            printf("Invalid Input\n");
            continue;
        }

        //values.push_back(0);
        for(int i =0; i< tokens.size(); i++)
            values.push_back(str2int(tokens[i]));

        /*for(int i =0; i< tokens.size(); i++)
            printf("%d ",values[i]);*/

        printf("%d\n", mergeSlides(values));
    }
}

