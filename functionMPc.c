#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100 //maximum users

/*------------------------------------------------*/ //Declarations

typedef char string10[11]; //for password
typedef char string15[16]; //for category
typedef char string20[21]; //for user name / item name
typedef char string30[31]; //for the address / item description

struct userTag 
{
    int             userID;
    long long int   contactNumber;
    string10        password;
    string30        address;
    string20        userName;
};

struct itemsTag
{
    int      productID,
             availQuantity,
             sellerID; //also corresponds to seller's user ID
    float    unitPrice;
    string20 itemName;
    string15 category;
    string30 itemDescription;
};

struct dateTag
{
    int month,
        day,
        year;
};

struct transactionsTag
{
    struct dateTag  date;
    struct itemsTag itemTransaction[5];
    int             buyerUserID,
                    SellerUserID;
    float           totalAmount;
	string20        userName;
    string20        buyerName;
};

struct cartTag
{
  struct itemsTag ItemsCart[10];
  int             countItems;
};

/*------------------------------------------------*/ //Initialization Function

/* 
initializedNull function initializes userID to 0
@param aUsers[] - contains all the users
@return - returns nothing (void)
*/
void
initializedNull (struct userTag aUsers[MAX])
{
    int i;
    for(i = 0; i < MAX; i++)
        aUsers[i].userID = '\0'; //basically initializing it to 0 lol
}

/* 
initializedNull1 function initializes sellerID to 0
@param - contains all aItems
@return - returns nothing (void)
*/
void
initializedNull1 (struct itemsTag aItems[MAX][20])
{
    int i, j;
    for(i = 0; i < MAX; i++)
    {
        for(j = 0; j < 20; j++)
        {
            aItems[i][j].sellerID = '\0';
        }
    }
}

/* 
initializedItemsZero function initializes items information to 0 and NULL
@param aItems - contains items information
@return - returns nothing (void)
*/
void
initializedItemsZero (struct itemsTag aItems)
{
    strcpy(aItems.itemName, "");
    strcpy(aItems.category, "");
    strcpy(aItems.itemDescription, "");
    aItems.availQuantity = '\0';
    aItems.unitPrice = '\0';
    aItems.sellerID = '\0';
    aItems.productID = '\0';
}

/* 
InitializedNullCart function initializes userCart sellerID to 0
@param userCart[] - contains the userCart information
@return - returns nothing (void)
*/
void
initializedNullCart (struct cartTag userCart[])
{
    int i, j;
    for(i = 0; i < MAX; i++)
        for(j = 0; j < 10; j++)
            userCart[i].ItemsCart[j].sellerID = '\0';
}

/*------------------------------------------------*/ //Function

/* 
swap function swaps the contents of two structs
@param *p1 - the address where the first struct is stored
@param *p2 - the address where the second struct is stored
@return - returns nothing (void)
*/
void 
swap(struct itemsTag *p1, struct itemsTag *p2) 
{
  struct itemsTag temp;
  temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}

void 
swapUser(struct userTag *p1, struct userTag *p2) 
{
  struct userTag temp;
  temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}

/* 
swap function swaps the contents of two structs
@param *p1 - the address where the first struct is stored
@param *p2 - the address where the second struct is stored
@return - returns nothing (void)
*/
void 
swapTrans(struct transactionsTag *p1, struct transactionsTag *p2) 
{
  struct transactionsTag temp;
  temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}

/* 
deleteContents function deletes the content/values stored in a variable
@param userCart[] - struct array where the items found in user's cart are stored
@param current - the current user
@param numID - variable to be checked
@param choice - action to be done (delete all, delete specific productID, delete same seller)
@return - returns nothing (void)
*/
void
deleteContents(struct cartTag userCart[], int current, int numID, int choice)
{
    int j, k;
    int nFound = 0;
    switch (choice)
    {
        case 1:
                //delete all same seller
                for(j = 0; j < 10; j++)
                {
                    if(userCart[current].ItemsCart[j].sellerID == numID)
                    {
                        userCart[current].countItems--; //debugging
                        
                        userCart[current].ItemsCart[j].sellerID = '\0';
                        userCart[current].ItemsCart[j].productID = '\0';
                        userCart[current].ItemsCart[j].availQuantity = '\0';
                        userCart[current].ItemsCart[j].unitPrice = '\0';
                        strcpy(userCart[current].ItemsCart[j].itemDescription, "");
                        strcpy(userCart[current].ItemsCart[j].category, "");
                        strcpy(userCart[current].ItemsCart[j].itemName, "");

                        for(k = j; k < userCart[current].countItems; k++)
                        {
                            swap(&userCart[current].ItemsCart[k], &userCart[current].ItemsCart[k+1]);
                            j = -1;
                        }

                        nFound = 1;
                    }
                }
                
                if(nFound == 0)
                    printf("Seller ID Does not exists!\n");

                //system("pause");
                nFound = 0;
                break;
        
        case 2: 
                //delete specific item
                
                userCart[current].countItems--; //debugging
                for(j = 0; j < userCart[current].countItems; j++)
                {
                    if(userCart[current].ItemsCart[j].productID == numID)
                    {
                        userCart[current].ItemsCart[j].sellerID = '\0';
                        userCart[current].ItemsCart[j].productID = '\0';
                        userCart[current].ItemsCart[j].availQuantity = '\0';
                        userCart[current].ItemsCart[j].unitPrice = '\0';
                        strcpy(userCart[current].ItemsCart[j].itemDescription, "");
                        strcpy(userCart[current].ItemsCart[j].category, "");
                        strcpy(userCart[current].ItemsCart[j].itemName, "");

                        for(k = j; k < userCart[current].countItems; k++)
                        {
                            swap(&userCart[current].ItemsCart[k], &userCart[current].ItemsCart[k+1]);
                        }

                        nFound = 1;
                    }
                }

                if(nFound == 0)
                    printf("Product ID Does not exists!\n");

                //system("pause");
                nFound = 0;
                break;

        //ALL
        case 3: 
                for(j = 0; j < numID; j++)
                {
                    userCart[current].ItemsCart[j].sellerID = '\0';
                    userCart[current].ItemsCart[j].productID = '\0';
                    userCart[current].ItemsCart[j].availQuantity = '\0';
                    userCart[current].ItemsCart[j].unitPrice = '\0';
                    strcpy(userCart[current].ItemsCart[j].itemDescription, "");
                    strcpy(userCart[current].ItemsCart[j].category, "");
                    strcpy(userCart[current].ItemsCart[j].itemName, "");

                    userCart[current].countItems--;
                }
                
                //system("pause");
                break;
    }
}

/* 
getString gets string input from the user (per letter to include white spaces)
@param *str - contains the address where the string will be stored
@return - returns nothing (void)
*/
void
getString(char * str) 
{
    int i;
    char ch;
    
    i = 0;
    do 
    {
        scanf("%c", &ch);
        if (ch != '\n') 
        {
            str[i] = ch;
            i++;
        }
    } while (ch != '\n');
    str[i] = '\0';
}

