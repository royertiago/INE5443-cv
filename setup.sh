#!/bin/bash

source process.sh

echo Generating train dataset...
./best_delta img/branquinha1pb.jpg img/porta1pb.jpg | format > nn_train/dog1.png
./best_delta img/branquinha2pb.jpg img/porta1pb.jpg | format > nn_train/dog2.png
./best_delta img/branquinha3pb.jpg img/porta1pb.jpg | format > nn_train/dog3.png
./best_delta img/branquinha1pb.jpg img/porta2pb.jpg | format > nn_train/dog4.png
./best_delta img/branquinha3pb.jpg img/porta2pb.jpg | format > nn_train/dog5.png
./best_delta img/kirra1pb.jpg img/porta1pb.jpg | format > nn_train/dog6.png
./best_delta img/kirra2pb.jpg img/porta1pb.jpg | format > nn_train/dog7.png
./best_delta img/kirra1pb.jpg img/porta2pb.jpg | format > nn_train/dog8.png
./best_delta img/kirra2pb.jpg img/porta2pb.jpg | format > nn_train/dog9.png
./best_delta img/larapiopb.jpg img/porta1pb.jpg | format > nn_train/human1.png
./best_delta img/larapiopb.jpg img/porta2pb.jpg | format > nn_train/human2.png
./best_delta img/sergiopb.jpg img/porta1pb.jpg | format > nn_train/human3.png
./best_delta img/sergiopb.jpg img/porta2pb.jpg | format > nn_train/human4.png
./best_delta img/porta1pb.jpg img/porta2pb.jpg | format > nn_train/nothing1.png
./best_delta img/porta2pb.jpg img/porta1pb.jpg | format > nn_train/nothing2.png

echo Training network...
(
    for file in nn_train/dog*; do
        echo $file
    done
    echo
    for file in nn_train/human*; do
        echo $file
    done
    echo
    for file in nn_train/nothing*; do
        echo $file
    done
) | ./train_neural_net

echo Done.
