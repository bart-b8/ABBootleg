#include "./System.h"

Point System::convert_to_Allegro_Coordinate_System(const Point classic) {
  std::map<std::string, double> cfg = Config::Get().Map();
  Point out;
  out.x_ = classic.x_;
  out.y_ =
      cfg["game.playground_height"] - classic.y_;
  return out;
}


Point System::convert_to_Classic_Coordinate_System(const Point allegro) {
  return convert_to_Allegro_Coordinate_System(allegro);
}

