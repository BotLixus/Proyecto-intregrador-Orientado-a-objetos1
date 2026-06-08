#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <vector>
#include "ObjetoRentable.h"

using namespace std;

class Cliente {
private:
    int idCliente;
    string nombre;
    string telefono;
    bool tieneLicencia;
    bool tieneLicenciaEspecial;
    int horasRenta;
    int diasRenta;
    double depositoEntregado;
    double totalPagar;

    // Relaciones usando punteros IMPORTANTE ESTUDIAR
    ObjetoRentable* productoRentado;
    vector<ObjetoRentable*> accesoriosRentados;

public:
    // Constructor con parametros para agilizar la creacion de clientes a a la hora de rentar
    Cliente(int id, string nom, string tel, bool lic, bool licEsp, int dias, int horas)
        : idCliente(id), nombre(nom), telefono(tel), tieneLicencia(lic),
          tieneLicenciaEspecial(licEsp), diasRenta(dias), horasRenta(horas),
          productoRentado(nullptr), depositoEntregado(0.0), totalPagar(0.0) {}

    // Destructor
    ~Cliente() = default;


    int getIdCliente() const { return idCliente; }
    string getNombre() const { return nombre; }
    string getTelefono() const { return telefono; }
    bool getTieneLicencia() const { return tieneLicencia; }
    bool getTieneLicenciaEspecial() const { return tieneLicenciaEspecial; }
    int getHorasRenta() const { return horasRenta; }
    int getDiasRenta() const { return diasRenta; }
    double getDepositoEntregado() const { return depositoEntregado; }
    double getTotalPagar() const { return totalPagar; }


    void setIdCliente(int id) { idCliente = id; }
    void setNombre(const string& nom) { nombre = nom; }
    void setTelefono(const string& tel) { telefono = tel; }
    void setTieneLicencia(bool lic) { tieneLicencia = lic; }
    void setTieneLicenciaEspecial(bool licEsp) { tieneLicenciaEspecial = licEsp; }
    void setHorasRenta(int horas) { horasRenta = horas; }
    void setDiasRenta(int dias) { diasRenta = dias; }
    void setDepositoEntregado(double dep) { depositoEntregado = dep; }
    void setTotalPagar(double total) { totalPagar = total; }



    // Metodos

    // Asigna el vehiculo que se va a rentar NO SE ACABO DE IMPLEMENTAR
    void asignarProducto(ObjetoRentable* prod) {
        productoRentado = prod;
    }

    // Añade un accesorio al vector de accesorios, NO SE ACABO DE IMPLEMENTAR
    void agregarAccesorio(ObjetoRentable* acc) {
        accesoriosRentados.push_back(acc);
    }

    
};

#endif