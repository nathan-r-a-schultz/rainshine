#!/bin/bash

# remove old location
awk '!/RAINSHINE_LOCATION/' ~/.bashrc > ~/.bashrc.tmp && mv ~/.bashrc.tmp ~/.bashrc

# get new location
read -rp "Enter your new location: " LOCATION

# export location and run source ~/.bashrc
echo "export RAINSHINE_LOCATION=$LOCATION" >> "$HOME/.bashrc"
source "$HOME/.bashrc"
echo "Location updated. You may need to run 'source ~/.bashrc' manually to apply changes."