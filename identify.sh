#!/bin/bash

if (( $# != 2 )); then
    echo "Usage: $0 <new_image> <base_image>"
    exit 1
fi

new="$1"
base="$2"

./best_delta "$1" "$2" | ./thresholding | ./largest_cluster | ./resize | ./neural_net
