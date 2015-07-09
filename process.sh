# Utility function used by setup.sh and identify.sh.
#
# This function reads an image in stdin,
# preformat it in a way proper to be fed to the neural network,
# and writes to stdout.
format() {
    format_noresize | ./resize
}

# Same as above, but does not resize the image as the last step.
format_noresize() {
    ./thresholding --ratio 0.4 | ./filter --kernel h | ./largest_cluster
}
