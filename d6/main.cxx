#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

int main()
{
  std::ifstream file{"../d6/input.txt"};
  std::string line, temp, strDistance, strTime;
  int result{0};

  std::getline(file, line);
  std::stringstream tss(line);
  tss >> temp;
  while (tss.tellg() != -1)
  {
    tss >> temp;
    strTime.append(temp);
  }

  std::getline(file, line);
  std::stringstream dss(line);
  dss >> temp;
  while (dss.tellg() != -1)
  {
    dss >> temp;
    strDistance.append(temp);
  }

  long time = std::stol(strTime);
  long distance = std::stol(strDistance);
  for (int i{0}; i < time; i++)
  {
    result += distance < (time - i) * i;
  }

  std::cout << result << std::endl;
  return 0;
}
