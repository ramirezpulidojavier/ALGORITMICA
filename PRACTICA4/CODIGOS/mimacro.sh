#!/bin/bash
echo "" > salida.dat
let i=10
while [ $i -le 250 ];do
  echo $i
  ./floyd2  $i >> salida_floyd2.dat
  let i=$i+10
done
