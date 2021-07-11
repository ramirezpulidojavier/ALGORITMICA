#!/bin/bash
echo "" > s-mezcla_total.dat
let i=10
let j=10
while [ $i -le 250 ];do
	echo $i $j
  ./mezcla_total $i $j >> s-mezcla_total.dat
  let i=$i+10
  let j=$j+10

done
