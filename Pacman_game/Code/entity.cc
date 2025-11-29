#include "entity.h"

#include "constants.h"

Entity::Entity(sf::Vector2f const& start_position, Grid& grid, int speed, sf::Color const& color)
    : current_target { start_position },
      previous_target {},
      current_direction {},
      grid { grid },
      speed { speed }
{
    setPosition(start_position);
    setFillColor(color);
}

void Entity::update()
{
    if (at_target_position())
    {
        sf::Vector2f tmp { current_target };
        select_new_target(current_target, current_direction);
        previous_target = tmp;
    }
    move_forward();

    time_passed += 1.0 / FPS;
}

bool Entity::at_target_position() const
{
    return abs(getPosition().x - current_target.x) < 0.1 and
           abs(getPosition().y - current_target.y) < 0.1;
}

void Entity::move_forward()
{
    move(static_cast<sf::Vector2f>(current_direction * speed));
}
