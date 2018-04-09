#!/bin/sh

# This script will make it easier to
# mount a remote folder for dev.
#
# Nicholas Siviglia
# ns533@njit.edu
# 01/04/2018

REMOTE_HOST="pi@192.168.1.8"

REMOTE_DIR="/home/pi/pi-door-alarm";

# Note that the local dir has to exist before mounting!
LOCAL_DIR="$HOME/Local/remote-pi-door-alarm";

if [ $(findmnt -lo source | grep -c $REMOTE_HOST:$REMOTE_DIR) -eq 0 ];
    then
        echo '\033[0;31m' Mounting '\033[0m' $REMOTE_HOST:$REMOTE_DIR to $LOCAL_DIR
        sshfs $REMOTE_HOST:$REMOTE_DIR $LOCAL_DIR -o reconnect
    else
        echo '\033[0;31m' Unmounting '\033[0m' $REMOTE_HOST:$REMOTE_DIR from $LOCAL_DIR
        fusermount -u $LOCAL_DIR
fi

