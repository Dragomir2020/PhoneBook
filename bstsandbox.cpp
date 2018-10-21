

#include<iostream>
#include <list>
// Library for BST and PhoneBook
#include <BST.h>
#include <vector>

int main(int argc, char* argv[]){
    
    DataStructures::PhoneBook<DataStructures::Person>* pb = new DataStructures::PhoneBook<DataStructures::Person>();
    
    
    pb->Add("Joey","Gill","+13304925839");
    pb->Add("Sandra","Dragomir","+13303232759");
    pb->Add("Scott","Smith","+13305750128");
    pb->Add("Scott","Dragomir","+13305750193");
    pb->Add("Dillon","Dragomir","+13305750709");
    
    pb->Display();
    
    std::cout << "Found: " << pb->Find("Dillon","Dragomir") << std::endl;
    
    pb->Change("Dillon","Dragomir", "+13305750193");
    
    std::cout << "Changed: " << "Dillon, Dragomir, +13305750193" << std::endl;
    
    std::cout << "Found: " << pb->Find("Dillon","Dragomir") << std::endl;
    
    std::cout << "Found(Gill Joey): " << pb->Find("Joey","Gill") << std::endl;
    
    //pb->Delete("Dillon", "Dragomir");
    
    pb->Delete("Joey", "Gill");
    
    std::cout << "Found(Joey Gill): " << pb->Find("Joey","Gill") << std::endl;
    
    std::cout << "Found(Scott Smith): " << pb->Find("Scott","Smith") << std::endl;
    
    // Redundant but shows how to delete
    delete pb;
    
    return 0;
}





