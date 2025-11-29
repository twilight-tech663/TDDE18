#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <cmath>

#include "grid.h"

/*
 * Declartion to represent a position on the map. Discrete steps where each
 * step is a seperate square.
 */
using Point = sf::Vector2i;

/*
 * Base class that represents all drawable movable objects in the game. Has
 * derived classes for Pacman and ghosts.
 */
class Entity : public sf::ConvexShape
{
public:
    Entity(sf::Vector2f const& start_position, Grid& grid, int speed, sf::Color const& color);
    virtual ~Entity() = default;

    /*
     * Update objects posistion. Each Entity choose a position one square
     * infront or backwards in either x- or y-axis and moves with constant
     * speed there. When it reaches the square they choose a new target and
     * restarts. select_new_target() is used to determine the target, and is
     * implemented in the derived class.
     */
    virtual void update();

protected:
    bool at_target_position() const;
    virtual void move_forward();
    
    /*
     * Updates current_target to a new position. Should be a square either
     * horizontally or vertically different from its' current position.
     */
    virtual void select_new_target(sf::Vector2f& current_target,
                                   sf::Vector2i& current_direction) const = 0;

    sf::Vector2f current_target;
    sf::Vector2f previous_target;
    sf::Vector2i current_direction;
    Grid& grid;
    int speed;

    float time_passed {};
};

#endif
