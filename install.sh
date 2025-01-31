#!/bin/bash

# the environment config function
configEnvVars() {

    # get the user's API key, units, and location
    echo "Please enter your weatherapi.com API key (input is hidden):"
    read -sp "API Key: " API_KEY

    # ensure the right input is used for inputs
    read -p "Would you like to use metric measurements or imperial measurements? [m/i]" UNITS
    if [[ "$UNITS" != [mMiI] ]]; then
        echo "Invalid inputs. Program aborted."
        exit 1
    fi

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
            echo "Invalid selection, install script aborted"
            exit 1
        ;;

    esac

    # write as env variables
    echo "export RAINSHINE_API_KEY=$API_KEY" >> "$HOME/.bashrc"
    echo "export RAINSHINE_LOCATION=$LOCATION" >> "$HOME/.bashrc"
    echo "export RAINSHINE_UNITS=$UNITS" >> "$HOME/.bashrc"
}

cd "$(dirname "$0")/src" || exit 1

# compile to an executable and handle errors if compilation fails
if ! make rainshine; then
    echo "Compilation failed"
    exit 1
fi

# define the install directory
INSTALL_DIR="$HOME/.local/bin"

# check if the install directory exists. if not, create it
if [[ ! -d "$INSTALL_DIR" ]]; then
    mkdir -p "$INSTALL_DIR"
fi

# copy the executable into the installation directory and handle errors if compilation fails
if ! cp rainshine "$INSTALL_DIR/"; then
    echo "Failed to copy executable to $INSTALL_DIR"
    exit 1
fi

# enter scripts directory and copy required scripts
cd scripts
if ! cp rainshinechangekey.sh rainshinechangelocation.sh "$INSTALL_DIR/"; then
    echo "Failed to copy scripts to $INSTALL_DIR"
    exit 1
fi

# allow for execution of the scripts
chmod +x "$INSTALL_DIR/rainshinechangekey.sh" "$INSTALL_DIR/rainshinechangelocation.sh"
cd ..

# copy the executable to the path
if [[ ":$PATH:" != *":$INSTALL_DIR:"* ]]; then
    
    if ! grep -qxF "export PATH=\$HOME/.local/bin:\$PATH" "$HOME/.bashrc"; then
        echo 'export PATH=$HOME/.local/bin:$PATH' >> "$HOME/.bashrc"
    fi

    export PATH=$INSTALL_DIR:$PATH
    echo "$INSTALL_DIR added to PATH"
fi

# check to see if the user already has environment variables from a previous installation
if [[ $(grep -q "RAINSHINE_API_KEY" ~/.bashrc && grep -q "RAINSHINE_LOCATION" ~/.bashrc; echo $?) -eq 0 ]]; then

    echo "You appear to already have environment variables for RainShine from a previous installation."
    read -rp "Use these existing environment variables? [Y/n]: " ANSWER

    # default answer is yes
    ANSWER=${ANSWER:-Y}

    if [[ "$ANSWER" =~ ^[Yy]$ ]]; then
        echo "Using existing environment variables."
    else
        echo "Proceeding without using the existing variables."
        awk '!/RAINSHINE_API_KEY/ && !/RAINSHINE_LOCATION/' ~/.bashrc > ~/.bashrc.tmp && mv ~/.bashrc.tmp ~/.bashrc # remove old environment variables to prevent clogging ~/.bashrc
        configEnvVars # configure the environment variables manually
    fi

else 

    # configure the environment variables manually
    configEnvVars

fi

# update the shell
source "$HOME/.bashrc"

# clean up compiled object files
rm rainshine
rm *.o

# inform user of a completed installation
echo "Installation complete. You may need to run 'source ~/.bashrc' manually to apply changes."