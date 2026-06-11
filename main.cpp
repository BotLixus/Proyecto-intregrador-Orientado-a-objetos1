// Sistema.h contiene la clase Sistema, que controla inventario, rentas, devoluciones, busquedas y clientes activos.
#include "Sistema.h"
#include <iostream>

// limits permite limpiar la entrada cuando el usuario escribe algo invalido.
#include <limits>
#include <string>

using namespace std;

// Limpia errores de cin.Se usa cuando el usuario escribe algo que no corresponde, por ejemplo texto cuando el programa esperaba un numero. No lo entendi completamente pero me ayudo, lo tome de internet
void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Esta funcion solo es para la demo, es para que inicie con datos y hacer menos pesado probar el programa
void cargarDatosIniciales(Sistema& sistema) {

    // Se agregan vehiculos normales.
    sistema.agregarVehiculo("V001", "Toyota Corolla", "Auto compacto automatico", 120, 850, 5);
    sistema.agregarVehiculo("V002", "Nissan Versa", "Auto economico", 95, 650, 5);

    // Se agregan vehiculos especiales.
    sistema.agregarVehiculoEspecial("E001", "Razer RZR", "Vehiculo todo terreno para aventura", 300, 2200, 2, 3500);
    sistema.agregarVehiculoEspecial("E002", "Yate", "Yate recreativo para paseo en agua", 800, 6500, 10, 10000);

    // Se agregan accesorios.
    sistema.agregarAccesorio("AC001", "Silla para bebe", "Asiento infantil", 20, 120, 4);
    sistema.agregarAccesorio("AC002", "GPS", "Navegador satelital", 15, 90, 6);
    sistema.agregarAccesorio("AC003", "Chalecos salvavidas", "Equipo de seguridad para agua", 25, 150, 20);
}

void mostrarMenu() {
    cout << "\nSISTEMA DE RENTA" << endl;
    cout << "1. Mostrar inventario general" << endl;
    cout << "2. Mostrar vehiculos" << endl;
    cout << "3. Mostra vehiculos especiales" << endl;
    cout << "4. Mostrar accesorios" << endl;
    cout << "5. Buscar producto" << endl;
    cout << "6. Rentar" << endl;
    cout << "7. Devolver" << endl;
    cout << "8. Mostrar clients activos" << endl;
    cout << "9. Eliminar producto" << endl;
    cout << "0. Salir" << endl;
}


int main() {
    // Se carga el sistema
    Sistema sistema;

    // Se cargna los datos iniciales para probrar el programa
    cargarDatosIniciales(sistema);

    int opcion;

    // do while para siempre mostrar el menu hasta que quiera salir el usuario
    do {
        mostrarMenu();
        cin >> opcion;

        // Por si el usuario pone algo mal sigue en el menu
        if (cin.fail()) {
            limpiarEntrada();
            cout << "Opcion invalida." << endl;
            continue;
        }

        // swith
        switch (opcion) {
            case 1:
                sistema.mostrarInventarioGeneral();
                break;

            case 2:
                sistema.mostrarVehiculos();
                break;

            case 3:
                sistema.mostrarVehiculosEspeciales();
                break;

            case 4:
                sistema.mostrarAccesorios();
                break;

            case 5: {
                int tipoBusqueda;
                string texto;

                cout << "Buscar por:" << endl;
                cout << "1. ID" << endl;
                cout << "2. Nombre" << endl;
                cout << "Opcion: ";
                cin >> tipoBusqueda;

                limpiarEntrada();

                cout << "Texto a buscar: ";
                getline(cin, texto);

                // COMPETENCIA: SOBRECARGA DE METODOS.
                // Si busca por ID, se llama buscarProducto(string).
                // Si busca por nombre, se llama buscarProducto(string, bool).
                if (tipoBusqueda == 1) {
                    sistema.buscarProducto(texto);
                } else if (tipoBusqueda == 2) {
                    sistema.buscarProducto(texto, true);
                } else {
                    cout << "Opcion invalida." << endl;
                }

                break;
            }

            case 6:
                // Inicia el proceso de renta
                sistema.rentar();
                break;

            case 7:
                // Inicia el proceso de devolucion.
                sistema.devolver();
                break;

            case 8:
                // Muestra los clientes con renta activa.
                sistema.mostrarClientes();
                break;

            case 9: {
                string id;

                cout << "ID del producto a eliminar: ";
                cin >> id;

                sistema.eliminarProducto(id);
                break;
            }

            case 0:
                cout << "Saliendo del sistema." << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
                break;
        }

    } while (opcion != 0);

    return 0;
}
