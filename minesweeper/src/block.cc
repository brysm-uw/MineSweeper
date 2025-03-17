#include <iostream>
#include "block.h"
#include <vector>
#include <string>
#include <unordered_map>

using namespace enviro;

void BlockManager::init()
{
    static bool runOnce = true;
    watch("connection", [&](Event &e)
          {
            // Draw the board, and distribute bombs, only once.
            if(runOnce == true) {
            runOnce = false;
            int bombCount = 0;    
            int ctr = 0; // used for assigning unique agent ids
            for(int row = -100; row <= 60; row += 20) {
                for(int col = -80; col <= 80; col += 20) {
                    ctr++; 
                    if(ctr < 83) {
                        // Randomly decide if this block is a mine (20% chance)
                        bool isBomb = false;
                        if(bombCount < _maxBombs && (rand() % 100) < 20) {
                            isBomb = true;
                            bombCount++;
                        }
                        Agent& a = add_agent("Block", row, col, 0, {
                                                                        {"fill", "#C0C0C0"},  // Main block color (light gray)
                                                                        {"stroke", "#808080"}, // Dark gray stroke for shadow effect
                                                                        {"stroke-width", "2"}  // Adjust thickness to enhance shadow
                                                                    }
                                            );
                        // assign ids to the agents
                        a.set_client_id(std::to_string(ctr));
                         // register block's bomb status
                        _bombStatus[std::to_string(ctr)] = isBomb;
                    }
                }
            }
        } });
}
void BlockDecorator::init()
{
    watch("agent_click", [&](Event &e)
          {
        Agent &a = find_agent(e.value()["id"]);
        std::string id = a.get_client_id();
        int numId = std::stoi(id);
        int bombCount = 0;
        std::vector<int> neighbors = {
            numId - 1,  // Above
            numId + 1,  // Below
            numId - 9,  // Left
            numId + 9,  // Right
            numId - 10, // Top-left
            numId - 8,  // Top-right
            numId + 8,  // Bottom-left
            numId + 10  // Bottom-right
        };
        for (int neighborId : neighbors)
        {
            // Check if the neighbor is valid
            if (neighborId >= 2 && neighborId <= 82)
            {
                if (is_valid_neighbor(numId, neighborId))
                {
                    if (BlockManager::_bombStatus[std::to_string(neighborId)])
                    {
                        bombCount++;
                    }
                }
            }
        }
        if (BlockManager::_bombStatus[id])
        {
            a.decorate("<rect x='-10' y='-10' width='20' height='20' fill='red' stroke='none'/><circle cx='0' cy='0' r='7' fill='none' stroke='red' stroke-width='1'/><circle cx='0' cy='0' r='3' fill='black'/><line x1='0' y1='-7' x2='0' y2='-4' stroke='black' stroke-width='1.5'/><line x1='0' y1='7' x2='0' y2='4' stroke='black' stroke-width='1.5'/><line x1='-7' y1='0' x2='-4' y2='0' stroke='black' stroke-width='1.5'/><line x1='7' y1='0' x2='4' y2='0' stroke='black' stroke-width='1.5'/><line x1='-5' y1='-5' x2='-3' y2='-3' stroke='black' stroke-width='1.5'/><line x1='5' y1='5' x2='3' y2='3' stroke='black' stroke-width='1.5'/><line x1='5' y1='-5' x2='3' y2='-3' stroke='black' stroke-width='1.5'/><line x1='-5' y1='5' x2='-3' y2='3' stroke='black' stroke-width='1.5'/>");
            emit(Event("Death", "I Died!"));
        }
        else
        { 
            std::string color;
            switch (bombCount)
            {
                case 1: color = "blue"; break;           // 1 = Blue
                case 2: color = "green"; break;          // 2 = Green
                case 3: color = "red"; break;            // 3 = Red
                case 4: color = "orange"; break;         // 4 = Orange
                case 5: color = "yellow"; break;         // 5 = Yellow
                case 6: color = "cyan"; break;           // 6 = Cyan
                case 7: color = "purple"; break;         // 7 = Purple
                case 8: color = "#FFFFE0"; break;        // 8 = Light Yellow
                default: color = "black"; 
          }   
          a.decorate("<rect x='-8' y='-8' width='16' height='16' fill='#E0E0E0' stroke='none'/>"
              "<text x='-5' y='4' style='fill: " + color + "; font-size: 13px; font-weight: bold; font-family: \"Comic Sans MS\", cursive, sans-serif;'>" + std::to_string(bombCount) + "</text>");
        } });
}

bool BlockDecorator::is_valid_neighbor(int id, int neighborId)
{
    if (id % 9 == 1 && (neighborId == id - 1 || neighborId == id - 10 || neighborId == id + 8))
    { // Bottem edge check, will fail when evaluating wrapped-around neighbors
        return false;
    }
    if (id % 9 == 0 && (neighborId == id + 1 || neighborId == id - 8 || neighborId == id + 10))
    { // Top edge check, will fail when evaluating wwrapped-around neighbors
        return false;
    }
    return true; // This block is valid
}
