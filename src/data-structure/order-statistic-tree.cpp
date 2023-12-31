#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>
#include <iostream>
using namespace __gnu_pbds;
using namespace std;
// Ordered set is a policy based data structure in g++ that keeps the unique elements in
// sorted order. It performs all the operations as performed by the set data structure
// in STL in log(n) complexity and performs two additional operations also in log(n)
// complexity order_of_key (k) : Number of items strictly smaller than k
// find_by_order(k) : K‐th element in a set (counting from zero) tree<key_type,
// value_type(set if null), comparator, ...>
using ordered_set =
    tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;
using ordered_multi_set = tree<int, null_type, less_equal<int>, rb_tree_tag,
                               tree_order_statistics_node_update>;
void m_erase(ordered_multi_set &OS, int val) {
  int index = OS.order_of_key(val);
  ordered_multi_set::iterator it = OS.find_by_order(index);
  if (*it == val) OS.erase(it);
}
int main() {
  ordered_set X;
  for (int i = 1; i < 10; i += 2) X.insert(i);  // 1 3 5 7 9
  cout << boolalpha;
  cout << *X.find_by_order(2) << endl;              // 5
  cout << *X.find_by_order(4) << endl;              // 9
  cout << (X.end() == X.find_by_order(5)) << endl;  // true
  cout << X.order_of_key(-1) << endl;               // 0
  cout << X.order_of_key(1) << endl;                // 0
  cout << X.order_of_key(4) << endl;                // 2
  X.erase(3);
  cout << X.order_of_key(4) << endl;  // 1
  for (int t : X) cout << t << ' ';   // 1 5 7 9
}
