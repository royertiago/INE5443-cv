Computer vision: Intruder detection system
==========================================

This is the final assignment for the INE5443 discipline --- Pattern Recognition.

We were given a set of images;
two of them were the photo of an entrance of a house
and the other were photos of the same entrance,
but with either humans trying to open the door
or dogs walking around the balcony.

(In one of the photos,
the professor of the discipline,
Aldo von Wangenheim,
is "disguised" as a thief trying to invade the house;
that's why it is an "intruder detection system").

We were under the closed-world assumption;
that is, no other images would be added to our set.
In particular, we would not have to differentiate between a dog
and Aldo crawling towards the door.

Building
========

The project uses the libraries `opencv` and `fann`.
Install the packages `libopencv-dev` and `libfann-dev`;
then run

    make

in the command line.
(The makefile assumes a compiler that supports C++14.)

Running
=======

The detector uses a neural network that needs to be trained before use.
Run

    ./setup.sh

to perform the necessary training.
Then,
to simulate a detection against to the image `img/larapiopb.jpg`, for example,
run

    ./identify.sh img/larapiopb.sh
