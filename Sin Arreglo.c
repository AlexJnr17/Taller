#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_ORDERS 100
#define NAME_LEN 50

// Arreglos para productos
char productNames[MAX_PRODUCTS][NAME_LEN];
int productQuantities[MAX_PRODUCTS];
float productPrices[MAX_PRODUCTS];
int productCount = 0;

// Arreglos para órdenes
char orderProductNames[MAX_ORDERS][NAME_LEN];
int orderQuantities[MAX_ORDERS];
int orderCount = 0;

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("\nNo se pueden agregar más productos.\n");
        return;
    }
    printf("\n--- Agregar Producto ---\n");
    printf("Nombre del producto: ");
    scanf("%s", productNames[productCount]);
    printf("Cantidad disponible: ");
    scanf("%d", &productQuantities[productCount]);
    printf("Precio por unidad: ");
    scanf("%f", &productPrices[productCount]);
    productCount++;
    printf("Producto agregado con éxito.\n");
}

void editProduct() {
    char productName[NAME_LEN];
    printf("\n--- Editar Producto ---\n");
    printf("Nombre del producto a editar: ");
    scanf("%s", productName);

    for (int i = 0; i < productCount; i++) {
        if (strcmp(productNames[i], productName) == 0) {
            printf("Nuevo nombre: ");
            scanf("%s", productNames[i]);
            printf("Nueva cantidad disponible: ");
            scanf("%d", &productQuantities[i]);
            printf("Nuevo precio: ");
            scanf("%f", &productPrices[i]);
            printf("Producto editado con éxito.\n");
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
        if (strcmp(productNames[i], productName) == 0) {
            for (int j = i; j < productCount - 1; j++) {
                strcpy(productNames[j], productNames[j + 1]);
                productQuantities[j] = productQuantities[j + 1];
                productPrices[j] = productPrices[j + 1];
            }
            productCount--;
            printf("Producto eliminado con éxito.\n");
            return;
        }
    }
    printf("Producto no encontrado.\n");
}

void listProducts() {
    printf("\n--- Lista de Productos ---\n");
    for (int i = 0; i < productCount; i++) {
        printf("%d. %s - Cantidad: %d - Precio: %.2f\n", i + 1, productNames[i], productQuantities[i], productPrices[i]);
    }
}

void addOrder() {
    if (orderCount >= MAX_ORDERS) {
        printf("\nNo se pueden agregar más órdenes.\n");
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
        if (strcmp(productNames[i], productName) == 0) {
            if (productQuantities[i] >= quantity) {
                productQuantities[i] -= quantity;
                strcpy(orderProductNames[orderCount], productName);
                orderQuantities[orderCount] = quantity;
                orderCount++;
                printf("Orden creada con éxito.\n");
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
    printf("\n--- Lista de Órdenes ---\n");
    for (int i = 0; i < orderCount; i++) {
        printf("%d. Producto: %s - Cantidad: %d\n", i + 1, orderProductNames[i], orderQuantities[i]);
    }
}

void deleteOrder() {
    char productName[NAME_LEN];
    printf("\n--- Eliminar Orden ---\n");
    printf("Nombre del producto en la orden: ");
    scanf("%s", productName);

    for (int i = 0; i < orderCount; i++) {
        if (strcmp(orderProductNames[i], productName) == 0) {
            for (int j = i; j < orderCount - 1; j++) {
                strcpy(orderProductNames[j], orderProductNames[j + 1]);
                orderQuantities[j] = orderQuantities[j + 1];
            }
            orderCount--;
            printf("Orden eliminada con éxito.\n");
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
        fprintf(file, "%s %d %.2f\n", productNames[i], productQuantities[i], productPrices[i]);
    }
    fclose(file);
    printf("Productos guardados con éxito.\n");
}

void menu() {
    int choice;
    do {
        printf("\n--- Menú ---\n");
        printf("1. Agregar producto\n");
        printf("2. Editar producto\n");
        printf("3. Eliminar producto\n");
        printf("4. Listar productos\n");
        printf("5. Crear orden\n");
        printf("6. Listar órdenes\n");
        printf("7. Eliminar orden\n");
        printf("8. Guardar y salir\n");
        printf("Seleccione una opción: ");
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
                printf("Opción inválida.\n");
        }
    } while (choice != 8);
}

int main() {
    menu();
    return 0;
}
