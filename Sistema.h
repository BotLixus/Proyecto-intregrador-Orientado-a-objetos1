#ifndef SISTEMA_H
#define SISTEMA_H

// Cliente.h incluye tambien ObjetoRentable.h
#include "Cliente.h"

#include <iostream>
#include <string>
#include <vector>

// algorithm se usa para remove, que ayuda a eliminar apuntadores de los vectores, no lo comprendi muy bien hace falta practica
#include <algorithm>

// limits se usa con numeric_limits para limpiar correctamente el buffer de entrada, no lo comprendi muy bien hace falta practica
#include <limits>



using namespace std;

class Sistema {
private:
    // COMPETENCIA: MODIFICADORES DE ACCESO.
    // private porque todo es manejado por el sistema

    // COMPETENCIA: POLIMORFISMO.
    // Este vector guarda apuntadores de tipo ObjetoRentable*, pero dentro puede haber objetos de clases hijas
    vector<ObjetoRentable*> inventarioGeneral;

    // Vector especifico para vehiculos normales.
    vector<Vehiculo*> vehiculos;

    // Vector especifico para vehiculos especiales.
    vector<VehiculoEspecial*> vehiculosEspeciales;

    // Vector especifico para accesorios.
    vector<Accesorio*> accesorios;

    // Vector de clientes (Solo existen clientes cuando estan rentando)
    vector<Cliente*> clientesActivos;

    // Busca cualquier producto por ID dentro del inventario general. Solo Sistema necesita usarlo para validar operaciones.
    ObjetoRentable* buscarProductoInterno(string id) const {
        for (ObjetoRentable* producto : inventarioGeneral) {
            if (producto->getId() == id) {
                return producto;
            }
        }
        return nullptr;
    }

    // Busca un cliente por su ID, si no lo encuentra, regresa nullptr.
    Cliente* buscarClienteInterno(string idCliente) const {
        for (Cliente* cliente : clientesActivos) {
            if (cliente->getIdCliente() == idCliente) {
                return cliente;
            }
        }
        return nullptr;
    }

    // Busca un vehiculo normal o especial por ID. El parametro especial se pasa por referencia para avisar si el vehiculo encontrado pertenece a la clase VehiculoEspecial.
    Vehiculo* buscarVehiculoInterno(string id, VehiculoEspecial*& especial) const {
        especial = nullptr;

        for (Vehiculo* vehiculo : vehiculos) {
            if (vehiculo->getId() == id) {
                return vehiculo;
            }
        }

        for (VehiculoEspecial* vehiculoEspecial : vehiculosEspeciales) {
            if (vehiculoEspecial->getId() == id) {
                especial = vehiculoEspecial;
                return vehiculoEspecial;
            }
        }

        return nullptr;
    }

    // Busca un accesorio por ID dentro del vector de accesorios.
    Accesorio* buscarAccesorioInterno(string id) const {
        for (Accesorio* accesorio : accesorios) {
            if (accesorio->getId() == id) {
                return accesorio;
            }
        }
        return nullptr;
    }

public:
    // Destructor del sistema.
    ~Sistema() {
        for (Cliente* cliente : clientesActivos) {
            delete cliente;
        }

        for (ObjetoRentable* producto : inventarioGeneral) {
            delete producto;
        }
    }

    // Agrega un vehiculo normal al sistema.
    void agregarVehiculo(string id, string nombre, string descripcion, double precioHora, double precioDia, int capacidadPersonas) {
        if (buscarProductoInterno(id) != nullptr) {
            cout << "Ya existe un producto con ese ID." << endl;
            return;
        }

        Vehiculo* nuevo = new Vehiculo(id, nombre, descripcion, precioHora, precioDia, capacidadPersonas);

        inventarioGeneral.push_back(nuevo);
        vehiculos.push_back(nuevo);

        cout << "Vehiculo agregado correctamente." << endl;
    }

    // Agrega un vehiculo especial al sistema.
    void agregarVehiculoEspecial(string id, string nombre, string descripcion, double precioHora, double precioDia, int capacidadPersonas, double depositoRequerido) {
        if (buscarProductoInterno(id) != nullptr) {
            cout << "Ya existe un producto con ese ID." << endl;
            return;
        }

        VehiculoEspecial* nuevo = new VehiculoEspecial(id, nombre, descripcion, precioHora, precioDia, capacidadPersonas, depositoRequerido
        );

        inventarioGeneral.push_back(nuevo);
        vehiculosEspeciales.push_back(nuevo);

        cout << "Vehiculo especial agregado correctamente." << endl;
    }

