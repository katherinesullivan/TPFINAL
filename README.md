Este README contiene breve información sobre el uso del programa.

Para compilarlo, usar el comando:
make all

Este ejecutará los comandos "make interprete" y "make clean" a la vez.
Puede ejecutarlos por separado.

Ya puede ejecutar el interprete mediante ./main, y le dará espacio a comenzar a escribir, apareciendo el texto "nuevo comando" al principio y luego de cada vez que se procese un orden (salvo salir que cerrará el interprete).

Los comandos aceptados por el interprete son:


Para definir un conjunto:

Por extensión: un nombre para el alias, seguido de un espacio, seguido de un =, seguido de un espacio, seguido de una llave que abre, seguida por n ints separados entre ellos por una coma solamente, seguidos de una llave que cierra. O sea:
                        alias = {x1,x2,x3}

Por comprensión: un nombre para el alias, seguido de un espacio, seguido de un =, seguido de un espacio, seguido de una llave que abre, seguida de una x, seguida por :, seguida por un espacio, seguido por un int, seguido por un espacio, seguido por una x, seguida por un espacio, seguida por otro int, seguido por una llave que cierra. O sea:
                        alias = {x: int1 <= x <= int2}

Vacío: un nombre para el alias, seguido de un espacio, seguido de un =, seguido de un espacio, seguido de una llave que abre, seguida de una llave que cierra. O sea:
                        alias = {}

Haciendo el complemento de otro conjunto: un nombre para el alias, seguido de un espacio, seguido de un =, seguido de un espacio, seguido de un ~, seguido por el alias del conjunto al cual le queremos hacer el complemento
                        alias = ~alias1

Haciendo una operación entre dos conjuntos: un nombre para el alias, seguido de un espacio, seguido de un =, seguido de un espacio, seguido por el alias del primer conjunto con el que operar, seguido por un espacio, seguido por el operador, seguido por un espacio, seguido por el alias del segundo conjunto con el que operar. Los operadores permitidos son | para la unión, & para la intersección y - para la resta
                        alias = alias1 | alias2
                        alias = alias1 & alias2
                        alias = alias1 - alias2


Para imprimir un conjunto: la palabra imprimir, seguida por un espacio, seguida por el alias del conjunto a imprimir
                        imprimir alias


Para cerrar el interprete: la palabra salir
                        salir


No respetar estos formatos resultará en un error.
