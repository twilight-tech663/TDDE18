#ifndef GAME_H
#define GAME_H

#include "grid.h"
#include "entity.h"
#include "pacman.h"
#include "ghost_wrapper.h"
#include "constants.h"

/*
 * The Game class is responsible for the entire game. The class takes care of
 * the main loop and delegates responsibility to other classes.
 */
class Game
{
public:
    /*
     * Create a game instance and all the objects in the game world. These are
     * currently hard coded to specific positions. They should be read from a
     * map file.
    */
    Game();
       
    /*
     * Main loop of the game. Everything is run from there. Handles user input,
     * delegates to other functions to update game logic and render the window.
     * Also checks if the game is over.
    */
    void run();

    /*
     * Update game logic, e.g. move Pacman and the ghosts.
    */
    void update();
    
    /*
     * Check if Pacman has collided with any ghost.
    */
    bool check_collision() const;

    /*
     * Render all the objects in the game window.
    */
    void draw();
    
    /*
     * Calculate the points the player has collected.
     */
    int get_score();

private:
    Grid grid;
    Pacman pacman;
    std::vector<Ghost_Wrapper> ghosts;
    sf::RenderWindow window;
};

#endif
