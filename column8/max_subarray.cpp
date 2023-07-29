#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>

std::vector<int> load_array(std::istream& in)
{
  auto arr = std::vector<int>();

  int elem = 0;
  while (true)
  {
    in >> elem;
    if (in.good())
    {
      arr.emplace_back(elem);
    }
    else if (in.eof())
    {
      break;
    }
    else
    {
      throw std::logic_error("bad read!");
    }
  }

  return arr;
}

int max_subarray_a(const std::vector<int>& arr)
{
  int max = std::numeric_limits<int>::min();

  for (int i = 0; i < arr.size(); ++i)
  {
    int cur_count = 0;
    for (int j = i; j < arr.size(); ++j)
    {
      cur_count += arr.at(j);
    }
    max = std::max(max, cur_count);
  }

  return max;
}

int max_subarray_b(std::vector<int>& arr)
{
  size_t i = 0;
  size_t cur_ptr = 0;
  while (i < arr.size())
  {
    if (arr.at(i) > 0)
    {
      int sum = 0;
      size_t j = i;
      for (; j < arr.size() && arr.at(j) >= 0; ++j)
      {
        sum += arr.at(j);
        arr.at(j) = 0;
      }
      arr.at(cur_ptr) = sum;
      cur_ptr += 1;
      i = j;
    }
    else
    {
      int tmp = arr.at(i);
      arr.at(i) = 0;
      i += 1;

      arr.at(cur_ptr) = tmp;
      cur_ptr += 1;
    }
  }
  arr.resize(cur_ptr);

  return max_subarray_a(arr);
}

int max_subarray_c(std::vector<int>& arr)
{
  int max_so_far = 0;
  int max_end_here = 0;
  for (auto e : arr)
  {
    max_end_here = std::max(max_end_here + e, 0);
    max_so_far = std::max(max_so_far, max_end_here);
  }
  return max_so_far;
}

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cout << "I need a file input!" << std::endl;
    return -1;
  }

  auto in = std::ifstream(argv[1]);
  auto arr = load_array(in);
  in.close();

  std::cout << arr.size() << std::endl;

  auto tstart = std::chrono::high_resolution_clock::now();
  auto tend = std::chrono::high_resolution_clock::now();

  tstart = std::chrono::high_resolution_clock::now();
  auto max_a = max_subarray_a(arr);
  tend = std::chrono::high_resolution_clock::now();

  std::cout << max_a << std::endl;
  std::cout << "algorithm a: "
            << static_cast<double>((tend - tstart).count())/1000000
            << std::endl;

  auto arr_copy = arr;
  tstart = std::chrono::high_resolution_clock::now();
  auto max_b = max_subarray_b(arr);
  tend = std::chrono::high_resolution_clock::now();

  std::cout << max_b << std::endl;
  std::cout << "algorithm b: "
            << static_cast<double>((tend - tstart).count())/1000000
            << std::endl;

  arr_copy = arr;
  tstart = std::chrono::high_resolution_clock::now();
  auto max_c = max_subarray_c(arr);
  tend = std::chrono::high_resolution_clock::now();

  std::cout << max_c << std::endl;
  std::cout << "algorithm c: "
            << static_cast<double>((tend - tstart).count())/1000000
            << std::endl;

  return 0;
}
