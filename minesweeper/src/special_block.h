#ifndef __SPECIAL_BLOCK_AGENT__H
#define __SPECIAL_BLOCK_AGENT__H

#include "enviro.h"
using namespace enviro;

// Class: SpecialBlockController
// Used to initially set the default state of the face.
class SpecialBlockController : public Process, public AgentInterface
{

public:
    SpecialBlockController() : Process(), AgentInterface() {}
    // Method: init
    // This method simply sets the default smile of the face.
    void init();
    void start() {}
    void update() {}
    void stop() {}
};
// Class: SpecialBlockFacialExpressionsController
// This class manages the behavior and facial expressions of the silly face in this game.
// It handles events like agent clicks and death, and updates the face's appearance based on its state.
class SpecialBlockFacialExpressionsController : public Process, public AgentInterface
{

public:
    SpecialBlockFacialExpressionsController() : Process(), AgentInterface() {}

    // Method: init
    // This method is called once when the process starts.
    // Watches for an agent to be clicked, changes the face to the "O" expression, and initializes the "timer".
    void init();
    void start() {}

    // Method: update
    // This method is called at each simulation step to update the block's state.
    // It reverts the face back to the smiley state after a delay if the minesweeper is not dead.
    // Permanently marks the face dead if the minesweeper dies.
    void update();
    void stop() {}

private:
    double time_elapsed;
    bool _isDead = false;
};

class SpecialBlock : public Agent
{
public:
    SpecialBlock(json spec, World &world) : Agent(spec, world)
    {
        add_process(c);
        add_process(s);
    }

private:
    SpecialBlockController c;
    SpecialBlockFacialExpressionsController s;
};

DECLARE_INTERFACE(SpecialBlock)

#endif
