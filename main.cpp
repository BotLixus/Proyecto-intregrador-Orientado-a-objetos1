#include <iostream>
#include "Sistema.h"

using namespace std;

int main() {

    Sistema sistema;

    // VEHICULO NORMAL
    Vehiculo* auto1 = new Vehiculo();

    auto1->setId(1);
    auto1->setNombre("Toyota Corolla");
    auto1->setDescripcion("Sedan familiar");
    auto1->setPrecioHora(100);
    auto1->setPrecioDia(800);
    auto1->setCapacidadPersonas(5);

    sistema.agregarAlInventario(auto1);


    // VEHICULO ESPECIAL

    VehiculoEspecial* cuatrimoto = new VehiculoEspecial();

    cuatrimoto->setId(2);
    cuatrimoto->setNombre("Cuatrimoto ATV");
    cuatrimoto->setDescripcion("Vehiculo para terreno dificil");
    cuatrimoto->setPrecioHora(150);
    cuatrimoto->setPrecioDia(1200);
    cuatrimoto->setCapacidadPersonas(2);
    cuatrimoto->setDepositoRequerido(5000);

    sistema.agregarVehiculoEspecial(cuatrimoto);

    // ACCESORIO

    Accesorio* casco = new Accesorio();

    casco->setId(3);
    casco->setNombre("Casco Profesional");
    casco->setDescripcion("Casco de seguridad");
    casco->setPrecioHora(10);
    casco->setPrecioDia(50);
    casco->setCantidad(20);

    sistema.agregarAlInventario(casco);


    // MOSTRAR INVENTARIO
    // POLIMORFISMO

    cout << "\n INVENTARIO \n\n";

    sistema.mostrarInventario();


    // SOBRECARGA DE BUSQUEDA

    cout << "\n BUSQUEDA POR ID \n";

    ObjetoRentable* encontrado1 =
        sistema.buscarObjeto(2);

    if (encontrado1 != nullptr) {

        cout << encontrado1->mostrarInformacion()
             << endl;
    }

    cout << "\n BUSQUEDA POR NOMBRE \n";

    ObjetoRentable* encontrado2 =
        sistema.buscarObjeto("Casco Profesional");

    if (encontrado2 != nullptr) {

        cout << encontrado2->mostrarInformacion()
             << endl;
    }

    // RENTA NORMAL
    cout << "\n RENTA DE VEHICULO NORMAL \n";

    sistema.realizarRenta(
        101,
        "David",
        "4421111111",
        true,
        false,
        1,
        2,
        5
    );

    // RENTA CON DEPOSITO

    cout << "\n RENTA DE VEHICULO ESPECIAL \n";

    sistema.realizarRenta(
        102,
        "Carlos",
        "4422222222",
        true,
        true,
        2,
        1,
        3
    );

    // INTENTAR RENTAR OTRA VEZ

    cout << "\n INTENTO DE RENTA DUPLICADA \n";

    sistema.realizarRenta(
        103,
        "Pedro",
        "4423333333",
        true,
        false,
        1,
        1,
        1
    );

    return 0;
}