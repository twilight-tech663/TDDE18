#include "given.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

int WIDTH = 19;
int HEIGHT = 22;

bool operator==(Point const& lhs, Point const& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::istream& operator>>(std::istream& is, Point& rhs)
{
    return is >> rhs.x >> rhs.y;
}

Pacman::Pacman()
    : pos {}, dir {1,0}
{}

Point Pacman::get_position() const
{
    return pos;
}

void Pacman::set_position(Point const& p)
{
    if (p.x >= WIDTH or p.x < 0 or p.y >= HEIGHT or p.y < 0)
    {
        throw std::runtime_error("position outside valid range");
    }
    pos = p;
}

Point Pacman::get_direction() const
{
    return dir;
}

void Pacman::set_direction(Point const& p)
{
    if (p.x > 1 or p.x < -1 or p.y > 1 or p.y < -1 or abs(p.x + p.y) != 1)
    {
        throw std::runtime_error("direction outside valid range");
    }
    dir = p;
}

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
    return is_angry() ? pacman.get_position() : scatterpos;
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

    if(d.x == 1 && d.y == 0)
    {
        p.x += 2;
    }
    else if(d.x == 0 && d.y == 1)
    {
        p.y += 2;
    }
    else if(d.x == -1 && d.y == 0)
    {
        p.x -= 2;
    }
    else if(d.x == 0 && d.y == -1)
    {
        p.y -= 2;
    }
    if(out_bundary(p))
    {
        throw std::runtime_error("position outside valid range");
    }
    return p;
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

    int x = std::abs(p_pacman.x - p_clyde.x);       // pacman's position 
    int y = std::abs(p_pacman.y - p_clyde.y);
    int distance = x + y;

    return distance > step ? p_pacman : scatterpos;
}

Point Clyde::get_scatter_point() const
{
    return scatterpos;
}

Ghost_Tester::Ghost_Tester()
    : pacman {}, chase{true}        // initialize the ghosts vector
{
    ghosts.push_back(new Blinky{pacman, {}, {WIDTH-1,HEIGHT-1}});
    ghosts.push_back(new Pinky{pacman, {}, {0,HEIGHT-1}});
    ghosts.push_back(new Clyde{pacman, {}, {0,0}, 8});
}

Ghost_Tester::~Ghost_Tester()       // release memory
{
    for (Ghost* g : ghosts)
    {
        delete g;
    }
}

void Ghost_Tester::run()
{
    while(true)
    {
        draw_map();
        std::cout << "> ";

        std::string line {};
        std::getline(std::cin, line);
        std::istringstream iss {line};

        std::string command {};
        iss >> command;

        try// cause set position may throw exception, need catch it 
        {
            if (command == "pos")
            {
                Point new_pos {};
                iss >> new_pos.x >> new_pos.y;
                pacman.set_position(new_pos);
            }
            else if (command == "dir")
            {
                Point new_dir{};
                iss >> new_dir.x >> new_dir.y;
                pacman.set_direction(new_dir);
            }
            else if (command == "red" || command == "pink" || command == "orange")
            {
                Point new_pos{};
                iss >> new_pos.x >> new_pos.y;

                if(command == "red")
                {
                    ghosts[0]->set_position(new_pos);
                }
                else if(command == "pink")
                {
                    ghosts[1]->set_position(new_pos);
                }
                else if(command == "orange")
                {
                    ghosts[2]->set_position(new_pos);
                }
            }
            else if (command == "chase")
            {
                chase = true;
            }
            else if (command == "scatter")
            {
                chase = false;
            }
            else if (command == "anger")
            {
                Blinky* blinky = dynamic_cast<Blinky*>(ghosts[0]);   // set_angry only exist in blinky(derived) class
                if(blinky != nullptr)                                // need convert base class pointer to derived class, compiler only know ghosts[0] is a base pointer, don't know it point to blinky
                {
                    blinky->set_angry(true);
                }
            }
        }
        catch(std::runtime_error& e)
        {
            std::cerr << "Error:" << e.what() << std::endl;
        }
        catch(std::exception& e)
        {
            std::cerr << "Unknown error" << e.what() << std::endl;
        }
        if (command == "quit")
        {
            break;
        }
}
}

std::string Ghost_Tester::to_draw(Point const& curr_pos)
{
    std::string to_draw{"  "};
    Point target{};
    
    if (pacman.get_position() == curr_pos)
    {
        to_draw[1] = '@';
    }

    for (Ghost* g : ghosts)
    {
        std::string color{};
        color = g->get_color();
        if (g->get_position() == curr_pos)
        {
            to_draw[0] = static_cast<char>(toupper(color[0]));      // display ghosts position
        }
        try     // derived class pinky's scatter may throw exception, need catch it
        {
            chase ? target = g->get_chase_point() : target = g->get_scatter_point();    // return chase or scatter target point
            
            if(target == curr_pos)
            {
                to_draw[0] = static_cast<char>(tolower(color[0]));      // display ghosts target position
            }
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        } 
    }
    return to_draw;
}

void Ghost_Tester::draw_map()
{
    std::cout << "+" << std::setfill('-') << std::setw(WIDTH * 2) << "-" << "+\n";
    
    for (int y {HEIGHT - 1}; y >= 0; --y) 
    {
        std::cout << "|";
        for (int x {}; x < WIDTH; ++x) 
        {
            std::cout << to_draw( Point{x,y} );
        }
        std::cout << "|\n";
    }

    std::cout << "+" << std::setfill('-') << std::setw(WIDTH * 2) << "-" << "+" << std::endl;
}