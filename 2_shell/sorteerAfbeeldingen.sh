#!/usr/bin/env bash
DIRNAME=$1
mkdir -p Afbeeldingen
find $DIRNAME -name '*.jpg' -o -name '*.png' | xargs -I {} mv {} Afbeeldingen/
