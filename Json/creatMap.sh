#!/bin/sh

if [ $# != 1 ]
then
    echo "$0 Map.json"
    return 1
fi

name=$(echo $1 | cut -f 1 -d '.')
nameC=./$name.c
nameH=./$name.h

echo $nameC
touch -f $nameC
echo "#include <nds.h>" > $nameC
echo  >> $nameC

touch -f $nameH
echo "#pragma once" > $nameH
echo  >> $nameH
echo "#include <nds.h>" >> $nameH
echo  >> $nameH

nbLayer=$(cat $1 | jq ".layers | length")

i="0"
while [ $i -lt $nbLayer ]
do
    type=$(cat $1 | jq ".layers[$i].type")
    echo "$type"
    if [ "$type" = "\"tilelayer\"" ]
    then
	h=$(cat $1 | jq ".layers[$i].height")
	w=$(cat $1 | jq ".layers[$i].width")
	size=$(echo "$h*$w" | bc)
	name=$(cat $1 | jq ".layers[$i].name" | tr -d " " | tr -d "\"")
	# echo "ok"
	data=$(cat $1 | jq ".layers[$i].data[]-1" | tr '\n' ',')
	data=${data%?}
	echo "extern u16	$name[$size];" >> $nameH
	echo "u16	$name[$size] = {$data};" >> $nameC
	echo >> $nameC
	echo >> $nameC
    else
	echo "coucou"
    fi
    i=$(($i + 1))
done

