#include <cstdlib>
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <vector>

/**
 * On laptop: 3M numbers max 10M
 * real	0m3.515s
 * user	0m1.276s
 * sys	0m2.233s
 */
std::ofstream& generate_random_nums(std::ofstream& of, size_t k, size_t n)
{
  // Ref: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<size_t> distrib(0, n-1);

  auto inserted_bitmap = std::vector<bool>(n, false);

  size_t count = 0;
  while (count < k)
  {
    auto elem = distrib(gen);
    if (!inserted_bitmap.at(elem))
    {
      inserted_bitmap.at(elem) = true;
      of << elem << std::endl;
      count += 1;
    }
  }

  return of;
}


/**
 * On laptop: 3M numbers max 10M
 * real	0m1.021s
 * user	0m0.957s
 * sys	0m0.060s
 *
 * The batching seems to really help with the file I/O.
 *
 * Idea: we could try measuring random number generation to see if we are
 *       close to what we can get by with STL random number generator.
 */
std::ofstream& batched_generate_random_nums(std::ofstream& of,
                                            size_t k, size_t n,
                                            size_t batch_size=128)
{
  // Ref: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
  std::random_device rd;  // a seed source for the random number engine
  std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<size_t> distrib(0, n-1);

  auto inserted_bitmap = std::vector<bool>(n, false);

  size_t count = 0;
  auto batch = std::vector<size_t>(batch_size, 0);
  while (count < k)
  {
    size_t i = 0;
    for (; count < k && i < batch_size; ++i)
    {
      auto elem = distrib(gen);
      if (!inserted_bitmap.at(elem))
      {
        batch.at(i) = elem;
        inserted_bitmap.at(elem) = true;
        count += 1;
      }
    }

    auto out_stringstream = std::stringstream();
    for (size_t j = 0; j < i; ++j)
    {
      out_stringstream << batch.at(j) << std::endl;
    }
    of << out_stringstream.str();
  }

  return of;
}


int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cout << "I need two arguments n_nums, max_num, and file_name!"
              << std::endl;
    return -1;
  }

  int n_nums = std::atoi(argv[1]);
  int max = std::atoi(argv[2]);
  auto of = std::ofstream(argv[3]);

  batched_generate_random_nums(of, n_nums, max);

  return 0;
}
