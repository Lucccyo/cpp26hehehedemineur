#include <print>
#include <contracts>
#include <cassert>
#include "grid.h"

namespace GridCell {
  struct Cell {
    int num;
    bool is_safe;
  };

  Grid<Cell> init(std::size_t width, std::size_t height)
    // pre(width  > 0 && height > 0)
    // post(map: grid_safe map)
  {
    Cell c0;
    c0.num = 0;
    c0.is_safe = true;
    return Grid<Cell>(width, height, c0);
  }

  int get_random_up_bounded(int upper_bound) {
    return rand() % (upper_bound + 1 - 0) + 0;
  }

  void bombard_cell(Grid<Cell>& grid_cell, int ri, int rj) {
    grid_cell(ri, rj).is_safe = false;
    grid_cell(ri, rj).num = -1;
    if (grid_cell.north_west(ri, rj) && grid_cell.north_west(ri, rj)->is_safe)
      { grid_cell.north_west(ri, rj)->num++; }
    if (grid_cell.north(ri, rj) && grid_cell.north(ri, rj)->is_safe)
      { grid_cell.north(ri, rj)->num++; }
    if (grid_cell.north_east(ri, rj) && grid_cell.north_east(ri, rj)->is_safe)
      { grid_cell.north_east(ri, rj)->num++; }
    if (grid_cell.west(ri, rj) && grid_cell.west(ri, rj)->is_safe)
      { grid_cell.west(ri, rj)->num++; }
    if (grid_cell.east(ri, rj) && grid_cell.east(ri, rj)->is_safe)
      { grid_cell.east(ri, rj)->num++; }
    if (grid_cell.south_west(ri, rj) && grid_cell.south_west(ri, rj)->is_safe)
      { grid_cell.south_west(ri, rj)->num++; }
    if (grid_cell.south(ri, rj) && grid_cell.south(ri, rj)->is_safe)
      { grid_cell.south(ri, rj)->num++; }
    if (grid_cell.south_east(ri, rj) && grid_cell.south_east(ri, rj)->is_safe)
      { grid_cell.south_east(ri, rj)->num++; }
  }

  void bombard(Grid<Cell>& grid_cell, size_t bomb_count)
    // pre(bomb_count >= 0 && bomb_count <= m.width * m.height)
  {
    for (int bc = bomb_count - 1; bc >= 0; --bc) {
      int ri = get_random_up_bounded(grid_cell.height - 1);
      int rj = get_random_up_bounded(grid_cell.width - 1);
      if (grid_cell(ri, rj).is_safe) {
        bombard_cell(grid_cell, ri, rj);
      } else {
        bc = bc + 1;
      }
    }
  }

  void print_cell(Cell const& cell, std::ostream& out) {
    if (cell.is_safe) { out << ' ' << cell.num << ' '; }
    else { out << " ■ "; }
  }
}

void say(const std::string& s)
  // pre(s.length() > 4)
{ std::print("{}\n\n", s); }

int main(){
  int seed = time(0);
  srand(seed);
  std::string debug_header = std::format("Démineur playground\tseed = {}", seed);
  say(debug_header);
  Grid<GridCell::Cell> grid_cell = GridCell::init(8, 8);
  GridCell::bombard(grid_cell, 10);
  grid_cell.print_grid(GridCell::print_cell);
}
