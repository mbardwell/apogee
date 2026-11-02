// C++14: strategy is a generic lambda; the template inlines it into the loop.
template <class F> void scale(int* b, int n, F f) { for (int i = 0; i < n; ++i) b[i] = f(b[i]); }
void gain(int* b, int n) { scale(b, n, [](auto x) { return x * 2; }); }
