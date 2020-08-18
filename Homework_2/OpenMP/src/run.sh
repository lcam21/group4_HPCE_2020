#!/bin/bash

echo "# This is an execution example, depends on your computer architecture the timing report can be change."
echo "# For pi.c"
./pi

echo " "
echo "# For pi_omp_private.c"
./pi_omp_private

echo " "
echo "# For pi_omp_threads.c"
./pi_omp_threads

echo " "
echo "# For pi_omp_teams.c"
./pi_omp_teams
