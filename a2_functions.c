/********* definitions.c ********
    Student Name 	= Ahmed Rashid
    Student Number	= 101256081
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "a2_nodes.h"
#include "a2_functions.h"
#include "assert.h"

// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
    user_t *user = malloc(sizeof(user_t));
    assert(user != NULL);
    user->friends = NULL;
    user->posts = NULL;
    strcpy(user->username, username);
    strcpy(user->password, password);

    //If the new node data is less than the head node or the list is empty 
     if (users == NULL || strcmp(user->username, users->username) < 0)
    {
        user->next = users;
        return user;
    }

    user_t *temp = users;
    while (temp->next != NULL && strcmp(user->username, temp->next->username) > 0)
    {
        temp = temp->next; // keep going to next node until we are either at the end of the list or the desired location is found
    }

    user->next = temp->next; // put the user in its place
    temp->next = user;
    return users;
}

user_t *find_user(user_t *users, const char *username)
{
    assert(users != NULL);
    for ( ; users != NULL && strcmp(users->username, username) != 0; )
    { // keep iterating until we are find the user or at the end of the list
      users = users->next;
    }
    return users;
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
   friend_t* temp = malloc(sizeof(friend_t));
   assert(temp != NULL); // allocate memory for temporary variable
   strcpy(temp->username, username); 
   return temp;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
    friend_t *new_friend = create_friend(friend); // use previous function to create a friend
    if (user->friends == NULL || strcmp(friend, user->friends->username) < 0)
    { // If the list is empty or the new node data is less than the head node data
        new_friend->next = user->friends;
        user->friends = new_friend;
    }
    else
    {
        friend_t *current = user->friends;
        while (current->next != NULL && strcmp(new_friend->username, current->next->username) > 0)
        {
            current = current->next;
        }

        new_friend->next = current->next;
        current->next = new_friend;
    }
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
    friend_t *current = user->friends;
    friend_t *previous = NULL; // create a friend struct that tracks our previos
    while (current != NULL && strcmp(current->username, friend_name) != 0)
    {
        previous = current;
        current = current->next;
    } // keep iterating through the list and keep track of previous node until desired location is found.

    if(current == NULL) // out of range
    {
        printf("Invalid friend's name\n");
        return 0;
    }
    else
    { // in range
        if (previous != NULL) 
        {
            previous->next = current->next;
        }
        else
        {
            user->friends = current->next;
        }
        free(current); // delete the 'current' node.
        current = NULL; // to ensure no dangaling pointers.
        return 1;
    }
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
    post_t* post = malloc(sizeof(post_t));
    assert(post != NULL);
    strcpy(post->content, text);
    return post;
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text)
{
   post_t *new_post = create_post(text);
   new_post->next = user->posts; // add post to beginnig of the list of posts.
   user->posts = new_post;
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number)
{
   post_t* post = user->posts;
   int count = 0;
   if(post == NULL){ // no posts in the linked list
      return 0;
   }
   if(number == 1){
        user->posts = post->next;
        free(post);
        printf("Post %d was deleted successfully!\n", number);
        return 1;
    }
     while (post != NULL && count < number - 2)
    {
        post = post->next;
        count++;
    }
    if (post == NULL || post->next == NULL) // out of range
    {
        printf("Invalid post's number\n");
        return 0;
    }
    post_t *temp = post->next->next;
    free(post->next);
    post->next = temp;
    return 1;
}

/*
   Function that  displays a specific user's posts
*/
void display_user_posts(user_t *user)
{
   
   post_t* post = user->posts;
   int counter = 1;
   
   if(post == NULL){ // No posts
      printf("No posts available for %s", user->username);
   }
   else{
      while (post != NULL){ 
        printf("%d- %s: %s\n", counter, user->username, post->content); // print posts until end of list.
        post = post->next;
        counter++;
      }
   }
}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user)
{
    friend_t* friends = user->friends; 
    printf("\nList of %s's friends:\n", user->username);
    if(friends == NULL){ //empty list
      printf("No friends availible for %s\n\n", user->username);
    }
    else{
      for(int count = 1; friends != NULL; friends = friends->next, count++){
         printf("%d - %s\n", count, friends->username); // print in a specific format
      }
    }
}
/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t *users)
{
    _Bool cont = 1;
    char choice;
    int count = 0;
    user_t *user = users;
    while (user != NULL)
    {
        if (count < 2 && cont)
        {
            display_user_posts(user);
            user = user->next;
            count++;
        }
        else
        {
            printf("\n\nDo you want to display next 2 users posts? (Y/N): ");
            scanf(" %c", &choice);
            if (choice == 'Y' || choice == 'y')
            {
                count = 0;
                printf("\n\n");
            }
            else if (choice == 'N' || choice == 'n')
            {
                return;
            }
            else
            {
                printf("Invalid input!\n");
            }
        }
    }


}

/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
   assert(users != NULL);
    for(; users != NULL; users = users->next);
    free(users);
    users = NULL;
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
   printf("\n***********************************************\n");
   printf("                   Main Menu:                  \n");
   printf("***********************************************\n");
   printf("1. Registar a new user\n");
   printf("2. Manage a user's profile (change password)\n");
   printf("3. Manage a user's posts (display/add/remove)\n");
   printf("4. Manage a user's friends (display/add/remove)\n");
   printf("5. Display ALL posts\n");
   printf("6. Exit\n");
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
