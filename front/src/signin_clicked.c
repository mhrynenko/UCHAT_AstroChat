#include "../inc/GUI_headeR.h"

bool is_log_in = false;
void on_signin_button_clicked() {
	gtk_widget_hide(error_label);

	char *name = (char*)gtk_entry_get_text(GTK_ENTRY(username_entry));
	char *password = (char*)gtk_entry_get_text(GTK_ENTRY(password_entry));
	char* req;
    
	if (!strlen(name) && !strlen(password)) {
		add_css_style_by_name(username_entry, "entry_with_error");
		add_css_style_by_name(password_entry, "entry_with_error");
		return;
	}
	else if (!strlen(password) && strlen(name)) {
		add_css_style_by_name(password_entry, "entry_with_error");
		return;
	}
	else if (!strlen(name) && strlen(password)) {
		add_css_style_by_name(username_entry, "entry_with_error");
		return;
	}
	
	req = mx_json_client_make_log_in(name, password);
	SSL_write(ssl, req, strlen(req));
	if(is_disconnected){
		gtk_label_set_text(GTK_LABEL(error_label), "Reconnecting... Try again");
		gtk_widget_show(error_label);
		return;
	}
	wait_answer();
	if (status_error == ERROR_OCCURED) {
		gtk_label_set_text(GTK_LABEL(error_label), "Wrong password or login");
		gtk_widget_show(error_label);
		status_error = -1;
		return;
	}
	is_log_in = true;
	// req = mx_json_client_make_prediction();
	// send(clientSocket, req, strlen(req), 0);
	// status_error = -1;
	// wait_answer();
	status_error = -1;
	user_info.user_password = password;
	gtk_widget_hide(start_window);
	mx_strdel(&req);
	GUI_chat();
}
void on_username_activate(){
	//on_signin_button_clicked();
	gtk_widget_grab_focus(password_entry);
}
void on_password_entry_activate(){
	gtk_widget_activate(signin_button);
}

