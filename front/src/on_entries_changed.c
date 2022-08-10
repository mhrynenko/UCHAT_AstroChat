#include "../inc/GUI_headeR.h"

void on_username_entry_changed() {
	remove_css_style(username_entry);
}

void on_password_entry_changed() {
	remove_css_style(password_entry);
}

void on_name_reg_entry_changed() {
	remove_css_style(name_reg_entry);
}

void on_username_reg_entry_changed() {
	is_wrong_login = false;
	gtk_widget_hide(error_reg_label);
	char *username = (char*)gtk_entry_get_text(GTK_ENTRY(username_reg_entry));
	if (check_correct_login (username) == 1) {
		is_wrong_login = true;
		gtk_label_set_text(GTK_LABEL(error_reg_label), "Login must be > 5 and consists of only eng chars, digits or '_'");
		gtk_widget_show(error_reg_label);
	}
	remove_css_style(username_reg_entry);
	/*if(event->keyval == GDK_KEY_s)
	printf("pfffffff");*/
}

void on_password_reg_entry_changed() {
	is_wrong_pass = false;
	gtk_widget_hide(error_reg_label);
	char *password = (char*)gtk_entry_get_text(GTK_ENTRY(password_reg_entry));
	if (check_correct_password (password, &pass_strength) == 1) {
		is_wrong_pass = true;
		gtk_label_set_text(GTK_LABEL(error_reg_label), "Password can be > 5 and consists of only eng chars,\ndigits or '_-@.*/'");
		gtk_widget_show(error_reg_label);
	}
	if (pass_strength == 0 || pass_strength == 1) {
		is_wrong_pass = true;
		gtk_label_set_text(GTK_LABEL(error_reg_label), "Password is too easy");
		gtk_widget_show(error_reg_label);
		add_css_style_by_name (password_reg_entry, "entry_with_bad_password");
	}
	if (pass_strength == 2 || pass_strength == 3) {
		add_css_style_by_name (password_reg_entry, "entry_with_medium_password");
	}
	if (pass_strength == 4) {
		add_css_style_by_name (password_reg_entry, "entry_with_good_password");
	}
	// remove_css_style(password_reg_entry);
}

void on_passwordrepeat_reg_entry_changed() {
	remove_css_style(passwordrepeat_reg_entry);
}

//gui-chat
void on_find_entry_changed() {
	add_css_style_by_name(GTK_WIDGET(find_entry), "find_entry");
}

void on_find_entry_activate(){
    if(groupcreateflag == 0) gtk_widget_activate(actions_menuButton);
    else {
        groupcreateflag = 0;
        char* nameofgroup = (char*)gtk_entry_get_text(GTK_ENTRY(find_entry));
        create_group_from_userlist(strdup(group_users), strdup(nameofgroup));
        //Zdesm json na gruppi
        gtk_entry_set_text(GTK_ENTRY(find_entry), "");
        gtk_entry_set_placeholder_text (GTK_ENTRY(find_entry),"Someone's login...");
        gtk_popover_popdown(GTK_POPOVER(settings_popovermenu));
    }
}