    // Agrega un accesorio al sistema.
    void agregarAccesorio(string id, string nombre, string descripcion, double precioHora, double precioDia, int cantidad) {
        if (buscarProductoInterno(id) != nullptr) {
            cout << "Ya existe un producto con ese ID." << endl;
            return;
        }

        Accesorio* nuevo = new Accesorio(id, nombre, descripcion, precioHora, precioDia, cantidad);
        inventarioGeneral.push_back(nuevo);
        accesorios.push_back(nuevo);

        cout << "Accesorio agregado correctamente." << endl;
    }

    // Elimina un producto del sistema usando su ID. ynamic_cast para saber si el producto es Vehiculo, VehiculoEspecial o Accesorio.
    void eliminarProducto(string id) {
        ObjetoRentable* producto = buscarProductoInterno(id);

        if (producto == nullptr) {
            cout << "No se encontro el producto." << endl;
            return;
        }

        // COMPETENCIA: POLIMORFISMO.
        // producto es ObjetoRentable*, pero dynamic_cast resiva si apunta a un Vehiculo. Esto sirve porque el inventario general guarda distintos tipos de objetos.
        if (Vehiculo* vehiculo = dynamic_cast<Vehiculo*>(producto)) {
            if (!vehiculo->getDisponible()) {
                cout << "No se puede eliminar un vehiculo rentado." << endl;
                return;
            }

            vehiculos.erase(remove(vehiculos.begin(), vehiculos.end(), vehiculo), vehiculos.end());
        }

        // Si el producto es VehiculoEspecial, tambien se elimina del vector de especiales.
        if (VehiculoEspecial* especial = dynamic_cast<VehiculoEspecial*>(producto)) {
            vehiculosEspeciales.erase(remove(vehiculosEspeciales.begin(),
            vehiculosEspeciales.end(), especial), vehiculosEspeciales.end());
        }

        // Si el producto es Accesorio, se elimina del vector de accesorios.
        if (Accesorio* accesorio = dynamic_cast<Accesorio*>(producto)) {
            accesorios.erase(remove(accesorios.begin(),
            accesorios.end(), accesorio), accesorios.end());
        }

        // Tambien se elimina del inventario general.
        inventarioGeneral.erase(remove(inventarioGeneral.begin(), inventarioGeneral.end(), producto), inventarioGeneral.end());

        delete producto;

        cout << "Producto eliminado correctamente." << endl;
    }

    // Cambia si un vehiculo esta disponible o no.
    void actualizarDisponibilidadVehiculo(string id, bool disponible) {
        VehiculoEspecial* especial = nullptr;
        Vehiculo* vehiculo = buscarVehiculoInterno(id, especial);

        if (vehiculo == nullptr) {
            cout << "No se encontro el vehiculo." << endl;
            return;
        }

        vehiculo->setDisponible(disponible);

        cout << "Disponibilidad actualizada." << endl;
    }

    // Cambia la cantidad disponible de un accesorio.
    void actualizarCantidadAccesorio(string id, int nuevaCantidad) {
        Accesorio* accesorio = buscarAccesorioInterno(id);

        if (accesorio == nullptr) {
            cout << "No se encontro el accesorio." << endl;
            return;
        }

        accesorio->setCantidad(nuevaCantidad);

        cout << "Cantidad actualizada." << endl;
    }

    // COMPETENCIA: SOBRECARGA DE METODOS.
    // Este buscarProducto recibe solo un string y busca por ID.
    ObjetoRentable* buscarProducto(string id) const {
        ObjetoRentable* producto = buscarProductoInterno(id);

        if (producto == nullptr) {
            cout << "No se encontro un producto con ese ID." << endl;
            return nullptr;
        }

        cout << "\nProducto encontrado por ID:" << endl;

        // COMPETENCIA: POLIMORFISMO.
        // Aunque producto es ObjetoRentable*, se ejecuta el mostrarInformacion() correcto segun si el objeto real es Vehiculo, VehiculoEspecial o Accesorio.
        cout << producto->mostrarInformacion() << endl;

        return producto;
    }

    // COMPETENCIA: SOBRECARGA DE METODOS.
    // Este buscarProducto recibe string y bool, por eso es una version diferente. Si buscarPorNombre es true, busca coincidencias por nombre.
    vector<ObjetoRentable*> buscarProducto(string nombre, bool buscarPorNombre) const {
        vector<ObjetoRentable*> resultados;

        if (!buscarPorNombre) {
            ObjetoRentable* producto = buscarProducto(nombre);

            if (producto != nullptr) {
                resultados.push_back(producto);
            }

            return resultados;
        }

        for (ObjetoRentable* producto : inventarioGeneral) {
            if (producto->getNombre().find(nombre) != string::npos) {
                resultados.push_back(producto);
            }
        }

        if (resultados.empty()) {
            cout << "No se encontraron productos con ese nombre." << endl;
        } else {
            cout << "\nProductos encontrados por nombre:" << endl;

            for (ObjetoRentable* producto : resultados) {
                cout << producto->mostrarInformacion() << endl << endl;
            }
        }

        return resultados;
    }

