
/////////////////////////////
//FILE NAME: BST.h//
/////////////////////////////

////////////////
//Contributers//
////////////////

///////////////////////////////////////////////

// NAME                   DATE           CHANGE
// Dillon Dragomir        10-15-2018     Added fucntions to header file
// Dillon Dragomir        10-17-2018     Added interface, save and restore functionality

///////////////////////////////////////////////

////////////////
//DEPENDANCIES//
////////////////

#ifndef BST_H
#define BST_H

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <list>
#include <vector>

namespace DataStructures{
    
    namespace Tree{
        
        template<typename T>
        struct TreeNode{
            T* value;
            TreeNode* right;
            TreeNode* left;
        };
        
        // Each Tree node at most can have two pointers
        template<typename T>
        class BST{
            
        public:
            int count;
            TreeNode<T>* rootNode;
            
            // Constructor
            BST(){
                count = 0;
                rootNode = new TreeNode<T>();
            }
            
            // Destructor
            ~BST(){
                clear();
                // Must delete root node after
                // Value of node should already be NULL
                delete rootNode;
            }
            
            // Add Value to Tree
            void add(T* value){
                count += 1;
                if(rootNode->value == NULL){
                    rootNode->value = value;
                    return;
                } else {
                    addRecursive(value, rootNode);
                }
            }
            
            void update(T* value){
                if(rootNode->value == NULL){
                    rootNode->value = value;
                    return;
                } else {
                    updateRecursive(value, rootNode);
                }
            }
            
            // Returns null if DNE
            T* get(T* value){
                return getRecursive(value, rootNode);
            }
            
            void deleteNode(T* value){
                if(count == 1 || count == 0){
                    clear();
                } else{
                    count -= 1;
                    deleteNodeRecursive(value, rootNode, NULL);
                }
            }
            
            // Checks whether value exists
            bool exists(T* value){
                if(get(value, rootNode) == NULL){
                    return false;
                } else {
                    return true;
                }
            }
            
            // Returns bst array in order
            std::list<T>* inOrder(){
                std::list<T>* arr = new std::list<T>();
                if(rootNode->value != NULL){
                    return orderRecursive(arr, rootNode, "IN");
                } else {
                    delete arr;
                    return NULL;
                }
                
            }
            
            
            // Returns bst array in pre order
            std::list<T>* preOrder(){
                std::list<T>* arr = new std::list<T>();
                if(rootNode->value != NULL){
                    return orderRecursive(arr, rootNode, "PRE");
                } else {
                    delete arr;
                    return NULL;
                }
                
            }
            
            // Returns bst array in post order
            std::list<T>* postOrder(){
                std::list<T>* arr = new std::list<T>();
                if(rootNode->value != NULL){
                    return orderRecursive(arr, rootNode, "POST");
                } else {
                    delete arr;
                    return NULL;
                }
            }
            
            // Shallow Copy
            
            // Deep Copy
            
            //Size
            int size(){
                return count;
            }
            
            // Clear
            void clear(){
                // Must delete all nodes
                count = 0;
                clearRecursive(rootNode);
                // Must re-initialize root node, because implementation counts on this
                rootNode = new TreeNode<T>();
            }
            
        private:
            
            void deleteNodeRecursive(T* object, TreeNode<T>* currNode, TreeNode<T>* prevNode){
                if(*(currNode->value) == *object){
                    // Check three cases
                    if(currNode->left == NULL && currNode->right == NULL){
                        // Both children null
                        //std::cout << "No children: " << currNode->value->fullName << std::endl;
                        // Needed to handle inserting single node and delting root node
                        if(prevNode != NULL){
                            // Remove pointers to node before deleting
                            if(prevNode->left == currNode){
                                prevNode->left = NULL;
                            }
                            if(prevNode->right == currNode){
                                prevNode->right = NULL;
                            }
                        } else {
                            rootNode = currNode;
                        }
                        // Delete person and tree node
                        if(currNode->value != NULL){
                            delete currNode->value;
                        }
                        delete currNode;
                    } else if(currNode->left == NULL || currNode->right == NULL){
                        // One child null
                        //std::cout << "One child" << std::endl;
                        // Find the node to replace the deleted one
                        TreeNode<T>* updateNode;
                        if(currNode->left != NULL){
                            updateNode = currNode->left;

                        } else {
                            updateNode = currNode->right;
                        }
                        // Needed to update root node
                        if(prevNode != NULL){
                            // Find which pointer from the previous node to update
                            if(prevNode->left == currNode){
                                prevNode->left = updateNode;
                            } else {
                                prevNode->right = updateNode;
                            }
                        } else {
                            rootNode = updateNode;
                        }
                        // Delete the node
                        delete currNode->value;
                        delete currNode;
                    } else {
                        //std::cout << "Two children" << std::endl;
                        // Neither child null, must find inorder successor
                        TreeNode<T>* successor = currNode->right;
                        TreeNode<T>* ss = currNode;
                        while(successor->left != NULL && successor->right != NULL){
                            ss = successor;
                            if(successor->left != NULL){
                                successor = successor->left;
                            } else {
                                successor = successor->right;
                            }
                        }
                        // Must remove pointer pointing to successor
                        if(ss->left == successor){
                            ss->left = NULL;
                        } else {
                            ss->right = NULL;
                        }
                        // Update deleted node with successor
                        successor->left = currNode->left;
                        successor->right = currNode->right;
                        // Needed to delete root node
                        if(prevNode != NULL){
                            // Find which pointer from the previous node to update
                            if(prevNode->left == currNode){
                                prevNode->left = successor;
                            } else {
                                prevNode->right = successor;
                            }
                        } else {
                            rootNode = successor;
                        }
                        delete currNode->value;
                        delete currNode;
                    }
                    return;
                }
                if(*currNode->value > *object){
                    if(currNode->left == NULL){
                        return;
                    }
                    deleteNodeRecursive(object, currNode->left, currNode);
                } else {
                    if(currNode->right == NULL){
                        return;
                    }
                    deleteNodeRecursive(object, currNode->right, currNode);
                }
            }
            
