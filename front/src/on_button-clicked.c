#include "../inc/GUI_headeR.h"

void on_registerNow_button_clicked() {
	gtk_widget_hide(error_label);
	gtk_widget_hide(error_reg_label);
	
	gtk_stack_set_visible_child(GTK_STACK(start_stack), register_grid);

	add_css_style_by_name (username_entry, "entry_out_of_focus");
	gtk_entry_set_text(GTK_ENTRY(username_entry), "");

	add_css_style_by_name(password_entry, "entry_out_of_focus");
	gtk_entry_set_text(GTK_ENTRY(password_entry), "");
}

void on_back_button_clicked() {
	gtk_widget_hide(error_reg_label);

	gtk_stack_set_visible_child(GTK_STACK(start_stack), start_grid);

	remove_css_style(name_reg_entry);
	remove_css_style(username_reg_entry);
	remove_css_style(password_reg_entry);
	remove_css_style(passwordrepeat_reg_entry);

	gtk_entry_set_text(GTK_ENTRY(name_reg_entry), "");
	gtk_entry_set_text(GTK_ENTRY(username_reg_entry), "");
	gtk_entry_set_text(GTK_ENTRY(password_reg_entry), "");
	gtk_entry_set_text(GTK_ENTRY(passwordrepeat_reg_entry), "");

	add_css_style_by_name(name_reg_entry, "entry_out_of_focus");
	add_css_style_by_name(username_reg_entry, "entry_out_of_focus");
	add_css_style_by_name(password_reg_entry, "entry_out_of_focus");
	add_css_style_by_name(passwordrepeat_reg_entry, "entry_out_of_focus");
	add_css_style_by_name (birthdate_reg_label, "birthdate_reg_label");

	picked_date = NULL;
	gtk_label_set_text (GTK_LABEL(birthdate_reg_label), "Birthdate...");
}

//------------------------------gui-chat------------------------------//
void on_changestile_button_clicked(){
    if(stileflag == 0){
        stileflag = 1;
	    gtk_css_provider_load_from_path (provider, "front/resources/theme_chat.css", NULL);
    }
    else if(stileflag == 1){
         stileflag = 0;
	gtk_css_provider_load_from_path (provider, "front/resources/theme_chat1.css", NULL);
   
    }
}

void on_exit_button_clicked(){
    //gtk_widget_show(start_window);
    gtk_widget_hide (chat_window);
    exit(0);
}

void on_welcomepage_button_clicked () {
    gtk_stack_set_visible_child_name (GTK_STACK(chat_stack), "welcomepage");
    gtk_window_set_title (GTK_WINDOW(chat_window), "Welcome to the AstroChat");
}

void chatname_button_clicked (GtkWidget *button) {
    int tempindex = 0;
    const char *clicked_button_name = gtk_widget_get_name(GTK_WIDGET(button)); 
    for(tempindex = 0; grouparr[tempindex].chatroomid!=atoi(clicked_button_name); tempindex++);
    gtk_stack_set_visible_child_name(GTK_STACK(chat_stack), clicked_button_name);
    gtk_window_set_title (GTK_WINDOW(chat_window), grouparr[tempindex].chatroomname);
    scroll_down(grouparr[tempindex].ChatScrolledWondow);
    scroll_down(grouparr[tempindex].ChatScrolledWondow);
    
}

gboolean on_edit_message_button_clicked (GtkWidget *button, GdkEventButton *event, msg_t *msg) {
    (void)button;
    if (event->type == GDK_BUTTON_PRESS  &&  event->button == 1) {
        int tempindex = 0;
        while(grouparr[tempindex].chatroomid != msg->chatroomid && tempindex!= 101){
            tempindex++;
        }
        if (tempindex == 101){
            printf("PIZDAAAAAAAAA\n");
            //return;
        }
        GtkTextBuffer* message_textBuffer = gtk_text_buffer_new(NULL);;
        gchar* edittext;
        edittext = (gchar*)gtk_label_get_text(GTK_LABEL(msg->msg_label));    
        gtk_text_buffer_set_text(GTK_TEXT_BUFFER(message_textBuffer), edittext, strlen(edittext));
        gtk_text_view_set_buffer(GTK_TEXT_VIEW(grouparr[tempindex].TextField), message_textBuffer);
        gtk_widget_grab_focus(grouparr[tempindex].TextField);

        add_css_style_by_name(GTK_WIDGET(grouparr[tempindex].TextField), "editing_textview");  
        add_css_style_by_name(GTK_WIDGET(msg->msg_label), "editing_label");  

        grouparr[tempindex].editflag = msg->msgid;
        //free(msg_edit_text);
        return FALSE;
    }
    return FALSE;
} 

