#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>

void juggle_rotate_left(std::string& str, size_t shift)
{
  if (shift == str.size())
  {
    return;
  }

  auto gcd = std::gcd(str.size(), shift);
  for (size_t start = 0; start < gcd; ++start)
  {
    auto tmp = str.at(start);
    size_t i = start;
    size_t j = (i+shift)%str.size();
    while (j != start)
    {
      str.at(i) = str.at(j);
      i = j;
      j = (j+shift)%str.size();
    }
    str.at(i) = tmp;
  }
}

void dnc_rotate_left(std::string& str, size_t shift)
{
}

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cout << "I need a string input and shift amount!" << std::endl;
    return -1;
  }

  auto input = std::string(argv[1]);
  size_t shift = atol(argv[2]);

  juggle_rotate_left(input, shift);
}
