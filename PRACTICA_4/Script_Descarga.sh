#!/bin/bash

wget -O web.html https://usac.edu.gt/
cp web.html web_editada.html

sed -i 's/<h6/<hX/g' web_editada.html
sed -i 's/<h5/<h6/g' web_editada.html
sed -i 's/<h4/<h5/g' web_editada.html
sed -i 's/<h3/<h4/g' web_editada.html
sed -i 's/<h2/<h3/g' web_editada.html
sed -i 's/<h1/<h2/g' web_editada.html
sed -i 's/<hX/<h6/g' web_editada.html

echo "Count original:"
for i in {1..6}; do
    echo "Nivel $i: $(grep -o "<h$i" web.html | wc -l)"
done

echo "Count modificado:"
for i in {1..6}; do
    echo "Nivel $i: $(grep -o "<h$i" web_editada.html | wc -l)"
done