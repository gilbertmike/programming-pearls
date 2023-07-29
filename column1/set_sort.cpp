#include <fstream>
#include <iostream>
#include <set>

/**
 * On laptop: 3M numbers 10M max
 * real	0m8.553s
 * user	0m6.158s
 * sys	0m2.385s
 * 
 * I could try batching the file I/O, but I won't.
 */
std::ostream& set_sort(std::ostream& out, std::istream& in)
{
  auto sorted_set = std::set<size_t>();
  auto keep_going = true;
  while (keep_going)
  {
    size_t elem = 0;
    in >> elem;
    if (in.good())
    {
      sorted_set.emplace(elem);
    }
    keep_going = !in.eof();
  }

  for (auto elem : sorted_set)
  {
    out << elem << std::endl;
  }

  return out;
}

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cout << "I need an input and output file name!" << std::endl;
    return -1;
  }

  auto in = std::ifstream(argv[1]);
  auto out = std::ofstream(argv[2]);

  set_sort(out, in);

  return 0;
}
