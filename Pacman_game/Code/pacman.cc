#include "pacman.h"

#include <SFML/Window/Keyboard.hpp>
#include <cmath>

#include "constants.h"

Pacman::Pacman(sf::Vector2f const& start_position, Grid& grid)
    : Entity{start_position, grid, 2, sf::Color::Yellow},
      next_direction {}, score {}
{
    int no_points { 8 };
    float radius { 10 };
    
    setPointCount(no_points);
    
    for (int i {}; i < no_points; ++i)
    {
        setPoint(i, sf::Vector2f{ std::cos(6.28f / (no_points) * i) * radius,
                                  std::sin(6.28f / (no_points) * i) * radius });
    }
}

void Pacman::update()
{
    handle_input();

    if (next_direction == -current_direction)
    {
        current_direction = next_direction;
        std::swap(current_target, previous_target);
    }

    if (grid.eat_food(to_grid_pos(getPosition())))
    {
        score += 10;
    }

    Entity::update();
}

Point Pacman::get_position() const
{
    return { static_cast<int>((getPosition().x - TILE_SIZE) / TILE_SIZE),
             static_cast<int>((getPosition().y - TILE_SIZE) / TILE_SIZE) };
}

Point Pacman::get_direction() const
{
    return { current_direction.x, current_direction.y };
}

void Pacman::select_new_target(sf::Vector2f& current_target,
                               sf::Vector2i& current_direction) const
{
    // Returns all possible next points. Will either be a position forwards in
    // the player's direction, or stand still.
    std::vector<sf::Vector2i> candidates { next_direction, current_direction };
    
    // Step through the list with potential points and pick the first one that isn't a wall.
    for (sf::Vector2i const& candidate : candidates)
    {
        sf::Vector2f new_target { current_target + static_cast<sf::Vector2f>(candidate * static_cast<int>(TILE_SIZE)) };
        if ( not grid.wall_at(to_grid_pos(new_target)) )
        {
            current_direction = candidate;
            current_target = new_target;
            return;
        }
    }
    current_direction = {};
}

void Pacman::handle_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        next_direction = {0, -1};
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        next_direction = {0, 1};
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) or sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        next_direction = {-1, 0};
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) or sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        next_direction = {1, 0};
    }
}

