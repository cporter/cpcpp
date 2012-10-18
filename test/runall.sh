#!/bin/sh

# Could there possibly be a more hokey way to run a bunch of test?
# There could not.

for x in $@
do
    ./$x
done
