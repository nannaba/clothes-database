//
//  main.cpp
//  teamProject

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 The main file puts everything together and makes the whole project work
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "Clothes.h"
#include "HashTable.h"
#include "BST.h"
using namespace std;

void welcome();
void readFromFile(string fileName, HashTable* &hata, BinarySearchTree* &tree1, BinarySearchTree* &tree2);
void displayMenu();
void processMenu(HashTable* &hata, BinarySearchTree* &tree1, BinarySearchTree* &tree2);
bool insertManager(Clothes &data, HashTable* &hata, BinarySearchTree* &tree1, BinarySearchTree* &tree2);
bool deleteManager(string key, HashTable* &hata, BinarySearchTree* &tree1, BinarySearchTree* &tree2);
bool PrimarySearchManager(string key, HashTable* &hata);
bool SecondarySearchManager(string key, HashTable* &hata);
void listManager(string option, HashTable* &hata, BinarySearchTree* &tree1, BinarySearchTree* &tree2);

// display function to pass to BST traverse functions
void display(Clothes & now)
{
    cout << now.getPrimary() << setw(30) << now.getSecondary() << setw(5) << "$"<< fixed <<setprecision(2)
    << now.getPrice() << setw(15) << now.getMaterial() << setw(15) << now.getType() << endl;
}

