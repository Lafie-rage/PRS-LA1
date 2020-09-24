#!/bin/bash

find /etc -maxdepth 1 -type f -writable
find /etc -maxdepth 1 -type f -readable
