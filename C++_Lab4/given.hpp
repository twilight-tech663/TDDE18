#ifndef GIVEN_H
#define GIVEN_H
#include <stdexcept>
#include <iostream>

extern int WIDTH;
extern int HEIGHT;

struct Point
{
    int x;
    int y;
};
bool operator==(Point const& lhs, Point const& rhs);
std::istream& operator>>(std::istream& is, Point& rhs);


class Pacman
{
public:

    Pacman();
    
    Point get_position() const;
    void set_position(Point const& p);

    Point get_direction() const;
    void set_direction(Point const& p);

private:
    
    Point pos {};
    Point dir {};
};

class Ghosts
{
public:
    Ghosts(Pacman &p, Point start_pos, Point scatter_pos, std::string color);
    virtual ~Ghosts() = default;

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

class Blinky : public Ghosts
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

class Pinky : public Ghosts
{
public:
    Pinky(Pacman& p, Point start_pos, Point scatter_pos, std::string color = "pink");

    Point get_chase_point() const override;
    Point get_scatter_point() const override;
};

class Clyde : public Ghosts
{
public:
    Clyde(Pacman& p, Point start_pos, Point scatter_pos, int n, std::string color = "orange");

    Point get_chase_point() const override;
    Point get_scatter_point() const override;

private:
    int step;
};

class Ghost_Tester
{
public:
    Ghost_Tester();
    ~Ghost_Tester();
    void run();

private:
    std::string to_draw(Point const& curr_pos);
    void draw_map();
    Pacman pacman;
    bool chase;
    std::vector<Ghosts*> ghosts{};
};


#endif