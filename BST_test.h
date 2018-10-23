#ifndef BST_TEST_H
#define BST_TEST_H

#include "BST.h"
#include <string>
// Needed for space removal.
#include <sstream>
#include <algorithm>
#include <cxxtest/TestSuite.h>
#include <ctime>

//NEW FUNCTIONALITY
class PhoneBook : public CxxTest::TestSuite {
public:
    // Test the add functionality
	void testAdd1(){
        DataStructures::PhoneBook<DataStructures::Person>* pb = new DataStructures::PhoneBook<DataStructures::Person>();
        pb->Add("Joey","Gill","+13304925839");
        pb->Add("Sandra","Dragomir","+13303232759");
        pb->Add("Scott","Smith","+13305750128");
        pb->Add("Scott","Dragomir","+13305750193");
        pb->Add("Dillon","Dragomir","+13305750709");
	    TS_ASSERT(pb->Find("Joey","Gill") == "+13304925839");
        delete pb;
	}
    
    // Test the delete functionality
    void testDelete1(){
        DataStructures::PhoneBook<DataStructures::Person>* pb = new DataStructures::PhoneBook<DataStructures::Person>();
        pb->Add("Joey","Gill","+13304925839");
        TS_ASSERT(pb->Count() == 1);
        pb->Add("Sandra","Dragomir","+13303232759");
        TS_ASSERT(pb->Count() == 2);
        pb->Delete("Sandra", "Dragomir");
        TS_ASSERT(pb->Count() == 1);
        TS_ASSERT(pb->Find("Sandra","Dragomir") == "-1");
        pb->Delete("Joey", "Gill");
        TS_ASSERT(pb->Find("Joey","Gill") == "-1");
        TS_ASSERT(pb->Count() == 0);
        delete pb;
    }
    
    // Add node and delete it
    void testDelete2(){
        DataStructures::PhoneBook<DataStructures::Person>* pb = new DataStructures::PhoneBook<DataStructures::Person>();
        pb->Add("Joey","Gill","+13304925839");
        TS_ASSERT(pb->Count() == 1);
        TS_ASSERT(pb->Find("Joey","Gill") == "+13304925839");
        pb->Delete("Joey", "Gill");
        TS_ASSERT(pb->Count() == 0);
        TS_ASSERT(pb->Find("Joey","Gill") == "-1");
        delete pb;
    }
	
    void testDelete3(){
	DataStructures::PhoneBook<DataStructures::Person>* pb = new DataStructures::PhoneBook<DataStructures::Person>();
	pb->Add("Joey","Gill","+13304925839");
	pb->Add("Bob","Dylan","+13304925839");
	pb->Add("Gram","Nap","+13304925839");
	pb->Add("Hello","World","+13304925834");
	pb->Add("Sandra","Mech","+13304925839");
	pb->Add("Low","Down","+13304925839");
	pb->Delete("Joey", "Gill");
	pb->Delete("Sandra", "Mech");
	pb->Delete("Gram", "Nap");
	pb->Delete("Low", "Down");
	pb->Delete("Bob", "Dylan");
	TS_ASSERT(pb->Count() == 1);
	delete pb;
    }
    
    // Test the count
    void testCount1(){
        DataStructures::PhoneBook<DataStructures::Person>* pb = new DataStructures::PhoneBook<DataStructures::Person>();
        pb->Add("Joey","Gill","+13304925839");
        TS_ASSERT(pb->Count() == 1);
        pb->Add("Sandra","Dragomir","+13303232759");
        TS_ASSERT(pb->Count() == 2);
        pb->Delete("Sandra", "Dragomir");
        TS_ASSERT(pb->Count() == 1);
        delete pb;
    }
    
    // Test find
    // With nothing in list
    void testFind1(){
        DataStructures::PhoneBook<DataStructures::Person>* pb = new DataStructures::PhoneBook<DataStructures::Person>();
        TS_ASSERT(pb->Find("first","last") == "-1");
        delete pb;
    }
    // Insert and delete
    void testFind2(){
        DataStructures::PhoneBook<DataStructures::Person>* pb = new DataStructures::PhoneBook<DataStructures::Person>();
        pb->Add("first","last","+13304925839");
        TS_ASSERT(pb->Find("first","last") == "+13304925839");
         pb->Delete("first", "last");
        TS_ASSERT(pb->Find("first","last") == "-1");
        delete pb;
    }
    
    // TEST BST Main Functionality
    // Insert and delete
    void testBBST1(){
        DataStructures::Tree::BST<DataStructures::Person>* bst = new DataStructures::Tree::BST<DataStructures::Person>();
        DataStructures::Person* p1 = new DataStructures::Person("first","last","+13304925839");
        bst->add(p1);
        TS_ASSERT(bst->get(p1)->phoneNumber == "+13304925839");
        delete p1;
        //delete bst;
        
    }
    
};


class Interface_TEST : public CxxTest::TestSuite {
public:
    // TEST BST Main Functionality
    // Save() and Load()
    void testInterface1(){
        DataStructures::Interface* interface1 = new DataStructures::Interface();
        interface1->Add("Dillon","Dragomir","+13305750709");
        interface1->Add("Suzie","Murdock","+13308932354");
        interface1->Add("Sandra","Dragomir","+13420542345");
        interface1->Add("Jesus","Lord","+14135132934");
        interface1->Save("./test.txt");
        TS_ASSERT(interface1->Find("Dillon","Dragomir") == "+13305750709");
        DataStructures::Interface* interface2 = new DataStructures::Interface();
        interface2->Load("./test.txt");
        TS_ASSERT(interface2->Find("Dillon","Dragomir") == "+13305750709");
        TS_ASSERT(interface2->Find("Sandra","Dragomir") == "+13420542345");
    }
    // Test the change command in the interface
    void testInterface2(){
        DataStructures::Interface* interface1 = new DataStructures::Interface();
        interface1->Add("Dillon","Dragomir","+13305750709");
        interface1->Add("Suzie","Murdock","+13308932354");
        interface1->Add("Sandra","Dragomir","+13420542345");
        interface1->Add("Jesus","Lord","+14135132934");
        // Test the change functionality
        TS_ASSERT(interface1->Find("Sandra","Dragomir") == "+13420542345");
        interface1->Change("Sandra","Dragomir","+13235322123");
        TS_ASSERT(interface1->Find("Sandra","Dragomir") == "+13235322123");
    }
};

#endif
