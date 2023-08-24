/*********************************************************************************************************  
This is to certify that this project is our own work, based on our personal efforts in studying and applying the concepts learned.  We 
have constructed the functions and their respective algorithms and corresponding code by ourselves.  The program was run, tested, 
and debugged by our own efforts.  We further certify that we have not copied in part or whole or otherwise plagiarized the work of other 
students and/or persons. 
                                                                                    Reina Althea C. Garcia, DLSU ID# 12276502  
																					Isabelle Turla, DLSU ID# 12209201																			
*********************************************************************************************************/ 

#include "functionMPc.c"

int main()
{
    FILE *pUsers;
    FILE *pItems;
    FILE *pCart;
    FILE *ptrTransaction;
    
    struct userTag aUsers[MAX]; //list of users
    struct itemsTag aItems[MAX][20]; //list of items per user
    struct cartTag userCart[MAX]; //cart per user
    struct transactionsTag pTransaction[MAX][30];
    struct dateTag aDate;
    //temp
    struct dateTag tempDateStart;
    struct dateTag tempDateEnd;
    struct transactionsTag aTransaction[MAX]; //storage of all transaction

    string10 tempUserPassword;
    string10 tempAdminPassword;
    string15 tempCategory;
    string15 keyword;
    string20 cartID; //filename for user's cart

    char cDump;
    int nChoice;
    int tempSellerID;
    int tempUserID;
    int tempProductID;
    int tempQuantity;
    int userMatched = 0;
    int sellerMatched = 0;
    int itemsMatched = 0;
    int cartMatched = 0;
    int quantityAdded;
    int product;
    int nFound = 0; //checks if the user exists already
    int nNum = 0; //number of users
    int i[MAX] = {0}; //number of items per user (initialized everything to 0)
    int j, k, m; //for loop iterations
    int currentUser;
    int storeVar2;
    int storeVar;
    int newData; //new users (that are not part of the previous users)
    int end = 0;
    int length; //storing the length
    int nTrans = 0; //number of items in the transaction
    int transaction = 0; //number of transaction
    //testing
    int newTrans;
    int loop;
    int seller[MAX];
    int buyer[MAX];

    pUsers = fopen("users.txt", "r");
    pItems = fopen("items.txt", "r");

    initializedNull(aUsers);
    initializedNull1(aItems);
    initializedNullCart(userCart);

    //reading (if file exists)
    j = 0;
    if(pUsers != NULL)
    {
        rewind(pUsers); //puts back the file pointer at the start of the file
        
        // (!feof(pUsers)) //buggy
        while(fscanf(pUsers, "%d%c%s%c",  &aUsers[j].userID, &cDump, aUsers[j].password, &cDump) == 4)
        {
            //printf("users: entered here\n"); //debugging

            //-- (removes white space)
            fgets(aUsers[j].userName, 21, pUsers);
            length = strlen(aUsers[j].userName);
            aUsers[j].userName[length-1] = '\0';
            //--(removes white space)
            fgets(aUsers[j].address, 31, pUsers);
            length = strlen(aUsers[j].address);
            aUsers[j].address[length-1] = '\0';
            //--
            fscanf(pUsers, "%I64d%c%c", &aUsers[j].contactNumber, &cDump, &cDump);
            
		    j++;
            nNum++;
        }
        newData = nNum;

        fclose(pUsers);
    }
    else 
    {
        pUsers = fopen("users.txt", "w");
        newData = nNum;
    }

    if(pItems != NULL)
    {
        rewind(pItems);
        readItemsFile(pItems, aItems, i);
        fclose(pItems);
    }
    else pItems = fopen("items.txt", "w");

    //program proper
    if(pUsers != NULL && pItems != NULL)
    {
        do
        {
            //system("cls"); 
            displayMenu();
            scanf("%d", &nChoice);
            printf("\n");

            if(nNum < 1 && nChoice == 2)
                printf("There are no registered user yet\n\n");
            else
            switch (nChoice)
            {
                //Register as a user//
                case 1: 
                        //system("cls");

                        if(nNum == 100)  
                            printf("Max # of users reached!\n");
                        else
                        {
                            printf("\n|| Register as a user ||");
                            printf("\nEnter user ID: ");
                            scanf("%d", &tempUserID);

                            for(j = 0; j < MAX; j++)
                                if(aUsers[j].userID == tempUserID)
                                    nFound = 1;
                            
                            if (nFound)
                                printf("\n|| The given User ID exist already! ||");
                            else
                            {
                                aUsers[nNum].userID = tempUserID;
                                getUserInfo(&aUsers[nNum]);
                                nNum++;
                            }
                            
                            nFound = 0;
                        }
                        printf("\n");

                        // system("pause");
                        // system("cls"); 
                        break;

                //User Menu//
                case 2: 
                        //system("cls"); 

                        printf("\n|| USER MENU ||\n");
                        printf("Enter UserID: ");
                        scanf("%d%c", &tempUserID, &cDump);
                        printf("Enter Password: ");
                        getString(tempUserPassword);

                        for(j = 0; j < MAX && !userMatched; j++)
                        {
                            if(aUsers[j].userID == tempUserID && strcmp(aUsers[j].password, tempUserPassword) == 0)
                            { 
                                userMatched = 1;
                                currentUser = j;
                            }
                        }
                        if(userMatched)
                        {
                            do
                            {
                                //system("cls"); 
                                displayUserMenu();
                                scanf("%d", &nChoice);
                                printf("\n");
                                switch (nChoice)
                                {
                                    //Sell Menu
                                    case 1: 
                                            do
                                            {
                                                //system("cls");
                                                displaySellMenu();
                                                scanf("%d", &nChoice);
                                                printf("\n");
                                                switch (nChoice)
                                                {
                                                    //Add New Item
                                                    case 1:
                                                            printf("|| Add New Item ||\n");
                                                            if (i[currentUser] < 20)
                                                            {
                                                                printf("Enter Product ID: ");
                                                                scanf("%d%c", &tempProductID, &cDump);

                                                                for(j = 0; j < MAX; j++)
                                                                    for(k = 0; k < 20; k++)
                                                                        if(aItems[j][k].productID == tempProductID)
                                                                            nFound = 1;

                                                                if(nFound)
                                                                    printf("Product Already Exists!\n");
                                                                else
                                                                {
                                                                    aItems[currentUser][i[currentUser]].sellerID = aUsers[currentUser].userID;
                                                                    aItems[currentUser][i[currentUser]].productID = tempProductID;

                                                                    getItemInfo(&aItems[currentUser][i[currentUser]]);
                                                                    i[currentUser]++; //i means count of items added
                                                                }

                                                            }    
                                                            else printf("Can't add items anymore!\n");
                                                            
                                                            nFound = 0;

                                                            //system("pause");
                                                            break;
                                        
                                                    //Edit Stock
                                                    case 2: 
                                                            if (i[currentUser] > 0)
                                                            {
                                                                //system("cls");

                                                                printf("|| Edit Stock ||\n");
                                                                sortProductID(aItems, i[currentUser], currentUser);                                                                

                                                                printf("items: %d\n", i[currentUser]);
                                                                displayTable(aItems, i[currentUser], currentUser);
                                                                
                                                                printf("\nEnter Product ID to be edited: ");
                                                                scanf("%d", &tempProductID);

                                                                for(j = 0; j < i[currentUser]; j++) //check if correct
                                                                {
                                                                    if(aItems[currentUser][j].productID == tempProductID)
                                                                    {
                                                                        itemsMatched = 1;
                                                                        product = j; //index of the product
                                                                    }
                                                                }

                                                                if(itemsMatched)
                                                                {
                                                                    do
                                                                    {
                                                                        //system("cls");

                                                                        displayEditStock();
                                                                        scanf("%d", &nChoice);
                                                                        scanf("%c", &cDump);
                                                                        printf("\n");
                                                                        switch (nChoice)
                                                                        {
                                                                            //Replenish
                                                                            case 1: 
                                                                                    printf("How many quantity will be added? ");
                                                                                    scanf("%d", &quantityAdded);

                                                                                    aItems[currentUser][product].availQuantity += quantityAdded;

                                                                                    //system("cls");
                                                                                    displayTable(aItems, i[currentUser], currentUser);


                                                                                    break;
                                                                            //Change Price
                                                                            case 2: 
                                                                                    printf("What will be the new price? ");
                                                                                    scanf("%f", &aItems[currentUser][product].unitPrice);

                                                                                    //system("cls");
                                                                                    displayTable(aItems, i[currentUser], currentUser);

                                                                                    break;
                                                                            //Change Item Name
                                                                            case 3: 
                                                                                    printf("What will be the new name? ");
                                                                                    getItemString(&aItems[currentUser][product], 1);
                                                                                    
                                                                                    //system("cls");
                                                                                    displayTable(aItems, i[currentUser], currentUser);
                                                                                    
                                                                                    break;
                                                                            //Change Category
                                                                            case 4: 
                                                                                    printf("What will be the new category? ");
                                                                                    getItemString(&aItems[currentUser][product], 2);

                                                                                    //system("cls");
                                                                                    displayTable(aItems, i[currentUser], currentUser);

                                                                                    break;
                                                                            //Change Description
                                                                            case 5: 
                                                                                    printf("What will be the new description? ");
                                                                                    getItemString(&aItems[currentUser][product], 3);

                                                                                    //system("cls");
                                                                                    displayTable(aItems, i[currentUser], currentUser);

                                                                                    break;
                                                                            //Finish Editing
                                                                            case 6: break;
                                                                            default: printf("|| Invalid menu option ||\n");
                                                                        }
                                                                    } while (nChoice != 6);
                                                                    
                                                                }
                                                                else if (itemsMatched == 0)
                                                                    printf("\n|| Invalid Product ID! ||\n\n");
                                                                
                                                            }
                                                            else printf("\n|| No stock yet. ||\n");

                                                            itemsMatched = 0;
                                                            
                                                            //system("pause");
                                                            break;
                                                    
                                                    //Show My Products
                                                    case 3: 
                                                            //system("cls");

                                           
            
                                                            printf("|| Show My Products ||\n");
															
															for(j = 0; j < MAX; j++)
															{
																//used aUsers to check since its the same seller ID (same placement in arrays as well)
																if(aItems[j][0].sellerID == aUsers[currentUser].userID)
																{
																	sellerMatched = 1;
																	storeVar = j;
																}
																
                                                            }
															
															if(sellerMatched)
                                                            {
                                                                printf("\nSELLER ID: %d\n", tempSellerID);
                                                                sortProductID(aItems, i[storeVar], storeVar);
                                                                displayTable(aItems, i[storeVar], storeVar);
                                                            }
                                                            else printf("\nNo stock yet.\n");

                                                            sellerMatched = 0;
															
                                                           

                                                            //system("pause");
                                                            break;

                                                    //Show My Low Stocks
                                                    case 4: 
                                                            //system("cls");
                                                            printf("|| Show Low Products ||\n");

                                                            showLowStock(aItems, i[currentUser], currentUser);
                                                            
                                                            break;

                                                    //Exit Sell Menu
                                                    case 5: break;
                                                    default: printf("Invalid menu option\n\n");
                                                }
                                            } while (nChoice != 5);
                                            break;
                                    //Buy Menu
                                    case 2: 

                                            sprintf(cartID, "%d", aUsers[currentUser].userID); // "converts" integer to string
                                            strcat(cartID, ".bag.txt");

                                            pCart = fopen(cartID, "r");
                                            if(pCart)
                                            {
                                                rewind(pCart);
                                                readCartFile(pCart, userCart, currentUser);
                                                fclose(pCart);
                                            }

                                            //system("pause");

                                            do
                                            {
                                                //system("cls");

                                                displayBuyMenu();
                                                scanf("%d", &nChoice);
                                                printf("\n");

                                                switch(nChoice)
                                                {
                                                    //Display All Products (from different sellers)
                                                    case 1: 

                                                            printf("\n|| Display All Products ||\n");
                                                            displayAllProducts(aItems, i);

                                                            break;

                                                    //Show All Products by a Specific Seller
                                                    case 2: 
                                                            printf("Enter Seller ID that you wish to find: ");
                                                            scanf("%d", &tempSellerID);
															
															sellerMatched = 0;

                                                            for(j = 0; j < MAX; j++)
															{
																//used aUsers to check since its the same seller ID (same placement in arrays as well)
																if(aItems[j][0].sellerID == tempSellerID)
																{
																	sellerMatched = 1;
																	storeVar = j;
																}
																
                                                            }       

                                                            if(sellerMatched)
                                                            {
                                                                printf("\nSELLER ID: %d\n", tempSellerID);
                                                                sortProductID(aItems, i[storeVar], storeVar);
                                                                displayTable(aItems, i[storeVar], storeVar);
                                                            }
                                                            else printf("|| Did not find any user. ||\n");

                                                            sellerMatched = 0;
                                                            
                                                            //system("pause");
                                                            break;

                                                    //Search Products by Category 
                                                    case 3: 
                                                            printf("Enter category you want to see: ");
                                                            scanf("%c", &cDump);
                                                            getString(tempCategory);
                                                            

                                                            for(k = 0; k < MAX; k++)
                                                                if(aItems[k][0].sellerID != '\0')
                                                                    showCategory(aItems, i[k], k, tempCategory);

                                                            //system("pause");
                                                            break;

                                                    //Search by Name
                                                    case 4: 
                                                            
                                                            printf("Enter keyword you want to see: ");
                                                            scanf("%c", &cDump);
                                                            getString(keyword);
                                                            
                                                            for(k = 0; k < MAX; k++)
                                                                if(aItems[k][0].sellerID != '\0')
                                                                    showByName(aItems, i[k], k, keyword);

                                                            //system("pause");
                                                            break;
                                                            
                                                    //Add to Cart
                                                    case 5: 
                                                            if(userCart[currentUser].countItems < 10)
                                                            {
                                                                printf("|| Add To Cart ||\n");
                                                                printf("Enter product ID: ");
                                                                scanf("%d", &tempProductID);

                                                                printf("Enter quantity: ");
                                                                scanf("%d", &tempQuantity);

                                                                for(k = 0; k < userCart[currentUser].countItems; k++)
                                                                    if(userCart[currentUser].ItemsCart[k].productID == tempProductID)
                                                                        cartMatched = 1;

                                                                if(!cartMatched)
                                                                {
                                                                    for(k = 0; k < MAX; k++)
                                                                    {
                                                                        for(j = 0; j < i[k]; j++) //loop the number of items
                                                                        {
                                                                            if(aItems[k][j].productID == tempProductID) //checking if the product exist
                                                                            {
                                                                                if(aItems[k][j].availQuantity >= tempQuantity) //checking if the quantity is available
                                                                                {
                                                                                    if(aUsers[currentUser].userID != aItems[k][j].sellerID) //checking if the buyer != seller
                                                                                    {
                                                                                        storeVar = j; //index of the specific variable
                                                                                        storeVar2 = k; //user
                                                                                        itemsMatched = 1;
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                    
                                                                    if(itemsMatched)
                                                                    {
                                                                        printf("|| Item added to cart successfully! ||\n");
                                                                        //copying every information to the new userCart (they have same struct)
                                                                        userCart[currentUser].ItemsCart[userCart[currentUser].countItems] = aItems[storeVar2][storeVar];

                                                                        userCart[currentUser].ItemsCart[userCart[currentUser].countItems].availQuantity = tempQuantity;
                                                                        userCart[currentUser].countItems++;
                                                                    }
                                                                    else printf("|| items did not match! ||\n");
                                                                    itemsMatched = 0;
                                                                }
                                                                else printf("|| Item is in cart already! ||\n");
                                                                cartMatched = 0;
                                                            }
                                                            else printf("|| Cart is full already. You may choose to proceed to Edit Cart or Check Out before adding any items. ||\n");

                                                            //system("pause");
                                                            break;

                                                    //Edit Cart
                                                    case 6: 
                                                            do
                                                            {
                                                                //system("cls");

                                                                sortSellerID1(userCart[currentUser].ItemsCart, userCart[currentUser].countItems); 
                                                                
                                                                //printf("%d\n", userCart[currentUser].countItems); //debugging
                                                                for(j = 0; j < userCart[currentUser].countItems; j++)
                                                                {
                                                                    displayCart1(userCart[currentUser].ItemsCart, j);
                                                                }

                                                                displayEditCart();
                                                                scanf("%d", &nChoice);
                                                                printf("\n");

                                                                switch(nChoice)
                                                                {
                                                                    //delete all product from one seller
                                                                    case 1: 
                                                                            printf("Enter SELLER ID: ");
                                                                            scanf("%d", &tempSellerID);

                                                                            deleteContents(userCart, currentUser, tempSellerID, 1);

                                                                            break;

                                                                    //delete specific item from seller
                                                                    case 2: 
                                                                            printf("Enter Product ID: ");
                                                                            scanf("%d", &tempProductID);
                                                                            
                                                                            deleteContents(userCart, currentUser, tempProductID, 2);

                                                                            break;
                                                                    
                                                                    //change quantity
                                                                    case 3: 
                                                                            printf("Enter Product ID: ");
                                                                            scanf("%d", &tempProductID);

                                                                            printf("Enter New Quantity: ");
                                                                            scanf("%d", &tempQuantity);

                                                                            if(checkItems(aItems, i, tempProductID, tempQuantity))
                                                                                changeQuantity(userCart, currentUser, tempProductID, tempQuantity);
                                                                            else printf("|| ERROR ||\n");

                                                                            //system("pause");
                                                                            break;

                                                                    //return 
                                                                    case 4: break;
                                                                }
                                                            } while (nChoice != 4);
                                                            
                                                            break;
                                                    //Check Out Menu
                                                    case 7: 

                                                            ptrTransaction = fopen("transaction.txt", "a");
                                                            do
                                                            {
                                                                getDate(&aDate);
                                                                checkAvailability(aItems, userCart, currentUser, i);

                                                                // system("pause");
                                                                // system("cls"); 

                                                                displayCheckOutMenu();
                                                                scanf("%d", &nChoice);
                                                                printf("\n");

                                                                switch(nChoice)
                                                                {
                                                                    //All items in the cart will be brought by the buyer
                                                                    case 1: 
                                                                            k = 0; //for looping of items 
                                                                            m = 0; //m is for counting of cart items
                                                                                                                        
                                                                            sortSellerID1(userCart[currentUser].ItemsCart, userCart[currentUser].countItems);

                                                                            while(m < userCart[currentUser].countItems)
                                                                            {
                                                                                //check each items in the cart
                                                                                if(userCart[currentUser].ItemsCart[k].sellerID != '\0')
                                                                                {
                                                                                    //check if ntrans == 5
                                                                                    //if yes, then it means new transaction
                                                                                    if(nTrans == 5)
                                                                                    {
                                                                                        transaction++;
                                                                                        nTrans = 0;
                                                                                    }

                                                                                    pTransaction[currentUser][transaction].itemTransaction[nTrans] = userCart[currentUser].ItemsCart[k];
                                                                                    
                                                                                    pTransaction[currentUser][transaction].SellerUserID = userCart[currentUser].ItemsCart[k].sellerID;
                                                                                    pTransaction[currentUser][transaction].buyerUserID = aUsers[currentUser].userID;
                                                                                    pTransaction[currentUser][transaction].date = aDate; 

                                                                                    //check whether the current and the next item in the cart has different seller
                                                                                    //if yes, then it means new transaction
                                                                                    if(userCart[currentUser].ItemsCart[k].sellerID != userCart[currentUser].ItemsCart[k+1].sellerID)
                                                                                    {
                                                                                        transaction++; //meaning new transaction
                                                                                        nTrans = 0; //start storing at index 0
                                                                                        m++;
                                                                                        k++;
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        nTrans++;
                                                                                        k++;
                                                                                        m++;
                                                                                    }
                                                                                }
                                                                                else
                                                                                {
                                                                                    k++; 
                                                                                    m++;
                                                                                }
                                                                            }
                                                                            nTrans = transaction;

                                                                            displayTransaction1(pTransaction, aUsers, currentUser, nTrans, nNum); //displays
                                                                            writeTransanctionFile1(ptrTransaction, pTransaction, currentUser, transaction); //write to file
                                                                            changeQuantityCO(aItems, userCart, currentUser, i, 0, 3); //change the quantity
                                                                            deleteContents(userCart, currentUser, userCart[currentUser].countItems, 3); //delete items in cart

                                                                            transaction++;

                                                                            break;

                                                                    //Check Out Specific Seller
                                                                    case 2:
                                                                            printf("\nEnter seller ID you want to buy from: ");
                                                                            scanf("%d", &tempSellerID);

                                                                            for(j = 0; j < userCart[currentUser].countItems; j++)
                                                                                if(userCart[currentUser].ItemsCart[j].sellerID == tempSellerID)
                                                                                    nFound = 1;

                                                                            if(nFound)
                                                                            {
                                                                                sortSellerID1(userCart[currentUser].ItemsCart, userCart[currentUser].countItems);

                                                                                nTrans = 0; newTrans = 0;

                                                                                for(j = 0; j < userCart[currentUser].countItems; j++)
                                                                                {
                                                                                    if(userCart[currentUser].ItemsCart[j].sellerID == tempSellerID)
                                                                                    {
                                                                                        if(nTrans == 5)
                                                                                        {
                                                                                            transaction++;
                                                                                            newTrans++;
                                                                                            nTrans = 0;
                                                                                        }

                                                                                        pTransaction[currentUser][transaction].itemTransaction[nTrans] = userCart[currentUser].ItemsCart[j];
                                                                                                                                                                            
                                                                                        pTransaction[currentUser][transaction].SellerUserID = userCart[currentUser].ItemsCart[j].sellerID;
                                                                                        pTransaction[currentUser][transaction].buyerUserID = aUsers[currentUser].userID;
                                                                                        pTransaction[currentUser][transaction].date = aDate; 
                                                                                        nTrans++;               
                                                                                    }
                                                                                }
                                                                                
                                                                                displayTransaction(pTransaction, aUsers, currentUser, transaction-newTrans, nNum, transaction);
                                                                                writeTransanctionFile(ptrTransaction, pTransaction, currentUser, transaction-newTrans, transaction);
                                                                                changeQuantityCO(aItems, userCart, currentUser, i, tempSellerID, 2);
                                                                                deleteContents(userCart, currentUser, tempSellerID, 1);

                                                                                transaction++; //increment for the next transaction
                                                                            }
                                                                            else printf("|| Seller ID Not Found! ||\n");

                                                                            nFound = 0;                                                                       
                                                                            break;

                                                                    //specific product ID
                                                                    case 3: 

                                                                            printf("\nEnter product ID you want to buy: ");
                                                                            scanf("%d", &tempProductID);

                                                                            for(j = 0; j < userCart[currentUser].countItems; j++)
                                                                                if(userCart[currentUser].ItemsCart[j].productID == tempProductID)
                                                                                    nFound = 1;

                                                                            if(nFound == 1)
                                                                            {
                                                                                sortSellerID1(userCart[currentUser].ItemsCart, userCart[currentUser].countItems);

                                                                                nTrans = 0;

                                                                                for(j = 0; j < userCart[currentUser].countItems; j++)
                                                                                {
                                                                                    if(userCart[currentUser].ItemsCart[j].productID == tempProductID)
                                                                                    {                             //transaction variable means pang-ilang transaction na ng current user
                                                                                        pTransaction[currentUser][transaction].itemTransaction[nTrans] = userCart[currentUser].ItemsCart[j];
                                                                                                                                                                               
                                                                                        pTransaction[currentUser][transaction].SellerUserID = userCart[currentUser].ItemsCart[j].sellerID;
                                                                                        pTransaction[currentUser][transaction].buyerUserID = aUsers[currentUser].userID;
                                                                                        pTransaction[currentUser][transaction].date = aDate; 
                                                                                        nTrans++;
                                                                                    }
                                                                                }
                                                                                
                                                                                displayTransaction(pTransaction, aUsers, currentUser, transaction, nNum, transaction); //displaying properly
                                                                                writeTransanctionFile(ptrTransaction, pTransaction, currentUser, transaction, transaction);
                                                                                changeQuantityCO(aItems, userCart, currentUser, i, tempProductID, 1);
                                                                                deleteContents(userCart, currentUser, tempProductID, 2);

                                                                                transaction++;
                                                                            }
                                                                            else printf("|| Product ID Not Found! ||\n");
                                                                            
                                                                            nFound = 0;
                                                                            break;

                                                                    //EXIT
                                                                    case 4: 
                                                                            fclose(ptrTransaction);
                                                                            break;
                                                                }
                                                            } while (nChoice > 4 && nChoice < 1); //goes back to BUY MENU
                                                            
                                                            break; //break for case 7
                                                            
                                                    //Exit Buy Menu
                                                    case 8: break;
                                                }
                                            } while(nChoice != 8);
                                            break;
                                    //Exit User Menu
                                    case 3:          
                                            sortSellerID1(userCart[currentUser].ItemsCart, userCart[currentUser].countItems);

                                            //w for over[writing] (for changes to be recorded)
                                            pCart = fopen(cartID, "w");
                                            if(pCart)
                                            {
                                                writingCartFile(pCart, userCart, currentUser);
                                                fclose(pCart);
                                            }
                                            
                                            break;
                                    default: printf("|| Invalid menu option! ||\n\n");
                                }
                            } while (nChoice != 3);
                        }
                        else
                            printf("\n|| ERROR! Does not match any registered user! ||\n");

                        userMatched = 0;
                        break;

                //Admin Menu
                case 3: 
                        //system("cls");

                        printf("\n|| ADMIN MENU ||\n");
                        printf("Enter password: ");
                        scanf("%s", tempAdminPassword);

                        if(strcmp(tempAdminPassword, "H3LLo?") == 0)
                        {
                            ptrTransaction = fopen("transaction.txt", "r");
                            readTransactionFile(ptrTransaction, aTransaction);
                            fclose(ptrTransaction);
                            
                            do
                            {
                                //system("cls");

                                displayAdminMenu();
                                scanf("%d", &nChoice);
                                printf("\n");

                                switch(nChoice)
                                {
                                    case 1: 
                                            //system("cls");

                                            printf("|| Show All Users ||\n");
                                            if(nNum > 0)
                                                displayUserTable(aUsers, nNum);
                                            else
                                                printf("\n|| No Users Yet! ||\n");

                                            //system("pause");
                                            break;

                                    case 2:                                    
                                            //system("cls");

                                            printf("|| Show All Sellers ||\n");
                                            displaySellerTable(aUsers, aItems, i);

                                            //system("pause");
                                            break;
                                            
                                    case 3: 
                                            //system("cls");

                                            printf("|| Show Total Sales Duration ||\n");
                                            printf("\nSTART DATE:\n");
                                            getDate(&tempDateStart);
                                            printf("\nEND DATE:\n");
                                            getDate(&tempDateEnd);

                                            showTotalSales(aTransaction, tempDateStart, tempDateEnd);

                                            //system("pause");
                                            break;

                                    case 4: 
                                            //system("cls");

                                            printf("|| Show Seller Sales ||");
                                            printf("\nSTART DATE:\n");
                                            getDate(&tempDateStart);
                                            printf("\nEND DATE:\n");
                                            getDate(&tempDateEnd);

                                            printf("|| Show Seller Sales ||");
                                            sortSellerIDTransaction(aTransaction, MAX);
                                            k = sellerStorage(aTransaction, seller);
                                            displaySellerSales(aTransaction, tempDateStart, tempDateEnd, seller, k);

                                            //system("pause");
                                            break;

                                    case 5: 
                                            //system("cls");

                                            printf("|| Show Shopaholics ||\n");
                                            printf("\nSTART DATE:\n");
                                            getDate(&tempDateStart);
                                            printf("\nEND DATE:\n");
                                            getDate(&tempDateEnd);

                                            printf("|| Show Shopaholics ||");
                                            sortBuyerIDTransaction(aTransaction, MAX);
                                            k = buyerStorage(aTransaction, buyer);
                                            displayShopaholics(aTransaction, tempDateStart, tempDateEnd, buyer, k);

                                            //system("pause");
                                            break;

                                    //exit
                                    case 6: break;
                                }
                            } while(nChoice != 6);
                        }
                        else
                            printf("|| Unauthorized access not allowed ||\n");
                        
                        //system("pause");
                        break;
                //EXIT
                case 4: 
                        end = 1;

                        break;
                //Incorrect input
                default: printf("|| Invalid menu option ||\n\n");
            }
        } while (nChoice != 4);

        fclose(pUsers);
        fclose(pItems);
        
    }

    //saving everyhing in a file (USERS AND ITEMS)
    if(end)
    {
        pUsers = fopen("users.txt", "a");
        if(pUsers)
        {
            writeToFileUsers(pUsers, aUsers, nNum, newData);
            fclose(pUsers); //closing for appending
        }
        else printf("error\n");

        //w for [over]writing (in case there are changes in previously saved items)
        pItems = fopen("items.txt", "w");
        if(pItems)
        {
            for(loop = 0; loop < MAX; loop++)
                if(i[loop] != '\0')
                    sortSellerID(aItems, i[loop], loop);

            writeToFileItems(pItems, aItems, i);
            fclose(pItems);
        }
    }
    
    return 0;
}