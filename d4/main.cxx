#include <iostream>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <vector>

struct Card
{
  int nr;
  int gained;
  std::vector<int> wns;
  std::vector<int> ns;
};

int main()
{
  std::ifstream file{"../d4/input.txt"};
  std::string line, ignored;
  std::vector<Card> cards;
  constexpr int winningLength{10}, owningLength{25};
  int sum{0}, nr{0};

  while (std::getline(file, line))
  {
    std::stringstream iss(line);
    std::vector<int> twns, tns;
    Card c;
    int n;

    iss >> ignored >> ignored;
    for (int i{0}; i < winningLength; i++)
    {
      iss >> n;
      twns.emplace_back(n);
    }
    iss >> ignored;
    for (int i{0}; i < owningLength; i++)
    {
      iss >> n;
      tns.emplace_back(n);
    }

    c.wns = twns;
    c.ns = tns;
    c.nr = nr;
    c.gained = 1;
    cards.emplace_back(c);
    nr++;
  }

  for (const auto &c : cards)
  {
    int gainedCards{1};
    sum += c.gained;
    for (const auto &n : c.wns)
    {
      if (std::find(c.ns.begin(), c.ns.end(), n) != c.ns.end())
      {
        cards[c.nr + gainedCards].gained += 1 * c.gained;
        gainedCards++;
      }
    }
  }

  std::cout << sum << std::endl;
  return 0;
}
