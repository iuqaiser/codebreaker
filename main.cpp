/*
28 January 2021
Codebreaker Game Program
Written by Iman Umair-Qaiser
Codebreaker is a well-known game where a player has to guess a sequence of 4 terms, using hints as to whether their terms are correct depending on value and position in the sequence.
*/
 
#include <iostream>
#include <time.h>
using namespace std;
 
char cont = 'y';
int correct, misplace, i, b, ans, points;
int digits[4]; 
//the array that holds the values that the user guesses for the code. if all the values in digits[] matches the all the values in code[], in the correct sequence, then the user has guess the code correctly and wins the game
int code[4]; 
//array that holds the computer-generated code at the beginning of each game. the values of digits[] is compared to this one, and if digits[] matches each value perfectly, the player wins
int taken[4]; 
//this array is run to prevent overlaps and misreading of hints
 
void wrongDigits(){ 
  //this evaluates each digits of the digits[] array in the case that it does not match its corresponding value on the code[] array; it is then compared to every other value on the code[] array to find a 'misplaced' match
   for (int n; n < 4; n++){ 
     //runs through all 4 of the code[] array values (only called if a value in digits[] does not match up, therefore in a round, it is not necessarily run 4 times
       if (digits[i]==code[n]){  
         //if the current digit (digits[i]) matches the current code value (code[n]), then it moves onto the next step
           if (digits[n]!=code[n]){  
             //if the corresponding digits[] value doesn't already match the code[] value, it moves onto the next step
               if (taken[n] == 0){  
                 //a value in taken will only have a value of 0 or 1 (similar to a boolean, though it is not a boolean). if the digits[i] matches code[n], then a match has been made and no other number in digits[] can match with code[n] in order to avoid overlap.
                   taken[n]= 1;
                   //the value of taken[n] being changed to 1, as the code only runs if taken[n]=0
                   misplace++; 
                   //misplace is increment showing that another number is the correct value in the incorrect position
                   break; 
                   // this stops the for() loop from continuing to run for that value of digits[i]
               }
           }
       }
   }
}
 
void compareDigits(){ 
  //this functions takes the values of digits[] are determined in enterDigits() and evaluates and compares to their respective [i] values in code[]
   for (i=0; i < 4; i++){
       if (digits[i]==code[i]){  
         //first, it is evaluated whether the values at the same place in the arrays are equivalent to each other
           correct++; 
           //if that is the case, then the integer correct is incremented to indicate a correct answer (but does not specify which number is the correct one, allow the user to utilize logic and multiple attempts to determine the correct sequence
       } else {
           wrongDigits(); 
           //if the values at the same location do not match up, then digits[i] is evaluated against other values of code[]
           cout << "";
       }
   }
}
 
void enterDigits(){ 
  //this function takes in the user's 4-digit guess and divides it to fit the values of digits[].
   cout<< "Please enter your 4-digit guess: \n";
   cin >> ans;

   //calculations
   digits[0] = ans/1000; //the first digit is the thousands digit in ans
   digits[1] = (ans%1000)/100; //the second digit is the hundreds digit in ans
   digits[2] = (ans%100)/10; //the third digit is the tens digit in ans
   digits[3] = ans%10; //the fourth digit is the ones digit in ans
}
 
void codeMaker(){  
  //this function initializes and randomizes a 4-digit code with values from 0 to 9 using the rand()
   code [0] = rand() % 10; 
   //each value of the code[] array is randomized individually to prevent errors
   code [1] = rand() % 10;
   code [2] = rand() % 10;
   code [3] = rand() % 10;
}
 
int main(){
   //introduction
   cout << "Welcome to Codebreaker! \n";
   cout << "In this game, you, the player, will have to guess a computer-generated 4-digit sequence consisting of numbers from 0 to 9 (e.g. 8059, 4576). \n";
   cout << "You'll be given hints based on your answers, and you'll have to have all the correct number in the correct order in order to win.\n";
   cout << "Take your time though: you only have 10 tries! Good luck!\n";
  
   do{
       srand (time(NULL)); 
       //this is used to initialize the randomization function
       codeMaker(); 
       //calls the codeMaker function to generate a code before the round begins
       for (b=0; b < 10; b++){  
         //you can play unlimited rounds of Codemaker, comprised of 10 turns each. Each run of this for() loop accounts for 1 turn
      
           enterDigits(); 
           //calls the enterDigits() function to allow the user to enter a guess
           compareDigits(); 
           //calls on the compareDigits() to compare the values of the user-given digits[] array to the computer-generated code[] array and determine if the values match
           cout << correct << " numbers are the correct value and in the correct position. \n"; 
           //these two statements print hints for the user, giving feedback on their guess by hinting how many values they have correct, and how many need to be reaaranged
           cout << misplace << " numbers are the correct value, but are in the wrong position. \n";
          
           correct = 0; 
           //resets all relevant values to 0 in preparation for the next round
           misplace = 0;
           taken[0] = 0; 
           //each taken[] value is set to 0 individually as opposed to using a for() loop due to unexpected issues during the debugging process
           taken[1] = 0;
           taken[2] = 0;
           taken[3] = 0;
 
           if ((digits[0]==code[0])&&(digits[1]==code[1])&&(digits[2]==code[2])&&(digits[3]==code[3])) { 
             //the game is only won if all of the values in the user's array match the values in the program's array, so it evaluates corresponding values in each array to each other.
               cout << "You win! The code was "<< code[0]<<code[1]<<code[2]<<code[3]<< ". \n"<<endl; //
               points+=(1000-(b*100)); 
               //a player can win up to 1000 points in a game. Their points from each game are calculated by taking the number of turn they played and subtracting them from a thousand. (e.g. 8 turns = 1000 - 800 = 200 points earned.)
               break; 
               //if the user's code matches the program's code at any given turn, the player wins and the game ends (stopping the for() loop)
              
           } else if(b==9) { 
             // since b starts at 0, the value of b would be 9 when the player is on their tenth attempt. If they do not get the answer correct on their tenth attempt, they lose the round
               cout << "You lose! The code was "<< code[0]<<code[1]<<code[2]<<code[3] << ".\n";
           }
       }
      
       b = 0; 
       // the value of b is reset after each round and outside of the for loop in order to be used in point calculation
       cout << "You have " << points << " total points. Would you like to play again? (y/n): "; 
       // the total number of points (he sum of all the points earned through multiple games) is displayed, and the player is asked if they would like to play again.
       cin >> cont;
   } while ((cont == 'y'||(cont == 'Y'))); 
   //the do-while loop allows for multiple rounds within one session of the program. After each round, the player must input a y character (case-insensitive) to play again.
   cout << "Thank you for playing Codebreaker!\n"; 
   //if the player inputs a value other than y or Y, the game displays its end message and the program stops running.
   return 0;
}