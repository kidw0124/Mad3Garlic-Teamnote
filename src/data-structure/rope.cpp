#include<ext/rope>
using namespace __gnu_cxx;
crope arr; // or rope<T> arr;
string str; // or vector<T> str;
// Insert at position i with O(log n)
arr.insert(i, str);
// Delete n characters from position i with O(log n)
arr.erase(i, n);
// Replace n characters from position i with str with O(log n)
arr.replace(i, n, str);
// Get substring of length n starting from position i with O(log n)
crope sub = arr.substr(i, n);
// Get character at position i with O(1)
char c = arr.at(i); // or arr[i]
// Get length of rope with O(1)
int len = arr.size();