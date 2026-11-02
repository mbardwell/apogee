/* C: generic algorithm compiled once in a library; strategy = function pointer. */
void scale(int* b, int n, int (*f)(int)) { for (int i = 0; i < n; ++i) b[i] = f(b[i]); }
