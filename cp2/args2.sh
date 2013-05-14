#!/bin/bash

unset foo
foo=bud
echo ${foo:+bar}
echo $foo

exit 0