/* 
getUserInfo gets all information about the user
@param *u - the address where the user info is stored
@return - returns nothing (void)
*/
void 
getUserInfo (struct userTag *u)
{
    char cDump;
    printf("Please enter password: ");
    scanf("%s%c", u->password, &cDump);

    printf("Please enter name: ");
    getString(u->userName);

    printf("Please enter address: ");
    getString(u->address);

    printf("Please enter contact number: ");
    scanf("%I64d", &u->contactNumber);
}

int
isValidQuantity(struct itemsTag *i)
{
    int rtr = 0;

    if(i->availQuantity > 0)
        rtr = 1;

    return rtr;
}

int
isValidPrice(struct itemsTag *i)
{
    int rtr = 0;

    if(i->unitPrice > 0)
        rtr = 1;

    return rtr;
}


/* 
getUserInfo gets all information about the item
@param *i - the address where the item info is stored
@return - returns nothing (void)
*/
void
getItemInfo(struct itemsTag *i)
{
    printf("Enter Item Name: ");
    getString(i->itemName);

    printf("Enter Item Category: ");
    getString(i->category);

    printf("Enter Item Description: ");
    getString(i->itemDescription);

    do
    {
        printf("Enter Item Quantity: ");
        scanf("%d", &i->availQuantity);
    } while (!isValidQuantity(i));
    
    do
    {
        printf("Enter Unit Price: ");
        scanf("%f", &i->unitPrice); 
    } while (!isValidPrice(i));
}

/* 
getItemString function gets string information about item (this is for EDIT STOCK)
@param *i - the address where the item info is stored
@param choice - action to be done (get string for item name or category or item description)
@return - returns nothing (void)
*/
void
getItemString(struct itemsTag *i, int choice)
{
    switch(choice)
    {
        case 1: getString(i->itemName); break;
        case 2: getString(i->category); break;
        case 3: getString(i->itemDescription); break;
    }
}

void
sortUserID(struct userTag users[], int n) 
{
  int i, j, minimum;
  for (i = 0; i < n - 1; i++) 
  {
    minimum = i;
    for (j = i + 1; j < n; j++) 
	{
      if (users[minimum].userID > users[j].userID)
        minimum = j;
    }
    if (i != minimum)
      swapUser(&users[i], &users[minimum]);
  }
}

/* 
sortProductID function sorts the product ID in increasing order
@param items[][20] - 2D array where the items are stored
@param n - number of items
@param k - current user
@return - returns nothing (void)
*/
void 
sortProductID(struct itemsTag items[][20], int n, int k) 
{
  int i, j, minimum;
  for (i = 0; i < n - 1; i++) 
  {
    minimum = i;
    for (j = i + 1; j < n; j++) 
	{
      if (items[k][minimum].productID > items[k][j].productID)
        minimum = j;
    }
    if (i != minimum)
      swap(&items[k][i], &items[k][minimum]);
  }
}

/* 
sortBuyerIDTransaction function sorts the product ID in increasing order (ADMIN MENU)
@param aTransaction[] - 1D array where the transactions are stored
@param n - number of transactions
@return - returns nothing (void)
*/
void
sortBuyerIDTransaction(struct transactionsTag aTransaction[], int n)
{
    int i, j, minimum;
    for (i = 0; i < n - 1; i++) 
    {
        minimum = i;
        for (j = i + 1; j < n; j++) 
        {
            if (aTransaction[minimum].buyerUserID > aTransaction[j].buyerUserID)
                minimum = j;
        }
        if (i != minimum)
        swapTrans(&aTransaction[i], &aTransaction[minimum]);
    }
}

/* 
sortProductID function sorts the seller ID in increasing order
@param items[][20] - 2D array where the items are stored
@param n - number of items
@param k - current user
@return - returns nothing (void)
*/
void 
sortSellerID(struct itemsTag items[][20], int n, int k) 
{
  int i, j, minimum;
  for (i = 0; i < n - 1; i++) 
  {
    minimum = i;
    for (j = i + 1; j < n; j++) 
	{
      if (items[k][minimum].sellerID > items[k][j].sellerID)
        minimum = j;
    }
    if (i != minimum)
      swap(&items[k][i], &items[k][minimum]);
  }
}

/* 
sortProductID1 function sorts the seller ID in increasing order in the userCart (for USER CART)
@param items[][20] - 2D array where the items are stored
@param n - number of items
@param k - current user
@return - returns nothing (void)
*/
void 
sortSellerID1(struct itemsTag items[], int n) 
{
    int i, j, minimum;
    for (i = 0; i < n - 1; i++) 
    {
        minimum = i;
        for (j = i + 1; j < n; j++) 
        {
            if (items[minimum].sellerID > items[j].sellerID)
                minimum = j;
        }
        if (i != minimum)
        swap(&items[i], &items[minimum]);
    }
}

/* 
sortSellerIDTransaction function sorts the product ID in increasing order (ADMIN MENU)
@param aTransaction[] - 1D array where the transactions are stored
@param n - number of transactions
@return - returns nothing (void)
*/
void 
sortSellerIDTransaction(struct transactionsTag aTransaction[], int n) 
{
    int i, j, minimum;
    for (i = 0; i < n - 1; i++) 
    {
        minimum = i;
        for (j = i + 1; j < n; j++) 
        {
            if (aTransaction[minimum].SellerUserID > aTransaction[j].SellerUserID)
                minimum = j;
        }
        if (i != minimum)
        swapTrans(&aTransaction[i], &aTransaction[minimum]);
    }
}

/* 
displayTable function displays the items' information in table format (for EDIT STOCK)
@param items[][20] - 2D array where the items are stored
@param n - number of items
@param current - current user
@return - returns nothing (void)
*/
void 
displayTable(struct itemsTag i[][20], int n, int current)
{
    int j;
    printf("+------------+----------------------+-----------------+------------+------------+\n");
    printf("| %10s | %-20s | %-15s | %10s | %10s |\n", "Product ID", "Item Name", "Category", "Unit Price", "Quantity"); //header

    for(j = 0; j < n; j++)
    {
        printf("+------------+----------------------+-----------------+------------+------------+\n");
        printf("| %10d | %-20s | %-15s | %10.2f | %10d |", i[current][j].productID, i[current][j].itemName, i[current][j].category, i[current][j].unitPrice, i[current][j].availQuantity);
        printf("\n");
    }
    printf("+------------+----------------------+-----------------+------------+------------+\n");
}

