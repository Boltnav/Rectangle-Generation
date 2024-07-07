This work generates N number of *disjoint* rectangles on a 2D board. 

Some take-aways:
- This was used to generate ~20 rectangles to input to an RL algorithm which would further alter the positions and orderings of the same. This work required the rectangles to be disjoint as we wanted to figure out the minimum number of Guillotine Cuts as well as minimum number of rectangles that would be destroyed by the same.
- Later on (towards May), I made some simple alterations to use the code to generate a set of *non-disjoint* rectangles. Much more trivial, this was used for a similar but different problem of figuring out an Integrality Gap problem.
