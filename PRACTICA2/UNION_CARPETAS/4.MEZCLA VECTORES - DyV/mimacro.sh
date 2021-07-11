#!/bin/bash

let i=0
let j=2
let k=2

while [ $i -le 21 ];do
  echo $i
  ./ejecutable2O3 $j $k >> tiemposO3.dat
  let i=$i+1
  let j=$j+$j
  let k=$k+1
done

