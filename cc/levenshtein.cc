#include <iostream>
#include <string>
using namespace std;

class Twodarray {
private:
  int *arr_;
  int x_;
  int y_;

public:
  Twodarray(int x, int y);
  ~Twodarray();
  int get(int x, int y);
  void set(int x, int y, int val);
  void serialize();
};
Twodarray::Twodarray(int x, int y) : x_(x), y_(y) { arr_ = new int[x_ * y_]; }

Twodarray::~Twodarray() { delete[] arr_; }
int Twodarray::get(int x, int y) { return arr_[(x * y_) + y]; }
void Twodarray::set(int x, int y, int val) { arr_[(x * y_) + y] = val; }
void Twodarray::serialize() {
  for (int i = 0; i < this->x_ * y_; ++i) {
    cout << arr_[i] << " ";
  }
  cout << endl;
}

int lvstdist(string a, string b) {
  int x = a.size()+1;
  int y = b.size()+1;
  Twodarray t(x, y);
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      if (0 == i)
        t.set(i, j, j);
      else if (0 == j)
        t.set(i, j, i);
      else {
        int cost;
        if (a[i-1] == b[j-1])
          cost = 0;
        else
          cost = 1;
        int temp =
            min(min(t.get(i - 1, j), t.get(i, j - 1)) + 1, t.get(i - 1, j - 1) + cost);
        t.set(i, j, temp);
      }
    }
  }
  t.serialize();
  return t.get(x - 1, y - 1);
}

int main() {
  string a;
  string b;
  cin >> a >> b;
  cout << lvstdist(a, b) << endl;
  return 0;
}
