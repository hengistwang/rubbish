#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int fast_pow(int x, int y) {
  int ans = 1;
  for (;y;y>>=1) {
    if ((y & 1) == 1)
      ans *= x;
    x *= x;
  }
  return ans;
}

template <typename T>
vector<vector<T>> power_set(vector<T> v) {
  vector<vector<T>> ans;
  for (int i = 0; i < fast_pow(2, v.size()); ++i) {
    vector<T> t;
    int temp = i;
    int j = 0;
    while (temp) {
      if (temp & 1) 
        t.push_back(v[j]);
      ++j;
      temp >>= 1;
    }
    ans.push_back(t);
  }
  std::sort(ans.begin(),ans.end(),[](const vector<T>& a, const vector<T>& b){
      return a.size() < b.size();
      });
  return ans;
}

int main() {
  vector<int> i = {1,2,3};
  auto ans = power_set(i);
  cout<< ans.size() << endl;
  for(auto &i : ans) {
    for (auto &j : i) {
      cout << j << " ";
    }
    cout << endl;
  }
  cout << "#############################" << endl;
  vector<char> c = {'a','b','c'};
  auto cans = power_set(c);
  cout<< cans.size() << endl;
  for(auto &i : cans) {
    for (auto &j : i) {
      cout << j << " ";
    }
    cout << endl;
  }

  return 0;
}

