# C_GameOfLife
Conway’s Game of Life, written in C, using binary file inputs for starting map. 

Takes two arguments: 
1) the binary file (you'll find them easily by their lack of ".XXX" filename
2) number of generations to run

The code is kept in "main.c"

The currently compilied program is "Conway"

The four binary files are: "blinkers", "glider", "random", and "still" 

If you don't want the results in the terminal you can pipe it into a file as such: "./Conway random 100 > out.txt"

Largely ignore "testInts.txt", that's really only for extensive debugging

If you want to see it do something, run it a few times incrementing the generations, like this:
"./Conway blinkers 38"
"./Conway blinkers 40"
"./Conway blinkers 42"

Thank you and enjoy!
