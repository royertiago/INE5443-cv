#!/bin/bash

if (( $# != 2 )); then
    echo "Usage: $0 <new_image> <base_image>"
    exit 1
fi

source process.sh

./best_delta "$1" "$2" | format | ./neural_net
