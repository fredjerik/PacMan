# Gemini Project Instructions for Pac-Man

This file contains project-specific instructions for the Gemini agent.

---

## About the Project

This is a Pac-Man clone written in C++ using the SFML library. The architecture is based on the Model-View-Controller pattern and separates the game logic from the SFML representation layer.

---


## Coding Style & Conventions

*   **Indentation:** Use 4 spaces.
*   **Naming:** Classes are `PascalCase`, functions and variables are `snake_case`. Private members should have a trailing underscore (e.g., `window_`).
*   **Headers:** Use `#pragma once` or include guards. Prefer include guards.

---

## Preferred Libraries & Technologies

*   **Graphics:** SFML 2.6
*   **Build System:** CMake
*   **C++ Standard:** C++17

---

## Agent Instructions

*   At the end of each session, if significant work has been done, offer to save a summary of the conversation to a dated markdown file (e.g., `gemini-YYYY-MM-DD.md`) in the `gemini_summaries` directory.
---