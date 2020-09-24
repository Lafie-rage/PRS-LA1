#!/bin/bash

echo "Avant : `ls -l $1`"
touch $1
echo "Apres : `ls -l $1`"
