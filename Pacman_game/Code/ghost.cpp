#include "ghost.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

int WIDTH = 19;
int HEIGHT = 22;

Ghost::Ghost(Pacman &p, Point start_pos, Point scatter_pos, std::string c)
    : pacman{p}, startpos{start_pos}, scatterpos{scatter_pos}, color{c}
{}


bool Ghost::out_bundary(Point const& p) const
{
    return p.x >= WIDTH or p.x < 0 or p.y >= HEIGHT or p.y < 0 ? true : false;
}

void Ghost::set_position(Point const& p)
{
    if (out_bundary(p))
    {
        throw std::runtime_error("position outside valid range");
    }
    startpos = p;
}

Point Ghost::get_position() const
{
    return startpos;
}

std::string Ghost::get_color() const
{
    return color;
}

Blinky::Blinky(Pacman& p, Point start_pos, Point scatter_pos, std::string color)
    : Ghost{p, start_pos, scatter_pos, color}, angry{false}
{}

Point Blinky::get_chase_point() const
{
    return pacman.get_position();
}

Point Blinky::get_scatter_point() const
{
    if(is_angry())
    {
        return pacman.get_position();
    } else {
        return scatterpos;
    }
}

bool Blinky::is_angry() const
{
    return angry;
}

void Blinky::set_angry(bool angry_val)
{
    angry = angry_val;
}

Pinky::Pinky(Pacman& p, Point start_pos, Point scatter_pos, std::string color)
    : Ghost{p, start_pos, scatter_pos, color}
{}

Point Pinky::get_chase_point() const
{
    Point d = pacman.get_direction();
    Point p = pacman.get_position();
    
    if(d.x == 0 && d.y == 0)
    {
        return p;
    }
    else if(d.x == 1 && d.y == 0)
    {
        p.x += 2;
        if(out_bundary(p))
        {
            throw std::runtime_error("position outside valid range");
        }
        return p;
    }
    else if(d.x == 0 && d.y == 1)
    {
        p.y += 2;
        if(out_bundary(p))
        {
            throw std::runtime_error("position outside valid range");
        }
        return p;
    }
    else if(d.x == -1 && d.y == 0)
    {
        p.x -= 2;
        if(out_bundary(p))
        {
            throw std::runtime_error("position outside valid range");
        }
        return p;
    }
    else if(d.x == 0 && d.y == -1)
    {
        p.y -= 2;
        if(out_bundary(p))
        {
            throw std::runtime_error("position outside valid range");
        }
        return p;
    }
    else
    {
        throw std::runtime_error("wrong direction");
    }
}

Point Pinky::get_scatter_point() const
{
    return scatterpos;
}

Clyde::Clyde(Pacman& p, Point start_pos, Point scatter_pos, int n, std::string color)
    : Ghost{p, start_pos, scatter_pos, color}, step{n}
{}

Point Clyde::get_chase_point() const
{
    Point p_pacman = pacman.get_position();
    Point p_clyde = get_position(); 

    int x = std::abs(p_pacman.x - p_clyde.x);
    int y = std::abs(p_pacman.y - p_clyde.y);
    int distance = x + y - 1;

    if(distance > step)
    {
        return p_pacman;
    } else {
        return {0, 0};
    }
}

Point Clyde::get_scatter_point() const
{
    return scatterpos;
}
