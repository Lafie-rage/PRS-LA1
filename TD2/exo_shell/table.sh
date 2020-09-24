#!/bin/bash

for i in `seq 0 $2`;
do
  echo "$i x $1 = $(($1 * $i))"
done
