# TLA-Imaginate

# Compilar

Primero es necesario hacer un pull de ubuntu

```
docker pull ubuntu:latest
```

Luego se debe compilar el `Dockerfile` para tener un docker con todas las dependencias

```
docker build -t imaginate .
```

Por ultimo hay que correr el contenedor compartiendo el directorio donde se tienen los archivos a compilar y ejecutar

```
docker run -v /path:/src
--name imaginateN imaginate /bin/bash
```

Este comando va a abrir una sesion en el contenedor donde se va poder encontrar los archivos en /path de la computadora
en la carpeta /src en el docker.
