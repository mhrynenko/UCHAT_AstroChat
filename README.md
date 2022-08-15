ASTRO_CHAT

ИСПОЛЬЗУЕМЫЕ БИБЛИОТЕКИ: 
    -json-c
    -GTK+3
    -sqlite3
    -openSSL
    -libmx

USAGE:
 1. Для добавления индивидуального чата ввести логин пользователя в поле в левом верхнем углу, 
 после чего нажать на кнопку с тремя точками и из выпадающего меню выбрать "Create chat";
 #уже существущие чаты, чаты с самим собой, чаты с несуществующими пользователями создать нельзя

 2. Для добавления групового чата ввести логины пользователей через запятую в поле в левом верхнем углу,
 после чего нажать на кнопку с тремя точками и из выпадающего меню выбрать "Group's users", после чего 
 в это же поле ввести имя группы и нажать на "Group`s name"/Enter;
 #experimental feature

 3. Для удаления чата/группы - нажать правой кнопкой мыши по нему



<h1 align='center'> ASTRO_CHAT </h1>

### Description
This is our implementation of the real-time messaging application with astrology theme. It was a team app, where I did frontend part.  
I was engaged in the main layout and development of the login and registration window of our chat, validation of incoming user data, such as login, password, date of birth. Also I took part in the final layout of the chat, displaying the created groups, chats, helped with displaying, editing and deleting messages.
By the way, this app was developed just in 14 days.


####Promo video
https://user-images.githubusercontent.com/108219165/184611653-d631af73-c654-4c4e-8f66-94d65261f423.mp4


####Implemented features
- Client:
    - basic authentication and registration with date of birth to determine the zodiac sign
    ![изображение](https://user-images.githubusercontent.com/108219165/184611918-a1f47dcd-991c-4073-8a12-951d967096a0.png)
    - if client lost connection with server, app will try to reconnect
    - abilty to edit or delete messages after sending 
    - recipient can see sender's name and date, where message was sent
    ![изображение](https://user-images.githubusercontent.com/108219165/184612196-58c29624-bc7e-4a34-8726-20ed17e952a6.png)
    - creating individual or group chats
    ![изображение](https://user-images.githubusercontent.com/108219165/184612293-6f8eaa0d-9ea4-4c2b-a73a-e7b43e3048b3.png)
    - prediction for the day every day, that depends on zodiac sign
    - dark/light mode
    ![изображение](https://user-images.githubusercontent.com/108219165/184612477-c11207e1-1296-4335-bfaa-8e5e6bb0cf5e.png)

    
    
    
    
    
    

### How to start
*This program was developed on the MacOS, so it works correctly there.*   

In folder with cloned project use `make` to compile project. Start program with `./ush`.

To delete the program - `make uninstall`   
To delete all 'obj' files - `make clean`   
To reinstall the program - `make reinstall`