/* 
displayUserTable function displays all the user in table format (ADMIN MENU)
@param u[] - 1D array where the users are stored
@param n - number of items
@return - returns nothing (void)
*/
void 
displayUserTable(struct userTag u[], int n)
{
    sortUserID(u, n);

    int j;
      printf("+------------+-------------+-----------------------+---------------------------------+--------------+\n");
    printf("| %10s | %-11s | %-21s | %-31s | %11s |\n", "User ID", "Password", "Name", "Address", "Phone Number"); //header

    for(j = 0; j < n; j++)
    {
      printf("+------------+-------------+-----------------------+---------------------------------+--------------+\n");
      printf("| %10d | %-11s | %-21s | %-31s | %12I64d |", u[j].userID, u[j].password, u[j].userName, u[j].address, u[j].contactNumber);
      printf("\n");
    }
      printf("+------------+-------------+-----------------------+---------------------------------+--------------+\n");
}

/* 
displaySellerTable function displays the sellers' information in table format (ADMIN MENU)
@param u[] - 1D array where the users are stored
@param items[][20] - 2D array where the items are stored
@param n[] - number of items
@return - returns nothing (void)
*/
void 
displaySellerTable(struct userTag u[], struct itemsTag i[][20], int n[])
{

    int j;
      printf("+------------+-------------+-----------------------+---------------------------------+--------------+--------------+\n");
    printf("| %10s | %-11s | %-21s | %-31s | %11s | %12s |\n", "User ID", "Password", "Name", "Address", "Phone Number", "# of Items"); //header
    printf("+------------+-------------+-----------------------+---------------------------------+--------------+--------------+\n");

    for(j = 0; j < MAX; j++)
    {
        if(i[j][0].sellerID == u[j].userID && u[j].userID != '\0')
        {
            printf("| %10d | %-11s | %-21s | %-31s | %12I64d | %10d   |", u[j].userID, u[j].password, u[j].userName, u[j].address, u[j].contactNumber, n[j]);
            printf("\n");
            printf("+------------+-------------+-----------------------+---------------------------------+--------------+--------------+\n");
        }
        
    }
}

/* 
showLowStock function displays the products that have < 5 quantity (SELL MENU)
@param items[][20] - 2D array where the items are stored
@param numProducts - number of items
@param current - current user
@return - returns nothing (void)
*/
void
showLowStock (struct itemsTag i[][20], int numProducts, int current)
{
    int j, nFound = 0;
    char choice, cDump;

    j = 0;
    do
    {
        if(i[current][j].availQuantity < 5 && i[current][j].productID)
        {
            printf("\nProduct ID: %d\n", i[current][j].productID);
            printf("Item Name: %s\n", i[current][j].itemName);
            printf("Category: %s\n", i[current][j].category);
            printf("Item Description: %s\n", i[current][j].itemDescription);
            printf("Quantity Available: %d\n", i[current][j].availQuantity);
            printf("Numeric Unit Price: %.2f\n", i[current][j].unitPrice);

            scanf("%c", &cDump);
            printf("\nEnter [N] to view next item or [X] to exit view: ");
            scanf("%c", &choice);

            nFound = 1;
        }
        j++;
    } while (choice != 'X' && j < numProducts);

    if(!nFound)
        printf("\n|| No stocks below 5! ||\n");
        
    nFound = 0;
    printf("\n");
    //system("pause");
}

/* 
displayAllProducts function displays all product (BUY MENU)
@param items[][20] - 2D array where the items are stored
@param n[] - number of items
@return - returns nothing (void)
*/
void
displayAllProducts(struct itemsTag i[][20], int n[])
{
    int loop;
    char cDump, choice;

    //sort sellerID from lowest to highest
    for(loop = 0; loop < MAX; loop++)
        if(n[loop] != '\0')
            sortSellerID(i, n[loop], loop);
    
    loop = 0;
    do
    {
        if(n[loop] != '\0' && i[loop][n[loop]-1].sellerID != '\0')
        {
            printf("\nSELLER ID: %d\n",i[loop][n[loop]-1].sellerID);
            sortProductID(i, n[loop], loop);
            displayTable(i, n[loop], loop);

            scanf("%c", &cDump);
            printf("\nEnter [N] to view next item or [X] to exit view: ");
            scanf("%c", &choice);
        }
        loop++;
    } while (choice != 'X' && loop < MAX);
}

/* 
showCategory function displays the items that have the category based on user input (SELL MENU)
@param items[][20] - 2D array where the items are stored
@param numProducts - number of items
@param current - current user
@param category - contains the category we are looking for
@return - returns nothing (void)
*/
void
showCategory (struct itemsTag i[][20], int numProducts, int current, string15 category)
{
    int j;
    char choice, cDump;

    j = 0;
    while(choice != 'X' && j < numProducts)
    {
        if(strcmp(i[current][j].category, category) == 0)
        {
            printf("\nProduct ID: %d\n", i[current][j].productID);
            printf("Item Name: %s\n", i[current][j].itemName);
            printf("Category: %s\n", i[current][j].category);
            printf("Item Description: %s\n", i[current][j].itemDescription);
            printf("Quantity Available: %d\n", i[current][j].availQuantity);
            printf("Numeric Unit Price: %.2f\n", i[current][j].unitPrice);

            
            printf("\nEnter [N] to view next item or [X] to exit view: ");
            scanf("%c%c", &choice, &cDump);
        }
        j++;
    }
            
    printf("\n");
}

/* 
showByName function displays the items that contain the keyword (SELL MENU)
@param items[][20] - 2D array where the items are stored
@param numProducts - number of items
@param current - current user
@param keyword - name we're looking for
@return - returns nothing (void)
*/
void
showByName (struct itemsTag i[][20], int numProducts, int current, string15 keyword)
{
    int j;
    char choice, cDump;

    j = 0;
    while (choice != 'X' && j < numProducts)
    {
        if(strstr(i[current][j].itemName, keyword))
        {
            printf("\nProduct ID: %d\n", i[current][j].productID);
            printf("Item Name: %s\n", i[current][j].itemName);
            printf("Category: %s\n", i[current][j].category);
            printf("Item Description: %s\n", i[current][j].itemDescription);
            printf("Quantity Available: %d\n", i[current][j].availQuantity);
            printf("Numeric Unit Price: %.2f\n", i[current][j].unitPrice);

            printf("\nEnter [N] to view next item or [X] to exit view: ");
            scanf("%c%c", &choice, &cDump);
        }
        j++;
    }
            
    printf("\n");
}

/* 
displayCart1 function displays the item information of specific seller (BUY MENU - edit cart)
@param items[] - 1D array where the items are stored
@param j - current item cart
@return - returns nothing (void)
*/
void
displayCart1 (struct itemsTag i[], int j)
{

    if(i[j].sellerID != i[j-1].sellerID)
    {
        printf("\n|| Seller ID: %d ||\n", i[j].sellerID);
        printf("+------------+----------------------+-----------------+------------+------------+\n");
        printf("| %10s | %-20s | %-15s | %10s | %10s |\n", "Product ID", "Item Name", "Category", "Unit Price", "Quantity"); //header
        printf("+------------+----------------------+-----------------+------------+------------+\n");
        printf("| %10d | %-20s | %-15s | %10.2f | %10d |", i[j].productID, i[j].itemName, i[j].category, i[j].unitPrice, i[j].availQuantity);
        printf("\n+------------+----------------------+-----------------+------------+------------+");
    }
    else
    {
        printf("| %10d | %-20s | %-15s | %10.2f | %10d |", i[j].productID, i[j].itemName, i[j].category, i[j].unitPrice, i[j].availQuantity);
        printf("\n+------------+----------------------+-----------------+------------+------------+");
    }
        
    printf("\n");
}

