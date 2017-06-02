# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

This Udacity project was very simple. As it is just the implementation of a simple PID controller, I did not expect to see good lateral control (lane keeping) without exhaustive parameter tuning, but even so, due to its linear nature (and the system is non linear), performance would depend heavily on the geometry of the road, the system, the speed, etc. 

Nevertheless, it is capable of keeping the car inside the track for a full loop. It is somewhat twitchy but exhaustive parameter tuning could help with that. I did not try to do exhaustive search or twiddle though because I cannot compile the project on my main computer, which has Windows 7, and cannot install Linux on it, and my 'battle' linux laptop suffers enormously when running the simulator. Basically, it is the outright textbook implementation, with only two additions:

	* An exponential moving average tries to smooth the derivative term a bit. This does not works well, and should be substitued by a Kalman filter if possible.
	* The integral error term is limited in magnitude, so it 'saturates', avoiding accumulating an overly large value. This helps to somewhat reduce the overshoot due to the integral term when this gets very big and takes a longer time to reduce back to 0.

A proper implementation, for example, in automotive, would need more safeguards and so on.

Tuning was done via adjusting first the proportional factor, then the derivative factor, then adding a small integral factor. After finding a version that keeps the car in the lane, adjustment of the proportional and drivative (upwards) was tried to help with the tight turns. The speed is set to a constant, though smaller than in the original version. I expected that a high P would lead to great overshoot, which happened, and this could be then compensated with the derivative term, which happened, and then finally trying to correct for bias in the controller with the integral term, though its effect is not as noticeable for my set of parameters. One thing I noticed is that the system has a very low publication frequency, and when I tested in a virtual machine, where the frequency was much smaller, the performance with similar parameters was much, much worse. I think that 10Hz, wich seems to be the 'good' frequency, is far too slow for this! In 100ms at 30 m/s, your error can be as high as 3m! MPC should alleviate this to some extent.

It would be cool to do an state space approach with a continous linearization (maybe via approximation multidimensional polynomials) of the system. And in that case the P and D factors blurr. You could say that the controller just, at all times, takes the state of the system and tries to apply a control input in the opposite 'direction' of the error, and so we would have: output = - Jacobian * K * error. Where K can be a matrix and the error a vector that has the derivatives of the system (we assume we want a 0 derivative for the error). In a linear system, this guarantees that the error will, eventually, go to zero (with some conditions on K), because the 'proportional' term in K opposes the error. The derivative helps with limiting the effect of the controller, so it avoids stronger than needed outputs (less overshoot), and the integral term adjust for biases in the steady, long term state (less permanent error). In a hand wavy way, that is the idea behind PID controllers.

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./
