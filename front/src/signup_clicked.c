#include "../inc/GUI_headeR.h"

void on_signup_button_clicked() {
	gtk_widget_hide(error_reg_label);

	char *name = (char*)gtk_entry_get_text(GTK_ENTRY(name_reg_entry));
	char *login = (char*)gtk_entry_get_text(GTK_ENTRY(username_reg_entry));
	char *password = (char*)gtk_entry_get_text(GTK_ENTRY(password_reg_entry));
	char *repeat_password = (char*)gtk_entry_get_text(GTK_ENTRY(passwordrepeat_reg_entry));
	char* req;
	bool is_wrong_entry = false;

	if (!strlen(name)) {
		is_wrong_entry = true;
		add_css_style_by_name(name_reg_entry, "entry_with_error");
	}
	if (!strlen(login)) {
		is_wrong_entry = true;
		add_css_style_by_name(username_reg_entry, "entry_with_error");
	}
	if (!strlen(password)) {
		is_wrong_entry = true;
		add_css_style_by_name(password_reg_entry, "entry_with_error");
	}
	if (!strlen(repeat_password)) {
		is_wrong_entry = true;
		add_css_style_by_name(passwordrepeat_reg_entry, "entry_with_error");
	}
	if (!picked_date) {
		is_wrong_entry = true;
		add_css_style_by_name (birthdate_reg_label, "birthdate_reg_label_with_error");
	}

	if (is_wrong_login) {
		gtk_label_set_text(GTK_LABEL(error_reg_label), "Login must be > 5 and consists of only eng chars, digits or '_'");
		gtk_widget_show(error_reg_label);
		return;
	}

	if (is_wrong_pass) {
		gtk_label_set_text(GTK_LABEL(error_reg_label), "Password must be > 5 and consists of only eng chars,\ndigits or '_-@.*/'");
		gtk_widget_show(error_reg_label);
		return;
	}

	if (is_wrong_entry) {
		return;
	}

	if (strcmp(password, repeat_password) != 0) {
		gtk_label_set_text(GTK_LABEL(error_reg_label), "Passswords are not the same");
		gtk_widget_show(error_reg_label);
		return;
	}

	req = mx_json_client_make_register(name, login, password, picked_date);
	SSL_write(ssl, req, strlen(req));
	if(is_disconnected){
		gtk_label_set_text(GTK_LABEL(error_reg_label), "Reconnecting... Try again");
		gtk_widget_show(error_reg_label);
		return;
	}

	wait_answer();	
	if (status_error == ERROR_OCCURED) {
		gtk_label_set_text(GTK_LABEL(error_reg_label), "This username is already exists");
		gtk_widget_show(error_reg_label);
		status_error = -1;
		return;
	}
	gtk_stack_set_visible_child(GTK_STACK(start_stack), start_grid);
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
void on_name_reg_entry_activate(){
	gtk_widget_grab_focus(username_reg_entry);
}
void on_username_reg_entry_activate(){
	gtk_widget_grab_focus(password_reg_entry);
}
void on_password_reg_entry_activate(){
	gtk_widget_grab_focus(passwordrepeat_reg_entry);
}
void on_passwordrepeat_reg_entry_activate(){
	gtk_widget_activate(calendar_menubutton);
}




