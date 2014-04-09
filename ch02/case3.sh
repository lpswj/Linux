#!/bin/bash

echo "Is it morning?Please answer yes or no"
read timeofday

case "$timeofday" in
		#yes | Y | y | Yes | YES )	 
		[yY] | [Yy][Ee][Ss] )
				echo "Good morning";;
		[nN]* )				 	
			   	echo "Good Afternoon";;
		* ) 
				echo "Sorry,answer not recognized"
				echo "Please answer yes or no"
				exit 1
				;;
esac

exit 0

