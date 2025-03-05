#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

GtkWidget *entry, *status_label, *file_chooser, *history_text_view;
GtkTextBuffer *history_buffer;
char save_path[512] = "./";

// Function to update download history
void update_history(const char *text) {
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(history_buffer, &end);
    gtk_text_buffer_insert(history_buffer, &end, text, -1);
}

// Function to handle the file chooser button click
void on_file_chooser_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Select Download Location",
                                                    GTK_WINDOW(data),
                                                    GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
                                                    "Cancel", GTK_RESPONSE_CANCEL,
                                                    "Select", GTK_RESPONSE_ACCEPT,
                                                    NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *folder = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        strncpy(save_path, folder, sizeof(save_path) - 1);
        g_free(folder);
    }
    gtk_widget_destroy(dialog);
}

// Function to handle the download button click
gboolean download_video(gpointer data) {
    const char *url = gtk_entry_get_text(GTK_ENTRY(entry));
    
    if (url == NULL || *url == '\0') {
        gtk_label_set_text(GTK_LABEL(status_label), "Please enter a YouTube URL.");
        return FALSE;
    }
    
    gtk_label_set_text(GTK_LABEL(status_label), "Downloading...");
    
    char command[1024];
    snprintf(command, sizeof(command), "yt-dlp -o '%s/%%(title)s.%%(ext)s' %s", save_path, url);
    
    int result = system(command);
    
    if (result == 0) {
        gtk_label_set_text(GTK_LABEL(status_label), "Download successful!");
        update_history("Download successful: ");
        update_history(url);
        update_history("\n");
    } else {
        gtk_label_set_text(GTK_LABEL(status_label), "Download failed. Check your URL or internet connection.");
        update_history("Download failed: ");
        update_history(url);
        update_history("\n");
    }
    
    return FALSE;
}

// Function to handle button click
void on_download_clicked(GtkWidget *widget, gpointer data) {
    g_timeout_add(100, download_video, NULL);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "YouTube Video Downloader");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    
    GtkWidget *vbox = gtk_vbox_new(FALSE, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter YouTube URL...");
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);
    
    GtkWidget *hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
    
    GtkWidget *download_button = gtk_button_new_with_label("Download");
    gtk_box_pack_start(GTK_BOX(hbox), download_button, FALSE, FALSE, 0);
    
    GtkWidget *file_chooser_button = gtk_button_new_with_label("Select Folder");
    gtk_box_pack_start(GTK_BOX(hbox), file_chooser_button, FALSE, FALSE, 0);
    
    status_label = gtk_label_new("Waiting for input...");
    gtk_box_pack_start(GTK_BOX(vbox), status_label, FALSE, FALSE, 0);
    
    history_text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(history_text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(history_text_view), FALSE);
    history_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(history_text_view));
    
    GtkWidget *scroll_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll_window), history_text_view);
    gtk_box_pack_start(GTK_BOX(vbox), scroll_window, TRUE, TRUE, 0);
    
    g_signal_connect(download_button, "clicked", G_CALLBACK(on_download_clicked), NULL);
    g_signal_connect(file_chooser_button, "clicked", G_CALLBACK(on_file_chooser_clicked), window);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all(window);
    
    gtk_main();
    
    return 0;
}
