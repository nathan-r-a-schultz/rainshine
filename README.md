# RainShine

RainShine is a command line tool for Linux. Its purpose is to easily fetch weather data and allow the user to view up-to-date forecasts in their terminal.

## Compatibility

As of right now, only Linux is officially supported. Development for RainShine has been conducted on Arch Linux, but RainShine should be compatible with all modern Linux distributions.

## Installation

Run ```install.sh``` (located in the root directory of the repo). You will likely need to give ```install.sh``` execution permissions. The installation script will guide you through the set up. Note that you will need an API key from https://www.weatherapi.com, which can be acquired for free.

## Usage

All commands are in the form ```rainshine [option...]```. Options are listed below.

| Command               | Output  |
| :-------------------  | :------ |
| current               | Gets current weather conditions     |
| forecast [int]        | Retrieves the forecast for the next number of days specified    |
| envinfo               | Retrieves your API key and location     |
| change [string]       | Allows the user to change either their location, their API key, or their units. Specified by the using the string "location", "key", or "units" |
| help                  | Prints out all available commands |