/* 
changeQuantity function changes the quantity of an item (SELL MENU)
@param userCart[] - 1D array where the items are stored
@param current - current user
@param numID - product ID to be changed
@param quantity - new quantity
@return - returns nothing (void)
*/
void
changeQuantity(struct cartTag userCart[], int current, int numID, int quantity)
{
    int j;

    for(j = 0; j < 10; j++)
        if(userCart[current].ItemsCart[j].productID == numID)
            userCart[current].ItemsCart[j].availQuantity = quantity;
  
}

/* 
checkItems function checks if the product ID exists and quantity is available (SELL MENU)
@param userCart[] - 1D array where the items are stored
@param current - current user
@param numID - product ID to be changed
@param quantity - new quantity
@return - returns nothing (void)
*/
int
checkItems (struct itemsTag i[][20], int nNum[], int tempProductID, int tempQuantity)
{
    int k, j, rtr = 0;

    for(k = 0; k < MAX; k++)
        for (j = 0; j < nNum[k]; j++)
            if(i[k][j].productID == tempProductID)
                if(i[k][j].availQuantity >= tempQuantity)
                    rtr = 1;

    return rtr;
}

/*------------------------------------------------*/ //Reading and Writing from/to files

/* 
writeToFileUsers function writes to file the contents of users array (end of the program)
@param *ptrUser - file pointer for user file
@param aUsers[] - 1D array where the items are stored
@param numUsers - number of users
@param newData - index where the writing will start
@return - returns nothing (void)
*/
void
writeToFileUsers(FILE *ptrUser, struct userTag aUsers[], int numUsers, int newData)
{
    int i;
    for(i = newData; i < numUsers; i++)
    {
        fprintf(ptrUser, "%d ", aUsers[i].userID);
        fprintf(ptrUser, "%s\n", aUsers[i].password);
        fprintf(ptrUser, "%s\n", aUsers[i].userName);
        fprintf(ptrUser, "%s\n", aUsers[i].address);
        fprintf(ptrUser, "%I64d\n\n", aUsers[i].contactNumber);
    }
}

/* 
writeToFileItems function writes to file the contents of items array (end of the program)
@param *ptrItems - file pointer for item file
@param aItems[][20] - 2D array where the items are stored
@param numProducts[] - 1D array of items count
@return - returns nothing (void)
*/
void
writeToFileItems(FILE *ptrItems, struct itemsTag aItems[][20], int numProducts[])
{
    int k, j;
    for(k = 0; k < MAX; k++) //users (row)
    {
        for(j = 0; j < numProducts[k]; j++) //items(column)
        {
            if(aItems[k][j].sellerID != '\0')
            {
                fprintf(ptrItems, "%d ", aItems[k][j].productID);
                fprintf(ptrItems, "%d\n", aItems[k][j].sellerID);
                fprintf(ptrItems, "%s\n", aItems[k][j].itemName);
                fprintf(ptrItems, "%s\n", aItems[k][j].category);
                fprintf(ptrItems, "%s\n", aItems[k][j].itemDescription);
                fprintf(ptrItems, "%d ", aItems[k][j].availQuantity);
                fprintf(ptrItems, "%.2f\n\n", aItems[k][j].unitPrice);
            }
        }
    }
}

/* 
readItemsFIle function reads (scanf) the file and store its content to aray (start of the program)
@param *ptrItems - file pointer for user file
@param aItems[][20] - 2D array where the items are stored
@param i[] - 1D arrays which contains the number of items per user
@return - returns nothing (void)
*/
void
readItemsFile(FILE *ptrItems, struct itemsTag aItems[][20], int i[])
{
    int j, k;
    int prevInd;
    char cDump;
    int length;

    j = 0; 
    k = 0;

    //(!feof(ptrItems))

    while(fscanf(ptrItems, "%d%c%d%c", &aItems[j][k].productID, &cDump, &aItems[j][k].sellerID, &cDump) == 4)
    {
        //printf("entered here\n"); //debugging
        
        //--
        fgets(aItems[j][k].itemName, 21, ptrItems);
        length = strlen(aItems[j][k].itemName);
        aItems[j][k].itemName[length-1] = '\0';
        //--
        fgets(aItems[j][k].category, 16, ptrItems);
        length = strlen(aItems[j][k].category);
        aItems[j][k].category[length-1] = '\0';
        //--
        fgets(aItems[j][k].itemDescription, 31, ptrItems);
        length = strlen(aItems[j][k].itemDescription);
        aItems[j][k].itemDescription[length-1] = '\0';
        //--
        fscanf(ptrItems, "%d%c%f%c%c", &aItems[j][k].availQuantity, &cDump, &aItems[j][k].unitPrice, &cDump, &cDump);

        if (k > 0)
        {
            if(aItems[j][k-1].sellerID != aItems[j][k].sellerID)
            {
                //printf("entered here\n");
                prevInd = k;
                j++; //next seller
                k = 0; //reset item to 0
                aItems[j][k] = aItems[j-1][prevInd]; //copying the whole struct
                initializedItemsZero(aItems[j-1][prevInd]); //initializing it to zero (remove its content)
            }
        }
        k++;
        i[j]++;
    }
}

/* 
readItemsFIle function reads (scanf) the file and store its content to aray (BUY MENU)
@param *ptrCart - file pointer for cart file
@param aCart[] - 1D arrays which contains the information of each items in the cart
@param current - current user
@return - returns nothing (void)
*/
void
readCartFile (FILE *ptrCart, struct cartTag aCart[], int current)
{
    int j;
    int length;
    char cDump;

    aCart[current].countItems = 0;

    j = 0;

    //(!feof(ptrCart))

    while(fscanf(ptrCart, "%d%c%d%c", &aCart[current].ItemsCart[j].productID, &cDump, &aCart[current].ItemsCart[j].sellerID, &cDump) == 4)
    {
        
        //--
        fgets(aCart[current].ItemsCart[j].itemName, 21, ptrCart);
        length = strlen(aCart[current].ItemsCart[j].itemName);
        aCart[current].ItemsCart[j].itemName[length-1] = '\0';
        //--
        fgets(aCart[current].ItemsCart[j].category, 21, ptrCart);
        length = strlen(aCart[current].ItemsCart[j].category);
        aCart[current].ItemsCart[j].category[length-1] = '\0';
        //--
        fgets(aCart[current].ItemsCart[j].itemDescription, 30, ptrCart);
        length = strlen(aCart[current].ItemsCart[j].itemDescription);
        aCart[current].ItemsCart[j].itemDescription[length-1] = '\0';
        //--
        fscanf(ptrCart, "%d%c%f%c%c", &aCart[current].ItemsCart[j].availQuantity, &cDump, &aCart[current].ItemsCart[j].unitPrice, &cDump, &cDump);

        j++;
        aCart[current].countItems++;
    }
}

