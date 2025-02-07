#!/bin/bash

if [[ grep "RAINSHINE_UNITS=[mM]" ~/.bashrc ]]; then

    # remove old env variable and write a new one
    awk '!/RAINSHINE_UNITS/' ~/.bashrc > ~/.bashrc.tmp && mv ~/.bashrc.tmp ~/.bashrc
    echo "export RAINSHINE_API_KEY=i" >> "$HOME/.bashrc"
    source "$HOME/.bashrc"
    echo "Units updated to imperial. You may need to run 'source ~/.bashrc' manually to apply changes."

elif [[ grep "RAINSHINE_UNITS=[iI]" ~/.bashrc ]]; then

    # remove old env variable and write a new one
    awk '!/RAINSHINE_UNITS/' ~/.bashrc > ~/.bashrc.tmp && mv ~/.bashrc.tmp ~/.bashrc
    echo "export RAINSHINE_API_KEY=m" >> "$HOME/.bashrc"
    source "$HOME/.bashrc"
    echo "Units updated to metric. You may need to run 'source ~/.bashrc' manually to apply changes."

fi