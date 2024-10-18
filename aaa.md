## IT_Hive


## Description
Welcome to IT_Hive - simple web application blog that is made for people to share their thoughts, stats and even courses expanding our IT community. IT_Hive is inspired by different people in IT that have same problem, finding one place for IT people to post their thoughts on different world IT events.


## Main Goal
1. The app is defined by registrated people, so registration and log in are a must.

2. The app itself has three buttons that are used for navigation inside the application (Following, Search, Account)
  # Following:
    - All posts from blogers that User is following.
  # Search:
    - All posts and all blogers existing on the app which also User can follow.
  # Account:
    - All account settings e.g. Fisrt Name, Last Name, People that He/She follows.
    - If User is also a blogger He/She can see people following him.

3. Admin User is the only one that has rights to let other people become blogers (they need to fill out the form) and he can also delete and modify other blogers posts if He finds them undesireable.


### Database
Short base development:
Database is made of five tables (Status, User_1, Following_Status, User_2, Blog). User_1 and User_2 have same attributes.
  # Status:
    - Admin
    - Blogger
    - Regular_User
  # User:
    - First_Name
    - Last_Name
    - Status_Key
    - Following_Status_Key
  # Blog:
    - Headline
    - Body
    - Date
    - Blogger_Name
  # Following_Status:
    - User_1_Key
    - User_2_Key
    - Is_Following


## Authors
##### Udovčić Marko
##### Parčina Ivan
##### Peran Toma

## Improvements
At the top of this document are the basic functionalities that this application needs to have to call it simple blog. Down here are just some ideas of improvements that would help this application become better and more desireable.  
- [] Blogger can see its blogging history
- [] Links inside blogs are unlocked by premium pass
- [] Blog Star rating
- [] Light/Dark theme switch...