            T* getRecursive(T* object, TreeNode<T>* currNode){
                if(currNode->value != NULL){
                    if(*(currNode->value) == *object){
                        return currNode->value;
                    }
                    if(*currNode->value > *object){
                        if(currNode->left == NULL){
                            return NULL;
                        }
                        return getRecursive(object, currNode->left);
                    } else {
                        if(currNode->right == NULL){
                            return NULL;
                        }
                        return getRecursive(object, currNode->right);
                    }
                } else {
                    return NULL;
                }
            }
            
            void updateRecursive(T* object, TreeNode<T>* currNode){
                if(*(currNode->value) == *object){
                    T* oldNode = currNode->value;
                    currNode->value = object;
                    delete oldNode;
                    return;
                }
                // Adds node if it does not exist in list to update
                if(*currNode->value > *object){
                    if(currNode->left == NULL){
                        currNode->left = new TreeNode<T>();
                        currNode->left->value = object;
                        return;
                    }
                    updateRecursive(object, currNode->left);
                } else {
                    if(currNode->right == NULL){
                        currNode->right = new TreeNode<T>();
                        currNode->right->value = object;
                        return;
                    }
                    updateRecursive(object, currNode->right);
                }
            }
            
            // Recursively deletes all the nodes
            void clearRecursive(TreeNode<T>* node){
                if(node != NULL){
                    if(node->value != NULL){
                        delete node->value;
                    }
                    if(node->left != NULL){
                        clearRecursive(node->left);
                    }
                    if(node->right != NULL){
                        clearRecursive(node->right);
                    }
                    delete node;
                }
            }
            
            // Loops over tree to recursively insert a new node
            void addRecursive(T* value, TreeNode<T>* currNode){
                if(*currNode->value > *value){
                    if(currNode->left == NULL){
                        currNode->left = new TreeNode<T>();
                        currNode->left->value = value;
                        return;
                    }
                    addRecursive(value, currNode->left);
                } else {
                    if(currNode->right == NULL){
                        currNode->right = new TreeNode<T>();
                        currNode->right->value = value;
                        return;
                    }
                    addRecursive(value, currNode->right);
                }
                
            }
            
            // Recursively loops over the tree to output values into a list in teh given order
            std::list<T>* orderRecursive(std::list<T>* arr, TreeNode<T>* currNode, std::string type){
                if(type == "PRE"){
                    arr->push_back(*currNode->value);
                }
                if(currNode->left != NULL){
                    orderRecursive(arr, currNode->left, type);
                }
                if(type == "IN"){
                    arr->push_back(*currNode->value);
                }
                if(currNode->right != NULL){
                    orderRecursive(arr, currNode->right, type);
                }
                if(type == "POST"){
                    arr->push_back(*currNode->value);
                }
                return arr;
            }
        };
        
    }
    
    // This class stores the data and is passed into the BST
    // Greater than comparator must be defined for the tree to compare the objects
    class Person {
        
    public:
        // Data variables
        std::string firstName;
        std::string lastName;
        std::string fullName;
        std::string phoneNumber;
        
        // Must define these to work in binary search tree
        bool operator> (const Person &p1){
            return (fullName > p1.fullName);
        }
        
        bool operator== (const Person &p1){
            return (fullName == p1.fullName);
        }
        
