#!/bin/bash
# Program that surveys the main tools of this repository.
# For details, see each tool's source code.

# Most of the compiled programs read images to stdout
# and read them in stdin.
# The program 'show' reads an image from stdin and shows it to the screen,
# like this:
# (press any key to continue)
./show < img/larapiopb.jpg

# The program that does not read data from stdin is 'best_delta'.
# This program takes two images as command-line arguments
# and computes the positive difference between them.
# To reduce noise, this program try to move the images
# horizontally and vertically until it finds the lowest possible variation.
./best_delta img/larapiopb.jpg img/porta1pb.jpg | ./show

# To convert this to a binary image, use the tool 'thresholding'.
# It may simply receive an absolute threshold parameter, like this:
./best_delta img/larapiopb.jpg img/porta1pb.jpg | ./thresholding 50 | ./show

# or a relative threshold parameter, like this:
./best_delta img/larapiopb.jpg img/porta1pb.jpg \
    | ./thresholding --ratio 0.4 | ./show

# Even after 'best_delta', some noise may still be left;
# a way to remove this noise is to apply an opening operation to the resulting image.
# However, images like img/branquinha1.jpg will cause trouble,
# because what is left is almost big as the noise.
./best_delta img/branquinha2pb.jpg img/porta2pb.jpg \
    | ./thresholding --ratio 0.4 | ./show

# A way to work around is to use an horizontal 1x3 matrix to perform the opening
# instead of the default 3x3.
# This is achieved through use of 'filter'.
./best_delta img/branquinha2pb.jpg img/porta2pb.jpg \
    | ./thresholding --ratio 0.4 \
    | ./filter --kernel h \
    | ./show
# The intuition behind this is that, as the greatest source of noise
# is a single column of pixels,
# a filter that is delicate enough to only affect pixel columns
# will not destroy the entire content of the image.

# Still some noise remains. But thanks to this processing,
# the noise is geographically separated from the important parts of the image.
# The program 'largest_cluster' finds the largest pixel cluster,
# using a technique similar to the flood fill algorithm.
# This leaves only the "most important cluster" in the image.
./best_delta img/branquinha2pb.jpg img/porta2pb.jpg \
    | ./thresholding --ratio 0.4 \
    | ./filter --kernel h \
    | ./largest_cluster \
    | ./show

# This information seemed enough to feed a neural network.
# We simply pipe it through 'resize', to make it into a 10x10 image
# (because the neural network requires exactly 100 pixels to recognize an image)
# and pipe to 'neural_net', which will do the recognition.
#
# (The neural net must be trained beforehand; run ./setup before this line.)
./best_delta img/branquinha2pb.jpg img/porta2pb.jpg \
    | ./thresholding --ratio 0.4 \
    | ./filter --kernel h \
    | ./largest_cluster \
    | ./resize \
    | ./neural_net

# This should print something like
#   Dog index: 0.864201
#   Human index: 1.3167e-8
# in the command line instead of showing an image.

# Finally, all this procedure is encapsulated in the 'identify.sh' command.
./identify.sh img/larapiopb.jpg
