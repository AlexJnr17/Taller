#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_ORDERS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int quantity;
    float price;
} Product;

typedef struct {
    char productName[NAME_LEN];
    int quantityOrdered;
} Order;

Product products[MAX_PRODUCTS];
Order orders[MAX_ORDERS];
int productCount = 0;
int orderCount = 0;

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("\nNo se pueden agregar mas productos.\n");
        return;
    }
    printf("\n--- Agregar Producto ---\n");
    printf("Nombre del producto: ");
    scanf("%s", products[productCount].name);
    printf("Cantidad disponible: ");
    scanf("%d", &products[productCount].quantity);
    printf("Precio por unidad: ");
    scanf("%f", &products[productCount].price);
    productCount++;
    printf("Producto agregado con exito.\n");
}

void editProduct() {
    char productName[NAME_LEN];
    printf("\n--- Editar Producto ---\n");
    printf("Nombre del producto a editar: ");
    scanf("%s", productName);

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, productName) == 0) {
            printf("Nuevo nombre: ");
            scanf("%s", products[i].name);
            printf("Nueva cantidad disponible: ");
            scanf("%d", &products[i].quantity);
            printf("Nuevo precio: ");
            scanf("%f", &products[i].price);
            printf("Producto editado con exito.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void deleteProduct() {
    char productName[NAME_LEN];
    printf("\n--- Eliminar Producto ---\n");
    printf("Nombre del producto a eliminar: ");
    scanf("%s", productName);

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, productName) == 0) {
            for (int j = i; j < productCount - 1; j++) {
                products[j] = products[j + 1];
            }
            productCount--;
            printf("Producto eliminado con exito.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void listProducts() {
    printf("\n--- Lista de Productos ---\n");
    for (int i = 0; i < productCount; i++) {
        printf("%d. %s - Cantidad: %d - Precio: %.2f\n", i + 1, products[i].name, products[i].quantity, products[i].price);
    }
}

void addOrder() {
    if (orderCount >= MAX_ORDERS) {
        printf("\nNo se pueden agregar mas ordenes.\n");
        return;
    }

    char productName[NAME_LEN];
    int quantity;

    printf("\n--- Crear Orden ---\n");
    printf("Nombre del producto: ");
    scanf("%s", productName);
    printf("Cantidad a ordenar: ");
    scanf("%d", &quantity);

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, productName) == 0) {
            if (products[i].quantity >= quantity) {
                products[i].quantity -= quantity;
                strcpy(orders[orderCount].productName, productName);
                orders[orderCount].quantityOrdered = quantity;
                orderCount++;
                printf("Orden creada con exito.\n");
                return;
            } else {
                printf("Cantidad insuficiente en el inventario.\n");
                return;
            }
        }
    }
    printf("Producto no encontrado.\n");
}

void listOrders() {
    printf("\n--- Lista de Ordenes ---\n");
    for (int i = 0; i < orderCount; i++) {
        printf("%d. Producto: %s - Cantidad: %d\n", i + 1, orders[i].productName, orders[i].quantityOrdered);
    }
}

void deleteOrder() {
    char productName[NAME_LEN];
    printf("\n--- Eliminar Orden ---\n");
    printf("Nombre del producto en la orden: ");
    scanf("%s", productName);

    for (int i = 0; i < orderCount; i++) {
        if (strcmp(orders[i].productName, productName) == 0) {
            for (int j = i; j < orderCount - 1; j++) {
                orders[j] = orders[j + 1];
            }
            orderCount--;
            printf("Orden eliminada con exito.\n");
            return;
        }
    }
    printf("Orden no encontrada.\n");
}

void saveToFile() {
    FILE *file = fopen("productos.txt", "w");
    if (!file) {
        printf("Error al guardar los productos.\n");
        return;
    }
    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%s %d %.2f\n", products[i].name, products[i].quantity, products[i].price);
    }
    fclose(file);
    printf("Productos guardados con exito.\n");
}

void menu() {
    int choice;
    do {
        printf("\n--- Menu ---\n");
        printf("1. Agregar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Listar productos\n");
        printf("5. Crear orden\n");
        printf("6. Listar ordenes\n");
        printf("7. Eliminar orden\n");
        printf("8. Guardar y salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                editProduct();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                listProducts();
                break;
            case 5:
                addOrder();
                break;
            case 6:
                listOrders();
                break;
            case 7:
                deleteOrder();
                break;
            case 8:
                saveToFile();
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (choice != 8);
}

int main() {
    menu();
    return 0;
}
