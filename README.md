

# Demo de renta de vehículos y vehículos especiales para dunas y mar
¿De qué trata?

Este proyecto consiste en un sistema desarrollado en C++ para administrar un negocio de renta turística enfocado en vehículos para recorridos en playa, mar y dunas.

El sistema permite registrar vehículos normales, vehículos especiales y accesorios, además de controlar su disponibilidad, procesar rentas, registrar devoluciones y administrar a los clientes que mantienen una renta activa.

Su objetivo principal es facilitar la administración del inventario y reducir errores durante el proceso de renta, permitiendo que el trabajador consulte rápidamente la información disponible y mantenga un mejor control de los recursos del negocio.

Descripción general del código

El proyecto está basado en Programación Orientada a Objetos y utiliza herencia, polimorfismo, encapsulamiento, clases abstractas, sobrescritura y sobrecarga de métodos.

Clases principales
ObjetoRentable

Es una clase abstracta que representa cualquier elemento que puede ser rentado dentro del negocio.

Contiene información común como:

ID
Nombre
Descripción
Precio por hora
Precio por día
Disponibilidad

Además, declara el método virtual puro:

virtual string mostrarInformacion() const = 0;

que debe ser implementado por todas las clases derivadas.

Vehiculo

Hereda de ObjetoRentable.

Representa los vehículos turísticos estándar disponibles para renta y agrega información relacionada con la capacidad de personas.

VehiculoEspecial

Hereda de Vehiculo.

Representa vehículos que requieren medidas adicionales de seguridad para su uso, agregando un depósito obligatorio que debe entregar el cliente antes de completar la renta.

Accesorio

Hereda de ObjetoRentable.

Representa elementos complementarios que pueden rentarse junto con los vehículos, como equipo de seguridad u otros accesorios.

También administra la cantidad disponible de cada accesorio.

Cliente

Almacena la información de las personas que tienen una renta activa.

Cada cliente mantiene:

Información personal.
Vehículo rentado.
Accesorios rentados.
Cantidades de accesorios rentados.
Tiempo de renta.
Depósito entregado.
Total pagado.
Sistema

Es la clase principal del proyecto y coordina toda la lógica del programa.

Administra:

Inventario general.
Vehículos.
Vehículos especiales.
Accesorios.
Clientes activos.

Además, se encarga de:

Registrar productos.
Eliminar productos.
Buscar productos.
Buscar clientes.
Mostrar inventario.
Procesar rentas.
Registrar devoluciones.
Actualizar disponibilidad y cantidades.
main.cpp

Funciona únicamente como punto de entrada del programa y menú de interacción con el usuario.

Toda la lógica principal se encuentra centralizada dentro de la clase Sistema.

Conceptos de Programación Orientada a Objetos utilizados
Herencia
Vehiculo hereda de ObjetoRentable.
Accesorio hereda de ObjetoRentable.
VehiculoEspecial hereda de Vehiculo.
Clase abstracta

ObjetoRentable es una clase abstracta debido al método virtual puro:

virtual string mostrarInformacion() const = 0;
Polimorfismo

Se utiliza mediante:

vector<ObjetoRentable*> inventarioGeneral;

permitiendo almacenar distintos tipos de objetos rentables en una misma colección.

Sobrescritura

Cada clase derivada implementa su propia versión de:

mostrarInformacion()
Sobrecarga

La clase Sistema implementa dos versiones del método:

buscarProducto(string id);
buscarProducto(string nombre, bool buscarPorNombre);
Encapsulamiento

Los atributos se encuentran protegidos mediante modificadores de acceso private y protected, y se manipulan mediante métodos públicos.

Casos que pueden afectar el funcionamiento del sistema
1. Eliminación de un producto asociado a una renta activa

Los clientes almacenan apuntadores a los vehículos y accesorios rentados. Si un producto fuera eliminado mientras sigue asociado a una renta activa, los apuntadores quedarían inválidos y podrían provocar comportamientos inesperados durante consultas o devoluciones.

2. Inconsistencias en la disponibilidad del inventario

El sistema depende de que los vehículos y accesorios actualicen correctamente su disponibilidad y cantidades al momento de realizar una renta o devolución. Además, el encargado del negocio debe mantener un control adecuado de las operaciones realizadas. Si se omiten devoluciones, se registran rentas fuera del sistema o no se lleva un seguimiento adecuado del inventario, podrían generarse inconsistencias que permitan rentar productos que ya se encuentran ocupados o no disponibles.

Por esta razón, se recomienda que el trabajador mantenga un registro complementario de las operaciones realizadas y verifique periódicamente el inventario físico para asegurar que la información almacenada en el sistema coincida con la realidad.



Requisitos

Para compilar el proyecto se recomienda utilizar:

MSYS2
Compilador G++
Instalación de MSYS2

https://www.msys2.org/

Instalación de G++

https://www.msys2.org/docs/environments/

Cómo compilar y ejecutar

Abrir la terminal de MSYS2 y navegar a la carpeta donde se encuentran los archivos del proyecto:

cd "RUTA DE LA CARPETA CON LOS ARCHIVOS"

Compilar:

g++ -std=c++17 main.cpp -o sistema.exe

Ejecutar:

./sistema.exe

Estructura de archivos

El proyecto se encuentra dividido en los siguientes archivos principales:

main.cpp
Punto de entrada del programa. Se encarga de crear el sistema y mostrar el menú de interacción con el usuario.
Sistema.h
Contiene la clase Sistema, responsable de administrar el inventario, los clientes, las rentas y las devoluciones.
Cliente.h
Define la clase Cliente, que almacena la información de los usuarios que mantienen una renta activa.
ObjetoRentable.h
Contiene la clase abstracta ObjetoRentable y las clases derivadas Vehiculo, VehiculoEspecial y Accesorio.
README.md
Documento que describe el funcionamiento general del proyecto.
Relación con el diagrama UML

El proyecto incluye un diagrama UML que representa la estructura general del sistema.

La clase ObjetoRentable funciona como clase base abstracta para todos los elementos que pueden ser rentados. A partir de ella derivan las clases Vehiculo y Accesorio, mientras que VehiculoEspecial hereda de Vehiculo para incorporar el manejo de depósitos de seguridad.

La clase Cliente mantiene la información de las rentas activas, incluyendo el vehículo y los accesorios asociados al cliente.

Finalmente, la clase Sistema centraliza la administración del inventario, los clientes y las operaciones de renta y devolución, actuando como el controlador principal del programa.


<img width="2801" height="1630" alt="image" src="https://github.com/user-attachments/assets/c6a62140-3168-4462-81fe-2de2f8a25ada" />