/* 
writingCartFile function writes to file the contents of the array (BUY MENU - exit)
@param *ptrCart - file pointer for cart file
@param aCart[] - 1D arrays which contains the information of each items in the cart
@param currentUser - current user
@return - returns nothing (void)
*/
void
writingCartFile(FILE *ptrCart, struct cartTag aCart[], int currentUser)
{
    int j;
    for(j = 0; j < aCart[currentUser].countItems; j++)
    {
        //if(aCart[currentUser].ItemsCart[j].sellerID != 0)
        //{
            fprintf(ptrCart, "%d ", aCart[currentUser].ItemsCart[j].productID);
            fprintf(ptrCart, "%d\n", aCart[currentUser].ItemsCart[j].sellerID);
            fprintf(ptrCart, "%s\n", aCart[currentUser].ItemsCart[j].itemName);
            fprintf(ptrCart, "%s\n", aCart[currentUser].ItemsCart[j].category);
            fprintf(ptrCart, "%s\n", aCart[currentUser].ItemsCart[j].itemDescription);
            fprintf(ptrCart, "%d ", aCart[currentUser].ItemsCart[j].availQuantity);
            fprintf(ptrCart, "%.2f\n\n", aCart[currentUser].ItemsCart[j].unitPrice);
        //}
    }
}

/*------------------------------------------------*/ //Display Function

/*
All the functions here just displays the menu option
*/
void 
displayMenu()
{
    printf("\n");
    printf("\n---------------------------------------------------------------\n");
    printf("######  ##   ##  #######  #######  ######  ##  ##   ##  ####### \n");
    printf("##      ##   ##  ##   ##  ##   ##  ##   #  ##  ###  ##  ##      \n");
    printf("######  #######  ##   ##  #######  ######  ##  ## # ##  ## #### \n");
    printf("    ##  ##   ##  ##   ##  ##       ##      ##  ##  ###  ##   ## \n");
    printf("######  ##   ##  #######  ##       ##      ##  ##   ##  ####### \n\n");
    

    printf("                   #######  #######  #######   \n");
    printf("                   ##   ##  ##   ##  ##   ##   \n");
    printf("                   #######  #######  #######   \n");
    printf("                   ##   ##  ##       ##        \n");
    printf("                   ##   ##  ##       ##        \n\n");
    
    printf("[1] Register as a User\n");
    printf("[2] User Menu\n");
    printf("[3] Admin Menu\n");
    printf("[4] Exit\n");
    printf("---------------------------------------------------------------\n");
    printf("Please enter one selection: ");
}

void 
displayUserMenu()
{
    printf("\n");
    printf("|| USER MENU ||\n");
    printf("---------------------------------------------------------------\n");
    printf("OPTIONS\n");
    printf("[1] Sell Menu\n");
    printf("[2] Buy Menu\n");
    printf("[3] Exit User Menu\n");
    printf("---------------------------------------------------------------\n");
    printf("Please enter one selection: ");
}

void 
displaySellMenu()
{
    printf("\n");
    printf("|| SELL MENU ||\n");
    printf("---------------------------------------------------------------\n");
    printf("OPTIONS\n");
    printf("[1] Add New Item\n");
    printf("[2] Edit Stock\n");
    printf("[3] Show My Products\n");
    printf("[4] Show My Low Products\n");
    printf("[5] Exit Sell Menu\n");
    printf("---------------------------------------------------------------\n");    
    printf("Please enter one selection: ");
}

void 
displayEditStock()
{
    printf("\n");
    printf("|| Edit Stock Option ||\n");
    printf("---------------------------------------------------------------\n");
    printf("OPTIONS\n");
    printf("[1] Replenish\n");
    printf("[2] Change Price\n");
    printf("[3] Change Item Name\n");
    printf("[4] Change Category\n");
    printf("[5] Change Description\n");
    printf("[6] Finish Editing\n");
    printf("---------------------------------------------------------------\n");
    printf("Please enter one selection: ");
}

void 
displayBuyMenu()
{
    printf("\n");
    printf("|| BUY MENU ||\n");
    printf("---------------------------------------------------------------\n");
    printf("OPTIONS\n");
    printf("[1] View All Products\n");
    printf("[2] Show All Products by a Specific Seller\n");
    printf("[3] Search Products By Category\n");
    printf("[4] Search Products By Name\n");
    printf("[5] Add To Cart\n");
    printf("[6] Edit Cart\n");
    printf("[7] Check Out Menu\n");
    printf("[8] Exit Buy Menu\n");
    printf("---------------------------------------------------------------\n");
    printf("Please enter one selection: ");
}

void 
displayEditCart()
{
    printf("\n");
    printf("|| Edit Cart ||\n");
    printf("---------------------------------------------------------------\n");
    printf("OPTIONS\n");
    printf("[1] Remove All items from Seller\n");
    printf("[2] Remove Specific Item\n");
    printf("[3] Edit Quantity\n");
    printf("[4] Finish Edit Cart\n");
    printf("---------------------------------------------------------------\n");
    printf("Please enter one selection: ");
}

void 
displayCheckOutMenu()
{
    printf("\n");
    printf("|| Check Out Menu ||\n");
    printf("---------------------------------------------------------------\n");
    printf("OPTIONS\n");
    printf("[1] All\n");
    printf("[2] By a Specific Seller\n");
    printf("[3] Specific Item\n");
    printf("[4] Exit Check Out\n");
    printf("---------------------------------------------------------------\n");
    printf("Please enter one selection: ");
}

void 
displayAdminMenu()
{
    printf("\n");
    printf("|| ADMIN MENU ||\n");
    printf("---------------------------------------------------------------\n");
    printf("OPTIONS\n");
    printf("[1] Show All Users\n");
    printf("[2] Show All Sellers\n");
    printf("[3] Show Total Sales in Given Duration\n");
    printf("[4] Show Seller Sales\n");
    printf("[5] Show Shopaholics\n");
    printf("[6] Back To Main Menu\n");
    printf("---------------------------------------------------------------\n");
    printf("Please enter one selection: ");
}

/*------------------------------------------------*/ //Reading and Writing from/to files