        Person(std::string firstname, std::string lastname, std::string phonenumber){
            firstName = firstname;
            lastName = lastname;
            phoneNumber = phonenumber;
            fullName = lastName + " " + firstName;
        }
        
        ~Person(){
            // Nothing to delete
        }
        
    };
    
    
    template<typename T>
    class PhoneBook{
        
    private:
        DataStructures::Tree::BST<T>* bst;
        
    public:
        // New Phone book
        PhoneBook(){
            bst = new DataStructures::Tree::BST<T>();
            
        }
        
        // Load previous phone book from text file
        PhoneBook(std::string filePath, std::string fileName){
            bst = new DataStructures::Tree::BST<T>();
        }
        // Takes inOrder list of list objects
        PhoneBook(std::list<T>* names){
            bst = new DataStructures::Tree::BST<T>();
            
        }
        
        ~PhoneBook(){
            delete bst;
        }
        
        int Count(){
            return bst->size();
        }
        
        // Adds person to phone book
        void Add(std::string first, std::string last, std::string number){
            bst->add(new T(first, last, number));
        }
        
        void Delete(std::string first, std::string last){
            T* node = new T(first, last, "");
            bst->deleteNode(node);
            delete node;
        }
        
        // Returns phone number given name
        // Returns -1 if they do not exist
        std::string Find(std::string firstName, std::string lastName){
            T* personToFind = new T(firstName, lastName, "");
            T* found = bst->get(personToFind);
            delete personToFind;
            if(found == NULL){
                return "-1";
            } else {
                return found->phoneNumber;
            }
        }
        
        // Returns true if the person already exists in the phone book
        bool Exists(){
            if(Find() != "-1" ){
                return true;
            }
            return false;
        }
        
        // Changes phone number given persons name and phone number
        void Change(std::string firstName, std::string lastName, std::string phoneNumber){
            bst->update(new T(firstName, lastName, phoneNumber));
        }
        
        void Display(){
            std::list<T>* treeList = bst->inOrder();
            for(typename std::list<T>::iterator it = treeList->begin(); it != treeList->end(); ++it){
                std::cout << it->fullName << std::endl;
            }
        }
        
        // Gets people to save to text file
        std::list<T>* GetPeople(){
            return bst->preOrder();
        }
        
        
    };
    
    
    // This will be ther interface for the user to interact with the phonebook
    class Interface{
        
    public:
        Interface(){
            pb = new DataStructures::PhoneBook<DataStructures::Person>();
        }
        
        ~Interface(){
            delete pb;
        }
        
        void Add(std::string firstName, std::string lastName, std::string phoneNumber){
            checkExists();
            pb->Add(firstName,lastName, phoneNumber);
        }
        
        void Delete(std::string firstName, std::string lastName){
            checkExists();
            pb->Delete(firstName,lastName);
        }
        
        std::string Find(std::string firstName, std::string lastName){
            checkExists();
            return pb->Find(firstName,lastName);;
        }
        
        void Change(std::string firstName, std::string lastName, std::string phoneNumber){
            checkExists();
            pb->Change(firstName,lastName, phoneNumber);
        }
        // Displays tree InOrder in command line
        void Display(){
            pb->Display();
        }
        // Deletes  the phone book
        void Quit(){
            delete pb;
        }
        // Saves tree to text file
        void Save(std::string filePath){
            std::list<DataStructures::Person>* treeList = pb->GetPeople();
            std::ofstream myfile;
            myfile.open(filePath.c_str());
            for(std::list<DataStructures::Person>::iterator it = treeList->begin(); it != treeList->end(); ++it){
                myfile << it->firstName << "," << it->lastName << "," << it->phoneNumber << "\n";
            }
            myfile.close();
        }
        // Loads tree from text file
        void Load(std::string filePath){
            std::ifstream input(filePath.c_str());
            std::vector<std::string>* person;
            for( std::string line; getline( input, line ); )
            {
                person = parseData(line);
                if(person != NULL && person->size() == 3){
                    Add(person->at(0),person->at(1),person->at(2));
                }
            }
        }
        
    private:
        DataStructures::PhoneBook<DataStructures::Person>* pb;
        void checkExists(){
            if(pb == NULL){
                pb = new DataStructures::PhoneBook<DataStructures::Person>();
            }
        }
        
        // Parse text string into vector
        std::vector<std::string>* parseData(std::string str){
            std::vector<std::string>* result = new std::vector<std::string>();
            std::stringstream s(str);
            while( s.good() )
            {
                std::string substr;
                getline( s, substr, ',' );
                result->push_back( substr );
            }
            return result;
        }
    };
}


#endif
