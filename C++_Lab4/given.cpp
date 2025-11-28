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

Ghosts::Ghosts(Pacman &p, Point start_pos, Point scatter_pos, std::string c)
    : pacman{p}, startpos{start_pos}, scatterpos{scatter_pos}, color{c}
{}

bool Ghosts::out_bundary(Point const& p) const
{
    return p.x >= WIDTH or p.x < 0 or p.y >= HEIGHT or p.y < 0 ? true : false;
}

void Ghosts::set_position(Point const& p)
{
    if (out_bundary(p))
    {
        throw std::runtime_error("position outside valid range");
    }
    startpos = p;
}

Point Ghosts::get_position() const
{
    return startpos;
}

std::string Ghosts::get_color() const
{
    return color;
}

Blinky::Blinky(Pacman& p, Point start_pos, Point scatter_pos, std::string color)
    : Ghosts{p, start_pos, scatter_pos, color}, angry{false}
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
    : Ghosts{p, start_pos, scatter_pos, color}
{}

Point Pinky::get_chase_point() const
{
    Point d = pacman.get_direction();
    Point p = pacman.get_position();

    if(d.x == 1 && d.y == 0)
    {
        p.x += 2;
        if(out_bundary(p))
        {
            throw std::runtime_error("position outside valid range");
        }
        return p;
    }
    if(d.x == 0 && d.y == 1)
    {
        p.y += 2;
        if(out_bundary(p))
        {
            throw std::runtime_error("position outside valid range");
        }
        return p;
    }
    if(d.x == -1 && d.y == 0)
    {
        p.x -= 2;
        if(out_bundary(p))
        {
            throw std::runtime_error("position outside valid range");
        }
        return p;
    }
    if(d.x == 0 && d.y == -1)
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
    : Ghosts{p, start_pos, scatter_pos, color}, step{n}
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

Ghost_Tester::Ghost_Tester()
    : pacman {}, chase{true}        // initialize the ghosts vector
{
    ghosts.push_back(new Blinky{pacman, {1,1}, {WIDTH-1,HEIGHT-1}});
    ghosts.push_back(new Pinky{pacman, {2,2}, {0,HEIGHT-1}});
    ghosts.push_back(new Clyde{pacman, {3,3}, {0,0}, 8});
}

Ghost_Tester::~Ghost_Tester()       // release memory
{
    for (Ghosts* g : ghosts)
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
            try
            {
                for (Ghosts* g : ghosts)
                {
                    if(g->out_bundary(new_pos))
                    {
                        throw std::runtime_error("position outside valid range");
                    }
                }
                if(command == "red")
                {
                    ghosts[0]->set_position(new_pos);
                }
                if(command == "pink")
                {
                    ghosts[1]->set_position(new_pos);
                }
                if(command == "orange")
                {
                    ghosts[2]->set_position(new_pos);
                }
            }
            catch(std::exception& e)
            {
                std::cerr << e.what();
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
            Blinky* blinky = dynamic_cast<Blinky*>(ghosts[0]); 
            if(blinky != nullptr)
            {
                blinky->set_angry(true);
            }
        }
        else if (command == "quit")
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

    for (Ghosts* g : ghosts)
    {
        std::string color{};
        color = g->get_color();
        if (g->get_position() == curr_pos)
        {
            to_draw[0] = static_cast<char>(toupper(color[0]));
        }
        try
        {
            if(chase)
            {
                target = g->get_chase_point();
            } else {
                target = g->get_scatter_point();
            }
            if(target == curr_pos)
            {
                std::string color{};
                color = g->get_color();
                to_draw[0] = static_cast<char>(tolower(color[0]));
            }
        }
        catch (std::exception& e)
        {
            std::cerr << e.what();
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