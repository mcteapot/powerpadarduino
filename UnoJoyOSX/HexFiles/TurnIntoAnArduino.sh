#!/bin/bash
# Proper header for a Bash script.

# TurnIntoAnArduino
# Run script to turn UnoJoy back into Arduino 

# Functions
writeboardonetwo () {
	# Arduino R1/R2
	echo ""
	echo "CONVERTING R1/R2:"
	
	echo "Erasing Board"
	RETURNDATA=$(dfu-programmer at90usb82 erase 3>&1 1>&2 2>&3 | tee >(cat - >&2))
	if [ "$RETURNDATA" != "" ]; then
		echo ""
		echo "ERROR: Is Arduino in DFU mode?"
		echo "Script is exiting."
		exit 1
	fi

	echo "Updating Code"
	sudo dfu-programmer at90usb82 flash Arduino-usbserial-uno.hex
	echo "Resetting Board"
	sudo dfu-programmer at90usb82 reset€
	
	echo ""
	echo "SUCCESS: GRAB BEERS!"
	echo "Disconnect and reconnect Arduino"
	echo ""

	exit 1
}

writeboardthree () {
	# Arduino R3
	echo ""
	echo "CONVERTING R3:"
	
	RETURNDATA=$(dfu-programmer atmega16u2 erase 3>&1 1>&2 2>&3 | tee >(cat - >&2))
	if [ "$RETURNDATA" != "" ]; then
		echo ""
		echo "ERROR: Is Arduino in DFU mode?"
		echo "Script is exiting."
		exit 1
	fi

	sudo dfu-programmer atmega16u2 flash Arduino-usbserial-uno.hex
	sudo dfu-programmer atmega16u2 reset
	
	echo ""
	echo "SUCCESS: GRAB BEERS!"
	echo "Disconnect and reconnect Arduino"

	exit 1
}

# Script start
echo ""
echo "-------------------------------------"
echo "*** Converting Arduino to UnoJoy ***"
echo "-------------------------------------"
# Checks to see if dfu-programmer is installed on the computer
if which dfu-programmer >/dev/null; then
    echo "dfu-programmer exists"

else
	echo "The program FLIP: dfu-programmer used to flash the board was not found..."
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


loopVar=0

while [ "$loopVar" == 0 ]; do
	
	echo ""	
	echo "Press (y) if running the Uno R3, if Uno R1/R2 press (n), or (q) to exit, followed by [ENTER]:"
	read unoAnswer
	echo ""	

	if [ "$unoAnswer" == "y" ]; then
		echo "Arduino R3"
		let "loopVar = 1"

		writeboardthree
	
	elif [ "$unoAnswer" == "n" ]; then
		echo "Arduino R2/R1"
		let "loopVar = 1"

		writeboardonetwo

	elif [ "$unoAnswer" == "q" ]; then
		echo "exit script"
		exit 1
	else
		echo "wrong command, enter again."

	fi
done


