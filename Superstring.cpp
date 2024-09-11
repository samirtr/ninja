Problem statement
You are given a set of strings. You have to find the length of the Optimal Superstring for this set.

Note:

1. A string is said to be the Superstring of a set of strings if all the strings of the set are present in it as a substring.

2. A Superstring is said to be an Optimal Superstring if its length is minimum out of all possible Superstrings for a given set of strings. 

3. Each string of the set consists of the uppercase English alphabet.
Detailed explanation ( Input/output format, Notes, Images )
Constraints:
1 <= N <= 14
1 <= |Si| <= 100

Time Limit: 1 sec.
Sample Input 1:
2
AA
AAAA
Sample Output 1:
4
Explanation of sample input 1:
In string “AAAA”, both strings “AA” and “AAAA” are present as substrings.
Sample input 2:
3
ABC
CDE
EFG
Sample output 2:
7
Explanation of sample input 2:
In string “ABCDEFG”, all the strings given in the set are present as a substring.

Solution:

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// Function to calculate the maximum overlap between suffix of s1 and prefix of s2
int calculateOverlap(const string& s1, const string& s2) {
    int max_overlap = 0;
    int min_len = min(s1.length(), s2.length());
    
    for (int k = 1; k <= min_len; ++k) {
        if (s1.substr(s1.length() - k) == s2.substr(0, k)) {
            max_overlap = k;
        }
    }
    return max_overlap;
}

int optimalSuperstring(vector<string> s, int size) {
    int n = size;

    // Step 1: Precompute the overlaps between all pairs of strings
    vector<vector<int>> overlaps(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                overlaps[i][j] = calculateOverlap(s[i], s[j]);
            }
        }
    }

    // Step 2: DP array to store the minimum length of superstring for a given set (represented by a bitmask)
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
    vector<vector<int>> parent(1 << n, vector<int>(n, -1));

    // Step 3: Initialize DP for the base case where each string is taken individually
    for (int i = 0; i < n; ++i) {
        dp[1 << i][i] = s[i].length();
    }

    // Step 4: Fill the DP table
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) { // If the i-th string is in the current set
                for (int j = 0; j < n; ++j) {
                    if (i != j && (mask & (1 << j))) { // If j-th string is also in the set
                        int prev_mask = mask ^ (1 << i);
                        int overlap_length = dp[prev_mask][j] + s[i].length() - overlaps[j][i];
                        if (overlap_length < dp[mask][i]) {
                            dp[mask][i] = overlap_length;
                            parent[mask][i] = j;
                        }
                    }
                }
            }
        }
    }

    // Step 5: Find the minimum length from the DP table
    int final_mask = (1 << n) - 1; // All strings are used
    int min_len = INT_MAX;
    int last = -1;
    for (int i = 0; i < n; ++i) {
        if (dp[final_mask][i] < min_len) {
            min_len = dp[final_mask][i];
            last = i;
        }
    }

    return min_len;
}

int main() {
    int n;
    cin >> n; // Number of strings
    
    vector<string> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i]; // Input strings
    }
    
    cout << optimalSuperstring(s, n) << endl; // Output the optimal superstring length
    
    return 0;
}
