Sistema de Renta Turística para Playa y Dunas
Descripción del proyecto

Este proyecto consiste en un sistema desarrollado en C++ para administrar un negocio de renta turística ubicado en una zona de playa y dunas.

El sistema permite controlar la disponibilidad de vehículos y accesorios, registrar clientes y calcular el costo de las rentas realizadas. Su objetivo principal es ayudar al trabajador a mantener organizado el inventario y evitar errores durante el proceso de renta.

Funcionalidades

El sistema permite:

Registrar vehículos normales.
Registrar vehículos especiales.
Registrar accesorios.
Consultar el inventario disponible.
Buscar objetos por ID o por nombre.
Registrar clientes.
Procesar rentas.
Calcular el costo total de una renta.
Aplicar depósitos de seguridad a vehículos especiales.
Identificación de clases y relación con el problema

Para modelar el negocio se identificaron las siguientes clases:

ObjetoRentable

Clase abstracta que representa cualquier elemento que puede ser rentado. Contiene información común como ID, nombre, descripción, precios y disponibilidad.

Vehiculo

Hereda de ObjetoRentable y representa los vehículos turísticos estándar disponibles para renta.

VehiculoEspecial

Hereda de Vehiculo y agrega un depósito requerido para actividades de mayor riesgo, como recorridos en dunas.

Accesorio

Hereda de ObjetoRentable y representa elementos complementarios como cascos o equipo de seguridad.

Cliente

Almacena la información de las personas que realizan rentas y los productos asociados a ellas.

Sistema

Administra el inventario, los clientes, las búsquedas y el proceso completo de renta.

Relación del diagrama UML con el problema

El diagrama UML representa la estructura del negocio de renta turística. La clase ObjetoRentable funciona como base para todos los elementos que pueden rentarse, mientras que Vehiculo, VehiculoEspecial y Accesorio representan los distintos productos disponibles para los clientes.

La clase Cliente mantiene la relación con los objetos rentados y la clase Sistema coordina todo el funcionamiento del programa. Gracias a estas relaciones, el UML refleja de forma clara cómo se administran vehículos, accesorios, clientes y pagos dentro del negocio.

Conceptos de Programación Orientada a Objetos Implementados
Herencia
Vehiculo hereda de ObjetoRentable.
Accesorio hereda de ObjetoRentable.
VehiculoEspecial hereda de Vehiculo.
Clase Abstracta

La clase ObjetoRentable es abstracta debido al método virtual puro:

virtual string mostrarInformacion() = 0;
Polimorfismo

Se utiliza mediante:

vector<ObjetoRentable*> inventario;

permitiendo almacenar distintos tipos de objetos rentables en una misma colección.

Sobrescritura

Cada clase derivada implementa su propia versión de:

mostrarInformacion()
Sobrecarga

La clase Sistema implementa dos métodos de búsqueda:

buscarObjeto(int id);
buscarObjeto(string nombre);
Encapsulamiento

Los atributos se encuentran protegidos mediante modificadores de acceso y se manipulan mediante getters y setters.

Casos que pueden afectar el funcionamiento del sistema
IDs duplicados

El sistema asume que cada objeto posee un identificador único. Si existen IDs repetidos, las búsquedas pueden devolver resultados incorrectos.

Registro incorrecto de vehículos especiales

Los vehículos especiales deben agregarse utilizando:

agregarVehiculoEspecial(...)

Si se agregan mediante:

agregarAlInventario(...)

el depósito requerido no será considerado durante la renta.

Datos de renta inválidos

Actualmente no se valida que los días u horas de renta sean positivos. Ingresar valores negativos puede generar cálculos incorrectos en el costo total.

COMO CORRER EL PROGRAMA+

 cd "RUTA DE LA CARPETA CON LOS ARCHIVOS"
g++ -std=c++17 main.cpp -o sistema.exe 
./sistema.exe


<img width="1048" height="1774" alt="image" src="https://github.com/user-attachments/assets/d235546a-9aaf-4198-8fc1-41f9eb4e01af" />

