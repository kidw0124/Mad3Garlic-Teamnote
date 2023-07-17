// Longest increasing subsequence
// O(n*logn)
vec lis(vec& arr) {
  int n = arr.size();
  vec tmp = vec();
  vec from = vec();
  for (int x: arr) {
    int loc = lower_bound(tmp.begin(), tmp.end(), x) - tmp.begin();
    if (loc == tmp.size()) {
      tmp.push_back(x);
    }
    else {
      tmp[loc] = x;
    }
    from.push_back(loc);
  }
  vec lis = vec(tmp.size());
  int target = tmp.size()-1;
  for (int i=n-1; i>=0; i--) {
    if (target == from[i]) {
      lis[target--] = arr[i];
    }
  }
  return lis;
}