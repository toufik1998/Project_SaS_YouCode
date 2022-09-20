#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>


// Structures Area
struct Medicine{
    int id;
    char name[20];
    int amount;
    float prix;
};

struct Transaction{
    int idProduct;
    char nameProduct[20];
    int amountProductBuying;
    float prixProductBuying;
    char buyTime[50];
};


// Global Variables
int totalPrix = 0;
int totalProducts = 0; // numbers of buying product
int lentghArray = 7;
int lentghArrayTransaction = 0;
//  list of all transactions
struct Transaction transactionArray[100];
// list of medecines
struct Medicine medicineArray[100] = {
        {11, "doliprane", 4, 25.99},
        {34, "parasitamol", 3, 20.99},
        {33, "aspro", 2, 20.99},
        {36, "aspirine", 2, 22.99},
        {45, "nodeep", 6, 65.99},
        {5, "setamix", 7, 75.99},
        {2, "maztech", 3, 35.99},
    };


// Functions
void addProduct(){
    int numbers;
    printf("<><><><> Please enter number of products : ");
    scanf("%d", &numbers);
    for(int i = 0; i < numbers; i++){
        struct Medicine medicine;
        printf("=> Medicine id : ");
        scanf("%d", &medicine.id);
        printf("=> Medicine name : ");
        scanf("%s", &medicine.name);
        printf("=> Medicine amount : ");
        scanf("%d", &medicine.amount);
        printf("=> Medicine prix : ");
        scanf("%f", &medicine.prix);

        printf("\n");

        medicineArray[lentghArray] = medicine;
        ++lentghArray;
    }
}


int searchProduct(){
    int choiceSearchDelete;
    printf("Would you like to search with NAME or ID \n");
    printf("[1] ===>> Search  with Name \n");
    printf("[2] ===>> Search with ID \n");
    scanf("%d", &choiceSearchDelete);
    if(choiceSearchDelete == 1){
    char searchName[20];
    printf("Please enter the name of the medecine : ");
    scanf("%s", searchName);
    for(int i = 0; i < lentghArray; i++){
        if(strcmp(searchName, medicineArray[i].name) == 0){
            printf("\t The name of medecin product %s,\t ID ==>>   %d,\t Amount ==>> %d,\t Prix ==>> %.2f \n", medicineArray[i].name, medicineArray[i].id, medicineArray[i].amount, medicineArray[i].prix);
            return i;
        }
    }

    printf("Sorry! we dont have any medecine with this name \n");
    }else {
        int searchId;
        printf("Please enter ID of the medecine : ");
        scanf("%d", &searchId);
        for(int i = 0; i < lentghArray; i++){
        if(searchId == medicineArray[i].id){
            printf("\t The name of medecin product %s,\t ID ==>>   %d,\t Amount ==>> %d,\t Prix ==>> %.2f \n", medicineArray[i].name, medicineArray[i].id, medicineArray[i].amount, medicineArray[i].prix);
            return i;
        }
    }

    printf("Sorry! we dont have this medecine \n");
    }
    return -1;
}


void showProduct(){
    int sortAlphaPrix;
    struct Medicine help;

    printf("\n");
    printf("Would you like to sort with Alphabetical or Price \n");
    printf("[1] ==>> Sort  with Alphabetical \n");
    printf("[2] ==>> Sort with Prix \n");
    scanf("%d", &sortAlphaPrix);

    if(sortAlphaPrix == 1){
        for(int i = 0; i < lentghArray; i++){
            for(int j = i + 1; j < lentghArray; j++){
                if(strcmp(medicineArray[i].name, medicineArray[j].name) > 0 ){
                    help = medicineArray[i];
                    medicineArray[i] = medicineArray[j];
                    medicineArray[j] = help;
                }
            }
        }
    }else{
        for(int i = 0; i < lentghArray; i++){
            for(int j = i + 1; j < lentghArray; j++){
                if(medicineArray[i].prix < medicineArray[j].prix){
                    help = medicineArray[i];
                    medicineArray[i] = medicineArray[j];
                    medicineArray[j] = help;
                }
            }
        }
    }

    printf("\t ----------\t----------\t----------\t----------\n");
    printf("\t|   name   |\t|    id    |\t|  amount  |\t|   prix   |\n");
    printf("\t ----------\t----------\t----------\t----------\n");

    for(int i = 0; i < lentghArray; i++){
        printf("\t%s           \t%d           \t%d         \t%.2f\n", medicineArray[i].name, medicineArray[i].id, medicineArray[i].amount, medicineArray[i].prix);
    }

    printf("\n");
}
void deleteProduct(){
    int i , index = searchProduct();
    if(index != -1){
        for(i = index; i < lentghArray; i++){
            medicineArray[i] = medicineArray[i + 1];
        }

        --lentghArray;
    }
}


