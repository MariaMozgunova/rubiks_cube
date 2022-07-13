<div id="top"></div>



<!-- PROJECT SHIELDS -->
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#explaining-the-concepts">Explaining the concepts</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#how-i-was-struggling-to-implement-visualization">How I was struggling to implement visualization</a></li>
    <li><a href="#whats-next">What's next?</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

This project solves the [Rubik's Cube](https://en.wikipedia.org/wiki/Rubik%27s_Cube).

The following actions are possible:

- Read and write to a file the state of the Rubik's Cube
- Check whether the current configuration of the Rubik's Cube is solvable or not
- Output to any `std::ostream` the state of the Rubik's Cube
- Spin the facelets of the Rubik's Cube
- Generate the solvable state of the Rubik's Cube
- Solve the Rubik's Cube [now with the visualization]

<p align="right">(<a href="#top">back to top</a>)</p>



### Explaining the concepts

Several [efficient algorithms](https://en.wikipedia.org/wiki/Optimal_solutions_for_Rubik%27s_Cube) to solve Rubik's Cube are already developed. In the project, I implemented the heuristic approach.

First things first, the facelet and the cubie are shown in the picture below.
![facelet and cubie](https://github.com/MariaMozgunova/pictures/blob/master/facelet_and_cubie.png?raw=true)

To input the state of the Rubik's Cube into the program, you give it a 6-element array of 9 uints. Specify the colors as follow: `BLUE`=0, `ORANGE`=1, `GREEN`=2, `RED`=3, `WHITE`=4, `YELLOW`=5.

The program outputs the state of the Rubik's Cube as the 6 strings of 9 elements. To decode the string use the mapping: `B`=`BLUE`; `O`=`ORANGE`; `G`=`GREEN`; `R`=`RED`; `W`=`WHITE`;`Y`=`YELLOW`;

To check the correctness of the Rubik's Cube's state program validates four conditions Edge Permutation Parity, Edge Orientation Parity, Corner Permutation Parity, Corner Orientation Parity as specified in [this paper](http://www.math.rwth-aachen.de/~Martin.Schoenert/Cube-Lovers/David_Vanderschel__Orbit_Classification.html). You can check if the cube is solvable using `RubiksCube::validate_cube()` method.

To output the cube's current state use `RubiksCube::print_cube(std::ostream &out = std::cout)` function.

To arbitrarily rotate the cube's facelets use `RubiksCube::rotate(uint8_t cmd)`. The argument `cmd` can take 12 values: 
`0`=rotate the upper facelet clockwise, 
`1`=rotate the upper facelet counterclockwise, 
`2`=rotate the down facelet clockwise, 
`3`=rotate the down facelet counterclockwise, 
`4`=rotate the right facelet clockwise, 
`5`=rotate the right facelet counterclockwise, 
`6`=rotate the left facelet clockwise, 
`7`=rotate the left facelet counterclockwise, 
`8`=rotate the front facelet clockwise, 
`9`=rotate the front facelet counterclockwise, 
`10`=rotate the back facelet clockwise, 
`11`=rotate the back facelet counterclockwise.

You can shuffle the cube with the `RubiksCube::shuffle()` function. What it does is generate some number of rotations.

You can get the sequence of rotations to solve the cube with the `RubiksCube::solve()` function. 

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

To use this Rubik's Cube solver, follow the simple steps below.

### Installation

1. Clone the repo `git clone https://github.com/MariaMozgunova/rubiks_cube.git`
2. Include the Rubik's Cube solver into your code `#include "rubiks_cube/rubiks_cube.hpp"`

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

See `main.cpp` for an example of usage.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- VISUALIZATION JOURNEY -->
## How I was struggling to implement visualization

First of all, I decided to use `GLUT` to visualize my Solver. However, when a lot of my attempts to install it failed, I decided that something was going wrong. It is then that I discovered you could use [`vcpkg`](https://www.youtube.com/watch?v=pSirBt4OgXQ) to easily install any package with VisualStudio. 

Next, I realized that the modern way to work with graphics is through `glad` and `glfw3`. Thus, I installed `glad` and `glfw3` with `vcpkg`... and here began my journey of exploring OpenGL. Btw, I can recommend [Learn OpenGL tutorial](https://learnopengl.com/Introduction) for those who are learning how to work with `glad` and `glfw3`.

First things first, I tried to draw a square composed of two triangles and spin one of them.

![spin single triangle]()

After that, I was curious whether I could rotate multiple triangles simultaneously. I built four squares out of eight triangles.

![rotate multiple figures at once](https://github.com/MariaMozgunova/pictures/blob/master/%D0%BA%D1%83%D0%B1%D0%B8%D0%BA%202%20by%202%20by%201.png)

Subsequently, I started building each facelet cubie by cubie.

![first two squares](https://github.com/MariaMozgunova/pictures/blob/master/building%20each%20facelet%20cubie%20by%20cubie.png)

![two opposite sides](https://github.com/MariaMozgunova/pictures/blob/master/get%20B%20facelet%20nearly%20for%20free%20(notice%20that%20z%20coordinates%20can%20only%20be%20negated).png)

![only up and down left](https://github.com/MariaMozgunova/pictures/blob/master/got%20a%20bracelet.png)

![got a skeleton for the cube](https://github.com/MariaMozgunova/pictures/blob/master/hey%2C%20skeleton%20is%20finally%20built.png)

The next step was to color the cube.

![color the cube](https://github.com/MariaMozgunova/pictures/blob/master/look!%20it%20actually%20works.png)

Rotating the whole cube worked alright.

![rotate the whole cube]()

However, trying to rotate the particular facelet was a disaster.

![cubie is missing](https://github.com/MariaMozgunova/pictures/blob/master/hey%2C%20why%20some%20of%20the%20squares%20are%20missing.png)

After dealing with the above issue, I managed to make visualization into my code. Watch the video solving the cube below!

![visualization of the entire solution]()

I also managed to decrease by two the number of moves required to solve the Rubik's Cube compared to my initial implementation.



<!-- FURTHER DEVELOPMENT -->
## What's next?

I should consider filling in the cube as now you can see all the insides while it is rotating.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Maria Mozgunova - [Twitter - @MariaMozgunova](https://twitter.com/MariaMozgunova) - mariiamozgunova@gmail.com

Project Link: [https://github.com/MariaMozgunova/rubiks_cube](https://github.com/MariaMozgunova/rubiks_cube)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [README Template](https://github.com/othneildrew/Best-README-Template)

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/MariaMozgunova/rubiks_cube/blob/master/LICENSE
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/mariamozgunova/
