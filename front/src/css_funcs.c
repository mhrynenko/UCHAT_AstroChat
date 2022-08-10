#include "../inc/GUI_headeR.h"

void remove_css_style (GtkWidget *widget) {
	context = gtk_widget_get_style_context(GTK_WIDGET(widget));
	gtk_style_context_remove_provider(context, GTK_STYLE_PROVIDER(provider));
}

void add_css_style (GtkWidget *widget) {
	context = gtk_widget_get_style_context(widget);
	gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void add_css_style_by_name (GtkWidget *widget, char *name) {
	gtk_widget_set_name(widget, name);
	add_css_style(widget);
}
