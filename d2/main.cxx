#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Game
{
  int nr;
  int r;
  int b;
  int g;
};

constexpr unsigned int hash(const char *s, int off = 0)
{
  return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
}

int main()
{
  constexpr int redCap{12}, blueCap{14}, greenCap{13};
  std::ifstream file{"../d2/input.txt"};
  std::string line, ignored, currentColor;
  int sum{0}, currentNumber;

  while (std::getline(file, line))
  {
    std::replace(line.begin(), line.end(), ':', ' ');
    std::replace(line.begin(), line.end(), ';', ' ');
    std::replace(line.begin(), line.end(), ',', ' ');

    std::stringstream iss(line);
    Game tempGame{};
    iss >> ignored >> tempGame.nr;

    while (iss.tellg() != -1)
    {
      iss >> currentNumber >> currentColor;

      switch (hash(currentColor.c_str()))
      {
      case hash("red"):
        tempGame.r = (currentNumber > tempGame.r) ? currentNumber : tempGame.r;
        break;
      case hash("green"):
        tempGame.g = (currentNumber > tempGame.g) ? currentNumber : tempGame.g;
        break;
      case hash("blue"):
        tempGame.b = (currentNumber > tempGame.b) ? currentNumber : tempGame.b;
        break;
      }
    }
    sum += tempGame.r * tempGame.b * tempGame.g;
  }
  std::cout << sum << std::endl;

  return 0;
}
