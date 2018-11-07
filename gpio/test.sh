#!/bin/bash

PIN=$1
FOLDER="/sys/class/gpio/gpio${PIN}"

if [ $# -ne 1 ]; then
	echo "pin number?"
	exit 1
fi

if [ ! -d ${FOLDER} ]; then
	echo "exporting gpio${PIN}"
	echo ${PIN} > /sys/class/gpio/export
	echo out > /sys/class/gpio/gpio${PIN}/direction
fi

value=0
get_gpio_value()
{
	value=`cat /sys/class/gpio/gpio${1}/value`
}

while read key
do
	#read "Press any key to switch gpio, 'enter' to exit." -s -n 1 key
	if [ "${key}" = "" ]; then
		echo "exit."
		break
	else
		get_gpio_value $PIN
		value=`expr 1 - $value`
		echo ${value} > /sys/class/gpio/gpio${PIN}/value
		get_gpio_value $PIN
		echo "switch to ${value}"
	fi
done

exit 0