    // Busca y muestra la informacion de un cliente
    Cliente* buscarClientePorID(string idCliente) const {
        Cliente* cliente = buscarClienteInterno(idCliente);

        if (cliente == nullptr) {
            cout << "No se encontro un cliente activo con ese ID." << endl;
            return nullptr;
        }

        cout << "\nCliente encontrado:" << endl;
        cout << cliente->mostrarInformacion() << endl;

        return cliente;
    }

    // Muestra todos los productos registrados
    void mostrarInventarioGeneral() const {
        cout << "\nINVENTARIO GENERAL" << endl;

        if (inventarioGeneral.empty()) {
            cout << "No hay productos registrados." << endl;
            return;
        }

        for (ObjetoRentable* producto : inventarioGeneral) {
            cout << producto->mostrarInformacion() << endl << endl;
        }
    }

    // Muestra solo vehiculos normales.
    void mostrarVehiculos() const {
        cout << "\nVEHICULOS" << endl;

        if (vehiculos.empty()) {
            cout << "No hay vehiculos registrados." << endl;
            return;
        }

        for (Vehiculo* vehiculo : vehiculos) {
            cout << vehiculo->mostrarInformacion() << endl << endl;
        }
    }

    // Muestra solo vehiculos especiales.
    void mostrarVehiculosEspeciales() const {
        cout << "\nVEHICULOS ESPECIALES" << endl;

        if (vehiculosEspeciales.empty()) {
            cout << "No hay vehiculos especiales registrados." << endl;
            return;
        }

        for (VehiculoEspecial* vehiculo : vehiculosEspeciales) {
            cout << vehiculo->mostrarInformacion() << endl << endl;
        }
    }

    // Muestra solo accesorios.
    void mostrarAccesorios() const {
        cout << "\nACCESORIOS" << endl;

        if (accesorios.empty()) {
            cout << "No hay accesorios registrados." << endl;
            return;
        }

        for (Accesorio* accesorio : accesorios) {
            cout << accesorio->mostrarInformacion() << endl << endl;
        }
    }

    // Muestra los clientes
    void mostrarClientes() const {
        cout << "\nCLIENTES ACTIVOS" << endl;

        if (clientesActivos.empty()) {
            cout << "No hay clientes activos." << endl;
            return;
        }

        for (Cliente* cliente : clientesActivos) {
            cout << cliente->mostrarInformacion() << endl << endl;
        }
    }

