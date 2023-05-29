# tareaRA2

para compilar los codigos Host.cpp y Server.cpp se requiere ingresar en la terminal el comando "make"
una vez compilados los codigos se pueden eliminar los ejecutables con el comando "make clean"

para ejecutar los programas compilados se debe ingresar en el caso del Server el comando " ./Server 8080 " 
y en el caso del Host se ingresa el comando " ./Host 127.0.0.1 8080 " 
donde "127.0.0.1" es la IP entrante que leera el Host
y 8080 es el puerto que permite la conexion entre los sockets del server y los clientes (Host) entrantes.
tanto la IP como el PUERTO son dinamicos.



