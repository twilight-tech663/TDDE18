#ifndef PACMAN_H
#define PACMAN_H

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "grid.h"

/*
 * The Pacman class represent the player character in the game. It also
 * contains functionallity to move and render it. 
 *
 * Speciallization of the base class Entity.
 */
class Pacman : public Entity
{
public:
    Pacman(sf::Vector2f const& start_position, Grid& grid);

    /*
     * Update Pacman's position and direction.
     */
    void update() override;

    /*
     * Get the different properties from Pacman.
     */
    unsigned get_score() const { return score; };
    Point get_position()  const;
    Point get_direction() const;

protected:

    /*
     * Use user input to calculate what square the player is moving to.
     */
    void select_new_target(sf::Vector2f& current_target,
                           sf::Vector2i& current_direction) const override;
    
private:

    /*
     * Check what buttons are pressed and update the variable next_direction
     * based on that.
     *
     * Change this if you want different buttons to control Pacman.
     */
    void handle_input();

    sf::Vector2i next_direction;
    unsigned score;
};

#endif
