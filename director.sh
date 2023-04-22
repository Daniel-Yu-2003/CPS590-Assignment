#Daniel Yu 501120369 daniel1.yu@torontomu.ca
#!/bin/bash

display () { #display the files
	clear # clear the terminal
	for i in $(eval echo {1..$1}); do # loop through the files
		echo "$(<star$i.txt)" # print content of the file
	done
}

clean () { # function to clean the system
	for i in $(eval echo {1..$1}); do # loop through the files
		rm star$i.txt # remove the files
	done
	kill -SIGKILL $$ #terminate self
}

W=$1
sPID=$2
for i in $(eval echo {1..$W}); do # run the worker files
	exec ./worker star$i.txt $sPID &
done

while $(eval echo 2 > 1); do # forever loop
	display $W # call display function
	trap "clean $W" SIGINT # trap SIGINT signal and call signal function
	sleep 1
done
