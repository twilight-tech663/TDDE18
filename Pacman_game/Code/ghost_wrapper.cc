#include "ghost_wrapper.h"

#include <cmath>
#include <algorithm>

#include "constants.h"

Ghost_Wrapper::Ghost_Wrapper(sf::Vector2f const& start_position, Grid& grid, Ghost* ghost)
    : Entity {start_position, grid, 1, get_sfml_color(ghost)}, ghost {ghost}
{
    setPointCount(7);
    
    // Calculates a couple of points for a circle to create the classic Pacman-shape.
    float radius { static_cast<float>(TILE_SIZE) / 2 };
    int no_points { 5 };
    for (int i {}; i < no_points; ++i)
    {
        setPoint(i, sf::Vector2f{ std::cos(3.14f / (no_points - 1) * i) * radius,
                                  -std::sin(3.14f / (no_points - 1) * i) * radius });
    }
    setPoint(5, {-radius, radius});
    setPoint(6, { radius, radius});
    
}

void Ghost_Wrapper::update()
{
    if ((chase_mode && time_passed > 10) or
        (!chase_mode && time_passed > 5))
    {
        chase_mode = !chase_mode;
        time_passed = 0;
        
        current_direction = -current_direction;
        std::swap(current_target, previous_target);
    }

    Entity::update();
}

// Ghost AI description: https://gameinternals.com/understanding-pac-man-ghost-behavior
void Ghost_Wrapper::select_new_target(sf::Vector2f& current_target,
                              sf::Vector2i& current_direction) const
{
    sf::Vector2i curr { to_grid_pos(current_target) };
    sf::Vector2i goal {};

    // Get the new 'goal'-point. This is different for each ghost.
    ghost->set_position(to_grid_pos(getPosition()));
    if (chase_mode)
    {
        goal = ghost->get_chase_point();
    }
    else
    {
        goal = ghost ->get_scatter_point();
    }

    // Find all points adjecent to the ghost. These are possible next destinations.
    std::vector<sf::Vector2i> potential_points { {curr.x + 1, curr.y}, {curr.x - 1, curr.y},
                                                 {curr.x, curr.y + 1}, {curr.x, curr.y - 1} };

    // Sort the points so that the point closest to the 'goal'-point is first.
    std::sort(potential_points.begin(), potential_points.end(),
              [&goal](sf::Vector2i const& p1, sf::Vector2i const& p2)
              {
                  double p1_dist { pow(p1.x - goal.x, 2) + pow(p1.y - goal.y, 2) };
                  double p2_dist { pow(p2.x - goal.x, 2) + pow(p2.y - goal.y, 2) };
                  return p1_dist < p2_dist;
              });

    // Find the first point that is not a wall, or the position the ghost was just on.
    sf::Vector2i best_point = *std::find_if(potential_points.begin(), potential_points.end(),
                                            [this](sf::Vector2i const& p)
                                            {
                                                return not grid.wall_at(p) and p != to_grid_pos(previous_target); 
                                            });

    // Update the ghost's direction. Checks if the ghost is standing still to avoid 0-division.
    sf::Vector2f new_direction = (to_world_pos(best_point) - current_target);
    float length = sqrt( (new_direction.x * new_direction.x) +
                         (new_direction.y * new_direction.y));
    if (length != 0)
    {
        current_target = to_world_pos(best_point);
        current_direction = static_cast<sf::Vector2i>(new_direction / length);
    }
    else
    {
        current_direction = {};
    }
}

sf::Color Ghost_Wrapper::get_sfml_color(Ghost* ghost) const
{
    std::string color {ghost->get_color()};
    if (color == "red"   ) return sf::Color::Red;
    if (color == "green" ) return sf::Color::Green;
    if (color == "blue"  ) return sf::Color::Blue;
    if (color == "orange") return sf::Color{255,165,0};
    if (color == "yellow") return sf::Color::Yellow;
    if (color == "pink"  ) return sf::Color{255,105,180};
    if (color == "purple") return sf::Color{128,0,128};
    if (color == "brown" ) return sf::Color{139,69,19};
    if (color == "gray"  ) return sf::Color{128,128,128};
    if (color == "black" ) return sf::Color::Black;
    return sf::Color::White;
}
