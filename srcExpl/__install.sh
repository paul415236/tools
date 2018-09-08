#!/bin/bash

USER=`whoami`

if [ ! -d /home/$USER/.vim/plugin ]; then
	mkdir -p /home/$USER/.vim/plugin
fi
cp -f ./plugin/* /home/$USER/.vim/plugin/

if [ ! -d /home/$USER/.vim/doc ]; then
	mkdir -p /home/$USER/.vim/doc
fi
cp -f ./doc/* /home/$USER/.vim/doc/
