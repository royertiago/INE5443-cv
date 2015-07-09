# Utility function used by setup.sh and identify.sh.
#
# This function reads an image in stdin,
# preformat it in a way proper to be fed to the neural network,
# and writes to stdout.
format() {
    ./thresholding | ./largest_cluster | ./resize
}
