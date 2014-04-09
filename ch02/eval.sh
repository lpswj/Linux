#!/bin/bash

foo=10
x=foo
y='$'$x
eval z='$'$x
echo $y
echo $z

exec man ls
