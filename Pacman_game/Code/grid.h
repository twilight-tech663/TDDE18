#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>

/*
 * Data type representing a row in the grid that is the map.
 */
using Row = std::vector<char>;
std::istream& operator>>(std::istream& is, Row& row);

/*
 * Helper function to convert between two different coordinate systems.
 *
 * 'grid' is a coordinate system where is square on the board is a coordinate.
 * 'word' is a coordinate system where each pixel on the screen is a coordinate.
 */
sf::Vector2i to_grid_pos(sf::Vector2f const& pos);
sf::Vector2f to_world_pos(sf::Vector2i const& pos);

/*
 * Class representing the entire map. Keeps track of all the positions for the
 * walls and food.
 */
class Grid
{
public:

    Grid(std::string const& map_file);

    /*
     * Render all the walls and food.
    */
    void draw(sf::RenderWindow& window) const;

    /*
     * True if there is a wall on the given position. Note that the position
     * should be in 'grid'-system.
    */
    bool wall_at(sf::Vector2i const& grid_pos) const;

    /*
     * True if there was a food on the given coordinate. Will remove food. Note
     * that coordinate is in 'grid'-system. 
     *
     * If there wasn't any food there, return false without side effects.
    */
    bool eat_food(sf::Vector2i const& grid_pos);

    int food_count() const;

private:
    std::vector<Row> rows {};
};

#endif
