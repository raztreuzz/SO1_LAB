#!/bin/bash

if [ ! -d "$1" ]; then
    echo "Error: La ruta no es un directorio válido."
    exit 1
fi

find "$1" -type d -exec chmod 740 {} \;

find "$1" -type f -exec chmod 764 {} \;

echo "Permisos modificados correctamente."