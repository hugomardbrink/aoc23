#include <iostream>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <omp.h>

struct MapRow
{
  long source;
  long destination;
  long range;
};

long findDestination(long seed, const std::vector<std::vector<MapRow>> &maps)
{
  long location{seed};
  for (const auto &map : maps)
  {
    for (const auto &mr : map)
    {
      if (location >= mr.source && location < mr.source + mr.range)
      {
        location = mr.destination + (location - mr.source);
        break;
      }
    }
  }
  return location;
}

int main()
{
  std::ifstream file{"../d5/input.txt"};
  std::string line, ignored;
  std::vector<std::pair<long, long>> seeds;
  std::vector<std::vector<MapRow>> maps{};
  long mapIndex{-1};

  std::getline(file, line);
  std::stringstream seedSS(line);
  seedSS >> ignored;
  while (seedSS.tellg() != -1)
  {
    long seedStart, seedRange;
    seedSS >> seedStart >> seedRange;
    seeds.emplace_back(seedStart, seedRange);
  }

  while (std::getline(file, line))
  {
    std::stringstream iss(line);

    if (isalpha(line[0]))
    {
      mapIndex += isalpha(line[0]);
      maps.push_back({});
    }

    while (isdigit(line[0]) && iss.tellg() != -1)
    {
      MapRow mr;
      iss >> mr.destination >> mr.source >> mr.range;
      maps[mapIndex].emplace_back(mr);
    }
  }

  long result = std::numeric_limits<long>::max();
  int i, j;

#pragma omp parallel for schedule(static) private(i, j) shared(seeds, result, maps)
  for (i = 0; i < seeds.size(); i++)
  {
    for (j = 0; j < seeds[i].second; j++)
    {
      long destination = findDestination(seeds[i].first + j, maps);
      result = std::min(result, destination);
    }
  }

  std::cout << result << std::endl;

  return 0;
}