    // Metodo principal para realizar una renta. Pide datos del vehiculo, cliente, licencias, tiempo de renta y accesorios.
    void rentar() {
        string idVehiculo, idCliente, nombreCliente, telefono;
        bool tieneLicencia, tieneLicenciaEspecial;
        int diasRenta, horasRenta;
        double depositoEntregado = 0;

        cout << "ID del vehiculo a rentar: ";
        cin >> idVehiculo;

        VehiculoEspecial* vehiculoEspecial = nullptr;
        Vehiculo* vehiculo = buscarVehiculoInterno(idVehiculo, vehiculoEspecial);

        if (vehiculo == nullptr) {
            cout << "No se encontro el vehiculo." << endl;
            return;
        }

        if (!vehiculo->getDisponible()) {
            cout << "El vehiculo no esta disponible." << endl;
            return;
        }

        cout << "ID del cliente: ";
        cin >> idCliente;

        if (buscarClienteInterno(idCliente) != nullptr) {
            cout << "Ese cliente ya tiene una renta activa." << endl;
            return;
        }

        // Limpia el salto de linea que queda despues de usar cin, para que getline pueda leer correctamente el nombre completo. No lo comprendi bien pero me ayudo a terminar el codigo
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nombre completo del cliente: ";
        getline(cin, nombreCliente);

        cout << "Telefono: ";
        getline(cin, telefono);

        cout << "Tiene licencia normal? 1 = Si, 0 = No: ";
        cin >> tieneLicencia;

        if (!tieneLicencia) {
            cout << "No se puede rentar sin licencia normal." << endl;
            return;
        }

        cout << "Tiene licencia especial? 1 = Si, 0 = No:, si es Vehiculo Especial y no requiere marcar si";
        cin >> tieneLicenciaEspecial;

        // Si el vehiculo encontrado era especial, se pide licencia especial y deposito.
        if (vehiculoEspecial != nullptr) {
            if (!tieneLicenciaEspecial) {
                cout << "Este vehiculo requiere licencia especial." << endl;
                return;
            }

            cout << "Deposito requerido: $" << vehiculoEspecial->getDepositoRequerido() << endl;
            cout << "Deposito entregado: ";
            cin >> depositoEntregado;

            if (depositoEntregado < vehiculoEspecial->getDepositoRequerido()) {
                cout << "Deposito insuficiente." << endl;
                return;
            }
        }

        cout << "Dias de renta: ";
        cin >> diasRenta;

        cout << "Horas de renta: ";
        cin >> horasRenta;

        if (diasRenta < 0 || horasRenta < 0 || (diasRenta == 0 && horasRenta == 0)) {
            cout << "Tiempo de renta invalido." << endl;
            return;
        }

        // Se crea el cliente porque ya se validaron los datos principales de la renta.
        Cliente* cliente = new Cliente(idCliente, nombreCliente, telefono, tieneLicencia, tieneLicenciaEspecial, diasRenta, horasRenta, depositoEntregado);

        // Se relaciona el cliente con el vehiculo rentado
        cliente->asignarVehiculo(vehiculo);

        char respuesta;
        cout << "Desea agregar accesorios? s/n: ";
        cin >> respuesta;

        // Permite agregar varios accesorios a la misma renta.
        while (respuesta == 's' || respuesta == 'S') {
            string idAccesorio;
            int cantidad;

            cout << "ID del accesorio: ";
            cin >> idAccesorio;

            cout << "Cantidad: ";
            cin >> cantidad;

            Accesorio* accesorio = buscarAccesorioInterno(idAccesorio);

            if (accesorio == nullptr) {
                cout << "No se encontro el accesorio." << endl;
            } else if (cantidad <= 0) {
                cout << "Cantidad invalida." << endl;
            } else if (cantidad > accesorio->getCantidad()) {
                cout << "No hay suficientes unidades disponibles." << endl;
            } else {
                accesorio->setCantidad(accesorio->getCantidad() - cantidad);
                cliente->asignarAccesorio(accesorio, cantidad);
                cout << "Accesorio agregado." << endl;
            }

            cout << "Desea agregar otro accesorio? s/n: ";
            cin >> respuesta;
        }

        // Calcula el total del vehiculo.
        double total = diasRenta * vehiculo->getPrecioDia()
                     + horasRenta * vehiculo->getPrecioHora();

        vector<Accesorio*> accesoriosCliente = cliente->getAccesoriosRentados();
        vector<int> cantidadesCliente = cliente->getCantidadesAccesoriosRentados();

        // Suma al total el costo de los accesorios rentados.
        for (int i = 0; i < accesoriosCliente.size(); i++) {
            total += cantidadesCliente[i] * diasRenta * accesoriosCliente[i]->getPrecioDia();
            total += cantidadesCliente[i] * horasRenta * accesoriosCliente[i]->getPrecioHora();
        }

        cliente->setTotalPagado(total);

        // El vehiculo deja de estar disponible porque ya fue rentado.
        vehiculo->setDisponible(false);

        // El cliente queda registrado como cliente activo.
        clientesActivos.push_back(cliente);

        cout << "Renta realizada correctamente." << endl;
        cout << "Total de renta: $" << total << endl;
    }

    // Registra la devolucion de una renta. Libera el vehiculo, devuelve accesorios al inventario y elimina el cliente activo.
    void devolver() {
        string idCliente;

        cout << "ID del cliente que devuelve: ";
        cin >> idCliente;

        Cliente* cliente = buscarClienteInterno(idCliente);

        if (cliente == nullptr) {
            cout << "No se encontro un cliente activo con ese ID." << endl;
            return;
        }

        Vehiculo* vehiculo = cliente->getVehiculoRentado();

        if (vehiculo != nullptr) {
            vehiculo->setDisponible(true);
        }

        vector<Accesorio*> accesoriosCliente = cliente->getAccesoriosRentados();
        vector<int> cantidadesCliente = cliente->getCantidadesAccesoriosRentados();

        // Regresa al inventario las cantidades de accesorios que el cliente habia rentado.
        for (int i = 0; i < accesoriosCliente.size(); i++) {
            accesoriosCliente[i]->setCantidad(
                accesoriosCliente[i]->getCantidad() + cantidadesCliente[i]
            );
        }

        // Si hubo deposito, pregunta si se devuelve o se retiene.
        if (cliente->getDepositoEntregado() > 0) {
            char respuesta;

            cout << "Se regresa el deposito? s/n: ";
            cin >> respuesta;

            if (respuesta == 's' || respuesta == 'S') {
                cout << "Deposito devuelto: $" << cliente->getDepositoEntregado() << endl;
            } else {
                cout << "Deposito retenido." << endl;
            }
        }

        // Elimina al cliente del vector de clientes activos.
        clientesActivos.erase(remove(clientesActivos.begin(), clientesActivos.end(), cliente),
                              clientesActivos.end());

        delete cliente;

        cout << "Devolucion registrada correctamente." << endl;
    }
};

#endif
