#!/bin/bash

case "$1" in

 "post" )
    postdata=""
    if [ -z $3 ]; then
        postdata=$(</dev/stdin)
    else
        if test -f "$3"; then
            postdata=`cat $3`
        else 
            postdata=$3
        fi
    fi
    curl -X POST -d "api_dev_key=$2" -d "api_paste_code=$postdata" -d 'api_option=paste' "https://pastebin.com/api/api_post.php"
 ;;

 "read" )
    if [ -z $3 ]; then
        curl -s "https://pastebin.com/$2" | grep -o -P '(?<=<div class=\"de1\">).*(?=</div></li></ol>)' 
    else
        curl -s "https://pastebin.com/$2" | grep -o -P '(?<=<div class=\"de1\">).*(?=</div></li></ol>)' >> $3
    fi
 ;;

esac
