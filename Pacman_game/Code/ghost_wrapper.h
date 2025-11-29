#ifndef GHOST_WRAPPER_H
#define GHOST_WRAPPER_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "entity.h"
#include "grid.h"
#include "ghost.h"




/*
 * A class that owns a object of the student created datatype "Ghost". See it
 * as a class that adds the graphical element and search algorithm to the
 * classes created by the students.
 */
class Ghost_Wrapper : public Entity
{
public:
    Ghost_Wrapper(sf::Vector2f const& start_position, Grid& grid, Ghost* ghost);
    
    /*
     * Extends Entity::update with functionallity to change between chase and scatter.
     *
     * Then calls the Entity's update member. Read there for details.
     */
    void update() override;

protected:

    /*
     * Chooses a new point for the ghost to head towrads. This is done as the
     * ghost reaches its' previous target. 
     *
     * Note this is not the same thing that the students implement. This is
     * square by square and uses student code, but they are not the same.
     */
    void select_new_target(sf::Vector2f& current_target,
                           sf::Vector2i& current_direction) const override;

private:

    /*
     * Convert the color string the ghost has stored to an actual SFML-color.
     *
     * Follow the pattern to add more colors.
     */
    sf::Color get_sfml_color(Ghost* ghost) const;

    std::unique_ptr<Ghost> ghost;
    bool chase_mode {true};
};

#endif
