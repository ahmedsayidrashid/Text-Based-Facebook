/********* main.c ********
    Student Name 	= Ahmed Rashid
    Student Number	= 101256081
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE 
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);
    fclose(csv_file);
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    
    /* IMPORTANT: You must use the users linked list created in the code above. 
                  Any new users should be added to that linked list.
    */

    // Your solution goes here
    _Bool countinue = 1;
    int choice;
    printf("**********************************************\n");
    printf("        Welcome to Text-Based Facebook.       \n");
    printf("**********************************************\n");
    while(countinue){
        char temp_username[30]; // temp usernames 
        char temp_password[15]; // temp passwords 
        char temp_new_password[15]; // temp new passwords
        while(true){ // get user input for option.
            print_menu();
            printf("Enter your choice: ");
            scanf("%d", &choice);
            if(choice > 6 || choice < 1){
                printf("Invalid choice. Please try again. \n");
            }
            else{
                break;
            }
        }
        switch(choice){
            case 1: // cases are the user input 
                printf("Enter a username: ");
                scanf("%s", temp_username); // get user input
                printf("Enter an up to 15 characters password: ");
                scanf("%s", temp_password);
                add_user(users, temp_username, temp_password); // call add_user to add the new user
                printf("\n**** User Added! ****\n");
                break;
            case 2: 
                printf("Enter username to update thier password: ");
                scanf("%s", temp_username);
                if(find_user(users, temp_username) != NULL){  // if the user exists in the data base
                    printf("\nEnter a new password that is up to 15 characters: ");
                    scanf("%s", temp_new_password);
                    user_t* temp_user = find_user(users, temp_username);
                    strcpy(temp_user->password, temp_new_password); // change the password
                    printf("\n**** Password Changed! ****\n");   
                }
                else{// if the user is not in the database
                    printf("------------------------------------\n");
                    printf("           User not found.          \n");
                    printf("------------------------------------\n");  
                }
                break;
            case 3: 
                printf("Enter username to manage their posts: ");
                scanf("%s", &temp_username);
                if(find_user(users, temp_username) != NULL){ 
                    user_t* temp_user = find_user(users, temp_username);
                    int input = 0;
                    char content[250];
                    while(input != 3){
                        printf("\n________________________________________\n");
                        printf("             %s posts            \n", temp_user->username);
                        display_user_posts(temp_user); // display all the users posts as long as we are in the we loop
                        printf("\n________________________________________\n");

                        printf("1. Add a new users post\n");
                        printf("2. Remove a users post\n");
                        printf("3. Return to main menu\n");
                        printf("Your choice is: ");
                        scanf("%d", &input);
                        if(input == 1){
                            printf("Enter your post content: ");
                            scanf(" %[^\n]s", content); // scan the entire text inluding whitespaces until it encounters a newline character
                            add_post(temp_user, content); // add a post to the users profile
                            printf("Post added to your profile.");
                        }
                        else if(input == 2){
                            int num_post;
                            printf("Which post do you want to delete? ");
                            scanf("%d", &num_post);
                            if(delete_post(temp_user, num_post)){ // if deleted successfully
                                printf("Post %d was deleted successfully", num_post);
                            }
                            else{ // if not, return to main menu
                                break;
                            }
                        }
                        else if(input == 3){ // return to main menu
                            break;
                        }
                        else{
                            printf("Please enter a valid input");
                        }
                    }
                }
                else{ 
                    printf("------------------------------------\n");
                    printf("           User not found.          \n");
                    printf("------------------------------------\n");  
                }
                break;
            case 4: 
                printf("\nEnter username to manage thier friends: ");
                scanf("%s", &temp_username);
                if(find_user(users, temp_username) != NULL){ 
                    user_t* temp_user = find_user(users, temp_username);  
                    int input = 0;
                    while(input != 4){
                        printf("------------------------------------\n");
                        printf("           %s friends          \n", temp_user->username);
                        printf("------------------------------------\n");

                        printf("1. Display all users friends\n");
                        printf("2. Add a new friend\n");
                        printf("3. Delete a friend\n");
                        printf("4. Return to main menu\n");
                        printf("Your choice is: ");
                        scanf("%d", &input);
                        if(input == 1){
                            display_user_friends(temp_user);
                            printf("\n________________________________________\n");
                        }
                        else if(input == 2){
                            printf("Enter a new friends name: ");
                            scanf("%s", &temp_username);
                            add_friend(temp_user, temp_username);
                            printf("Friend added to the list. \n");
                            printf("\n________________________________________\n");
                        }
                        else if(input == 3){
                            display_user_friends(temp_user);
                            printf("Enter a friend's name to delete: ");
                            scanf("%s" , temp_username);
                            delete_friend(temp_user, temp_username);
                            display_user_friends(temp_user);
                            printf("\n");
                        }
                        else if(input == 4){
                            break;
                        }
                        else{
                            printf("Please enter a valid input");
                        }                                                          
                    }
                }
                else{
                    printf("------------------------------------\n");
                    printf("           User not found.          \n");
                    printf("------------------------------------\n");  
                }
                break;
            case 5:
                display_all_posts(users);
                break;
            case 6: 
                printf("**********************************************\n");
                printf("Thank you for using Text-Based Facebook.\n");
                printf("                 GoodBye!               \n");
                printf("**********************************************\n");
                teardown(users);
                countinue = false;
                break;
            default:
                countinue = false;
                break;
        }
    }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

}