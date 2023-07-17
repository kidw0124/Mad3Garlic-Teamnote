// Extended Euclidean Algorithm
// ax+by=g
// return (g,x,y)
// O(logn) : n is max(a,b)
// Recursive function to demonstrate the extended Euclidean algorithm.
// It returns multiple values using tuple in C++.
tuple<int, int, int> extended_gcd(int a, int b)
{
    if (a == 0) {
        return make_tuple(b, 0, 1);
    }
 
    int gcd, x, y;
 
    // unpack tuple returned by function into variables
    tie(gcd, x, y) = extended_gcd(b % a, a);
 
    return make_tuple(gcd, (y - (b/a) * x), x);
}