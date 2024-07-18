#!/bin/bash

tab_counter=`head -n 1 $1 | sed "s/ /%space/g" | sed "s/,/ /g"`
tab_counter_arr=($tab_counter)

for (( i=1; i <= ${#tab_counter_arr[*]}; i++ ))
do
    column=$i
    arg_transport="\$$column"
    get_column=`awk -F "\"*,\"*" "{print $arg_transport}" $1 | sed "s/ /%space/g"`

    arr_transport=($get_column)

    post_sql="INSERT INTO \"`echo ${arr_transport[0]} | sed "s/%space/ /g"`\" VALUES ("
    for (( j=1; j < ${#arr_transport[*]}; j++ ))
    do
        return_spaces=`echo ${arr_transport[$j]} | sed "s/%space/ /g"`
        if [[ $return_spaces =~ ^[0-9]+$ ]]; then
            prep="$return_spaces, "
        else
            prep="'$return_spaces', "
        fi
        post_sql="$post_sql$prep"
    done
    post_sql=`echo "${post_sql::-2}"`
    insert_braket=")"
    post_sql="$post_sql$insert_braket"
    echo $post_sql >> result.sql
done
