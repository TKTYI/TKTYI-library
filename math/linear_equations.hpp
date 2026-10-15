// https://github.com/TKTYI/TKTYI-library/blob/main/math/linear_equations.hpp
template<typename T>
pair<bool, vector<T>> solve_linear(vector<vector<T>> A, vector<T> b) {
  assert(!A.empty());
  int N = A.size(), M = A[0].size(), rk = 0;
  assert(b.size() == N);
  vector<int> C;
  for (int i = 0; i < M; i++) {
    int j = rk;
    while (j < N && !A[j][i].val()) j++;
    if (j == N) continue;
    swap(A[rk], A[j]);
    swap(b[rk], b[j]);
    C.emplace_back(i);
    T a = 1 / A[rk][i];
    b[rk] *= a;
    for (auto&x : A[rk]) x *= a;
    for (j = 0; j < N; j++) if (j != rk) {
      T a = A[j][i];
      b[j] -= a * b[rk];
      for (int k = 0; k < M; k++) A[j][k] -= a * A[rk][k];
    }
    rk++;
  }
  for (int i = rk; i < N; i++) if(b[i].val()) {
    return make_pair(false, vector<T>(0));
  }
  vector<T> ans(M);
  for (int i = 0; i < rk; i++) ans[C[i]] = b[i];
  return make_pair(true, ans);
}