#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include <vector>
#include <string>
#include "ObjetoRentable.h"
#include "Cliente.h"

using namespace std;

class Sistema {
private:

    // Inventario general
    vector<ObjetoRentable*> inventario;

    // Clientes registrados
    vector<Cliente*> listaClientes;

    // Solo vehículos especiales
    vector<VehiculoEspecial*> inventarioEspeciales;

public:

    // Destructor
    ~Sistema() {

        for (auto obj : inventario)
            delete obj;

        for (auto cli : listaClientes)
            delete cli;
    }


    // Gestion del inventario

    void agregarAlInventario(ObjetoRentable* obj) {

        inventario.push_back(obj);
    }

    void agregarVehiculoEspecial(VehiculoEspecial* especial) {

        inventario.push_back(especial);
        inventarioEspeciales.push_back(especial);
    }

    void mostrarInventario() {

        for (auto obj : inventario) {

            cout << obj->mostrarInformacion()
                 << "\n-----------------\n";
        }
    }


    // Buscar objetoderenta
    ObjetoRentable* buscarObjeto(int id) {

        for (auto obj : inventario) {

            if (obj->getId() == id)
                return obj;
        }

        return nullptr;
    }

    ObjetoRentable* buscarObjeto(string nombre) {

        for (auto obj : inventario) {

            if (obj->getNombre() == nombre)
                return obj;
        }

        return nullptr;
    }

    VehiculoEspecial* buscarEspecial(int id) {

        for (auto especial : inventarioEspeciales) {

            if (especial->getId() == id)
                return especial;
        }

        return nullptr;
    }

    // Proceso para rentar
    void realizarRenta(int idCli,string nom,string tel,bool lic,bool licEsp,int idObj,int dias,int horas) {

        ObjetoRentable* obj = buscarObjeto(idObj);

        if (obj && obj->getDisponible()) {

            Cliente* nuevoCliente =
                new Cliente(idCli,nom,tel,lic,licEsp,dias,horas);

            nuevoCliente->asignarProducto(obj);

            obj->setDisponible(false);

            // Verificar si requiere depósito
            double deposito = 0.0;

            VehiculoEspecial* especial =
                buscarEspecial(idObj);

            if (especial != nullptr) {

                deposito =
                    especial->getDepositoRequerido();
            }

            // Calcular total
            double total =
                (obj->getPrecioDia() * dias) +
                (obj->getPrecioHora() * horas) +
                deposito;

            nuevoCliente->setDepositoEntregado(
                deposito
            );

            nuevoCliente->setTotalPagar(
                total
            );

            listaClientes.push_back(
                nuevoCliente
            );

            cout << "Renta procesada exitosamente para "
                 << nom
                 << ". Total cobrado: $"
                 << total
                 << endl;
        }
        else {

            cout << "Error: El vehiculo con ID "
                 << idObj
                 << " no existe o ya esta ocupado."
                 << endl;
        }
    }
};

#endif