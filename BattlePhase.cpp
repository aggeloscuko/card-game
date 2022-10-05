#include "Gameboard.hpp"
#include "Player.hpp"
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

using namespace std;


//Transforms a string to lowercase . Used to not consider case sensitivity of strings
string lower_case_string(string str){
    string::iterator it;
    for (it = str.begin() ; it != str.end() ; it++){
        *it = tolower(*it);
    }
    return str;
}

//Check if num is in the vector v
bool vector_search(vector<int> v, int num){

    vector<int>::iterator it;

    for (it = v.begin() ; it != v.end() ; it++){
        //The number was found
        if (*it == num) return 1;
    }
    return 0;
}

//Player1 will attack Player2
void  AttackPlayer(Player* player1, Player* player2){
    int number_input;
    list<Personality*> attacking_force;     //The personalities used by player1 to attack player2
    list<Personality*> defense_force;       //The personalities used by player2 to defend against player1

    ///////////////////////////      Player1 attacking phase     ////////////////////////////////////

    cout << player1->getName() <<". Choose personalities from the available army to attack" << endl;
    cout << "Showing available army..." << endl;
    player1->printAvailableArmy();
    cout << "Choose personalities by typing the number. Press 0 when you do not wish to add another personality to the attack" << endl;

    vector<int> stored_inputs; //stores which personalities were chosen to attack

    //player1 choses personalities for the attack
    //loop stops if the player has no more personalities to add to the attacking force (or if he presses 0)
    while(player1->armyIsAvailable()){

        cout << "Enter number" << endl;
        cin >> number_input;

        //If a number input is given more that once
        if (vector_search(stored_inputs, number_input)){
            cout << "That personality has already be chosen" << endl;
        }
        //Player has chosen to stop adding personalities to his attacking force
        if (number_input == 0){
            if (attacking_force.empty()){
                cout << "No personalities were chosen to attack. Chose at least one" << endl;
            }

            else{
                break;
            }
        }

        else if (number_input < 0){
            cout << "Number given has to be positive" << endl;
        }

        else{

            stored_inputs.push_back(number_input);

            int counter = 0;    //Stores how many untapped (available) personalities in the players army have been found
                                //while traversing the army

            list<Personality*>::iterator it;

            for (it = player1->getArmy()->begin() ; it != player1->getArmy()->end(); it++){

                //If the personality is untapped (available)
                if (!(*it)->get_isTapped()){

                    counter++;

                    //The personality in the list is the one the player chose to add to his attacking_force
                    if (counter == number_input){
                        (*it)->Tapped();                   //The personality becomes tapped
                        attacking_force.push_back((*it));  //Add the personality to the attacking_force

                    }
                }
            }
        }
    }


    ////////////////////////////////////      Player2 defense phase           //////////////////////////////////////

    cout << player2->getName() <<". Choose personalities from the available army to defend" << endl;
    cout << "Showing available army..." << endl;
    player2->printAvailableArmy();
    cout << "Choose personalities by typing the number. Press 0 when you do not wish to add another personality to the defense" << endl;

    stored_inputs.clear(); //Empty stored_inpots to store inputs of the personalities that were chosen for the defense

    //player2 choses personalities for the defense
    //loop stops if the player has no more personalities to add to his defense force (or if he presses 0)
    while(player2->armyIsAvailable()){
        
        cout << "Enter number" << endl;
        cin >> number_input;

        //If a number input is given more that once
        if (vector_search(stored_inputs, number_input)){
            cout << "That personality has already be chosen" << endl;
        }
        //Player has chosen to stop adding personalities to his defense force
        //Unlike player1, player2 is allowed to not use any of his available personalities for defense  
        if (number_input == 0) break;

        else if (number_input < 0){
            cout << "Number given has to be positive" << endl;
        }

        else{

            stored_inputs.push_back(number_input);

            int counter = 0;    //Stores how many untapped (available) personalities in the players army have been found
                                //while traversing the army

            list<Personality*>::iterator it;

            for (it = player2->getArmy()->begin() ; it != player2->getArmy()->end(); it++){

                //If the personality is untapped (available)
                if (!(*it)->get_isTapped()){

                    counter++;

                    //The personality in the list is the one the player chose to add to his attacking_force
                    if (counter == number_input){
                        (*it)->Tapped();                   //The personality becomes tapped
                        defense_force.push_back((*it));  //Add the personality to the attacking_force
                    }
                }
            }
        }
    }

    ////////////////////////     Players have chosen their attack and defense forces.     //////////////////////////////
    
    cout << "Initialising attack" << endl;
    //Evaluate the attacking and defensive points for each player

    int attacking_points = 0;  //The total attacking points of player1 attacking force
    int defensive_points = 0;  //The total defensive points of player2 (without defense of the province)

    //Printing the attacking force
    cout << player1->getName() << "'s attacking personality army..." << endl << endl;

    for(list<Personality*>::iterator it = attacking_force.begin() ; it != attacking_force.end() ; it++){
        attacking_points += (*it)->get_attack();
        (*it)->printCard();     //Print the personality  
        cout << endl;
    }

    //Printing the defensive force
    cout << endl << player2->getName() << "'s defense personality army" << endl << endl;

    for(list<Personality*>::iterator it = defense_force.begin() ; it != defense_force.end() ; it++){
        defensive_points += (*it)->get_defense();
        (*it)->printCard();
        cout << endl;
    }
    //Printing the statistics
    cout << endl;
    cout << "Attacking points are: " << attacking_points << endl;
    cout << "Defensive points are: " << defensive_points << endl;
    cout << "Province defense is: " <<  player2->getFirstProvince().getDefense() << endl;

    //Ckecking all battle scenarios

    int difference = attacking_points - defensive_points; 

    //Case 1: Player1 destroys player2's province

    if (difference > player2->getFirstProvince().getDefense()){
        cout << player1->getName() << " has won the fight. " << player2->getName() << "will lose a province and all his defensive personalities" << endl << endl;
        //Remove province

        player2->removeFirstProvince();

        //All personalities of player2 used for defence are dead
        list<Personality*>::iterator it;
        for(it = defense_force.begin(); it != defense_force.end() ; it++){

            (*it)->Dead();    //The personality died
        }


        player2->removeDeadArmy();  //Remove all personalities that died
    }


    //Case 2

    else if (difference > 0){

        cout << player1->getName() << " has more attacking power than the defensive power of " << player2->getName() << " but not enough to destroy the province" << endl;
        list<Personality*>::iterator it;
        for(it = defense_force.begin(); it != defense_force.end() ; it++){

            (*it)->Dead();          //Remove the personality from the army (the equips of the personality are removed by its destructor)
        }

        for (it = attacking_force.begin() ; it != attacking_force.end() ; it++){

            //Unequip as many equipped followers from the personality as needed (stop if the personality does not have any followers left)
            while(difference > 0 && (*it)->is_equipped_to_followers()){

                //Get a follower from the personality, subtract its attackBonus from the difference and unequip it
                difference -= (*it)->get_last_follower().get_attackBonus();
                (*it)->unequip_last_follower();

            }
            //All necessary follower unequips and personality deaths have been made so every other personality will lose honour
            if (difference <= 0){
                (*it)->reduce_honour();
            }

            //The unequips of the personality were not enough so the personality will die

            else{   
                difference -= (*it)->get_attack();
                (*it)->Dead();
            }   
        }

        player1->removeDeadArmy();
        player2->removeDeadArmy();
    }

    //Case 3
    //All personalities used for attack and defense will die

    else if (difference == 0){

        cout << "Both players have equal attacking and defensive power. They will lose all personalities used in this battle" << endl;

        list<Personality*>::iterator it;
        for(it = defense_force.begin(); it != defense_force.end() ; it++){

            (*it)->Dead();    //The personality died
        }

        for(it = attacking_force.begin(); it != attacking_force.end() ; it++){

            (*it)->Dead();    //The personality died
        }

        player1->removeDeadArmy();
        player2->removeDeadArmy();
    }

    //Case 4
    //meaning difference < 0
    else{

        cout << "The attacking force is less than the defensive force. " << player1->getName() << " will lose all personalities used for the attack" << endl;
        difference = -difference; //Make it positive

        list<Personality*>::iterator it;
        for(it = attacking_force.begin(); it != attacking_force.end() ; it++){

            (*it)->Dead();          //The personality dies
        }

        for (it = defense_force.begin() ; it != defense_force.end() ; it++){

            //Unequip as many equipped followers from the personality as needed (stop if the personality does not have any followers left)
            while(difference > 0 && (*it)->is_equipped_to_followers()){

                //Get a follower from the personality, subtract its attackBonus from the difference and unequip it
                difference -= (*it)->get_last_follower().get_attackBonus();
                (*it)->unequip_last_follower();

            }
            //All necessary follower unequips and personality deaths have been (Unlike in case 2, the personalities will not lose honour)
            if (difference <= 0) break;

            //The unequips of the personality were not enough so the personality will die
            difference -= (*it)->get_attack();
            (*it)->Dead();
        }

        player1->removeDeadArmy();
        player2->removeDeadArmy();
    }

}

