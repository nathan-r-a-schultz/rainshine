#!/bin/bash

# remove old location
awk '!/RAINSHINE_LOCATION/' ~/.bashrc > ~/.bashrc.tmp && mv ~/.bashrc.tmp ~/.bashrc

echo -e "\nThe following formats for locations are valid:\n[1] US Zipcode\n[2] Canada Postalcode\n[3] IP Address\n[4] Latitude/Longitude (decimal degree)\n[5] City name (not recommended for small towns or cities with common names)\n"
    read -p "Enter your option [1,2,3,4,5]: " FORMAT_SELECTION

    # Ask the user for their location based on their selection
    case "$FORMAT_SELECTION" in

        1)
            echo "Option [1] selected"
            read -p "Enter your US Zipcode: " LOCATION
        ;;

        2)
            echo "Option [2] selected"
            read -p "Enter your Canada Postalcode (do not use spaces): " LOCATION
            LOCATION="${LOCATION:0:3}+${LOCATION:3:3}"
        ;;

        3)
            echo "Option [3] selected"
            echo "Available IP addresses: "

            if command -v ip >/dev/null; then
                ip -4 addr show | awk '/inet / {print $2}' | cut -d/ -f1
            else
                echo "IP command not found. Please enter IP manually."
            fi
                read -p "Enter the IP address to use: " LOCATION
        ;;
    
        4)
            echo "Option [4] selected"
            read -p "Enter your latitude and longitude in the form (latitude,longitude): " LOCATION
        ;;

        5)
            echo "Option [5] selected"
            read -p "Enter the name of your city or town: " LOCATION
        ;;

        *)
            echo "Invalid selection, location change aborted"
            exit 1
        ;;

    esac

# export location and run source ~/.bashrc
echo "export RAINSHINE_LOCATION=$LOCATION" >> "$HOME/.bashrc"
source "$HOME/.bashrc"
echo "Location updated. You may need to run 'source ~/.bashrc' manually to apply changes."