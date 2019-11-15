#include <iostream>
#include <memory.h>

using namespace std;

string ics(const string& input){
    //string -> char[]
    int length = input.length();
    char arr[length];
    for(int i=0; i<length; i++)
        arr[i] = input.at(i);

    //length of increasing subsequence for each index
    int dp[length];

    //position for backtrace
    int pos[length];
    int idx = 0;
    memset(pos, -1, sizeof(pos));

    //saved for backtrace
    int saved[length];
    int k = 0;


    int max = 0;
    dp[0] = 1;

    for(int i =1; i<length; i++){
        dp[i] = 1;
        for(int j=0; j<i; j++){
            if(arr[i] > arr[j] && dp[j] + 1 > dp[i]){
                dp[i] = dp[j] + 1;
                pos[i] = j;
            }
        }
        if(max < dp[i]) {
            max = dp[i];
            idx = i;
        }
    }

    saved[k++] = idx;
    while(pos[idx] != -1){
        saved[k++] = pos[idx];
        idx = pos[idx];
    }

    string result;
    for(int i=k-1; i>=0; i--)
        result += arr[saved[i]];

    return result;
}

int main(){
    string input;
    while(true){
        getline(cin, input);
        int idx = input.find_first_of(' ');
        input = input.substr(0, idx);

        if(input.empty())
            return 0;

        cout << ics(input) << endl;
    }
}
