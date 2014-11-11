#!/bin/sh
mnt="/mnt"
kill_all() {
    PIDS=`fuser -m $1`
    if [ ! -z "$PIDS"  ];then
        for line in $PIDS
        do
            if [ "$line" -eq "1"  ]; then
                break
            fi
            kill -9 $line 
        done
    fi

}
foreachd(){
        for file in $mnt/*
        do
            if [ -d $file ]
            then
		kill_all $file 1>/dev/null 2>&1 
            fi
        done
}
foreachd $mnt

