#include "../inc/GUI_headeR.h"

GtkWidget *start_window;

GtkWidget *start_stack;

GtkWidget *start_grid, *username_entry, *password_entry, 
		  *signin_button, *registerNow_button, *error_label;

GtkWidget *register_grid, *username_reg_entry, *password_reg_entry, 
		  *passwordrepeat_reg_entry, *signup_button, *set_up_label,
		  *back_button, *error_reg_label, *name_reg_entry, 
		  *birthdate_reg_label, *calendar_menubutton;

GtkWidget *date_picker, *date_reg_box, *calendar_reg, *pick_calendar_button,
		  *close_calendar_button;

GtkBuilder *builder;
GtkCssProvider *provider;
GtkStyleContext *context;

GError* error = NULL;

char *picked_date = NULL;
bool is_wrong_login = false;
bool is_wrong_pass = false;
int pass_strength = 0;

void GUI_login(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	
	builder = gtk_builder_new();

	if (!gtk_builder_add_from_file (builder, "front/resources/start_window.glade", &error)) {
		/* загрузить файл не удалось */
		g_critical("Can't open file: %s", error->message);
		g_error_free(error);
	}

	gtk_builder_connect_signals(builder, NULL);

	get_from_glade();
	
	provider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (provider, "front/resources/theme_login.css", NULL);

	add_css_style (start_window);

	add_css_style (calendar_reg);

	add_css_style_by_name (birthdate_reg_label, "birthdate_reg_label");

	add_css_style_by_name (set_up_label, "set_up_label");

	add_css_style_by_name (error_label, "error_label");

	add_css_style_by_name (error_reg_label, "error_label");

	add_css_style_by_name (username_entry, "entry_out_of_focus");
	
	add_css_style_by_name (password_entry, "entry_out_of_focus");

	add_css_style_by_name (name_reg_entry, "entry_out_of_focus");
	
	add_css_style_by_name (username_reg_entry, "entry_out_of_focus");

	add_css_style_by_name (password_reg_entry, "entry_out_of_focus");
	
	add_css_style_by_name (passwordrepeat_reg_entry, "entry_out_of_focus");

	add_css_style_by_name (signin_button, "sign_button");
	
	add_css_style_by_name (signup_button, "sign_button");
	
	add_css_style_by_name (back_button, "back_button");

	add_css_style_by_name (calendar_menubutton, "calendar_menubutton");

	add_css_style_by_name (calendar_reg, "calendar");

	add_css_style_by_name (registerNow_button, "registerNow_button");

	add_css_style_by_name (date_picker, "date_picker");

	add_css_style_by_name (close_calendar_button, "calendar_buttons");

	add_css_style_by_name (pick_calendar_button, "calendar_buttons");

	gtk_widget_grab_focus(username_entry);

	gtk_window_set_position(GTK_WINDOW(start_window), GTK_WIN_POS_CENTER);
	gtk_widget_show_all(start_window);
	gtk_widget_hide(error_label);
	gtk_widget_hide(error_reg_label);

	gtk_main();

}

