#include <print>
#include <contracts>
#include <cassert>
#include <vector>

class Cell {
  public:
    int num;
    bool is_safe;
};

class Map {
  public:
    int width;
    int height;
    std::vector<std::vector<Cell>> content;
};

void print_map(const Map m) {
  for (auto i : m.content) {
    for (auto j : i) {
      j.num < 0
      ? std::print(" ■ ")
      : std::print(" {} ", j.num);
    }
    std::print("\n");
  }
}

Map init_map(int width, int height)
  pre(width  > 0 && height > 0)
{
  Cell c0;
  c0.num = 0;
  c0.is_safe = true;
  Map m;
  m.width = width;
  m.height = height;
  m.content =
    std::vector<std::vector<Cell>>(height, std::vector<Cell>(width, c0));
  assert(m.content.size() == height);
  assert(m.content[0].size() == width);
  return m;
}

int get_random_up_bounded(int upper_bound) {
  return rand() % (upper_bound + 1 - 0) + 0;
}

void bombard_cell(Map& m, int ri, int rj) {
  m.content[ri][rj].is_safe = false;
  m.content[ri][rj].num = -1;
  if (ri > 0 && rj > 0)                  {m.content[ri-1][rj-1].num++;}
  if (ri > 0)                            {m.content[ri-1][rj].num++;}
  if (ri > 0 && rj + 1 < m.width)        {m.content[ri-1][rj+1].num++;}
  if (rj > 0)                            {m.content[ri][rj-1].num++;}
  if (rj + 1 < m.width)                  {m.content[ri][rj+1].num++;}
  if (ri + 1 < m.height && rj > 0)       {m.content[ri+1][rj-1].num++;}
  if (ri + 1 < m.height)                 {m.content[ri+1][rj].num++;}
  if (ri + 1 < m.height && rj + 1 < m.width) {m.content[ri+1][rj+1].num++;}
}

void bombard_map(Map& m, int bomb_count)
  pre(bomb_count >= 0 && bomb_count <= m.width * m.height)
{
  for (int bc = bomb_count - 1; bc >= 0; --bc) {
    int ri = get_random_up_bounded(m.height - 1);
    int rj = get_random_up_bounded(m.width - 1);
    if (m.content[ri][rj].is_safe) {
      bombard_cell(m, ri, rj);
    } else {
      bc = bc + 1;
    }
  }
}

void say(const std::string& s)
  pre(s.length() > 4)
{
  std::print("{}\n\n", s);
}

int main(){
  int seed = time(0);
  srand(seed);
  std::string debug_header = std::format("Démineur playground\tseed = {}", seed);
  say(debug_header);
  Map m = init_map(8, 8);
  bombard_map(m, 10);
  print_map(m);
}