/* 
writeTransactionFile function writes to file the contents of transaction array (when checking out specific seller or item)
@param *ptrTransaction - file pointer for transaction file
@param pTransaction[][30] - 2D array where the items are stored
@param currentUser - current user (the user doing the checkout)
@param transaction - number of transaction
@return - returns nothing (void)
*/
void
writeTransanctionFile (FILE *ptrTransaction, struct transactionsTag pTransaction[][30], int currentUser, int transaction, int numTrans)
{
    int j;

    for(j = transaction; j < numTrans+1; j++)
    {
        fprintf(ptrTransaction, "%d/%d/%d\n", pTransaction[currentUser][j].date.month, 
                                            pTransaction[currentUser][j].date.day, 
                                            pTransaction[currentUser][j].date.year);
        fprintf(ptrTransaction, "%.2f\n", pTransaction[currentUser][j].totalAmount);
        fprintf(ptrTransaction, "%d\n", pTransaction[currentUser][j].buyerUserID);
        fprintf(ptrTransaction, "%s\n", pTransaction[currentUser][j].buyerName);
        fprintf(ptrTransaction, "%d\n", pTransaction[currentUser][j].SellerUserID);
        fprintf(ptrTransaction, "%s\n", pTransaction[currentUser][j].userName);
        fprintf(ptrTransaction, "\n");
    }
}

/* 
writeTransactionFile1 function writes to file the contents of transaction array (when checking out all items)
@param *ptrTransaction - file pointer for transaction file
@param pTransaction[][30] - 2D array where the items are stored
@param currentUser - current user (the user doing the checkout)
@param transaction - number of transaction
@return - returns nothing (void)
*/
void
writeTransanctionFile1 (FILE *ptrTransaction, struct transactionsTag pTransaction[][30], int currentUser, int transaction)
{
    int j;

    for(j = 0; j < transaction; j++)
    {
        fprintf(ptrTransaction, "%d/%d/%d\n", pTransaction[currentUser][j].date.month, 
                                            pTransaction[currentUser][j].date.day, 
                                            pTransaction[currentUser][j].date.year);
        fprintf(ptrTransaction, "%.2f\n", pTransaction[currentUser][j].totalAmount);
        fprintf(ptrTransaction, "%d\n", pTransaction[currentUser][j].buyerUserID);
        fprintf(ptrTransaction, "%s\n", pTransaction[currentUser][j].buyerName);
        fprintf(ptrTransaction, "%d\n", pTransaction[currentUser][j].SellerUserID);
        fprintf(ptrTransaction, "%s\n", pTransaction[currentUser][j].userName);
        fprintf(ptrTransaction, "\n");
    }
}

/* 
readTransactionFile function reads from file and store the contents in transaction array
@param *ptrTransaction - file pointer for transaction file
@param pTransaction[] - 1D array where the items are stored
@return - returns nothing (void)
*/
void
readTransactionFile (FILE *ptrTransaction, struct transactionsTag pTransaction[MAX])
{
    char cDump;
    int i, length;

    i = 0;

    //(!feof(ptrTransactio)) buggy
    while(fscanf(ptrTransaction, "%d%c%d%c%d%c",  &pTransaction[i].date.month, &cDump, 
                                                &pTransaction[i].date.day, &cDump, 
                                                &pTransaction[i].date.year, &cDump) == 6)
    {
        
        fscanf(ptrTransaction, "%f%c", &pTransaction[i].totalAmount, &cDump);
        fscanf(ptrTransaction, "%d%c", &pTransaction[i].buyerUserID, &cDump);
        // removes the null byte at the end
        fgets(pTransaction[i].buyerName, 20, ptrTransaction);
        length = strlen(pTransaction[i].buyerName);
        pTransaction[i].buyerName[length-1] = '\0';
        //
        fscanf(ptrTransaction, "%d%c", &pTransaction[i].SellerUserID, &cDump);
        // removes the null byte at the end
        fgets(pTransaction[i].userName, 20, ptrTransaction);
        length = strlen(pTransaction[i].userName);
        pTransaction[i].userName[length-1] = '\0';
        //
        fscanf(ptrTransaction, "%c", &cDump);

        i++;
    }
}  

/*------------------------------------------------*/ //Function

/* 
checkDateRange function checks if the date is within the given range (start and end)
@param aDate - struct which contains the date to be checked
@param aStart - struct which contains the start date
@param aEnd - cstruct which contains the end date
@return - returns 1 if within range, returns 0 if not
*/
int
checkDateRange(struct dateTag aDate, struct dateTag aStart, struct dateTag aEnd)
{
    int rtr = 0;
    int startDate = (aStart.year * 10000) + (aStart.month * 100) + aStart.day;
    int endDate = (aEnd.year * 10000) + (aEnd.month * 100) + aEnd.day;
    int givenDate = (aDate.year * 10000) + (aDate.month * 100) + aDate.day;

    if(givenDate >= startDate && givenDate <= endDate)
        rtr = 1;

    return rtr;
}

/* 
showTotalSales function displays the total sales within the duration
@param pTransaction[] - 1D array where the transactions are stored
@param aStart - struct which contains the start date
@param aEnd - cstruct which contains the end date
@return - returns 1 if within range, returns 0 if not
*/
void
showTotalSales(struct transactionsTag pTransaction[MAX], struct dateTag aStart, struct dateTag aEnd)
{
    int i;
    float sum = 0;

    for(i = 0; i < MAX; i++)
        if(checkDateRange(pTransaction[i].date, aStart, aEnd))
            sum += pTransaction[i].totalAmount;

    if(sum == 0)
         printf("|| no sales within duration ||\n");
    else printf("\nTotal Amount of sales within the durations: %.2f\n", sum);
}

/* 
displaySellerSales function computes and displays the total sale of each seller (ADMIN MENU)
@param pTransaction[] - 1D array contains all transactions
@param aStart - struct which contains the start date
@param aEnd - cstruct which contains the end date
@param seller[] - 1D array contains all seller ID
@param numSeller - number of seller
return - nothing (void)
*/
void
displaySellerSales(struct transactionsTag pTransaction[], struct dateTag aStart, struct dateTag aEnd, int seller[], int numSeller)
{
    int i, j;
    int next = 0;
    int found = 0;
    float sum[MAX] = {0};

    for(i = 0; i < numSeller; i++)
    {
        for(j = 0; j < MAX; j++)
        {
            if(checkDateRange(pTransaction[j].date, aStart, aEnd))
                if(pTransaction[j].SellerUserID == seller[i])
                {
                    sum[i] += pTransaction[j].totalAmount;
                    found = 1;
                }
        }  
    }

    if(found)
    {
        printf("\n+------------+----------------------+-------------+\n");
        printf("| %10s | %-20s | %10s |", "Seller ID", "Seller Name", "Total Sales");
        printf("\n+------------+----------------------+-------------+\n");
        for(i = 0; i < numSeller; i++)
        {
            for(j = 0; j < MAX && !next; j++)
            {
                if(pTransaction[j].SellerUserID == seller[i])
                {
                    if(checkDateRange(pTransaction[j].date, aStart, aEnd))
                    {
                        printf("| %10d | %-20s | %10.2f  |", pTransaction[j].SellerUserID, pTransaction[j].userName, sum[i]);
                        printf("\n+------------+----------------------+-------------+\n");
                        next = 1;
                    }
                }
            } 
            next = 0; 
        }
    }
    else printf("|| no sales within duration. ||\n");
}

