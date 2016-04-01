#!/bin/bash

VAR=abc-123-xyz

case "$VAR" in
  abc) echo "abc";;
  *123*) echo "123 found";;
  abc-123-xyz) echo "complete";;  
  xyz) echo "xyz";;
esac
