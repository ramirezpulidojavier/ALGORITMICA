#!/bin/bash


let i=1
let j=1
while [ $i -le 15 ];do
  echo $i $j $j
  ./BORRAR $j $j >> borrar.dat
  let i=$i+1
  let j=$j+$j
done