/* 
displayShopaholics function computes and displays the total amount for each buyer (ADMIN MENU)
@param pTransaction[] - 1D array contains all transactions
@param aStart - struct which contains the start date
@param aEnd - cstruct which contains the end date
@param buyer[] - 1D array contains all buyer ID
@param numSeller - number of buyer
return - nothing (void)
*/
void
displayShopaholics(struct transactionsTag pTransaction[], struct dateTag aStart, struct dateTag aEnd, int buyer[], int numBuyer)
{
    int i, j;
    int next = 0;
    int found = 0;
    float sum[MAX] = {0};

    for(i = 0; i < numBuyer; i++)
    {
        for(j = 0; j < MAX; j++)
        {
            if(checkDateRange(pTransaction[j].date, aStart, aEnd))
                if(pTransaction[j].buyerUserID == buyer[i])
                {
                    sum[i] += pTransaction[j].totalAmount;
                    found = 1;
                }
        }  
    }

    if(found)
    {
        printf("\n+------------+----------------------+--------------+\n");
        printf("| %10s | %-20s | %10s |", "Buyer ID", "Buyer Name", "Total Amount");
        printf("\n+------------+----------------------+--------------+\n");
        
        for(i = 0; i < numBuyer; i++)
        {
            for(j = 0; j < MAX && !next; j++)
            {
                if(pTransaction[j].buyerUserID == buyer[i])
                {
                    if(checkDateRange(pTransaction[j].date, aStart, aEnd))
                    {
                        printf("| %10d | %-20s | %10.2f   |", pTransaction[j].buyerUserID, pTransaction[j].buyerName, sum[i]);
                        printf("\n+------------+----------------------+--------------+\n");
                        next = 1;
                    }
                }
            } 
            next = 0; 
        }
    }
    else printf("|| no sales within duration. ||\n");
}

/* 
isValidDate function checks if the date is valid (BUY MENU - checkout)
@param *date - contains the date
@return - returns 1 if valid and returns 0 if not
precondition - no negative integers/value
*/
int
isValidDate(struct dateTag *date)
{
  int rtr = 0;
  switch(date->month)
  {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12: 
            if(date->day <= 31)
                rtr = 1;
            else printf("\nINVALID DAY!\n\n");

            break;
    case 4:
    case 6:
    case 9:
    case 11: 
            if(date->day <= 30)
                rtr = 1;
            break;
    case 2:
            if(date->day <= 28)
                rtr = 1;
            else printf("\nINVALID DAY!\n\n");
            break;

    default: printf("\nINVALID MONTH!\n\n");
  }
    return rtr;
}

/* 
getDate function get date from the user (BUY MENU - checkout)
@param *date - address where the date is placced
@return - returns nothing (void)
*/
void 
getDate(struct dateTag *date) //it must be a pointer to be able to change its data
{
  char cDump;
  int valid = 0;

  do
  {
    printf("Enter month: ");
    scanf("%d", &date->month);
    printf("Enter day: ");
    scanf("%d", &date->day);
    printf("Enter year: ");
    scanf("%d%c", &date->year, &cDump);

    printf("\n");

    valid = isValidDate(date);

  } while(valid == 0);
}

/* 
changeQuantityCO function updates the quantity of the items that have been checked out (BUY MENU - checkout)
@param i[][20] - 2D array which contains the items information
@param aCart[] - 1D arrays which contains the information of each items in the cart
@param currentUser - current user
@param num[] - 1D arrays which contains the number of items (per user)
@param tempVar - vproduct ID to be changed
@param choice - action to be done (for switch)
@return - returns nothing (void)
*/
void
changeQuantityCO(struct itemsTag i[][20], struct cartTag c[], int currentUser, int num[], int tempVar, int choice)
{
    int j, k, m;

    switch(choice)
    {   
        //product ID
        case 1: 
                for(k = 0; k < MAX; k++)
                    for(j = 0; j < num[k]; j++)
                        if(i[k][j].productID == tempVar)
                            for(m = 0; m < c[currentUser].countItems; m++)
                                if(c[currentUser].ItemsCart[m].productID == tempVar)
                                    i[k][j].availQuantity -= c[currentUser].ItemsCart[m].availQuantity;
                break;
        //seller ID
        case 2:
                for(k = 0; k < MAX; k++)
                    for(j = 0; j < num[k]; j++)
                        if(i[k][j].sellerID == tempVar)
                            for(m = 0; m < c[currentUser].countItems; m++)
                                if(c[currentUser].ItemsCart[m].sellerID == tempVar && c[currentUser].ItemsCart[m].productID == i[k][j].productID)
                                    i[k][j].availQuantity -= c[currentUser].ItemsCart[m].availQuantity;
                break;
        //All
        case 3:
                for(k = 0 ; k < MAX; k++)
                    for(j = 0; j < num[k]; j++)
                        for(m = 0; m < c[currentUser].countItems; m++)
                            if(i[k][j].productID == c[currentUser].ItemsCart[m].productID)
                                i[k][j].availQuantity -= c[currentUser].ItemsCart[m].availQuantity;

                break;
    }
}

/* 
displayChanges function displays the changes in quantity and price (if theres any) (BUY MENU - checkout)
@param c - 1D array of items in the usercart
@param i - 1D arrays of items
@return - returns nothing (void)
*/
void
displayChanges(struct itemsTag c, struct itemsTag i, int count)
{
    printf("- ITEM NUMBER #%d -\n", count);
    printf("|| OLD ||\n");
    printf("+------------+-----------+------------+\n");
    printf("| %10s | %9s | %10s |\n", "Product ID", "Quantity", "Unit Price"); //header
    printf("+------------+-----------+------------+\n");
    printf("| %10d | %9d | %10.2f |\n", c.productID, c.availQuantity, c.unitPrice);
    printf("+------------+-----------+------------+\n");

    printf("|| NEW ||\n");
    printf("+------------+-----------+------------+\n");
    printf("| %10s | %9s | %10s |\n", "Product ID", "Quantity", "Unit Price"); //header
    printf("+------------+-----------+------------+\n");
    printf("| %10d | %9d | %10.2f |\n", i.productID, i.availQuantity, i.unitPrice);
    printf("+------------+-----------+------------+\n\n");
}

