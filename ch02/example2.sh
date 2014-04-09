#!/bin/bash

for file in $(ls t*.sh);
do
		lpr $file
done

exit 0
