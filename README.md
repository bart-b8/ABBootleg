# Angry Birds Bootleg

Course project for E017210A Programmeren. Counting for 30% to the final grade. We received some startcode including:
 - a wrapper for allegro.
 - example code to help us with hitdetection
 - example code for a singleton class construction

We had to deliver our code by a deadline that compiled without errors, showed logical design and runs smoothly.

# User Instructions

## Ubuntu

Install dependencies: 

```bash
sudo apt update && sudo apt upgrade -y
sudo apt install build-essential pkg-config cmake gcc g++ gdb git libsdl1.2-dev libsdl-image1.2-dev libglew-dev libboost-test-dev libncurses-dev -y
```

Clone this repo:

```bash
git clone https://github.com/bart-b8/ABBootleg.git
```

Open Project.code-workspace in VS Code:

```bash
cd ABBootleg
code Project.code-workspace
```

The task _**Run (+build)**_ will compile and run the game.
