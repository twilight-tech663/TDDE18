#include "grid.h"

#include <fstream>
#include <deque>
#include <algorithm>

#include "constants.h"

std::istream& operator>>(std::istream& is, Row& row)
{
    std::string line {};
    getline(is, line);
    std::istringstream iss {line};

    if (line.size() != WIDTH)
    {
        is.setstate(std::ios::failbit);
    }

    row.clear();
    
    char c {};
    while(iss >> c)
    {
        row.push_back(c);
    }
    
    if ( row.size() != 0 and row.size() != WIDTH )
    {
        throw std::runtime_error{"wrong width [" + std::to_string(row.size()) + "] of row. Expected " + std::to_string(WIDTH)};
    }
    return is;
}

sf::Vector2i to_grid_pos(sf::Vector2f const& pos)
{
    return { static_cast<int>((pos.x - TILE_SIZE) / TILE_SIZE),
             static_cast<int>((pos.y - TILE_SIZE) / TILE_SIZE) };
}

sf::Vector2f to_world_pos(sf::Vector2i const& pos)
{
    return { static_cast<float>(pos.x * TILE_SIZE + TILE_SIZE),
             static_cast<float>(pos.y * TILE_SIZE + TILE_SIZE) };
}

Grid::Grid(std::string const& map_file)
{
    std::ifstream ifs {map_file};
    
    Row row {};
    while (ifs >> row)
    {
        rows.push_back(row);
    }

    if (rows.size() != HEIGHT)
    {
        throw std::runtime_error{"wrong height [" + std::to_string(rows.size()) + "] of map. Expected " + std::to_string(HEIGHT)};
    }
}

void Grid::draw(sf::RenderWindow& window) const
{
    // Create a rectangle with correct size and color. Moved around and drawn
    // to create the walls.
    sf::RectangleShape box {{TILE_SIZE / 1.5f, TILE_SIZE / 1.5f}};
    box.setFillColor(sf::Color::Blue);
    box.setOrigin(box.getSize().x / 2,box.getSize().y / 2);

    // Create a circle with correct size and color. Moved around and drawn for
    // each piece of fodd.
    sf::CircleShape food {2};
    food.setFillColor(sf::Color::White);
    food.setOrigin(food.getRadius(), food.getRadius());
    
    for (unsigned i {}; i < rows.size(); ++i)
    {
        for (unsigned j {}; j < rows[i].size(); ++j)
        {
            switch (rows[i][j])
            {
            case 'w':
                box.setPosition((j + 1) * TILE_SIZE, (i + 1) * TILE_SIZE);
                window.draw(box);
                break;
            case 'f':
                food.setPosition((j + 1) * TILE_SIZE, (i + 1) * TILE_SIZE);
                window.draw(food);
                break;
            default:
                break;
            }
        }
    }
}

bool Grid::wall_at(sf::Vector2i const& grid_pos) const
{
    if (grid_pos.x < 0 or grid_pos.x >= static_cast<int>(rows[0].size()) or
        grid_pos.y < 0 or grid_pos.y >= static_cast<int>(rows.size()) )
    {
        return true;
    }
    
    return rows[grid_pos.y][grid_pos.x] == 'w';
}

bool Grid::eat_food(sf::Vector2i const& grid_pos)
{
    if (rows[grid_pos.y][grid_pos.x] == 'f')
    {
        rows[grid_pos.y][grid_pos.x] = 'e';
        return true;
    }
    return false;
}


int Grid::food_count() const
{
    int count {};

    for (unsigned i {}; i < rows.size(); ++i)
    {
        for (unsigned j {}; j < rows[i].size(); ++j)
        {
            if (rows[i][j] == 'f')
            {
                ++count;
            }
        }
    }
    return count;
}
