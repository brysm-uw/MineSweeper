#include <iostream>
#include "special_block.h"

using namespace enviro;

void SpecialBlockController::init()
{
    decorate("<circle cx='0' cy='0' r='7' fill='#FFD700' stroke='#000' stroke-width='1'/><circle cx='-2.5' cy='-2' r='1' fill='#000'/><circle cx='2.5' cy='-2' r='1' fill='#000'/><path d='M-3 2 Q0 4 3 2' stroke='#000' stroke-width='1' fill='none'/>");
}
void SpecialBlockFacialExpressionsController::init()
{
    watch("agent_click", [&](Event &e)
          {
        if (!_isDead) {
            decorate("<circle cx='0' cy='0' r='7' fill='#FFD700' stroke='#000' stroke-width='1'/><circle cx='-2.5' cy='-2' r='1' fill='#000'/><circle cx='2.5' cy='-2' r='1' fill='#000'/><circle cx='0' cy='2.5' r='1.5' fill='none' stroke='#000' stroke-width='1'/>");
        } });
    time_elapsed = 0; // Initialze the timer to 0.
}
void SpecialBlockFacialExpressionsController::update()
{
    time_elapsed += 1 / 30.0; // Assuming update() is called 30 times per second
    watch("Death", [&](Event &e)
          {
        _isDead = true;
        // Replace the face to it's death state
        decorate(" <circle cx='0' cy='0' r='7' fill='#FFD700' stroke='#000' stroke-width='1'/><line x1='-4.5' y1='-2' x2='-2' y2='-4.5' stroke='#000' stroke-width='0.8'/><line x1='-2' y1='-2' x2='-4.5' y2='-4.5' stroke='#000' stroke-width='0.8'/><line x1='2' y1='-2' x2='4.5' y2='-4.5' stroke='#000' stroke-width='0.8'/><line x1='4.5' y1='-2' x2='2' y2='-4.5' stroke='#000' stroke-width='0.8'/><path d='M-4 3 Q0 0.5 4 3' stroke='#000' stroke-width='1' fill='none'/>"); });
    if (!_isDead && time_elapsed >= 0.3)
    { // 10 ticks seems to be about right
        // Revert back to the smiley face if no bomb is discovered
        decorate("<circle cx='0' cy='0' r='7' fill='#FFD700' stroke='#000' stroke-width='1'/><circle cx='-2.5' cy='-2' r='1' fill='#000'/><circle cx='2.5' cy='-2' r='1' fill='#000'/><path d='M-3 2 Q0 4 3 2' stroke='#000' stroke-width='1' fill='none'/>");
        time_elapsed = 0; // Revert the timer back to 0.
    }
}