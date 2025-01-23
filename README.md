# Fract-ol

Fract-ol is a graphical project developed as part of the 42 school curriculum. The goal of the project is to create a program that generates and visualizes fractals, such as the Mandelbrot set, Julia set, and other variations. The project requires a deep understanding of algorithms, mathematics, and graphical programming using the MinilibX library.

![burningships](https://github.com/user-attachments/assets/8a468226-8c30-4739-a834-c3b12f76c85d)
![mandelbrot](https://github.com/user-attachments/assets/db5c7d8e-e903-4abb-88d6-94216a3112bc)
![julia](https://github.com/user-attachments/assets/93a86dff-2aa6-41b9-815b-79388831d9e7)

---

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [Fractals Supported](#fractals-supported)
- [Bonus Features](#bonus-features)
- [Resources](#resources)
- [Acknowledgments](#acknowledgments)

---

## Introduction
Fract-ol explores the world of fractals, which are intricate geometric shapes that exhibit self-similarity at different scales. By using mathematical formulas and iterative algorithms, this program generates mesmerizing visual patterns. This project not only teaches the beauty of fractals but also challenges the developer to manage complex graphical calculations and efficient rendering.

---

## Features
- Render the **Mandelbrot** set.
- Render the **Julia** set with customizable parameters.
- Smooth color gradients for fractal visualization.
- Zoom and pan functionality to explore fractals in detail.
- Real-time updates for Julia set parameters based on mouse movement.
- Highly optimized rendering with the MinilibX library.

---

## Installation

To build and run the project, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/D0ge42/fractol.git
   cd fractol
   ```

2. Compile the program using `make`:
   ```bash
   make
   ```

3. Run the program:
   ```bash
   ./fractol <fractal_name> [parameters]
   ```

---

## Usage

### Basic Syntax
```bash
./fractol <fractal_name> [additional_parameters]
```

### Examples
- Mandelbrot set:
  ```bash
  ./fractol Mandelbrot
  ```

- Julia set (with custom parameters):
  ```bash
  ./fractol Julia -0.7 0.27015
  ```

- Additional fractals:
  ```bash
  ./fractol <other_fractal>
  ```

---

## Controls
- **Zoom In/Out:** Scroll up/down.
- **Move:** Arrow keys.
- **Shift fractal colors** press "a".
- **Exit Program:** Press `ESC or Window close button`.

---

## Fractals Supported
1. **Mandelbrot Set:**
   A famous fractal defined by the equation:
   ```
   z = z^2 + c
   ```

2. **Julia Set:**
   A fractal closely related to the Mandelbrot set, where the parameter `c` is fixed, and the initial value of `z` varies.

3. **Bonus Fractals:**
   Additional fractals can be implemented as bonus features, such as:
   - Burning Ship
---

## Resources
- [MinilibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx/)
- [Understanding Mandelbrot and Julia Sets](https://mathworld.wolfram.com/MandelbrotSet.html)
- [Fractal Geometry Basics](https://fractalfoundation.org/resources/what-are-fractals/)

---
