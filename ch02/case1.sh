#!/bin/bash

echo "Is it morning?Please answer yes or no"
read timeofday

case "$timeofday" in
		yes) echo "Good morning";;
		no) echo "Good Afternoon";;
		y ) echo "Good morning";;
		n ) echo "Good afternoon";;
		* ) echo "Sorry,answer not recognized";;
esac

exit 0

