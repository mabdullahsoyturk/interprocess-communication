# Interprocess Communication
This repository contains some of the methods to communicate between processes on unix based operating systems.

# Task

Assume that you have several files representing bags containing balls with different colors.
An input file might contain comma separated colors such as “yellow, yellow, green, red, blue,
blue, orange, blue, yellow, red”. In this project, you are supposed to implement several
programs which will count the colors of each ball in a bag given as input, and find and output
the probability to take out a definite color from the bag in an output file. The color to be
chosen will be given as user input. The programs will be named psearch. They need to take
the following command line parameters: a string keyword (chosen color), number of input
files (n), input filenames, and an output filename. Number of input files will be greater than or
equal to 1. Each input file is a text file; containing a sequence of lines. All of these lines may
contain one or more strings. The output file will contain the probability (2/7) along with the
count of balls of different colors in the format below:
<probability>: <your result>
<input filename>, <color name>: <color count>. The output must be sorted according to first
<input filename> and then <color name>. An example execution of your program should be:
psearch orange 3 input1.txt input2.txt input3.txt output.txt
