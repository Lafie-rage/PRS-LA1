#!bin/bash

fileName = `date+%Y%M%d`

if [! -d $fileName]; then
  mkdir $fileName
fi

mv exo3/* $fileName

cat $fileName/* > Gros_fichier.$$
ls $fileName/* >  Nom_du_scrip.$$
