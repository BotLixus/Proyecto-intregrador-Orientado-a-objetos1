#ifndef CLIENTE_H
#define CLIENTE_H

// Se incluye ObjetoRentable.h porque Cliente necesita usar Vehiculo y Accesorio.
#include "ObjetoRentable.h"

// sstream sirve para crear textos largos y regresarlos como string.
#include <sstream>
// Usar vectores
#include <vector>

using namespace std;

class Cliente {
private:
    // COMPETENCIA: MODIFICADORES DE ACCESO. Estos atributos son private porque solo la clase Cliente debe controlarlos directamente.
    string idCliente;           // Clave del cliente
    string nombreCompleto;      // Nombre completo del cliente
    string telefono;            // Telefono del cliente
    bool tieneLicencia;         // Indica si el cliente tiene licencia normal.
    bool tieneLicenciaEspecial; // Indica si el cliente tiene licencia especial (Yates, lanchas,etc)
    int diasRenta;              // Cantidad de dias que durara la renta.
    int horasRenta;             // Cantidad de horas adicionales de renta.
    double depositoEntregado;   // Dinero que entrego como deposito si es necesario
    double totalPagado;         // Total calculado de la renta.

    // Apuntador al vehiculo rentado, guarda la direccion del vehiculo que ya existe en Sistema.
    Vehiculo* vehiculoRentado;

    // Lista de accesorios rentados por el cliente, se guardan apuntadores porque los accesorios originales estan en el inventario del Sistema.
    vector<Accesorio*> accesoriosRentados;

    // Lista paralela a accesoriosRentados, een la misma posicion se guarda cuantas unidades de ese accesorio rento el cliente.
    vector<int> cantidadesAccesoriosRentados;

public:
    // Constructor por default
    Cliente()
        : idCliente(""), nombreCompleto(""), telefono(""), tieneLicencia(false), tieneLicenciaEspecial(false), diasRenta(0), horasRenta(0), depositoEntregado(0), totalPagado(0), vehiculoRentado(nullptr) {}

    // Constructor con parametros. Se usa cuando el sistema registra una renta.
    Cliente(string idCliente, string nombreCompleto, string telefono, bool tieneLicencia, bool tieneLicenciaEspecial, int diasRenta, int horasRenta, double depositoEntregado)
        : idCliente(idCliente), nombreCompleto(nombreCompleto), telefono(telefono), tieneLicencia(tieneLicencia), tieneLicenciaEspecial(tieneLicenciaEspecial), diasRenta(diasRenta), horasRenta(horasRenta),
          depositoEntregado(depositoEntregado), totalPagado(0), vehiculoRentado(nullptr) {}

    // Getters
    string getIdCliente() const { return idCliente; }
    double getDepositoEntregado() const { return depositoEntregado; }
    Vehiculo* getVehiculoRentado() const { return vehiculoRentado; }

    // Estos getters regresan las listas de accesorios y cantidades para poder devolverlos al inventario.
    vector<Accesorio*> getAccesoriosRentados() const { return accesoriosRentados; }
    vector<int> getCantidadesAccesoriosRentados() const { return cantidadesAccesoriosRentados; }

    // Guarda el total final que el cliente pago por la renta.
    void setTotalPagado(double totalPagado) {
        this->totalPagado = totalPagado;
    }

    // Asigna el vehiculo que el cliente esta rentando.
    void asignarVehiculo(Vehiculo* vehiculo) {
        vehiculoRentado = vehiculo;
    }

    // Agrega un accesorio a la renta y su cantidad.
    void asignarAccesorio(Accesorio* accesorio, int cantidad) {
        accesoriosRentados.push_back(accesorio);
        cantidadesAccesoriosRentados.push_back(cantidad);
    }

    // Misma funcion que en objetorentable es para mostrar toda la info del objeto
    string mostrarInformacion() const {
        stringstream ss;

        ss << "ID cliente:" << idCliente
           << "\nNombre completo: " << nombreCompleto
           << "\nTelefono: " << telefono
           << "\nLicencia normal:" << (tieneLicencia ? "Si" : "No")
           << "\nLicencia especial: " << (tieneLicenciaEspecial ? "Si" : "No")
           << "\nDias de renta: " << diasRenta
           << "\nHoras de renta: " << horasRenta
           << "\nDeposito entregado: $" << depositoEntregado
           << "\nTotal pagado: " << totalPagado;

        // Muestra el vehiculo asociado a este cliente.
        ss << "\nVehiculo rentado: " << vehiculoRentado->getNombre()
           << " (ID: " << vehiculoRentado->getId() << ")";

        // Muestra los accesorios rentados. Si no hay accesorios, muestra "Ninguno".
        ss << "\nAccesorios rentados:";
        if (accesoriosRentados.empty()) {
            ss << " Ninguno";
        }
        else {
            for (int i = 0; i < accesoriosRentados.size(); i++) {
                ss << "\n - " << cantidadesAccesoriosRentados[i]
                   << " x " << accesoriosRentados[i]->getNombre()
                   << " (ID: " << accesoriosRentados[i]->getId() << ")";
            }
        }

        return ss.str();
    }
};

#endif
