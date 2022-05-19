#!/bin/bash

# read the input string for committing
read commit_params

# this shell script is for git committing
echo "commit the changes to the Github repo ..."
git add .
git commit -m"$commit_params"
git push

echo "success."