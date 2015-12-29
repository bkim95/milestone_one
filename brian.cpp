#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>

using namespace std;

int main(int argc, char **argv) {
    
    ALLEGRO_DISPLAY *display = NULL;
    
    if (!al_init()){
        al_show_native_message_box(NULL, NULL, NULL,
                                   "falled to initialize allegro!", NULL, NULL);
        return -1;
    }
    
    display = al_create_display(640, 480);
    
    if (!display){
        al_show_native_message_box(NULL, NULL, NULL,
                                   "falled to initialize allegro!", NULL, NULL);
        return -1;
    }
    
    al_init_font_addon();
    al_init_ttf_addon();
    
    ALLEGRO_FONT *font24 = al_load_font("/Library/Fonts/Arial.ttf", 24, 0);
    
    int screen_w = al_get_display_width(display);
    int screen_h = al_get_display_height(display);
    
    al_draw_textf(font, al_map_rgb(255, 255, 255), screen_w/2, 400, ALLEGRO_ALIGN_CENTRE, "Just testing..");
    
    //Bring buffer to the front to appear on screen
    al_flip_display();
    al_rest(5.0);
    
    al_destroy_display(display);
