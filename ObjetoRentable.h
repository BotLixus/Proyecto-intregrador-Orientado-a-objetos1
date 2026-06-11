#ifndef OBJETORENTABLE_H
#define OBJETORENTABLE_H

// sstream permite construir textos largos usando stringstream, como si fuera cout, pero guardando el resultado en una variable string.
#include <sstream>

#include <string>

using namespace std;

// COMPETENCIA: CLASES ABSTRACTAS.
// Esta clase es abstracta porque tiene un metodo virtual puro:virtual string mostrarInformacion() const = 0;
// Eso significa que no se pueden crear objetos directamente de ObjetoRentable, pero si se puede usar como base para Vehiculo, VehiculoEspecial y Accesorio.
class ObjetoRentable {
protected:

    // COMPETENCIA: MODIFICADORES DE ACCESO.

    string id;             // Clave de cada producto rentable
    string nombre;         // Nombre del vehiculo/accesorio
    string descripcion;    // Descripcion breve del producto.
    double precioHora;     // Precio que cuesta rentarlo por hora.
    double precioDia;      // Precio que cuesta rentarlo por dia.
    bool disponible;       // Indica si el producto esta disponible o no.

public:
    // Constructor default. Inicializa el objeto con valores vacios o en cero.
    ObjetoRentable(): id(""), nombre(""), descripcion(""), precioHora(0), precioDia(0), disponible(true) {}

    // Constructor con parametro crear un objeto ya con sus datos principales.
    ObjetoRentable(string id, string nombre, string descripcion, double precioHora, double precioDia)
        : id(id), nombre(nombre), descripcion(descripcion), precioHora(precioHora), precioDia(precioDia), disponible(true) {}

    // Destructor virtual. Es importante porque el sistema maneja objetos con apuntadores de tipo ObjetoRentable*, pero realmente pueden ser Vehiculo, VehiculoEspecial o Accesorio.
    virtual ~ObjetoRentable() = default;

    // Getters
    string getId() const { return id; }
    string getNombre() const { return nombre; }
    string getDescripcion() const { return descripcion; }
    double getPrecioHora() const { return precioHora; }
    double getPrecioDia() const { return precioDia; }
    bool getDisponible() const { return disponible; }

    // Setters
    void setId(string id) { this->id = id; }
    void setNombre(string nombre) { this->nombre = nombre; }
    void setDescripcion(string descripcion) { this->descripcion = descripcion; }
    void setPrecioHora(double precioHora) { this->precioHora = precioHora; }
    void setPrecioDia(double precioDia) { this->precioDia = precioDia; }
    void setDisponible(bool disponible) { this->disponible = disponible; }

    // Este metodo es para guardar toda la informacion que comparte las clases, para ahorrar codigo a la hora de usar Mostrarinformacion
    string informacionBase() const {
        stringstream ss;

        ss << "ID: " << id
           << "\nNombre: " << nombre
           << "\nDescripcion: " << descripcion
           << "\nPrecio por hora: $" << precioHora
           << "\nPrecio por dia: $" << precioDia
           << "\nDisponible: " << (disponible ? "Si" : "No");

        return ss.str();
    }

    // COMPETENCIA: POLIMORFISMO Y CLASES ABSTRACTAS.
    // Este metodo es virtual puro porque cada clase hija debe mostrar su informacion de manera diferente. Por eso ObjetoRentable funciona como clase base abstracta.
    virtual string mostrarInformacion() const = 0;
};

// COMPETENCIA: HERENCIA. Vehiculo hereda de ObjetoRentable
class Vehiculo : public ObjetoRentable {
protected:
    // protected porque VehiculoEspecial tambien necesita usar este atributo.
    int capacidadPersonas; // Cantidad de personas que caben en el vehiculo.

public:
    // Constructor
    Vehiculo() : ObjetoRentable(), capacidadPersonas(0) {}

    // Constructor con parametros. Primero manda los datos comunes al constructor de ObjetoRentable y luego guarda el dato propio de Vehiculo: capacidadPersonas.
    Vehiculo(string id, string nombre, string descripcion,double precioHora, double precioDia, int capacidadPersonas)
        : ObjetoRentable(id, nombre, descripcion, precioHora, precioDia), capacidadPersonas(capacidadPersonas) {}

    int getCapacidadPersonas() const { return capacidadPersonas; }

    void setCapacidadPersonas(int capacidadPersonas) {
        this->capacidadPersonas = capacidadPersonas;
    }

    // COMPETENCIA: SOBREESCRITURA DE METODOS.
    // Aqui se sobrescribe mostrarInformacion(), que viene de la clase madre, el virtual puro
    string mostrarInformacion() const override {
        stringstream ss;

        ss << informacionBase()
           << "\nTipo: Vehiculo"
           << "\nCapacidad de personas: " << capacidadPersonas;

        return ss.str();
    }
};

// COMPETENCIA: HERENCIA. VehiculoEspecial hereda de Vehiculo
class VehiculoEspecial : public Vehiculo {
private:
    // private porque este dato solo pertenece al vehiculo especial.
    double depositoRequerido; // Cantidad de dinero que se pide como deposito para rentarlo.

public:
    // Constructor
    VehiculoEspecial() : Vehiculo(), depositoRequerido(0) {}

    // Constructor con parametros, usa el constructor de Vehiculo y agrega el deposito requerido como dato especial.
    VehiculoEspecial(string id, string nombre, string descripcion, double precioHora, double precioDia, int capacidadPersonas, double depositoRequerido)
        : Vehiculo(id, nombre, descripcion, precioHora, precioDia, capacidadPersonas), depositoRequerido(depositoRequerido) {}

    double getDepositoRequerido() const { return depositoRequerido; }

    void setDepositoRequerido(double depositoRequerido) {
        this->depositoRequerido = depositoRequerido;
    }

    // COMPETENCIA: SOBREESCRITURA DE METODOS. VehiculoEspecial muestra informacion parecida a Vehiculo, pero agrega el deposito requerido.
    string mostrarInformacion() const override {
        stringstream ss;

        ss << informacionBase()
           << "\nTipo: Vehiculo especial"
           << "\nCapacidad de personas: " << capacidadPersonas
           << "\nDeposito requerido: $" << depositoRequerido;

        return ss.str();
    }
};

// COMPETENCIA: HERENCIA. Accesorio tambien hereda de ObjetoRentable
class Accesorio : public ObjetoRentable {
private:
    // private porque la cantidad solo debe modificarse con sus metodos.
    int cantidad; // Numero de unidades disponibles de ese accesorio.

public:
    // Constructor por default. Un accesorio sin cantidad no puede estar disponible para renta
    Accesorio() : ObjetoRentable(), cantidad(0) {disponible = false;}

    // Constructor con parametros. Si la cantidad es mayor que 0, se marca como disponible.
    Accesorio(string id, string nombre, string descripcion, double precioHora, double precioDia, int cantidad)
        : ObjetoRentable(id, nombre, descripcion, precioHora, precioDia), cantidad(cantidad) {disponible = cantidad > 0;}

    int getCantidad() const { return cantidad; }

    // Al cambiar la cantidad tambien se actualiza disponible, si cantidad es 0, ya no esta disponible.
    void setCantidad(int cantidad) {
        this->cantidad = cantidad;
        disponible = cantidad > 0;
    }

    // COMPETENCIA: SOBREESCRITURA DE METODOS. Accesorio muestra su informacion agregando la cantidad disponible.
    string mostrarInformacion() const override {
        stringstream ss;

        ss << informacionBase()
           << "\nTipo: Accesorio"
           << "\nCantidad disponible: " << cantidad;

        return ss.str();
    }
};

#endif
