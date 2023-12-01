#include <numeric>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
  std::ifstream file{"../d1/input.txt"};
  std::string line, value;
  std::vector<int> numbers;
  std::unordered_map<std::string, char> letterMap{{"one", '1'},
                                                  {"two", '2'},
                                                  {"three", '3'},
                                                  {"four", '4'},
                                                  {"five", '5'},
                                                  {"six", '6'},
                                                  {"seven", '7'},
                                                  {"eight", '8'},
                                                  {"nine", '9'}};

  while (std::getline(file, line))
  {
    std::map<int, char> lineNumbers;
    for (const auto &entry : letterMap)
    {
      auto pos = line.find(entry.first);
      while (pos != std::string::npos)
      {
        lineNumbers[pos] = entry.second;
        pos = line.find(entry.first, pos + 1);
      }
    }
    auto fstItr = std::find_if(line.begin(), line.end(), [](char c)
                               { return isdigit(c); });
    auto sndItr = std::find_if(line.rbegin(), line.rend(), [](char c)
                               { return isdigit(c); });
    if (fstItr != line.end())
    {
      lineNumbers[std::distance(line.begin(), fstItr)] = *fstItr;
      lineNumbers[std::distance(line.rbegin(), sndItr)] = *sndItr;
    }
    numbers.emplace_back(std::stoi(std::string(1, lineNumbers.begin()->second) + lineNumbers.rbegin()->second));
  }
  std::cout << std::accumulate(numbers.begin(), numbers.end(), 0) << std::endl;

  return 0;
}
