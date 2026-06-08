Sistema de Renta Turística para Playa y Dunas
Descripción del proyecto

Este proyecto consiste en un sistema desarrollado en C++ para administrar un negocio de renta turística ubicado en una zona de playa y dunas.

El sistema permite controlar la disponibilidad de vehículos y accesorios, registrar clientes y calcular el costo de las rentas realizadas.

Su objetivo principal es ayudar al trabajador a mantener organizado el inventario y evitar errores durante el proceso de renta.

Funcionalidades

El sistema permite:

Registrar vehículos normales.
Registrar vehículos especiales.
Registrar accesorios.
Consultar el inventario disponible.
Buscar objetos por ID o nombre.
Registrar clientes.
Procesar rentas.
Calcular el costo total de una renta.
Aplicar depósitos de seguridad a vehículos especiales.
Identificación de clases y relación con el problema

Para modelar el negocio se identificaron las siguientes clases:

ObjetoRentable

Clase abstracta que representa cualquier elemento que puede ser rentado dentro del negocio.

Contiene información común como:

ID
Nombre
Descripción
Precio por hora
Precio por día
Disponibilidad
Vehiculo

Hereda de ObjetoRentable.

Representa los vehículos turísticos estándar y agrega la capacidad de pasajeros.

VehiculoEspecial

Hereda de Vehiculo.

Representa vehículos utilizados en actividades más exigentes, como recorridos por dunas. Requiere un depósito de seguridad adicional antes de ser rentado.

Accesorio

Hereda de ObjetoRentable.

Representa elementos complementarios para la experiencia del cliente, como cascos o equipo de seguridad.

Cliente

Almacena la información de las personas que realizan rentas y los productos asociados a ellas.

Sistema

Administra el inventario, los clientes y el proceso completo de renta.

Estas clases representan directamente los elementos necesarios para el funcionamiento de un negocio de renta turística, permitiendo mantener el control de los productos disponibles, los clientes registrados y los pagos realizados.

Conceptos de Programación Orientada a Objetos Implementados
Herencia
Vehiculo hereda de ObjetoRentable.
Accesorio hereda de ObjetoRentable.
VehiculoEspecial hereda de Vehiculo.
Clase Abstracta

La clase ObjetoRentable es abstracta debido al método virtual puro:

virtual string mostrarInformacion() = 0;
Polimorfismo

El inventario utiliza:

vector<ObjetoRentable*> inventario;

permitiendo almacenar distintos tipos de objetos rentables en una misma colección.

Sobrescritura (Override)

Cada clase derivada implementa su propia versión del método:

mostrarInformacion()
Sobrecarga

La clase Sistema implementa dos métodos de búsqueda:

buscarObjeto(int id);
buscarObjeto(string nombre);
Encapsulamiento

Los atributos de las clases se encuentran protegidos mediante modificadores de acceso y son manipulados mediante getters y setters.

Casos que pueden afectar el funcionamiento del sistema
IDs duplicados

El sistema asume que cada objeto tiene un identificador único.

Si existen dos objetos con el mismo ID, las búsquedas pueden devolver resultados incorrectos y provocar operaciones sobre el objeto equivocado.

Registro incorrecto de vehículos especiales

Los vehículos especiales deben agregarse utilizando:

agregarVehiculoEspecial(...)

Si se agregan mediante:

agregarAlInventario(...)

no serán registrados dentro de la colección de vehículos especiales y el depósito correspondiente no será cobrado durante la renta.

Datos de renta inválidos

Actualmente no se valida que los días u horas de renta sean positivos.

Ingresar valores negativos puede producir cálculos incorrectos en el costo total de una renta.
