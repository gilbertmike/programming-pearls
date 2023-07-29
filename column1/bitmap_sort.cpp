#include <fstream>
#include <iostream>
#include <set>
#include <vector>

/**
 * On laptop: 3M numbers 10M max
 * real	0m11.515s
 * user	0m9.257s
 * sys	0m2.252s
 * 
 * I could try batching the file I/O, but I won't.
 */
std::ostream& bitmap_sort(std::ostream& out, std::istream& in)
{
  auto bitmap = std::vector<bool>();

  auto keep_going = true;
  while (keep_going)
  {
    size_t elem = 0;
    in >> elem;
    if (in.good())
    {
      if (bitmap.size() < elem+1)
      {
        bitmap.resize(elem+1, false);
      }
      bitmap.at(elem) = true;
    }
    keep_going = !in.eof();
  }

  for (size_t i = 0; i < bitmap.size(); ++i)
  {
    if (bitmap.at(i))
    {
      out << i << std::endl;
    }
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

  bitmap_sort(out, in);

  return 0;
}
