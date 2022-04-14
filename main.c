typedef struct allowedMACs{
    int linkedMAC;
    struct allowedMACs *next;
}links;


typedef struct tree_node
{
  int MAC;
  char firstName[21];
  char lastName[21];
  int broadcastRange;
  int x;
  int y;
  links *deviceLinks;
  int numLinks;
  struct tree_node *left;
  struct tree_node *right;
} BSTnode;



#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//adds a node if it is not already added
BSTnode *Join (FILE * ptr, BSTnode * Root);
//finds where to insert the node
BSTnode *insert (BSTnode * Root, BSTnode * temp);

//Wrapper function for linking nodes
int LINK(BSTnode* CurrentNode,int MACNUM, int MACNUM2);

//Links the two nodes
int linkme(BSTnode* linker, int linking);

//Wrapper function for Unlinking two nodes
int UNLINK(BSTnode* Root, int MACNUM, int MACNUM2);
//Unlinks two nodes
int unlinks(BSTnode* Unlinker, int unlinks);

//Finds the specified MAC
int findMac(BSTnode* CurrentNode, int MACNUM);


//Returns 1 if the node is in the tree
int find(BSTnode * CurrentNode, int num);

//Returns a node within the tree that has the MACnum of num
BSTnode* finds(BSTnode* CurrentNode, int num);

//Moves devices psuedorandomly
BSTnode* MOVEDEVICES(BSTnode* CurrentNode, int sizeX, int sizeY);

//Prints all members of the nodes
void printKisMembers(BSTnode* CurrentNode);

//Show the connections of a particular MAC
void SHOWCONNECTIONS(BSTnode* CurrentNode, int num);

int
main ()
{




//An input variable for the user commands
char input[10];

//An input variable for searching a MAC
int MACNUM = 0;

int MACNUM2 = 0;

int seed = 0;

int sizeX = 0;

int sizeY = 0;

int runs = 0;

//Creates file pointer and scans in variables
  FILE *ptr = fopen ("File1", "r");

fscanf(ptr,"%d", &seed);

fscanf(ptr,"%d", &sizeX);

fscanf(ptr,"%d", &sizeY);

fscanf(ptr,"%d", &runs);

  BSTnode*Root = NULL;

  BSTnode *CurrentNode = NULL;

  srand(seed);

  //While not EOF
while(fscanf(ptr,"%s",input) == 1){


  if(strcmp(input, "JOIN") == 0){

      CurrentNode = Root;

      Root = Join(ptr, Root);

  }

 if(strcmp(input, "FINDMAC") == 0){
     CurrentNode = Root;

     fscanf(ptr,"%d", &MACNUM);

     findMac(CurrentNode, MACNUM);

 }
 if(strcmp(input, "LINK") == 0){

     CurrentNode = Root;

     fscanf(ptr,"%d", &MACNUM);

     fscanf(ptr,"%d", &MACNUM2);

    LINK(CurrentNode, MACNUM, MACNUM2);

 }

 if(strcmp(input, "UNLINK") == 0){

     CurrentNode = Root;

     fscanf(ptr,"%d", &MACNUM);


     fscanf(ptr,"%d", &MACNUM2);

printf("UNLINK is not implemented");


 }

 if(strcmp(input, "PRINTKISMEMBERS") == 0){
CurrentNode = Root;

if(CurrentNode != NULL){
  printKisMembers(CurrentNode);
}
else{
    printf("Cannot Perform PRINTKISMEMBERS Command:There are currently no participants of the KIS system.\n");
}

 }

 if(strcmp(input, "MOVEDEVICES") == 0){
CurrentNode = Root;

if(CurrentNode != NULL){
MOVEDEVICES(CurrentNode, sizeX, sizeY);

}
else{
    printf("Cannot Perform MOVEDEVICES Command: There are currently no participants of the KIS system.\n");
}
 }

 if(strcmp(input, "SHOWCONNECTIONS") == 0){
     CurrentNode = Root;

      fscanf(ptr,"%d", &MACNUM);


      if(CurrentNode != NULL){
  SHOWCONNECTIONS(CurrentNode, MACNUM);
}

     else{
    printf("Cannot Perform PRINTKISMEMBERS Command:There are currently no participants of the KIS system.\n");
}


 }
  if(strcmp(input, "QUIT") == 0){

     CurrentNode = Root;

     fscanf(ptr,"%d", &MACNUM);

printf("QUIT is not implemented");


 }


}

//Frees the nodes
free(Root);
free(CurrentNode);

 return 0;
}

