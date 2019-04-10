#!/usr/bin/env bash
DIRNAME=$1
mkdir -p Afbeeldingen/Vakantie
find Afbeeldingen | grep vakantie | xargs -I {} mv {} Afbeeldingen/Vakantie
