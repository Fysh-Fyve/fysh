#!/bin/sh

files="md/*.md tex/*.tex uml/*.uml"

for f in $files; do
    aspell list < $f | sort | uniq -c
done

echo "I see ENGL 199 has failed you 😔. Please correct misspelled words..."

for f in $files; do
    aspell check $f
done
