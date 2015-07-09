#!/bin/bash

if (( $# != 1 )); then
    echo "Usage: $0 <new_image>"
    exit 1
fi

source process.sh

./best_delta "$1" img/porta1pb.jpg | format | ./neural_net