/* 
dsiplayTransaction function displays the summary of each transaction when user checks out specific seller or product (BUY MENU - checkout)
@param pTransaction[][30] - 2D array where the transaction are stored
@param u[] - 1D arrays where users' information are stored
@param current - current user
@param nNum- number of transaction
@param numUsers - number of users
@return - returns nothing (void)
*/
void
displayTransaction (struct transactionsTag pTransaction[][30], struct userTag u[], int current, int nNum, int numUsers, int nTrans)
{
    int j, i;
    float totalPrice[5];
    float sum = 0;

    //saving the name of the user
    for(i = nNum; i < nTrans+1; i++)
        for(j = 0; j < numUsers; j++)
        {
            if(pTransaction[current][i].itemTransaction[0].sellerID == u[j].userID)
                strcpy(pTransaction[current][i].userName, u[j].userName);
            if(pTransaction[current][i].buyerUserID == u[j].userID)
                strcpy(pTransaction[current][i].buyerName, u[j].userName);
        }
    
    for(i = nNum; i < nTrans+1; i++)
    {
        printf("\n+------------+------------+-----------------------+------------+-------------+\n");
        printf("| %10s | %10s | %-21s | %10s | %10s |", "Quantity", "Product ID", "Item Name", "Unit Price", "Total Price"); //header
        for(j = 0; j < 5; j++) //since its limited to only 5 items per transaction
        {
            if(pTransaction[current][i].itemTransaction[j].sellerID != '\0')
            {
                totalPrice[j] = pTransaction[current][i].itemTransaction[j].availQuantity * pTransaction[current][i].itemTransaction[j].unitPrice;
                sum += totalPrice[j];

                printf("\n+------------+------------+-----------------------+------------+-------------+\n");
                printf("| %10d | %10d | %-21s | %10.2f | %10.2f  |", pTransaction[current][i].itemTransaction[j].availQuantity, pTransaction[current][i].itemTransaction[j].productID, pTransaction[current][i].itemTransaction[j].itemName, 
                                                                    pTransaction[current][i].itemTransaction[j].unitPrice, totalPrice[j]);
            }       
        }
        printf("\n+------------+------------+-----------------------+------------+-------------+\n");
		pTransaction[current][i].totalAmount = sum;

        printf("Total Amount Due for the transaction: %.2f\n", pTransaction[current][i].totalAmount);
        printf("Payable to %d - %s\n", pTransaction[current][i].itemTransaction[0].sellerID, pTransaction[current][i].userName);        

        sum = 0;
    }
}

/* 
dsiplayTransaction1 function displays the summary of each transaction when the user checks out all items (BUY MENU - checkout)
@param pTransaction[][30] - 2D array where the transaction are stored
@param u[] - 1D arrays where users' information are stored
@param current - current user
@param nNum- number of transaction
@param numUsers - number of users
@return - returns nothing (void)
*/
void
displayTransaction1 (struct transactionsTag pTransaction[][30], struct userTag u[], int current, int nNum, int numUsers)
{
    int j, i;
    float totalPrice[5];
    float sum = 0;

    //saving the name of the user
    for(i = 0; i < nNum; i++)
        for(j = 0; j < numUsers; j++)
        {
            if(pTransaction[current][i].itemTransaction[0].sellerID == u[j].userID)
                strcpy(pTransaction[current][i].userName, u[j].userName);
            if(pTransaction[current][i].buyerUserID == u[j].userID)
                strcpy(pTransaction[current][i].buyerName, u[j].userName);
        }
    
    for(i = 0; i < nNum; i++)
    {
        printf("\n+------------+------------+-----------------------+------------+-------------+\n");
        printf("| %10s | %10s | %-21s | %10s | %10s |", "Quantity", "Product ID", "Item Name", "Unit Price", "Total Price"); //header
        for(j = 0; j < 5; j++) //since its limited to only 5 items per transaction
        {
            if(pTransaction[current][i].itemTransaction[j].sellerID != '\0')
            {
                totalPrice[j] = pTransaction[current][i].itemTransaction[j].availQuantity * pTransaction[current][i].itemTransaction[j].unitPrice;
                sum += totalPrice[j];

                printf("\n+------------+------------+-----------------------+------------+-------------+\n");
                printf("| %10d | %10d | %-21s | %10.2f | %10.2f  |", pTransaction[current][i].itemTransaction[j].availQuantity, pTransaction[current][i].itemTransaction[j].productID, pTransaction[current][i].itemTransaction[j].itemName, 
                                                                    pTransaction[current][i].itemTransaction[j].unitPrice, totalPrice[j]);
            }       
        }
        printf("\n+------------+------------+-----------------------+------------+-------------+\n");
		pTransaction[current][i].totalAmount = sum;
		//testing
        printf("Total Amount Due for the transaction: %.2f\n", pTransaction[current][i].totalAmount);
        printf("Payable to %d - %s\n", pTransaction[current][i].itemTransaction[0].sellerID, pTransaction[current][i].userName);

        sum = 0;
    }
}

/* 
checkAvailability function checks the new and old quantity and price of the products in the cart (BUY MENU - checkout)
@param aItems[][20] - 2D array where the items are stored
@param userCart[] - 1D array where the items in the cart are stored
@param currentUser - current user of the program
@param i[] - count of items
@return - returns nothing (void)
*/
void
checkAvailability(struct itemsTag aItems[][20], struct cartTag userCart[], int currentUser, int i[])
{
    int nChanges = 0;
    int count = 0;
    int j = 0; 
    int k = 0; 
    int m = 0;

    //check availability (why not create a function)
    for(j = 0; j < MAX; j++)
    {
        for(k = 0; k < i[j]; k++)
        {
            for(m = 0; m < userCart[currentUser].countItems; m++)
            {
                if(aItems[j][k].productID == userCart[currentUser].ItemsCart[m].productID)
                {
                    if(aItems[j][k].unitPrice != userCart[currentUser].ItemsCart[m].unitPrice ||
                        aItems[j][k].availQuantity != userCart[currentUser].ItemsCart[m].availQuantity) //idk abt quantity man
                    {
                        count++;
                        displayChanges(userCart[currentUser].ItemsCart[m], aItems[j][k], count);
                        nChanges = 1;
                    }
                }
            }
        }
    }
    if(nChanges)
        printf("|| You can still go back and edit your cart. ||\n\n");
}

/* 
sellerStorage function copies seller ID to an array (ADMIN MENU)
@param pTransaction[] - 1D array contains all transactions
@param seller[] - 1D array where the seller ID will be stored
return - returns the number of seller
*/
int
sellerStorage(struct transactionsTag pTransaction[], int seller[])
{
    int j;
    int k;

    k = 0;
    for(j = 0; j < MAX; j++)
    {
        seller[k] = pTransaction[j].SellerUserID;
        if(pTransaction[j].SellerUserID != pTransaction[j+1].SellerUserID)
            k++;
    }
    return k;
}

/* 
buyerStorage function copies buyer ID to an array (ADMIN MENU)
@param pTransaction[] - 1D array contains all transactions
@param buyer[] - 1D array where the buyer ID will be stored
return - returns the number of buyer
*/
int
buyerStorage(struct transactionsTag pTransaction[], int buyer[])
{
    int j;
    int k;

    k = 0;
    for(j = 0; j < MAX; j++)
    {
        buyer[k] = pTransaction[j].buyerUserID;
        if(pTransaction[j].buyerUserID != pTransaction[j+1].buyerUserID)
            k++;
    }
    return k;
}