#ifndef CONSTANTS_H
#define CONSTANTS_H

/*
 * Constants for different aspects of the game. These should be read from a file.
 *
 * (inline used to not have to put the definitions in a cc-fil. Not part of the
 * course!)
 */
inline int const WIDTH  { 19 };
inline int const HEIGHT { 22 };
inline int TILE_SIZE { 20 };

inline int const SCREEN_WIDTH  { WIDTH  * (TILE_SIZE + 1) };
inline int const SCREEN_HEIGHT { HEIGHT * (TILE_SIZE + 1) };
inline int const FPS { 60 };

#endif
