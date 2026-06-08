#ifndef OBJETORENTABLE_H
#define OBJETORENTABLE_H

#include <string>

using namespace std;

// Clase abstracta, cualquier cosa que pueda rentar el sistema
class ObjetoRentable {

protected:

    int id;
    string nombre;
    string descripcion;
    double precioHora;
    double precioDia;
    bool disponible;

public:

    // Constructor
    ObjetoRentable()
        : id(0),
          nombre(""),
          descripcion(""),
          precioHora(0.0),
          precioDia(0.0),
          disponible(true) {}

    // Destructor virtual, para poder borrar cualquier clase
    virtual ~ObjetoRentable() = default;


    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getDescripcion() const { return descripcion; }
    double getPrecioHora() const { return precioHora; }
    double getPrecioDia() const { return precioDia; }
    bool getDisponible() const { return disponible; }


    void setId(int id) { this->id = id; }
    void setNombre(const string& nombre) { this->nombre = nombre; }
    void setDescripcion(const string& descripcion) { this->descripcion = descripcion; }
    void setPrecioHora(double precioHora) { this->precioHora = precioHora; }
    void setPrecioDia(double precioDia) { this->precioDia = precioDia; }
    void setDisponible(bool disponible) { this->disponible = disponible; }

    //informacion comun en todas las clase, para ahorrar codigo
    string informacionBase() {

        return "ID: " + to_string(id) +
               "\nNombre: " + nombre +
               "\nDescripcion: " + descripcion +
               "\nPrecio por hora: $" + to_string(precioHora) +
               "\nPrecio por dia: $" + to_string(precioDia) +
               "\nDisponible: " + (disponible ? string("Si") : string("No"));
    }

    // Metodo Virtual para mostrar la distinta informacion en cada objeto
    virtual string mostrarInformacion() = 0;
};


// CLase vehiculo heradada de ObjetoRentable
class Vehiculo : public ObjetoRentable {

protected:

    int capacidadPersonas;

public:

    // Constructor
    Vehiculo()
        : ObjetoRentable(),
          capacidadPersonas(0) {}


    int getCapacidadPersonas() {
        return capacidadPersonas;
    }


    void setCapacidadPersonas(int capacidadPersonas) {
        this->capacidadPersonas = capacidadPersonas;
    }

    // Override
    string mostrarInformacion() override {

        return informacionBase() +
               "\nCapacidad: " +
               to_string(capacidadPersonas);
    }
};

//Clase VehiculoEspecial heradado de Vehiculo
class VehiculoEspecial : public Vehiculo {

private:

    double depositoRequerido;

public:

    // Constructor
    VehiculoEspecial()
        : Vehiculo(),
          depositoRequerido(0.0) {}


    double getDepositoRequerido() {
        return depositoRequerido;
    }


    void setDepositoRequerido(double depositoRequerido) {
        this->depositoRequerido = depositoRequerido;
    }

    // Override
    string mostrarInformacion() override {

        return Vehiculo::mostrarInformacion() +
               "\nDeposito requerido: $" +
               to_string(depositoRequerido);
    }
};
//Clase accesorio heredada de ObjetoRetable
class Accesorio : public ObjetoRentable {

private:

    int cantidad;

public:

    // Constructor
    Accesorio()
        : ObjetoRentable(),
          cantidad(0) {}

    int getCantidad() {
        return cantidad;
    }


    void setCantidad(int cantidad) {
        this->cantidad = cantidad;
    }

    // Override para mostrar las distintas informacion de los objetos
    string mostrarInformacion() override {

        return informacionBase() +
               "\nCantidad disponible: " +
               to_string(cantidad);
    }
};

#endif
