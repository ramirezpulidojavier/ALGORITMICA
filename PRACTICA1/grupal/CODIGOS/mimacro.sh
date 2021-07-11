#!/bin/bash
echo "" > datos_seleccion_O1.dat
let i=1000
while [ $i -le 30000 ];do
  echo $i
  ./seleccion_O1  $i >> datos_seleccion_O1.dat
  let i=$i+1000
done