//Handles the input of the user
//input is the command the player typed.
//state is the current state of the player (explanation of each state in the enum definition above)
//Player is the player who gave the input
PlayerBattleState Gameboard::handling_input(string input, PlayerBattleState state, Player* player){

    cout << endl;   //Automatically change line

    if (input == "end turn") return END_TURN;


    if (input == "print army"){
        cout << endl << "Showing available army (untapped personalities)" << endl << endl;
        player->printAvailableArmy();
    }
    //Check the first 7 characters of the input
    if (input.substr(0,7) == "attack "){

        //Get the remaining characters of the input (The name of the player who will be attacked)
        string str = input.substr(7);

        //If the player attacked himself
        if ( str == (lower_case_string(player->getName()))){
            cout << "Wrong input:You chose to attack yourself" << endl;
            return state;
        }

        list<Player*>::iterator it;

        //Search all players
        
        for (it = this->Players.begin() ; it != this->Players.end() ; it++){

            //Check if the player's name is the name of the input
            if (lower_case_string((*it)->getName()) == str){

                AttackPlayer(player, *it);
                if ((*it)->getProvinces()->empty()) Players.erase(it); 
                return state;
            }

        }

        cout << "No player has the given name. " << endl <<"Type 'help' for available commands" << endl << endl;
        return state;
    }

    else if(input == "help"){
        cout << "Current available commands (not case sensitive) :" << endl;
        cout << "/t'Attack <Player name>': Player has chosen to attack the player with name <Player name>" << endl;
        cout << "/t'Print Army': Player has chosen to see his available personalities" << endl << endl;;
        return state;

    }


    else{
        cout << "Invalid command. Type 'help' for available commands" << endl << endl;
        return state;
    }
}



void Gameboard::battle_phase(void){
    string input;
    PlayerBattleState state;                 //This variable takes a value given by handling_input() function 
    list<Player*>::iterator it;

    cout << "Entering battle phase!" << endl << endl;

//Each player's battle phase turn
for (it = Players.begin() ; it != Players.end() ; it++){
    state = INITIAL_STATE;
    cout << (*it)->getName() << " player's turn" << endl;

    while (state != END_TURN && (*it)->armyIsAvailable()){
    cout << "Enter action: " ;
    std::getline(cin , input);
    cout << "Input given is: " << lower_case_string(input) << endl;
    state = handling_input(lower_case_string(input), state, *it);

    }

    if (state == END_TURN){
        cout  << endl << (*it)->getName() << "'s turn has ended" << endl;
    }

    else {
        cout << endl << (*it)->getName() << "does not have any available personalities for attack. Ending his turn" << endl << endl;
    }
}
}