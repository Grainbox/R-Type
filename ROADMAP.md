# 🗺️ R-Type Project Roadmap

This roadmap outlines the planned enhancements and community goals for the R-Type project as it transitions to open source.

## Phase 1: Foundation & Stability (Current)
*Goal: Ensure the project is easy to build and run for everyone.*
- [x] Create automated setup scripts (`setup.ps1`, `build.sh`).
- [x] Revamp `README.md` with clear instructions.
- [x] Fix documentation typos and dead links.
- [ ] Stabilize CI/CD pipelines for Windows/Linux builds.

## Phase 2: Game Engine Enhancements
*Goal: Refine the core systems and add essential game loops.*
- [ ] **Issue: Entity Component System (ECS) Refactoring**
  - Implement a more performant component storage.
  - Add support for dynamic component addition/removal at runtime.
- [ ] **Issue: Animation System**
  - Integrate sprite-sheet animation support in the client.
  - Implement basic state-machine for player/enemy animations.
- [ ] **Issue: Resource Manager**
  - Create a centralized asset loader (Textures, Sounds, Fonts).
  - Implement basic caching to avoid redundant disk I/O.

## Phase 3: Gameplay & Content
*Goal: Make the game fun and replayable.*
- [ ] **Issue: Enemy AI Variety**
  - Implement different movement patterns (Sinusoidal, Zig-zag, Homming).
  - Add "Boss" entities with multiple health segments and phases.
- [ ] **Issue: Power-up System**
  - Create drops for weapon upgrades, shields, and speed boosts.
  - Implement weapon fire modes (Rapid fire, Spread shot, Charged laser).
- [ ] **Issue: Level Scroller**
  - Implement a background parallax scrolling system.
  - Add a level-loading mechanism from configuration files.

## Phase 4: Online & Social
*Goal: Expand the multiplayer experience.*
- [ ] **Issue: Lobby System**
  - Implement a basic pre-game lobby to wait for players.
  - Add support for basic chat in the lobby.
- [ ] **Issue: Leaderboards**
  - Implement a global high-score system (requires a database/backend).
- [ ] **Issue: Latency Compensation**
  - Research and implement client-side prediction and server reconciliation.

---

*Want to contribute? Check our [Contribution Guidelines](CONTRIBUTING.md) (Coming Soon!)*