gboolean on_delete_message_button_clicked (GtkWidget *button, GdkEventButton *event, int *message_id) {
    (void)button;
    if (event->type == GDK_BUTTON_PRESS  &&  event->button == 1) {
		char* req = mx_json_client_make_delete_msg(*message_id);
		SSL_write(ssl, req, strlen(req));
        return FALSE;
    }
    return FALSE;
} 

void send_button_clicked(GtkWidget *button, chat_t *group){
    (void)button;
    int CurentPage = atoi(gtk_stack_get_visible_child_name (GTK_STACK(chat_stack))); 

    GtkTextIter start, end;
    GtkTextBuffer* message_textBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(group->TextField));
    char *msg_text;
    char *temp_text;

    gtk_text_buffer_get_bounds (message_textBuffer, &start, &end);
    temp_text = gtk_text_buffer_get_text (message_textBuffer, &start, &end, FALSE); 
    msg_text = mx_strtrim(temp_text);

    if (!msg_text) {
        return;
    }
    //ЗАПРОС НА ОТПРАВКУ
    if(group->editflag == -1){
        char* req = mx_json_client_make_msg(msg_text, CurentPage);
        SSL_write(ssl, req, strlen(req));
        free(req);
        gtk_text_view_set_buffer(GTK_TEXT_VIEW(group->TextField), NULL);   
        gtk_widget_show_all(GTK_WIDGET(chat_stack));
        g_free (msg_text);
        g_free (temp_text);    
    }
    //ЭДИТ!!! МСГ ИД ЭТО editflag
    else {
        //СФОРМИРУЙТЕ ЗАПРОС НА ЭДИТ!!!!!!!
        char *req = mx_json_client_make_edit_msg(group->editflag, msg_text);
        SSL_write(ssl, req, strlen(req));
        free(req);

        gtk_text_view_set_buffer(GTK_TEXT_VIEW(group->TextField), NULL);   
        gtk_widget_show_all(GTK_WIDGET(chat_stack));
        group->editflag = -1;
    }
}

void on_createChat_button_clicked () {
    char *name = (char*)gtk_entry_get_text(GTK_ENTRY(find_entry));
    char *req;
    /*zdes otpravliam msg*/
    status_error = -1;
    req = mx_json_client_make_individual_chat(name);
	SSL_write(ssl, req, strlen(req));
    
    wait_answer();
    if (status_error == 0){
        gtk_entry_set_text(GTK_ENTRY(find_entry), "");
    }
    else {
        add_css_style_by_name(GTK_WIDGET(find_entry), "entry_with_error");
    }

    status_error = -1;
    
    gtk_popover_popdown(GTK_POPOVER(settings_popovermenu));
}

void on_createGroup_button_clicked(){
    if(groupcreateflag == 0){
		char* temp = (char*)gtk_entry_get_text(GTK_ENTRY(find_entry));
		group_users = strdup(temp);
		gtk_entry_set_text(GTK_ENTRY(find_entry), "");
		groupcreateflag = 1;
		gtk_entry_set_placeholder_text (GTK_ENTRY(find_entry),"Group's name...");
		gtk_button_set_label(GTK_BUTTON(createGroup_button), "   Group's name");
    }
    else {
        groupcreateflag = 0;
        char* nameofgroup = (char*)gtk_entry_get_text(GTK_ENTRY(find_entry));
        create_group_from_userlist(strdup(group_users), strdup(nameofgroup));
        gtk_entry_set_text(GTK_ENTRY(find_entry), "");
        gtk_entry_set_placeholder_text (GTK_ENTRY(find_entry),"Someone's login...");
        gtk_button_set_label(GTK_BUTTON(createGroup_button), "   Group's users");
        gtk_popover_popdown(GTK_POPOVER(settings_popovermenu));
        
    }
}

void right_click_on_chat_button(GtkWidget *button, GdkEventButton *event, chat_t* chat){
    (void) button;
    if (event->type == GDK_BUTTON_PRESS  &&  event->button == 3 ) {
        //chat->chatroomid or smth; вставьте удаление
		char* req = mx_json_client_make_del_group(chat->chatroomid);
        SSL_write(ssl, req, strlen(req));
        return;
    }
}

