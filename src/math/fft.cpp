void fft(int sign, int n, double *real, double *imag) {
  double theta = sign * 2 * pi / n;
  for (int m = n; m >= 2; m >>= 1, theta *= 2) {
    double wr = 1, wi = 0, c = cos(theta), s = sin(theta);
    for (int i = 0, mh = m >> 1; i < mh; ++i) {
      for (int j = i; j < n; j += m) {
        int k = j + mh;
        double xr = real[j] - real[k], xi = imag[j] - imag[k];
        real[j] += real[k], imag[j] += imag[k];
        real[k] = wr * xr - wi * xi, imag[k] = wr * xi + wi * xr;
      }
      double _wr = wr * c - wi * s, _wi = wr * s + wi * c;
      wr = _wr, wi = _wi;
    }
  }
  for (int i = 1, j = 0; i < n; ++i) {
    for (int k = n >> 1; k > (j ^= k); k >>= 1)
      ;
    if (j < i) swap(real[i], real[j]), swap(imag[i], imag[j]);
  }
}
// Compute Poly(a)*Poly(b), write to r; Indexed from 0
// O(n*logn)
int mult(int *a, int n, int *b, int m, int *r) {
  const int maxn = 100;
  static double ra[maxn], rb[maxn], ia[maxn], ib[maxn];
  int fn = 1;
  while (fn < n + m) fn <<= 1;  // n + m: interested length
  for (int i = 0; i < n; ++i) ra[i] = a[i], ia[i] = 0;
  for (int i = n; i < fn; ++i) ra[i] = ia[i] = 0;
  for (int i = 0; i < m; ++i) rb[i] = b[i], ib[i] = 0;
  for (int i = m; i < fn; ++i) rb[i] = ib[i] = 0;
  fft(1, fn, ra, ia);
  fft(1, fn, rb, ib);
  for (int i = 0; i < fn; ++i) {
    double real = ra[i] * rb[i] - ia[i] * ib[i];
    double imag = ra[i] * ib[i] + rb[i] * ia[i];
    ra[i] = real, ia[i] = imag;
  }
  fft(-1, fn, ra, ia);
  for (int i = 0; i < fn; ++i) r[i] = (int)floor(ra[i] / fn + 0.5);
  return fn;
}