//Shows Connections
void SHOWCONNECTIONS(BSTnode* CurrentNode, int num){
    //Keeps the head of the node
    BSTnode*Node = CurrentNode;

    BSTnode*Node2 = CurrentNode;
    //Keeps the current Node
    links* Node4 ;


    int temp = find(CurrentNode, num);
//If the node is in the tree
    if(temp == 1){

       BSTnode*Node3 = finds(CurrentNode, num);
Node4 = Node3->deviceLinks;

        printf("Connections for MAC %d, %s %s, currently at position (%d, %d):	There are a total of %d link(s).\n", Node3->MAC, Node3->firstName, Node3->lastName, Node3->x, Node3->y, Node3->numLinks);

        while(Node3->deviceLinks->next != NULL){

            //equals head
            Node2 = Node;

            Node2 = finds(Node2, Node3->deviceLinks->linkedMAC);


    printf("MAC %d %s %s, currently at position (%d, %d)\n",Node2->MAC, Node2->firstName, Node2->lastName, Node2->x, Node2->y);

    Node3->deviceLinks = Node3->deviceLinks->next;
}

            Node2 = Node;

            Node2 = finds(Node2, Node3->deviceLinks->linkedMAC);

    printf("MAC %d %s %s, currently at position (%d, %d)\n",Node2->MAC, Node2->firstName, Node2->lastName, Node2->x, Node2->y);

        Node3->deviceLinks = Node4;

    }
    else{
        printf("Cannot Perform SHOWCONNECTIONS Command:	MAC %d - This MAC Address is not in the KIS system", num);
    }



}

//Moves all devices psuedorandomly
BSTnode* MOVEDEVICES(BSTnode* CurrentNode, int sizeX, int sizeY){
    if(CurrentNode != NULL){

    CurrentNode->x = rand() % sizeX;

    CurrentNode->y = rand() % sizeY;

    return MOVEDEVICES(CurrentNode->left, sizeX, sizeY);

   return MOVEDEVICES(CurrentNode->right, sizeX, sizeY);
    }
return 0;
}

//scans in variables and serves as a wrapper function for insert
BSTnode* Join (FILE * ptr, BSTnode * Root)
{

  BSTnode *temp = (BSTnode *) malloc (sizeof (BSTnode));

     fscanf (ptr, "%d", &temp->MAC);

      fscanf (ptr, "%s", temp->firstName);

      fscanf (ptr, "%s", temp->lastName);

      fscanf (ptr, "%d", &temp->broadcastRange);

      fscanf (ptr, "%d", &temp->x);

      fscanf (ptr, "%d", &temp->y);

      temp->deviceLinks = NULL;

      temp->numLinks = 0;

     int control = find(Root, temp->MAC);


      if(control == 0){
      printf("%s %s, MAC %d, joined KIS.\n",temp->firstName,temp->lastName,temp->MAC);

	  return insert(Root, temp);
      }
      else{
          printf("Cannot Perform JOIN Command:\n");
          printf("MAC %d, %s %s - already a participant in the KIS program.\n", temp->MAC, temp->firstName, temp->lastName);


          return Root;
      }

}

//Inserts the node in a particular place in the Binary Tree
BSTnode *
insert (BSTnode * Root, BSTnode * temp)
{


  if (Root == NULL)
    {

      return temp;

    }
  else
    {
      if (temp->MAC > Root->MAC)
	{

	  Root->right = insert (Root->right, temp);
	}
      else
	{
	  Root->left = insert (Root->left, temp);
	}
      return Root;
    }


}

//Finds a particular MAC
int
findMac(BSTnode* CurrentNode, int MACNUM){
    if(CurrentNode != NULL){
        if(CurrentNode->MAC == MACNUM){
            printf("Found:  MAC %d, %s %s, currently at position (%d, %d)\n",CurrentNode->MAC,CurrentNode->firstName,CurrentNode->lastName, CurrentNode->x,CurrentNode->y);
            return 1;
        }
        if(MACNUM < CurrentNode->MAC){
            return findMac(CurrentNode->left, MACNUM);
        }
        else{
            return findMac(CurrentNode->right, MACNUM);
        }

    }
    else{
        printf("Cannot find %d\n", MACNUM);
        return 0;
    }

}


//Returns 1 if the node is in the tree and returns 0 if the node is not in the tree
int
find(BSTnode * CurrentNode, int num){

    if(CurrentNode != NULL){
    if(CurrentNode->MAC == num){
            return 1;

        }

     if(num < CurrentNode->MAC){
            return find(CurrentNode->left, num);
        }
        else{
            return find(CurrentNode->right, num);
        }

    }
    else{
        return 0;
    }
}