int main()
{
    // create hash table and bsts
    HashTable *table = new HashTable(53);
    BinarySearchTree *model =new BinarySearchTree;
    BinarySearchTree *name = new BinarySearchTree;
    
    readFromFile("clothes.txt", table, model, name);
    welcome();
    displayMenu();
    processMenu(table, model, name);
    
    return 0;
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Prints a welcome message
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
void welcome()
{
    cout << "\t\t*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n"
    << "\t\t\t   Welcome to:\n\n"
    << "\t\t     THE CLOTHING DATABASE\n"
    << "\t\t*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*\n"
    << "This program maintains a database of clothes.\n"
    << "The options are below:\n";
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Reads the data from the input file and inserts them into the hash table
 and binary trees
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
void readFromFile(string fileName, HashTable* &hata, BinarySearchTree* &tree1, BinarySearchTree* &tree2)
{
    Clothes dataIn;
    string model, name, type, material;
    double price;
    
    ifstream infile;
    infile.open(fileName);
    
    while(!infile)
    {
        cout << "Error opening " << fileName << " for reading\n";
        exit(111);
    }
    
    while(infile >> model)
    {
        dataIn.setPrimary(model);
        infile >> material;
        dataIn.setMaterial(material);
        infile >> price;
        infile.ignore();
        dataIn.setPrice(price);
        getline(infile, name, ',');
        dataIn.setSecondary(name);
        getline(infile, type, '\n');
        dataIn.setType(type);
        hata->insertHash(dataIn);
        tree1->insert(dataIn);
        tree2->inSecondary(dataIn);
        
    }
    infile.close();
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Displays the menu
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
void displayMenu()
{
    cout << "A - Add new data\n"
    << "D - Delete data\n"
    << "P - Search by primary key\n"
    << "S - Search by secondary key\n"
    << "L - List\n"
    << "W - Write data to file\n"
    << "T - Statistics\n"
    << "H - Help: show the menu again\n"
    << "Q - Quit\n";
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Processes the menu
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
void processMenu(HashTable* &hata, BinarySearchTree* &tree1, BinarySearchTree* &tree2)
{
    string choice;
    do
    {
        cout << "What would you like to do? ";
        cin >> choice;
        
        for(unsigned int i = 0; i < choice.length(); i++)
        {
            choice[i] = toupper(choice[i]);
        }
        
        if(choice == "A")
        {
            Clothes newData;
            string model, name, type, material;
            double price;
            
            cout << "Enter the model number: ";
            cin >> model;
            cin.clear();
            cin.ignore();
            cout << "Enter the name: ";
            getline(cin, name);
            cout << "Enter the type: ";
            cin >> type;
            cin.clear();
            cin.ignore();
            cout << "Enter the material: ";
            cin >> material;
            cin.clear();
            cin.ignore();
            cout << "Enter the price: ";
            cin >> price;
            cin.clear();
            cin.ignore();
            
            newData.setPrimary(model);
            newData.setSecondary(name);
            newData.setType(type);
            newData.setMaterial(material);
            newData.setPrice(price);
            
            bool success = insertManager(newData, hata, tree1, tree2);
            if(success == true)
                cout << "Successfully inserted\n";
            else
                cout << "Unable to insert\n";
        }
        else if(choice == "D")
        {
            string prikey;
            cout << "\nEnter the primary key of the item you want to delete: ";
            cin >> prikey;
            bool success = deleteManager(prikey, hata, tree1, tree2);
            if(success == true)
                cout << "Successfully deleted\n";
            else
                cout << "Unable to delete\n";
        }
        else if(choice == "P")
        {
            string key;
            cout << "\nEnter the primary key: ";
            cin >> key;
            bool success = PrimarySearchManager(key, hata);
            if(success == true)
                cout << "Successfully found\n";
            else
                cout << "Unable to find\n";
        }
        else if(choice == "S")
        {
            string key;
            cout << "\nEnter the secondary key: ";
            cin.clear();
            cin.ignore();
            getline(cin, key);
            bool success = SecondarySearchManager(key, hata);
            if(success == true)
                cout << "Successfully found\n";
            else
                cout << "Unable to find\n";
        }
        else if(choice == "L")
        {
            string option = "";
            
            cout << "\nList has these sub options:\n"
            << "1 - List unsorted data\n"
            << "2 - List data sorted by the primary key\n"
            << "3 - List data sorted by the secondary key\n"
            << "4 - List printed as an indented list\n";
            
            do
            {
                cout << "What would you like to do? ";
                cin >> option;
                
                if(option == "1" || option == "2" || option == "3" || option == "4")
                    listManager(option, hata, tree1, tree2);
                else
                    cout << "The options are 1, 2, 3, and 4\n";
                
            } while(option != "1" && option != "2" && option != "3" && option!="4");
        }
        else if(choice == "W")
        {
            string filename;
            cout << "Enter a filename: ";
            cin >> filename;
            filename += ".txt";
            bool success = hata->saveToFile(filename);
            if(success == true)
                cout << "Successfully written\n";
            else
                cout << "Unable to write\n";
        }
        else if(choice == "T")
        {
            int col = hata->getCollisions();
            int load = hata->getLoadFactor();
            cout << "Load factor: " << load << "%" << endl;
            cout << "Number of collisions: " << col << endl;
        }
        else if(choice == "H")
            displayMenu();
        else if(choice == "Q")
            hata->saveToFile("updatedClothes.txt");
        else
            cout << "Invalid choice" << endl;
    } while(choice != "Q");
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Manages insertion of data to the hash table and binary trees
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
bool insertManager(Clothes &data, HashTable* &hata, BinarySearchTree* &tree1, BinarySearchTree* &tree2)
{
    bool status = false, h, t1, t2;
    h = hata->insertHash(data);
    t1 = tree1->insert(data);
    t2 = tree2->inSecondary(data);
    if(h == true && t1 == true) //&& t2 == true)
        status = true;
    return status;
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Manages deletion of data to the hash table and binary trees
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
bool deleteManager(string key, HashTable* &hata, BinarySearchTree* &tree1, BinarySearchTree* &tree2)
{
    bool status = false, h, t1, t2;
    Clothes deleted;
    h = hata->deleteHash(key, deleted);
    t1 = tree1->remove(key);
    //t2 = tree2->removesec(deleted.getName());
    if(t1 == true)
        status = true;
    return status;
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Manages searching for the primary key
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
bool PrimarySearchManager(string key, HashTable* &hata)
{
    bool status;
    Clothes found;
    status = hata->searchHash(key, found);
    if(status == true)
    {
        cout << found.getPrimary() << setw(20) << found.getSecondary() << setw(5) << "$" << fixed << setprecision(2)
        << found.getPrice() << setw(15) << found.getMaterial() << setw(10) << found.getType() << endl;
    }
    return status;
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Manages searching for the secondary key
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
bool SecondarySearchManager(string key, HashTable* &hata)
{
    bool status;
    Clothes found;
    status = hata->searchSecondary(key, found);
    if(status == true)
    {
        cout << found.getPrimary() << setw(20) << found.getSecondary() << setw(5) << "$" << fixed << setprecision(2)
        << found.getPrice() << setw(15) << found.getMaterial() << setw(10) << found.getType() << endl;
    }
    return status;
}

/**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~
 Manages listing out the data
 There are three options: unsorted, primary, secondary
 **~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~**~~*/
void listManager(string option, HashTable* &hata, BinarySearchTree* &tree1, BinarySearchTree* &tree2)
{
    if(option == "1")
    {
        hata->printHash();
    }
    else if(option == "2")
    {
        tree1->inOrder(display);
    }
    else if(option == "3")
    {
        tree2->inOrder(display);
    }
    else
    {
        cout << "\nPrimary Key\n"
        << "______________________________________________________________________________________\n\n";
        tree1->printlevelOrder(display);
        cout << "\nSecondary Key\n"
        << "______________________________________________________________________________________\n\n";
        tree2->printlevelOrder(display);
    }
}
/*
*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
Welcome to:

THE CLOTHING DATABASE
*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
This program maintains a database of clothes.
The options are below:
A - Add new data
D - Delete data
P - Search by primary key
S - Search by secondary key
L - List
W - Write data to file
T - Statistics
H - Help: show the menu again
Q - Quit
What would you like to do? A
Enter the model number: 1234567891
Enter the name: Summer dress
Enter the type: Dress
Enter the material: cotton
Enter the price: 14.00
Successfully inserted
What would you like to do? L

List has these sub options:
1 - List unsorted data
2 - List data sorted by the primary key
3 - List data sorted by the secondary key
4 - List printed as an indented list
What would you like to do? 1
2000206909      Active Perforated Shorts    $17.95          nylon         bottom
2000133829            Grommet Choker Tee    $12.55         cotton           top
2000260651      Fleece Drawstring Hoodie    $15.90         cotton            top
2000258018                    Knit Dress    $8.95          rayon         dress
2000122281          French Terry Joggers    $25.95          rayon         bottom
2000277919            Knit Pullover Tuni    $11.46      polyester           top
2000270970          Skinny Striped Jeans    $10.00         cotton        bottom
1234567891                  Summer dress    $14.00         cotton          Dress
2000207973           Buffalo Plaid Shirt    $19.95         cotton            top
2000247589               High-Rise Pants    $19.90      polyester        bottom
2000267512         Sweetheart Tube Dress    $20.99      polyester         dress
1000176003           Hoodie Sleeve Scarf    $17.90         cotton   accessories
2000229406             Faux Suede Shorts    $18.45      polyester        bottom
2000241967           Ribbed Skater Dress    $13.29      polyester          dress
2000246830    Contemporary Flounce Dress    $10.00         cotton          dress
1000211930                    Knit Scarf    $5.99        acrylic  accessories
2000149008                Faux Fur Beret    $7.95           wool    accessories
2000240915                Tie-Sleeve Top    $19.90      polyester            top
2000225949         Floral Flare Leggings    $12.45      polyester         bottom
2000277442            Sweater-Knit Dress    $10.00        acrylic         dress
2000257791         Marled Ribbed Sweater    $13.50          rayon           top
2000148632            Floral Shift Dress    $19.90      polyester          dress
2000217049    Contemporary Metallic Cami    $15.90          rayon            top
2000260139        Heathered Knit Joggers    $10.00         cotton        bottom
2000282705               Drape-Front Top    $19.90          rayon           top
2000055578           Classic Woven Shirt    $19.00         cotton            top
What would you like to do? d

Enter the primary key of the item you want to delete: 2000207973
Successfully deleted
What would you like to do? P

Enter the primary key: 2000257791
2000257791Marled Ribbed Sweater    $13.50          rayon      top
Successfully found
What would you like to do? s

Enter the secondary key: Sweetheart Tube Dress
2000267512Sweetheart Tube Dress    $20.99      polyester    dress
Successfully found
What would you like to do? L

List has these sub options:
1 - List unsorted data
2 - List data sorted by the primary key
3 - List data sorted by the secondary key
4 - List printed as an indented list
What would you like to do? 4

Primary Key
______________________________________________________________________________________

1. 2000246830    Contemporary Flounce Dress    $10.00         cotton          dress
2. 2000282705               Drape-Front Top    $19.00          rayon           top
3. 2000247589               High-Rise Pants    $19.00      polyester        bottom
4. 2000260651      Fleece Drawstring Hoodie    $15.00         cotton            top
5. 2000270970          Skinny Striped Jeans    $10.00         cotton        bottom
6. 2000277919            Knit Pullover Tuni    $11.00      polyester           top
7. 2000277442            Sweater-Knit Dress    $10.00        acrylic         dress
6. 2000267512         Sweetheart Tube Dress    $20.00      polyester         dress
5. 2000258018                    Knit Dress    $8.00          rayon         dress
6. 2000260139        Heathered Knit Joggers    $10.00         cotton        bottom
6. 2000257791         Marled Ribbed Sweater    $13.00          rayon           top
2. 2000149008                Faux Fur Beret    $7.00           wool    accessories
3. 2000241967           Ribbed Skater Dress    $13.00      polyester          dress
4. 2000217049    Contemporary Metallic Cami    $15.00          rayon            top
5. 2000225949         Floral Flare Leggings    $12.00      polyester         bottom
6. 2000229406             Faux Suede Shorts    $18.00      polyester        bottom
7. 2000240915                Tie-Sleeve Top    $19.00      polyester            top
5. 2000206909      Active Perforated Shorts    $17.00          nylon         bottom
3. 1000211930                    Knit Scarf    $5.00        acrylic  accessories
4. 2000055578           Classic Woven Shirt    $19.00         cotton            top
5. 2000148632            Floral Shift Dress    $19.00      polyester          dress
6. 2000133829            Grommet Choker Tee    $12.00         cotton           top
7. 2000122281          French Terry Joggers    $25.00          rayon         bottom
5. 1234567891                  Summer dress    $14.00         cotton          Dress
4. 1000176003           Hoodie Sleeve Scarf    $17.00         cotton   accessories

Secondary Key
______________________________________________________________________________________

1. 2000246830    Contemporary Flounce Dress    $10.00         cotton          dress
2. 2000282705               Drape-Front Top    $19.00          rayon           top
3. 2000247589               High-Rise Pants    $19.00      polyester        bottom
4. 2000270970          Skinny Striped Jeans    $10.00         cotton        bottom
5. 2000267512         Sweetheart Tube Dress    $20.00      polyester         dress
6. 2000240915                Tie-Sleeve Top    $19.00      polyester            top
6. 2000277442            Sweater-Knit Dress    $10.00        acrylic         dress
7. 1234567891                  Summer dress    $14.00         cotton          Dress
5. 1000211930                    Knit Scarf    $5.00        acrylic  accessories
6. 2000241967           Ribbed Skater Dress    $13.00      polyester          dress
7. 2000257791         Marled Ribbed Sweater    $13.00          rayon           top
6. 2000258018                    Knit Dress    $8.00          rayon         dress
7. 2000277919            Knit Pullover Tuni    $11.00      polyester           top
7. 1000176003           Hoodie Sleeve Scarf    $17.00         cotton   accessories
4. 2000260651      Fleece Drawstring Hoodie    $15.00         cotton            top
5. 2000260139        Heathered Knit Joggers    $10.00         cotton        bottom
6. 2000148632            Floral Shift Dress    $19.00      polyester          dress
7. 2000133829            Grommet Choker Tee    $12.00         cotton           top
8. 2000122281          French Terry Joggers    $25.00          rayon         bottom
7. 2000225949         Floral Flare Leggings    $12.00      polyester         bottom
5. 2000229406             Faux Suede Shorts    $18.00      polyester        bottom
3. 2000217049    Contemporary Metallic Cami    $15.00          rayon            top
2. 2000149008                Faux Fur Beret    $7.00           wool    accessories
3. 2000207973           Buffalo Plaid Shirt    $19.00         cotton            top
4. 2000055578           Classic Woven Shirt    $19.00         cotton            top
4. 2000206909      Active Perforated Shorts    $17.00          nylon         bottom
What would you like to do? l

List has these sub options:
1 - List unsorted data
2 - List data sorted by the primary key
3 - List data sorted by the secondary key
4 - List printed as an indented list
What would you like to do? 3
2000149008                Faux Fur Beret    $7.00           wool    accessories
2000206909      Active Perforated Shorts    $17.00          nylon         bottom
2000207973           Buffalo Plaid Shirt    $19.00         cotton            top
2000055578           Classic Woven Shirt    $19.00         cotton            top
2000246830    Contemporary Flounce Dress    $10.00         cotton          dress
2000217049    Contemporary Metallic Cami    $15.00          rayon            top
2000282705               Drape-Front Top    $19.00          rayon           top
2000229406             Faux Suede Shorts    $18.00      polyester        bottom
2000260651      Fleece Drawstring Hoodie    $15.00         cotton            top
2000225949         Floral Flare Leggings    $12.00      polyester         bottom
2000148632            Floral Shift Dress    $19.00      polyester          dress
2000122281          French Terry Joggers    $25.00          rayon         bottom
2000133829            Grommet Choker Tee    $12.00         cotton           top
2000260139        Heathered Knit Joggers    $10.00         cotton        bottom
2000247589               High-Rise Pants    $19.00      polyester        bottom
1000176003           Hoodie Sleeve Scarf    $17.00         cotton   accessories
2000258018                    Knit Dress    $8.00          rayon         dress
2000277919            Knit Pullover Tuni    $11.00      polyester           top
1000211930                    Knit Scarf    $5.00        acrylic  accessories
2000257791         Marled Ribbed Sweater    $13.00          rayon           top
2000241967           Ribbed Skater Dress    $13.00      polyester          dress
2000270970          Skinny Striped Jeans    $10.00         cotton        bottom
1234567891                  Summer dress    $14.00         cotton          Dress
2000277442            Sweater-Knit Dress    $10.00        acrylic         dress
2000267512         Sweetheart Tube Dress    $20.00      polyester         dress
2000240915                Tie-Sleeve Top    $19.00      polyester            top
What would you like to do? W
Enter a filename: testClothes
Successfully written
What would you like to do? T
Load factor: 39%
Number of collisions: 5
What would you like to do? Q
*/


/*****************************/
/*    updatedClothes.txt     */
/*****************************/
/*
2000206909      Active Perforated Shorts    $17.95          nylon         bottom
2000133829            Grommet Choker Tee    $12.55         cotton           top
2000260651      Fleece Drawstring Hoodie    $15.90         cotton            top
2000258018                    Knit Dress    $8.95          rayon         dress
2000122281          French Terry Joggers    $25.95          rayon         bottom
2000277919            Knit Pullover Tuni    $11.46      polyester           top
2000270970          Skinny Striped Jeans    $10.00         cotton        bottom
1234567891                  Summer dress    $14.00         cotton          Dress
2000247589               High-Rise Pants    $19.90      polyester        bottom
2000267512         Sweetheart Tube Dress    $20.99      polyester         dress
1000176003           Hoodie Sleeve Scarf    $17.90         cotton   accessories
2000229406             Faux Suede Shorts    $18.45      polyester        bottom
2000241967           Ribbed Skater Dress    $13.29      polyester          dress
2000246830    Contemporary Flounce Dress    $10.00         cotton          dress
1000211930                    Knit Scarf    $5.99        acrylic  accessories
2000149008                Faux Fur Beret    $7.95           wool    accessories
2000240915                Tie-Sleeve Top    $19.90      polyester            top
2000225949         Floral Flare Leggings    $12.45      polyester         bottom
2000277442            Sweater-Knit Dress    $10.00        acrylic         dress
2000257791         Marled Ribbed Sweater    $13.50          rayon           top
2000148632            Floral Shift Dress    $19.90      polyester          dress
2000217049    Contemporary Metallic Cami    $15.90          rayon            top
2000260139        Heathered Knit Joggers    $10.00         cotton        bottom
2000282705               Drape-Front Top    $19.90          rayon           top
2000055578           Classic Woven Shirt    $19.00         cotton            top
 */

/*****************************/
/*    testClothes.txt     */
/****************************/
/*
2000206909      Active Perforated Shorts    $17.95          nylon         bottom
2000133829            Grommet Choker Tee    $12.55         cotton           top
2000260651      Fleece Drawstring Hoodie    $15.90         cotton            top
2000258018                    Knit Dress    $8.95          rayon         dress
2000122281          French Terry Joggers    $25.95          rayon         bottom
2000277919            Knit Pullover Tuni    $11.46      polyester           top
2000270970          Skinny Striped Jeans    $10.00         cotton        bottom
1234567891                  Summer dress    $14.00         cotton          Dress
2000247589               High-Rise Pants    $19.90      polyester        bottom
2000267512         Sweetheart Tube Dress    $20.99      polyester         dress
1000176003           Hoodie Sleeve Scarf    $17.90         cotton   accessories
2000229406             Faux Suede Shorts    $18.45      polyester        bottom
2000241967           Ribbed Skater Dress    $13.29      polyester          dress
2000246830    Contemporary Flounce Dress    $10.00         cotton          dress
1000211930                    Knit Scarf    $5.99        acrylic  accessories
2000149008                Faux Fur Beret    $7.95           wool    accessories
2000240915                Tie-Sleeve Top    $19.90      polyester            top
2000225949         Floral Flare Leggings    $12.45      polyester         bottom
2000277442            Sweater-Knit Dress    $10.00        acrylic         dress
2000257791         Marled Ribbed Sweater    $13.50          rayon           top
2000148632            Floral Shift Dress    $19.90      polyester          dress
2000217049    Contemporary Metallic Cami    $15.90          rayon            top
2000260139        Heathered Knit Joggers    $10.00         cotton        bottom
2000282705               Drape-Front Top    $19.90          rayon           top
2000055578           Classic Woven Shirt    $19.00         cotton            top
*/
