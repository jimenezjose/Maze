#include <iostream>
#include <vector>

using namespace std;

int main() {
  int * x = (int *) malloc(sizeof(int));
  vector<int *> list;
  list.push_back(x);
  list.clear();
  return 0;
}
