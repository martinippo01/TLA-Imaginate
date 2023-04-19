# TLA-Imaginate

## Docker

Primero es necesario hacer un pull de ubuntu

```
docker pull ubuntu:latest
```

Luego se debe compilar el `Dockerfile` para tener un docker con todas las dependencias (parados en el root del directorio)

```
docker build -t imaginate .
```

Por ultimo hay que correr el contenedor compartiendo el directorio donde se tienen los archivos a compilar y ejecutar

```
docker run -v /path:/src --name imaginateN imaginate /bin/bash
```

Este comando va a abrir una sesion en el contenedor donde se va poder encontrar los archivos en /path de la computadora
en la carpeta /src en el docker.


## Ejecución

Para compilar un programa, primero cree un archivo vacío denominado `program` (o el nombre que desee), con el siguiente contenido:

```
123123 + 123 - 2 * (454 + 890 / 89)
```

Luego, ejecute el compilador desde el directorio raíz del proyecto, o desde cualquier otro lugar indicando el path hacia el script `start.sh` y pasando por parámetro el path hacia el programa a compilar:

```bash
user@machine:path/ $ script/start.sh program
```

Debería obtener el resultado correcto de evaluar el programa anterior: `122318`.

## Testing

En Linux:

```bash
user@machine:path/ $ script/test.sh
```


Si desea agregar nuevos casos de uso, deberá crear un archivo por cada uno, que contenga el programa a testear dentro de las carpetas `test/accept` o `test/reject` según corresponda (es decir, si el mismo debe ser aceptado o rechazado por el compilador).