void buyProduct(){
    bool isExist = false;
    int printAmount, index;
    char nameOfProduct[20];
    showProduct();
    printf("Please enter the Name of the product : ");
    scanf("%s", &nameOfProduct);

    for(int i = 0; i < lentghArray; i++){
        if(strcmp(nameOfProduct, medicineArray[i].name) == 0){
            isExist = true;
            index = i;
            break;
        }
    }

    if(isExist){
        printf("\t The name of medecin product %s,\t ID ==>>   %d,\t Amount ==>> %d,\t Prix ==>> %.2f \n", medicineArray[index].name, medicineArray[index].id, medicineArray[index].amount, medicineArray[index].prix);
        printf("Please enter the amount of this product you want : ");
        scanf("%d", &printAmount);
        if(printAmount > medicineArray[index].amount){
            printf("Sorry!! we have just %d of this product\n", medicineArray[index].amount);
        }else{
            totalPrix += (medicineArray[index].prix * printAmount);
            totalProducts += printAmount;
            medicineArray[index].amount -= printAmount;
            // PUSH BUYING PRODUCT TO LIST FOR ALL TRANSACTIONS
            struct Transaction transaction;
            transaction.idProduct = medicineArray[index].id;
            strcpy(transaction.nameProduct , medicineArray[index].name);
            transaction.amountProductBuying = printAmount;
            transaction.prixProductBuying = (medicineArray[index].prix * printAmount);
            time_t  t = time(NULL);
            strcpy(transaction.buyTime , ctime(&t));
            transactionArray[lentghArrayTransaction] = transaction;
            lentghArrayTransaction++;
        }
    }else{
        printf("Sorry! we dont have this medecine \n");
    }
}

void maxMIn(){
    int i, min, max;
    min = transactionArray[0].prixProductBuying;
    max = transactionArray[0].prixProductBuying;

    for(i = 1; i < lentghArrayTransaction; i++){

            if(min > transactionArray[i].prixProductBuying){
                min = transactionArray[i].prixProductBuying;

            }

            if(max <  transactionArray[i].prixProductBuying){
                max = transactionArray[i].prixProductBuying;
            }
    }

    printf("The min price that we are buying is %d \n ", min);
    printf("The max price that we are buying is %d \n ", max);
}

void statistiqueProduct(){
    int i;
    float moyen = totalProducts != 0 ? ((float)totalPrix / (float)totalProducts) : 0;
    printf("------------ the sum price of all products : %d\n", totalPrix);
    printf("------------ the moyen price of all products : %.2f\n", moyen);


    printf("\t ----------\t----------\t----------\t-----------\t----------\n");
    printf("\t|   name   |   \t|    id    |   \t|  amount  |   \t|   prix   |   \t|   date   |\n");
    printf("\t ----------\t----------\t----------\t-----------\t----------\n");

    for(int i = 0; i < lentghArrayTransaction; i++){
        printf("\t%s            \t%d           \t%d         \t%.2f         \t%s\n", transactionArray[i].nameProduct, transactionArray[i].idProduct, transactionArray[i].amountProductBuying, transactionArray[i].prixProductBuying, transactionArray[i].buyTime);
    }

    maxMIn();

}


void updateProduct(){
    int updateId;
    bool isExist = false;
    int updateAmount, index;

    printf("this list for all products less than 3\n");
    printf("\t ----------\t----------\t----------\t----------\n");
    printf("\t|   name   |\t|    id    |\t|  amount  |\t|   prix   |\n");
    printf("\t ----------\t----------\t----------\t----------\n");

    for(int i = 0; i < lentghArray; i++){
        if(medicineArray[i].amount < 3){
            printf("\t%s           \t%d           \t%d         \t%.2f\n", medicineArray[i].name, medicineArray[i].id, medicineArray[i].amount, medicineArray[i].prix);
        }
    }

    printf("Please enter the ID of product you want to update amount : ");
    scanf("%d", &updateId);

    for(int i = 0; i < lentghArray; i++){
        if(medicineArray[i].id == updateId){
            isExist = true;
            index = i;
            break;
        }
    }

    if(isExist){
        printf("Please enter the amount you want add : ");
        scanf("%d", &updateAmount);
        medicineArray[index].amount += updateAmount;
    }else{
        printf("Sorry! unkown input please enter a correct name \n");
    }
}
void menu(){
    int choice;

    do{
        printf("\t ----------\t----------\t----------\n");
        printf("\t|\t    PHARMACY MANAGEMENT \t |\n");
        printf("\t ----------\t----------\t----------\n");
        printf("\t[1] <><><><><><>\t:\tADD\t\n");
        printf("\t[2] <><><><><><>\t:\tSEARCH\t\n");
        printf("\t[3] <><><><><><>\t:\tDELETE\t\n");
        printf("\t[4] <><><><><><>\t:\tSHOW\t\n");
        printf("\t[5] <><><><><><>\t:\tBUY\t\n");
        printf("\t[6] <><><><><><>\t:\tSTATISTIQUE\t\n");
        printf("\t[7] <><><><><><>\t:\tUPDATE\t\n");
        printf("\t[0] <><><><><><>\t:\tEXIT\t\n");
        printf("\n");
        printf("<><><><> Please enter your choice : \n");
        scanf("%d", &choice);
        system("cls");
        switch(choice){
            case 0: break;
            case 1: addProduct(); break;
            case 2: searchProduct(); break;
            case 3: deleteProduct(); break;
            case 4: showProduct(); break;
            case 5: buyProduct(); break;
            case 6: statistiqueProduct(); break;
            case 7: updateProduct(); break;
            default : printf("<><><><> Please enter a valid Number!!! <><><><>\n");
            printf("\n");
        }
    }while(choice != 0);
}


void main(){
    menu();
}
