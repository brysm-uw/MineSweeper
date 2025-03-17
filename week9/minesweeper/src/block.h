#ifndef __BLOCK_AGENT__H
#define __BLOCK_AGENT__H

#include "enviro.h"
#include <vector>
#include <unordered_map>

using namespace enviro;

// Class: BlockManager
// This class is responsible for managing the blocks' overall state, including bomb statuses.
// It works as a manager to keep track of which blocks contain bombs.
class BlockManager : public Process, public AgentInterface
{
public:
    // Constructor: BlockManager
    // Initializes the BlockManager process and agent interface.
    BlockManager() : Process(), AgentInterface() {}
    // Friend Class Declaration
    // Declares BlockDecorator as a friend, allowing it to access private members of BlockManager.
    friend class BlockDecorator;
    
    void init();
    void start() {}
    void update() {}
    void stop() {}

private:
    int _maxBombs = 10; // Maximum number of bombs allowed in the game
    static std::unordered_map<std::string, bool> _bombStatus; // Static map to store the mine status of each block
};

// Definition: _bombStatus
// Static map that tracks whether each block contains a bomb.
// The key is a string (e.g., block ID or coordinates), and the value is a boolean indicating bomb presence.
std::unordered_map<std::string, bool> BlockManager::_bombStatus;

// Class: BlockDecorator
// This class is responsible for decorating individual blocks. It handles visual and logical updates
// (e.g., determining whether a block is a valid neighbor or changing its appearance based on state).
class BlockDecorator : public Process, public AgentInterface
{
public:
    // Constructor: BlockDecorator
    // Initializes the BlockDecorator process and agent interface.
    BlockDecorator() : Process(), AgentInterface() {}
    void init();
    void start() {}
    void update() {}
    void stop() {}

private:
    // Method: is_valid_neighbor
    // Determines whether a neighboring block (specified by its relative position to a block's id) is valid.
    // This is used for calculating the number of adjacent bombs (is_valid_neighbor(blockId, adjacentBlockId)).
    bool is_valid_neighbor(int, int);
};

class Block : public Agent
{
public:
    Block(json spec, World &world) : Agent(spec, world)
    {
        add_process(m);
        add_process(c);
    }

private:
    BlockDecorator c;
    BlockManager m;
};

DECLARE_INTERFACE(Block)

#endif