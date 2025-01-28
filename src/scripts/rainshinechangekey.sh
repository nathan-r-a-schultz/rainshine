#!/bin/bash

# remove old api key
awk '!/RAINSHINE_API_KEY/' ~/.bashrc > ~/.bashrc.tmp && mv ~/.bashrc.tmp ~/.bashrc

# get new api key from the user
read -sp "Enter your new weather.com API key: " API_KEY

# export api key and run source ~/.bashrc
echo "export RAINSHINE_API_KEY=$API_KEY" >> "$HOME/.bashrc"
source "$HOME/.bashrc"
echo "API key updated. You may need to run 'source ~/.bashrc' manually to apply changes."