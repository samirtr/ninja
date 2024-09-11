Problem statement
Given an integer ‘N’, the task is to find the number of integers between 1 to N whose decimal number representation contains only 0s and 1s.

For example, 1011 , 11, 100 are all valid integers since they consist of 1s and 0s only, however 210, 3401 are not valid integers.

Note :
You don’t need to print anything. It has already been taken care of. Just implement the given function.
Detailed explanation ( Input/output format, Notes, Images )
Constraints :
1 <= T <= 10^4
1 <= N <= 10^9

Time Limit: 1sec
Sample input 1 :
2
10
21
Sample output 1 :
2
3
Explanation for sample input 1 :
In first case, there are only 2 numbers between 1 to 10 that contain only 1s or 0s i.e (1,10)In second case, there are only 3 numbers  containing only 0s and 1s i.e (1,10,11) 
Sample input 2 :
3
250
1505
3010
Sample output 2 :
7
15
15

Solution:
  #include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Function to count numbers with only 0s and 1s between 1 and N
int countBinaryNumbers(int N) {
    queue<long long> q;
    q.push(1); // Start with 1
    int count = 0;
    
    // BFS-like approach to generate numbers consisting of only 0s and 1s
    while (!q.empty()) {
        long long num = q.front();
        q.pop();
        
        // If the number is greater than N, stop processing further
        if (num > N) continue;
        
        // Count this valid number
        count++;
        
        // Generate the next numbers by appending 0 and 1
        q.push(num * 10);   // Append 0
        q.push(num * 10 + 1); // Append 1
    }
    
    return count;
}

int main() {
    int T;
    cin >> T; // Number of test cases
    vector<int> results;
    
    while (T--) {
        int N;
        cin >> N; // For each test case, read N
        results.push_back(countBinaryNumbers(N));
    }
    
    // Output the results for all test cases
    for (int result : results) {
        cout << result << endl;
    }
    
    return 0;
}


  
