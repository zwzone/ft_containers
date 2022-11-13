#include <iostream>
#include <vector>
#include "vector.hpp"

typedef std::vector<int>::iterator itVec;

void print(itVec begin, itVec end)
{
  std::cout << "[ ";
  while (begin != end)
  {
    std::cout << *begin << ' ';
    begin++;
  }
  std::cout << ']' << std::endl;
}

void print(const std::vector<int> &v)
{
  std::cout << "[ ";
  for (size_t i = 0; i < v.size(); i++)
    std::cout << v[i] << ' ';
  std::cout << ']' << std::endl;
}

int main(void)
{
  std::vector<int> v1(3, 100);
  std::vector<int> v2(4, 200);
  v1.erase(v1.begin() + 1, v1.end());
  print(v1.begin(), v2.end());
  print(v1);
  return (0);
}
