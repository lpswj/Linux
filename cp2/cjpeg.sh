#!/bin/bash

for image in *.gif
do
		cjpeg $image > ${image%%gif}jpg
done


