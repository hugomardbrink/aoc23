#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>

struct Number
{
  int value;
  int row;
  int start;
  int end;
};

struct PairHash
{
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const
  {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);

    return h1 ^ h2;
  }
};

bool isGear(const char &c)
{
  return c == '*';
}

int main()
{
  std::ifstream file{"../d3/input.txt"};
  std::vector<Number> ns{};
  std::vector<std::string> inputs{};
  std::unordered_map<std::pair<int, int>, std::vector<int>, PairHash> gears;
  std::string line;
  std::regex pattern("\\d+");
  int sum{0}, row{0};

  while (std::getline(file, line))
  {
    inputs.emplace_back(line);

    auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator i = begin; i != end; i++)
    {
      Number n;
      std::smatch match = *i;
      n.value = std::stoi(match.str());
      n.start = match.position();
      n.end = match.position() + match.str().size() - 1;
      n.row = row;

      ns.emplace_back(n);
    }
    row++;
  }

  int maxIndex = inputs[0].size() - 1;
  int inputsSize = inputs.size() - 1;

  for (const auto &n : ns)
  {
    int left{std::max(0, n.start - 1)}, right{std::min(n.end + 1, maxIndex)},
        before{std::max(n.row - 1, 0)}, after{std::min(n.row + 1, inputsSize)};

    if (isGear(inputs[n.row][left]))
    {
      gears[std::make_pair(n.row, left)].emplace_back(n.value);
      continue;
    }
    if (isGear(inputs[n.row][right]))
    {
      gears[std::make_pair(n.row, right)].emplace_back(n.value);
      continue;
    }

    for (auto i{left}; i <= right; i++)
    {
      if (isGear(inputs[before][i]))
      {
        gears[std::make_pair(before, i)].emplace_back(n.value);
        continue;
      }
      if (isGear(inputs[after][i]))
      {
        gears[std::make_pair(after, i)].emplace_back(n.value);
        continue;
      }
    }
  }

  for (const auto &gear : gears)
  {
    if (gear.second.size() == 2)
    {
      int product{1};
      for (const auto &num : gear.second)
      {
        product *= num;
      }
      sum += product;
    }
  }

  std::cout << sum << std::endl;

  return 0;
}
