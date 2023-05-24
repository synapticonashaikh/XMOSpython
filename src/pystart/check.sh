#!/usr/bin/env bash


line="# upload &&pycode.py%% $"
if [[ "$line" =~ "upload" ]]; then
        filename=$(grep -o -P '(?<=&&).*(?=%%)' <<< "$line")
        value=`cat $filename`  
        echo "$value" 
else
        echo $line # send it to xe file
fi