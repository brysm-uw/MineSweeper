# Minesweeper Game

Welcome to the **Minesweeper Game**! This project is a custom implementation of the classic Minesweeper logic and gameplay, built on a robust agent-based architecture using `enviro`.

## Project Overview

This Minesweeper project is a visually appealing, interactive game where players uncover blocks and avoid hidden mines. It uses a modular approach, separating game logic, block management, and block decoration into distinct classes. Each block reacts dynamically to player interaction, transitioning between various states (e.g., uncovered, dead, or flagged). The goal is to provide an engaging and entertaining experience while maintaining clear code organization for ease of development and future updates.

---

## Features
- **Dynamic Gameplay:**
  - Interactive grid with clickable blocks.
  - Automatically tracks and displays the number of adjacent bombs.

- **Minesweeper Aesthetic:**
  - Color-coded numbers for adjacent mines (1-8) matching the traditional Minesweeper style.

- **Block Behavior:**
  - Blocks change facial expressions dynamically based on events (`clicked`, `death`, `uncover`).
  - Smiley, surprised, and dead faces enhance the gameplay experience.

- **Agent-Based Structure:**
  - Each block is its own independent agent, allowing for clear encapsulation of behavior.
  - Managers handle bomb status and maintain game-wide state.

---

## Code Structure

### `BlockManager`
- **Purpose:** Manages the overall state of the Minesweeper grid, including bomb placement and tracking bomb statuses.
- **Key Responsibilities:**
  - Maintains a static map `_bombStatus` for storing the mine status of each block (keyed by block IDs or coordinates).
  - Prepares the game by initializing bomb placements and ensuring a specified maximum number of bombs.
  - Acts as the central manager for the Minesweeper grid.

---

### `BlockDecorator`
- **Purpose:** Handles the visual decoration and state logic of individual blocks.
- **Key Responsibilities:**
  - Decorates each block dynamically, based on its state (e.g., uncovered, flagged, or dead).
  - Determines valid neighboring blocks for calculating adjacent bomb counts.
  - Provides a clean separation of visual and logical concerns.

---

### `Block`
- **Purpose:** Represents an individual Minesweeper block, tying together both its decoration and management functionality.
- **Key Responsibilities:**
  - Integrates `BlockManager` (bomb-related logic) and `BlockDecorator` (visual styling) into a single cohesive unit.
  - Serves as the primary agent in the game, handling interactions and state changes.

---

### `SpecialBlockFacialExpressionsController`
- **Purpose:** Handles the facial expressions of special blocks to enhance user engagement.
- **Key Responsibilities:**
  - Watches for click events and changes the block's face to a surprised expression.
  - Dynamically reverts the face to a smiley state after a short delay.
  - Displays a "dead face" when the block is clicked and a bomb is present, preventing further changes.

---

## How to Play

1. **Start the Game:**
   - Launch the Minesweeper simulation via the provided environment setup.

2. **Interact:**
   - Click on any block to uncover it. If it's not a bomb, the number of adjacent bombs is displayed in Minesweeper-style color-coded numbers.
   - Avoid uncovering bombs!

3. **Explore:**
   - Blocks dynamically respond to your actions with facial expressions for added fun.

---

## Installation

1. Clone the repository:
   ```bash
   git clone git@github.com:brysm-uw/eep520-smith.git

2. **Navigate to the Project Folder:**
   ```bash
   cd minesweeper

3. **Ensure dependencies are installed for the enviro library. It's recommended to use Docker and grab the  klavins/enviro image: **
   ```bash
   docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.61 bash
4. **Start the React server, Run the project:**
   ```bash
   esm start
   enviro

---

## Project Highlights

- **Code Modularity:** Clear separation of concerns between block management, decoration, and game logic.
- **Custom SVG Styling:** Blocks are styled using SVG, enabling precise and visually appealing designs.
- **Interactive Gameplay:** Real-time updates and animations make the game both functional and fun.

---

## Key Challenges

During the development of this Minesweeper project, the following challenges were encountered and addressed:

1. **Timing Facial Expression Changes:**
   - Implementing precise timing for dynamic facial expressions on blocks (e.g., transitioning between surprised, smiley, and dead faces) posed a significant challenge. 
   - The solution involved using a timer mechanism (`time_elapsed`) within the `update` method to ensure facial expressions reverted to their default state after a fixed duration.

2. **State Management Between Processes:**
   - Coordinating and managing state information between `BlockManager` and `BlockDecorator` processes required careful planning.
   - To address this, shared variables (e.g., `_bombStatus`) and consistent logic across processes were used to maintain synchronization and ensure proper behavior.

3. **Agent Awareness Relative to an Arbitrary Agent:**
   - Developing functionality for agents (blocks) to detect and interact with other agents in arbitrary positions was complex, particularly for calculating valid neighbors and tracking adjacency.
   - This was solved by implementing methods like `is_valid_neighbor`, which used coordinate-based logic to assess relationships between agents.

## Future Enhancements
- Add difficulty levels with different grid sizes and bomb densities.
- Implement a timer to track player performance.
- Add a leaderboard to store and compare high scores.
- Introduce sound effects for clicks and explosions.
- There is currently no way to exit the game if the player loses.

---

## Credits
- Built using the `enviro` library for agent-based simulation, which is based off of 'Elma' for process management.
- Designed and implemented by Bryan Smith.
- Credits for previous project examples that assisted with some design decisions.
   
