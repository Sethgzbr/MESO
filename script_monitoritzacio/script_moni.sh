#!/bin/bash

hosts=("192.168.53.2" "192.168.53.3" "192.168.53.4" "meso.com" "google.com")

endpoint="a2lg3qizupe1nw-ats.iot.us-east-1.amazonaws.com"

for host in "${hosts[@]}"; do
    echo "Haciendo ping a $host..."
    if ping -c 3 -W 1 "$host" > /dev/null 2>&1; then
        echo "$host está respondiendo"
    else
        echo "$host no responde"
    fi
done

if systemctl is-active --quiet apache2; then
    echo "Apache está corriendo."
else
    echo "Apache no está activo. Intentando iniciarlo..."
    sudo systemctl start apache2
    if systemctl is-active --quiet apache2; then
        echo "Apache se inició correctamente."
    else
        echo "Apache no pudo iniciarse. Revisa los logs."
        exit 1
    fi
fi

if ss -tln | grep -q ':80'; then
    echo "Apache está escuchando en el puerto 80."
else
    echo "Apache no está escuchando en el puerto 80. Revisa la configuración."
    exit 1
fi

if curl -I http://localhost --max-time 5 2>/dev/null | grep -q "200 OK"; then
    echo "Apache está sirviendo contenido correctamente."
else
    echo "Apache no responde correctamente. Revisa los logs."
    exit 1
fi

if systemctl is-active --quiet postgresql; then
    echo "PostgreSQL está corriendo."
else
    echo "PostgreSQL no está activo. Intentando iniciarlo..."
    sudo systemctl start postgresql
    if systemctl is-active --quiet postgresql; then
        echo "PostgreSQL se inició correctamente."
    else
        echo "PostgreSQL no pudo iniciarse. Revisa los logs."
        exit 1
    fi
fi

if ss -tln | grep -q ':5432'; then
    echo "PostgreSQL está escuchando en el puerto 5432."
else
    echo "PostgreSQL no está escuchando en el puerto 5432. Revisa la configuración."
    exit 1
fi

if psql -U postgres -c '\l' > /dev/null 2>&1; then
    echo "PostgreSQL está respondiendo correctamente."
else
    echo "PostgreSQL no responde correctamente. Revisa los logs."
    exit 1
fi

echo "Haciendo ping al enpoint..."
    if ping -c 3 -W 1 "$endpoint" > /dev/null 2>&1; then
        echo "El endpoint está respondiendo"
    else
        echo "El endpoint no responde"
    fi
