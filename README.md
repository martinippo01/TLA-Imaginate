# Imaginate

Imaginate es un lenguaje pensado tanto para produccion de imagenes, como para el proceso creativo del diseñador grafico. Mediante el lenguaje, podras crear de forma deterministica, podiendo aplicar operaciones como filtros, efectos, flavours, etc. Si no que tambien permite crear imagenes de forma no deterministica, es decir, poder obtener una imagen producto de un pool de filtros, efectos y demas, donde se aplicaran los dichos de forma aleatoria.

## Docker y Construccion

 Primero es necesario hacer un pull de la siguiente imagen de docker. La cual es cortesia del grupo de Alejo Flores Lucey, al cual agradecemos por compartirnos dicha imagen de docker con todo configurado para poder compilar ambos proyectos.

```
$ docker pull alejofl/tla-compiler
```

Para construir el proyecto por completo, ejecute en la raíz del repositorio los siguientes comandos:

```bash
$ chmod u+x --recursive script
$ docker run -v "${PWD}:/root" -ti --rm alejofl/tla-compiler
$ ./script/build.sh
```

Este comando va a abrir una sesion en el contenedor donde se va podra correr los scripts .sh directamente desde ahi.


## Ejecución

Para compilar un programa, primero cree un archivo vacío denominado `program` (o el nombre que desee), con el siguiente contenido:

```Imaginate
Imaginate
    .addFocus("./Hola")
    .addContrast()
    .renderAll()
```

Luego, ejecute el compilador indicando el path hacia el script `start.sh` y pasando por parámetro el path hacia el programa a compilar:

```bash
root@docker-session:path/ $ ./script/start.sh program
```

Debería obtener el valor de retorno valido (0) para dicho programa. En caso de que se modifque la sintaxis del programa por una incorrecta, el valor de retorno sera diferente de 0.

## Testing

Para poder testear el correcto funcionamiento del compilador interpretando la sintaxis, se proveen en el directorio test casos de aceptacion y rechazo. Para validar esto, la catedra ha provisto el siguiente script ./script/test.sh que tratara de compilar todos los casos de aceptacion y rechazo y mostrara por stdout en cuales se acepto y cuales se rechazo.

```bash
root@docker-session:path/ $ ./script/test.sh
```


Si desea agregar nuevos casos de uso, deberá crear un archivo por cada uno, que contenga el programa a testear dentro de las carpetas `test/accept` o `test/reject` según corresponda (es decir, si el mismo debe ser aceptado o rechazado por el compilador).
