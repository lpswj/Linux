#!/bin/bash

echo "Is it morning?Please answer yes or no"
read timeofday

if [ "$timeofday" = "yes" ];then
		echo -n "Good morning"
elif [ "$timeofday" = "no" ];then
		echo -n "Good afternoon"
else
		echo -n "Sorry,$timeofday not recognized.Enter yes or no"
		#printf "sorry ,not recognized";
		exit 1
fi

exit 0
