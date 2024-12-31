#include "function.h"
#include <stdio.h>
#include <string.h>

// Giao dien man hinh chinh
void lobbyMenu(int choice){
    printf("\t\t MENU Category Management\n");
    printf("\t\t==================\n");
    printf("\t\t[1]. Category Management\n");
    printf("\t\t[2]. Client\n");
    printf("\t\t[3]. Exit\n");
    printf("\t\t==================\n");
    printf("\t\tNhap lua chon: ");
}

// Giao dien quan ly san pham cua Admin
void danhmucMenu(int choiceCategory){
    printf("================================================\n");
    printf("[1]. View Category Information\n"); // Hien cac san pham dang co trong cua hang
    printf("[2]. Add Category\n"); // Them san pham
    printf("[3].Add Category\n"); // Sua san pham
    printf("[4]. Delete Category\n"); // Xoa san pham 
    printf("[5]. Search Category\n"); // Sap xep san pham
    printf("[6]. Exit\n"); // Thoat
    printf("================================================\n");
    printf("Please enter your choice: ");
}

// Hien thi danh muc
void viewCategory(){
    FILE *ptr = fopen("Category.dat", "rb");
    if (ptr == NULL){
        printf("File Open Error.\n");
        return;
    }
    Category view;
    // In bang thong bao san pham 
    printf("*=======|===========================|=============*\n");
    printf("|  ID   |      Category Name        |   Quantity  |\n");
    printf("|=======|===========================|=============|\n");
    while (fread(&view, sizeof(Category), 1, ptr) != NULL){
        printf("|%6d | %-25s | %11d |\n",
            view.id,
            view.nameCategory,
            view.quantity);
        printf("|-------|---------------------------|-------------|\n");    
    }
    printf("*=======|===========================|=============*\n");
    // Dong tep
    fclose(ptr);
}

// Them danh muc
void addCategory(){
    FILE *ptr = fopen("Category.dat", "ab+");
    if (ptr == NULL){
        printf("File Open Error.\n");
        return;
    }
    Category add[50];
    int n;
    printf("Enter the quantity of categories you want to add:\n");
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++){
        printf("*Enter category information*\n");
        // ID danh muc
        printf("ID: ");
        scanf("%d", &add[i].id);
        getchar();
        // Ten danh muc
        printf("Category Name: ");
        fgets(add[i].nameCategory, sizeof(add[i].nameCategory), stdin);
        add[i].nameCategory[strcspn(add[i].nameCategory, "\n")] = '\0';
        fflush(stdin);
        // So luong danh muc
        printf("Number of Categories: ");
        scanf("%d", &add[i].quantity);
        getchar();
    }
    fwrite(add, sizeof(Category), n, ptr);
    printf("\nThe products have been successfully added.\n");
    // Dong tep
    fclose(ptr);
}

// Sua danh muc
void editCategory() {
    int addEdit;
    Category edit;
    FILE *ptr = fopen("Category.dat", "rb+");
    
    if (ptr == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    // Xac dinh tong so sdanh muc trong tep
    fseek(ptr, 0, SEEK_END);
    int totalProducts = ftell(ptr) / sizeof(Category);
    fseek(ptr, 0, SEEK_SET);

    // Kiem tra xem quan tri vien muon sua danh muc nao
    printf("Which category do you want to edit? Please enter the ID: ");
    scanf("%d", &addEdit);
    while (addEdit < 1 || addEdit > totalProducts) {
        printf("There is no ID %d you want to edit): ", totalProducts);
        scanf("%d", &addEdit);
    }

    // In ra chi tiet danh muc truoc khi sua
    printf("\nCategory Details:\n");
    fseek(ptr, (addEdit - 1) * sizeof(Category), SEEK_SET);
    fread(&edit, sizeof(Category), 1, ptr);
    printf("*=======|===========================|=============*\n");
    printf("|  ID   |       Category Name       |   Quantity  |\n");
    printf("|=======|===========================|=============|\n");
    printf("|%6d | %-25s | %11d |\n",
        edit.id,
        edit.nameCategory,
        edit.quantity);
    printf("|-------|---------------------------|-------------|\n");
    printf("*=======|===========================|=============*\n");

    // Sua san pham
    printf("\n*Product modification in progress*\n");
    getchar();
    printf("New Category Name: ");
    fgets(edit.nameCategory, sizeof(edit.nameCategory), stdin);
    edit.nameCategory[strcspn(edit.nameCategory, "\n")] = '\0';
    fflush(stdin);

    printf("Number of Categories: ");
    scanf("%d", &edit.quantity);
    getchar();

    // Luu danh mucda chinh sua vao tep
    fseek(ptr, (addEdit - 1) * sizeof(Category), SEEK_SET);
    fwrite(&edit, sizeof(Category), 1, ptr);

    // Dong tep
    fclose(ptr);
}

// Xoa danh muc
void deleteCategory() {
    int delID, found = 0;
    Category temp;
    FILE *ptr = fopen("Category.dat", "rb+");
    FILE *tempPtr = fopen("temp.dat", "wb");

    if (ptr == NULL || tempPtr == NULL) {
        printf("Cannot open file.\n");
        return;
    }

    printf("Which category do you want to delete? Please enter the ID: ");
    scanf("%d", &delID);

    // Sao chep tat ca danh muc ngoai tru danh muc can xoa vao tep tam thoi
    while (fread(&temp, sizeof(Category), 1, ptr) != NULL) {
        if (temp.id != delID) {
            fwrite(&temp, sizeof(Category), 1, tempPtr);
        } else {
            found = 1; // Danh dau rang da tim thay danh muc can xoa
        }
    }

    fclose(ptr);
    fclose(tempPtr);

    // Xoa tep goc va doi ten tep tam thoi thanh tep goc
    if (found) {
        remove("Category.dat");
        rename("temp.dat", "Category.dat");
        printf("The category has been successfully deleted.\n");
    } else {
        // Neu khong tim thay danh muc can xoa
        remove("temp.dat");
        printf("Category with the ID not found: %d.\n", delID);
    }
}

