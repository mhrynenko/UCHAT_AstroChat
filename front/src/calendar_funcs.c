#include "../inc/GUI_headeR.h"

void get_and_convert_date_to_string () {
	guint year = 0;
	guint month = 0;
	guint day = 0;
	gtk_calendar_get_date (GTK_CALENDAR(calendar_reg), &year, &month, &day);

	char *temp = mx_itoa(day);
	picked_date = strdup(temp);
	picked_date = mx_strjoin(picked_date, ".");

	if (month + 1 < 10) {
		picked_date = mx_strjoin(picked_date, "0");
	}

	temp = mx_itoa(month+1);
	picked_date = mx_strjoin(picked_date, temp);
	picked_date = mx_strjoin(picked_date, ".");

	temp = mx_itoa(year);
	picked_date = mx_strjoin(picked_date, temp);
	free(temp);

	gtk_label_set_text(GTK_LABEL(birthdate_reg_label), picked_date);
	gtk_popover_popdown (GTK_POPOVER(date_picker));
}

void on_calendar_reg_day_selected_double_click () {
	add_css_style_by_name (birthdate_reg_label, "birthdate_reg_label");
	get_and_convert_date_to_string();
}

void on_pick_button_clicked () {
	add_css_style_by_name (birthdate_reg_label, "birthdate_reg_label");
	get_and_convert_date_to_string();
}

void on_close_calendar_date_clicked () {
	gtk_popover_popdown (GTK_POPOVER(date_picker));
}

