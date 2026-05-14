# Proyecto-intregrador-Orientado-a-objetos1

¿De qué trata el proyecto?
Es un sistema diseñado para gestionar un negocio de renta de vehículos en la playa. El objetivo es que el trabajador tenga una herramienta organizada para controlar tanto los productos como el dinero. El proyecto se divide en tres sistemas principales:
Sistema de Control del Producto (Inventario): Sirve para administrar todas las unidades disponibles (autos, yates, Razers) y los productos extra necesarios, como chalecos salvavidas y gafas para la arena. Aquí se lleva el registro de qué está libre para rentar y qué no.
Sistema de Clientes: Es donde se anotan los datos de las personas y se guarda su documentación (como la licencia o identificación) para que el negocio tenga un respaldo de quién se llevó el vehículo.
Sistema de Cobro y Facturación: Es el que hace la cuenta final. Suma el tiempo que se usó el vehículo, los productos extra que se pidieron y genera la factura si el cliente la necesita.

Estado del Avance y Próximos Pasos:
Lo que se entrega en el diagrama ULM es el esqueleto funcional. Es la estructura de cómo se conectan las clases, pero todavía falta pulir los detalles. En la siguiente etapa voy a organizar mis ideas para añadir:
Atributos Técnicos: Detalles como la potencia, el tipo de tracción (4x4, integral), si es automático o estándar, y si el motor es eléctrico o de combustión.
Encapsulamiento: Implementar los getters y setters para que los sistemas puedan consultar y actualizar los datos de los productos de forma correcta y segura.
Lógica de Precios: Definir cómo cambian los costos dependiendo de si el vehículo es normal o de la categoría especial (como los Razers).
En si falta hacer una lluvia de ideas para añadir mas atributos y metodos a las clases de los autos, ademas de los setters y getters de los sistemas.

Objetivo de este diseño:
Este diagrama sirve como mapa para asegurar que el trabajador no olvide ningún cobro y que siempre sepa dónde están las unidades y los productos extra. Es una base sólida que permite que el negocio crezca y se mantenga ordenado sin importar cuántos clientes lleguen al día.

Identificación de clases y relación con el problema:
En el diagrama identifiqué las clases necesarias para que el negocio funcione: la jerarquía de vehículos (Vehiculo, Terrestre, Acuatico, TerrestreEspecial), los ProductoExtra (chalecos/gafas) y los sistemas de control. La relación es clara: el Sistema de Cobro se conecta con el Inventario y los Clientes para que todo el flujo de renta esté amarrado y no se pierda información.

Casos que harían que el proyecto deje de funcionar:
Fuga de RAM: Si borro vehículos del inventario pero no libero la memoria con delete, el programa va a consumir RAM hasta que la compu se trabe.
Punteros nulos: Si intento cobrar un vehículo que ya se borró de la lista, el programa va a buscar algo que no existe y va a tronar 
