#!/bin/bash
# Proper header for a Bash script.

# TurnIntoAnArduino
# Run script to turn Arduino back into Arduino 

echo "Hello World"

# Checks to see if dfu-programmer is installed on the computer
if which dfu-programmer >/dev/null; then
    echo "dfu-programmer exists"

else
	echo "The program dfu-programmer used to flash the memory was not found..."
	echo "Linux run apt-get to install."
	echo "Mac install threw mac ports."
	echo "Script is exiting."
	exit 1
	
fi


# Checks to see if firmware file is found on the computer
if [ ! -f Arduino-usbserial-uno.hex ]; then
	echo "File not found: Arduino-usbserial-uno.hex"
	echo "Script is exiting."
	exit 1

else
	echo "Arduino-usbserial-uno.hex exists"

fi