/*
//A wrapper function for unlinking two nodes
int UNLINK(BSTnode* CurrentNode, int num, int num2){
    if(num == num2){
        printf("Cannot Perform UNLINK Command:\n");
        printf("MAC %d and MAC %d are the same \n",num, num2);
        return 0;
    }
    int temp = 0;
    int temp2 = 0;

    BSTnode* Node1 = NULL;
    BSTnode* Node2 = NULL;

    temp = find(CurrentNode, num);

   temp2 = find(CurrentNode, num2);

    //If both of the MACs are in the Binary tree

    if(temp == 1 && temp2 == 1){
  Node1 = finds(CurrentNode, num);
  Node2 = finds(CurrentNode, num2);

  temp = unlinks(Node1,num2);
  temp2 = unlinks(Node2,num);

  if(temp == 0 || temp2 == 0){
      printf("Cannot Perform UNLINK Command:\n");

      printf("MAC %d and MAC %d are not currently linked. \n",num, num2);


      return 0;
  }
else{
     Node1->numLinks--;
    Node2->numLinks--;
    printf("Unlinked it");
    return 1;
}
    }
    else{
        //If both arent in the system
        if(temp != 1 && temp2 != 1){
        printf("Cannot Perform UNLINK Command:\n");
        printf("MAC %d - This MAC Address is not in the KIS system.\n",num);
        printf("MAC %d - This MAC Address is not in the KIS system.\n", num2);
        return 0;
        }
        //If one isnt in the system
        if(temp != 1 && temp2 == 1){
            printf("Cannot Perform UNLINK Command:\n");
        printf("MAC %d - This MAC Address is not in the KIS system.\n",num);
        return 0;
        }
        else{
            printf("Cannot Perform UNLINK Command:\n");
        printf("MAC %d - This MAC Address is not in the KIS system.\n",num2);
        return 0;
        }
    }



}



int unlinks(BSTnode* Unlinker, int unlinks){
    int control = 0;
    //If the list is not empty
    if(Unlinker->deviceLinks != NULL){
        links*temp = Unlinker->deviceLinks;
        links*front = Unlinker->deviceLinks;
        //Check every node in the linked list except for the last
    while(front->next != NULL){
        if(front->linkedMAC == unlinks){
            if(front != temp){
            temp->next = temp->next->next;
            }
            else{
                temp = temp->next;
            }
            free(front);
            return 1;

        }

        front = front->next;
        if(control == 1){
            temp = temp->next;
            control = 0;
        }
control++;
    }
    if(front->linkedMAC == unlinks){
            temp->next = NULL;

            free(front);

            return 1;
    }
        }

    return 0;


}
*/



//A wrapper function for Linking two nodes
int LINK(BSTnode* CurrentNode,int num, int num2){
    if(num == num2){
        printf("Cannot Perform LINK Command:\n");
        printf("MAC %d and MAC %d are the same \n",num, num2);
        return 0;
    }
    int temp = 0;
    int temp2 = 0;

    BSTnode* Node1 = NULL;
    BSTnode* Node2 = NULL;

   temp = find(CurrentNode, num);

   temp2 = find(CurrentNode, num2);

    //If both of the MACs are in the Binary tree
    if(temp == 1 && temp2 == 1){

  Node1 = finds(CurrentNode, num);
  Node2 = finds(CurrentNode, num2);
  printf("%d\n",Node1->MAC);
  printf("%d\n",Node2->MAC);
  temp = linkme(Node1,num2);

  temp2 = linkme(Node2,num);

  if(temp == 0 || temp2 == 0){
      printf("Cannot Perform LINK Command:\n");

      printf("MAC %d and MAC %d are currently linked. \n",num, num2);


      return 0;
  }
else{
    Node1->numLinks++;
    Node2->numLinks++;
    printf("LINKED IT\n");
    return 1;
}
    }
    else{
        //If both arent in the system
        if(temp != 1 && temp2 != 1){
        printf("Cannot Perform LINK Command:\n");
        printf("MAC %d - This MAC Address is not in the KIS system.\n",num);
        printf("MAC %d - This MAC Address is not in the KIS system.\n", num2);
        return 0;
        }
        //If one isnt in the system
        if(temp != 1 && temp2 == 1){
            printf("Cannot Perform LINK Command:\n");
        printf("MAC %d - This MAC Address is not in the KIS system.\n",num);
        return 0;
        }
        else{
            printf("Cannot Perform LINK Command:\n");
        printf("MAC %d - This MAC Address is not in the KIS system.\n",num2);
        return 0;
        }
    }



}


//Prints the members
void printKisMembers(BSTnode* CurrentNode){
    if(CurrentNode != NULL){
        printf("%s\n",CurrentNode->firstName);
        printKisMembers(CurrentNode->left);
        printKisMembers(CurrentNode->right);
    }

}



//Returns the node with the given MAC number if it is in the tree
BSTnode* finds(BSTnode* CurrentNode, int num){

    if(CurrentNode->MAC == num){

            return CurrentNode;

        }

     if(num < CurrentNode->MAC){
            return finds(CurrentNode->left, num);
        }
        else{
            return finds(CurrentNode->right, num);
        }
}


int linkme(BSTnode* linker, int linking){

if(linker->deviceLinks == NULL){
    linker->deviceLinks = (links*)malloc(sizeof(links));
    linker->deviceLinks->linkedMAC = linking;
    return 1;
}
else{
    links*pointer = linker->deviceLinks;
    while(pointer->next != NULL){
        if(pointer->linkedMAC == linking){

            return 0;
        }
        pointer =  pointer->next;


}
//Check last node
if(pointer->linkedMAC == linking){


            return 0;
    }
    else{
            pointer->next = (links*)malloc(sizeof(links));
            pointer->next->linkedMAC = linking;
            return 1;
    }

}

return 0;

}
