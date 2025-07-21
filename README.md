## 🎮 This Is a Small Project in My Portfolio: **PacMan**

<p align="center">
  <img src="https://raw.githubusercontent.com/sodepth/PacMan/main/Assets/Gif.gif" width="60%" alt="PacMan Gameplay">
</p>

---

### Gameplay Description

In **PacMan**, you take control of a round yellow character that moves around the screen, eating apples and avoiding deadly spikes. Key features:

- **Simple Yet Addictive Controls**
  Use **WASD** (or arrow keys) to move, **R** to restart the current round, and **ESC** to return to the main menu.

- **Game Modes**
  - **Speed Boost**: each time you collect an apple, your character’s speed increases.
  - **Infinite Apples**: apples instantly respawn at a new random location on the field.

- **Dynamic Object Placement**
  Apples and spikes appear at random, non-overlapping positions, thanks to a built-in position-generation algorithm that respects margins from the center and screen edges.

- **Shaders & Visual Effects**
  - A smoothly color-shifting animated shader for the background.
  - A “rainbow” apple in Speed Boost mode, created with a fragment shader.
  - A subtle blur shader effect when you lose.

- **Sound Design**
  Collecting an apple, winning, or losing each trigger WAV sound effects, enhancing immersion.

---

### Technologies & Tools

- **C++17**
- **SFML 2.5.x** (graphics, input, audio, shaders)
- **CMake** for build management

---

### Screenshots

<div align="center">
  <img src="https://raw.githubusercontent.com/sodepth/PacMan/main/Assets/1screen.png" width="30%" alt="Screenshot 1"/>
  <img src="https://raw.githubusercontent.com/sodepth/PacMan/main/Assets/2screen.png" width="30%" alt="Screenshot 2"/>
  <img src="https://raw.githubusercontent.com/sodepth/PacMan/main/Assets/3screen.png" width="30%" alt="Screenshot 3"/>
</div>

---

**PacMan** is a simple yet flexible project showcasing:
- Working with SFML graphics and shaders
- Well-organized, modular code architecture (Player, Apple, Spike, UI, Sounds)
- Algorithms for random object placement and collision handling
- UI/HUD setup and sound effects for full immersion

> Give it a try—building and playing is fast, controls feel responsive, and each new round is unpredictable thanks to dynamic object spawning!
