#include "../inc/GUI_headeR.h"

gboolean on_username_entry_focus_in_event () {
	remove_css_style(username_entry);
	add_css_style_by_name(password_entry, "entry_out_of_focus");
	return FALSE;
}

gboolean on_username_entry_focus_out_event () {
	add_css_style_by_name(username_entry, "entry_out_of_focus");
	return FALSE;
}

// ---
gboolean on_password_entry_focus_in_event () {
	remove_css_style(password_entry);
	add_css_style_by_name(username_entry, "entry_out_of_focus");
	return FALSE;
}

gboolean on_password_entry_focus_out_event () {
	add_css_style_by_name(password_entry, "entry_out_of_focus");
	return FALSE;
}

// ---
gboolean on_name_reg_entry_entry_focus_in_event () {
	remove_css_style(name_reg_entry);
	return FALSE;
}

gboolean on_name_reg_entry_entry_focus_out_event () {
	add_css_style_by_name(name_reg_entry, "entry_out_of_focus");
	return FALSE;
}

// ----
gboolean on_username_reg_entry_focus_in_event () {
	remove_css_style(username_reg_entry);
	return FALSE;
}

gboolean on_username_reg_entry_focus_out_event () {
	add_css_style_by_name(username_reg_entry, "entry_out_of_focus");
	return FALSE;
}

// ---
gboolean on_password_reg_entry_focus_in_event () {
	remove_css_style(password_reg_entry);
	return FALSE;
}

gboolean on_password_reg_entry_focus_out_event () {
	add_css_style_by_name(password_reg_entry, "entry_out_of_focus");
	return FALSE;
}

// ---
gboolean on_passwordrepeat_reg_entry_focus_in_event () {
	remove_css_style(passwordrepeat_reg_entry);
	return FALSE;
}

gboolean on_passwordrepeat_reg_entry_focus_out_event () {
	add_css_style_by_name(passwordrepeat_reg_entry, "entry_out_of_focus");
	return FALSE;
}

//gui-chat
gboolean on_messgae_text_view_focus_in_event (GtkWidget *text_view) {
    add_css_style_by_name(GTK_WIDGET(text_view), "textview_focus_in");
    return FALSE;
}

gboolean on_messgae_text_view_focus_out_event (GtkWidget *text_view) {
    add_css_style_by_name(GTK_WIDGET(text_view), "textview_focus_out");
    return FALSE;
}

gboolean on_find_entry_focus_out_event() {
    add_css_style_by_name(GTK_WIDGET(find_entry), "find_entry");
    return FALSE;
}

