#! /bin/bash
echo "input sth"
read input

SYSTEM='uname -s'
case $SYSTEM in
Linux)
  echo "linux system";;
*)
  echo "ni ta ma zai dou wo"
esac
#case $input in
#    yes|y|Yes|Yes) echo "input yes!";;
#	n* |N* ) echo "input no!";;
#	[a-z]|[A-Z] ) echo "sorry";;
#esac 
exit 0
