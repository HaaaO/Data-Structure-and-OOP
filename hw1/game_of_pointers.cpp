#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct Warrior {
    string weapon;
    int power;
};

//Feel free to modify the parameters if you need other values
bool skirmish(Warrior*** protectors, Warrior*** invaders, int skirmish_row,
		      int rows, int columns, int &reserves, ofstream &output){
    //returns true if the invaders breach the walls.
   if (skirmish_row >= 0 && skirmish_row < columns){
        for (int i = 0; i < rows; i++)
   {
     // check whether there are protectors
     // or invaders occupied in their position
    // no invader occupied, no assault happened
     if (invaders[skirmish_row][i] -> power == -1 )
     {
        output << "No assault" << endl;
     }
     // no protector occupied, wall is breached
     else if (protectors[i][skirmish_row] -> power == -1)
     {
        return true;
     }
     else 
     {
        // check whether invader and protector have the same weapon
        // if have the same weapon, check power
        if (protectors[i][skirmish_row] -> weapon 
             == invaders[skirmish_row][i] -> weapon )
        {
            //check if they have the same power
            // protector has stronger power, invader killed
            if (protectors[i][skirmish_row] -> power 
                > invaders[skirmish_row][i] -> power)
            {
                output << "Invader killed" << endl;
                invaders[skirmish_row][i] -> power = -1;
            }
            // same power, duel ends in draw
         else if (protectors[i][skirmish_row] -> power 
                  == invaders[skirmish_row][i] -> power)
            {
                output << "Duel ends in draw" << endl;
            }
            // invader has stronger power, check whether the protector will defect
            else 
            {
                // checker 
                bool chk = false;
                for (int w = 0; w < columns; w++)
                {
                    for (int m = 0; m < rows; m++ )
                    {
                        //if this is the first empty space found, protector defect
                        if ((chk!=false) && (invaders[w][m]-> power))
                        {
                            output << "Protector defected" << endl;
                            invaders[w][m] -> weapon = 
                            protectors[i][skirmish_row] -> weapon;
                            invaders[w][m] -> power = 
                            protectors[i][skirmish_row] -> power;
                            chk = true;
                        }
                    }
                }
                // if no empty space in invaders, protector 
               // killed, use reserve if there is any reserve
                if (chk == false)

                {
                    output << "Protector killed" << endl;
                    if (reserves != 0)
                     {
                         protectors[i][skirmish_row] -> weapon = "axe";
                         protectors[i][skirmish_row] -> power = 100;
                         reserves--;
                      }
                    else 
                     {
                protectors[i][skirmish_row] -> power = -1;
                      }
                }

            }
        }
        // if protector has axe when invader got sword, invader killed
        else if (protectors[i][skirmish_row] -> weapon == "axe")
        {
            output << "Invader killed" << endl;
            invaders[skirmish_row][i] -> power = -1;
        }
        // if protector has sword, and if there 
        //is empty space in invader, protector defect
        else if (protectors[i][skirmish_row] -> weapon == "sword")
        {
            bool chk = false;
            for (int j = 0; j< columns; j++)
            {
                for (int z = 0; z < rows; z ++)
                {
                    if ((chk==false)&&(invaders[j][z] -> power == -1))
                    {
                        output << "Protector defected" << endl;
                        invaders[j][z] -> weapon = "sword";
                        invaders[j][z] -> power =
                         protectors[i][skirmish_row] -> power;
                        chk = true;
                    }
                }

            }
            // protector killed
            if (chk == false)
            {
               output << "Protector killed" << endl;
            if (reserves != 0)
              {
                protectors[i][skirmish_row] -> weapon = "axe";
                protectors[i][skirmish_row] -> power = 100;
                reserves--;
              }
            else 
              {
                protectors[i][skirmish_row] -> power = -1;
              }
            }
        }
     }
    }
   }
   else{
    return false;
   }   
  return false;
}

int main(int argc, char* argv[])
{
    bool end;
    if (argc < 3) {
	   cerr << "Please provide an input and output file" << endl;
	   return -1;
    }


    ifstream input(argv[1]);
    ofstream output(argv[2]);

    int rows;
    int cols;
    int reserve;
    int skirmishes;

    input >> rows >> cols >> reserve >> skirmishes;

    //read the input file and initialize the values here.

    Warrior ***protectors = new Warrior**[rows];
    for (int i = 0; i < rows; i++){
        protectors[i] = new Warrior*[cols];
        for (int j = 0; j <cols; j++){
            protectors[i][j] = new Warrior;
        }
    }

    for (int i = 0; i < rows; i++){
        if ((i % 2) == 0){
            for (int j = 0; j < cols; j++)
            {
                protectors[i][j]->weapon = "axe";
                protectors[i][j]->power = i*10 + (j + 1) * 10;
            }
        }
        else{
            for (int j = 0; j < cols; j++)
            {
                protectors[i][j]->weapon = "sword";
                protectors[i][j]->power = i*10 + (j + 1) * 10;
            }
        }
    }

    Warrior ***invaders = new Warrior**[cols];
    for (int i = 0; i < cols; i++){
        invaders[i] = new Warrior*[rows];
        for (int j = 0; j <rows; j++){
            invaders[i][j] = new Warrior;
        }
    }


    for (int i = 0; i < cols; i++){
        if ((i % 2) == 1){
            for (int j = 0; j < rows; j++)
            {
                invaders[i][j]->weapon = "axe";
                invaders[i][j]->power = i*10 + (j + 1) * 10;
            }
        }
        else{
            for (int j = 0; j < rows; j++)
            {
                invaders[i][j]->weapon = "sword";
                invaders[i][j]->power = i*10 + (j + 1) * 10;
            }
        }
    }

    //initialize the protectors and invaders here.

    for (int i=1; i <= skirmishes; i++){
        int skirmish_row;
        input >> skirmish_row;
        //read the input file to find the value for skirmish row
        
        //In general, it is bad style to throw everything into your main function
        end = skirmish(protectors, invaders, 
            skirmish_row, rows, cols, reserve, output);
        if (end == true){
            break;
        }
    }

    if (end == true){
       output << "Winner: invaders" << endl;
    }
    else 
    {
       output << "Winner: protectors" << endl;
    }


    //output the winner and deallocate your memory.


    for (int i = 0; i < rows; i++){
        for (int j = 0; j <cols; j++){ 
            delete protectors[i][j];
        }
        delete [] protectors[i];
    }
    delete [] protectors;


    for (int i = 0; i < cols; i++){
        for (int j = 0; j <rows; j++){
           delete invaders[i][j];
        }
        delete [] invaders[i];
    }
    delete[] invaders;




    return 0;
}


