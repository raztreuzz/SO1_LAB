#!/bin/bash

if [ ! -d "$1" ]; then
    echo "Error: La ruta no es un directorio válido."
    exit 1
fi

for dir in $(find "$1" -type d); do
    chmod 740 "$dir"
done

for file in $(find "$1" -type f); do
    chmod 764 "$file"
done

echo "Permisos modificados correctamente."

