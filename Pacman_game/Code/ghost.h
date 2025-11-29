#ifndef GHOST_H
#define GHOST_H
#include <stdexcept>
#include <iostream>
#include "pacman.h"

class Ghost
{
public:
    Ghost(Pacman &p, Point start_pos, Point scatter_pos, std::string color);
    virtual ~Ghost() = default;

    bool out_bundary(Point const& P) const;
    void set_position(Point const& p);
    Point get_position() const;

    virtual Point get_chase_point() const = 0;      // pure virtual function
    virtual Point get_scatter_point() const = 0;
    std::string get_color() const;

protected:
    Pacman &pacman;                                 // need get pacman's position
    Point startpos{};
    Point scatterpos{};
    std::string color;
};

class Blinky : public Ghost
{
public:
    Blinky(Pacman& p, Point start_pos, Point scatter_pos, std::string color = "red");

    Point get_chase_point() const override;
    Point get_scatter_point() const override;
    bool is_angry() const;
    void set_angry(bool angry_val);

private:
    bool angry;
};

class Pinky : public Ghost
{
public:
    Pinky(Pacman& p, Point start_pos, Point scatter_pos, std::string color = "pink");

    Point get_chase_point() const override;
    Point get_scatter_point() const override;
};

class Clyde : public Ghost
{
public:
    Clyde(Pacman& p, Point start_pos, Point scatter_pos, int n, std::string color = "orange");

    Point get_chase_point() const override;
    Point get_scatter_point() const override;

private:
    int step;
};

#endif