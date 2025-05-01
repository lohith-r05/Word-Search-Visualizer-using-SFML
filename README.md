# Word Search Puzzle Solver

A simple yet effective C++ application that solves word search puzzles using SFML for graphical visualization. The program reads a grid of letters and a list of words from a file, finds the words in the grid (in all 8 directions), and highlights them in a colorful graphical window.

## Features

- **Reads input from a text file** (grid and comma-separated words)
- **Searches words** in 8 directions (horizontal, vertical, and diagonal)
- **Visualizes the puzzle** using [SFML](https://www.sfml-dev.org/)
- **Highlights found words** with different colors
- Supports uppercase and lowercase letters

## Demo

"FARTHESTKIMRSKTGSPRAANAPTNHANATTHTTTAENYHAANIHIPKNSLHHTRIEADAHIARIIONIBDSNMISVAHCHUIAIIIUEDASMLNKAVA"
"FARTHEST,VISIT,RAT,NEAT,MATHS"


- The first line must form a perfect square (e.g., 4x4 = 16 characters, 5x5 = 25 characters, etc.)
- The second line is a comma-separated list of words

**Output:**

- A grid rendered in a GUI window
- Words highlighted in color if found
- Console output displaying whether each word was found

## Screenshots

![image](https://github.com/user-attachments/assets/68166f78-2202-44c9-9357-97457a289779)
![image](https://github.com/user-attachments/assets/6246de0b-fa65-4a5b-acfe-3377ca2b32e5)


### Prerequisites

- **C++ compiler**
- **[SFML library](https://www.sfml-dev.org/download.php)** (Graphics module)
- `arial.ttf` font file in the executable directory
- CMake or any build system of your choice


