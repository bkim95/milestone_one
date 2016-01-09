#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

enum KEYS{UP, DOWN, LEFT, RIGHT};

using namespace std;

int main(int argc, char **argv) {
    
    float width = 640;
    float height = 480;
    
    bool done = false;
    bool redraw = true;
    bool keys[4] = {false, false, false, false};
    
    //For timer
    int count = 0;
    int FPS = 60;

    int pos_x = width/2;
    int pos_y = height/2;
    
    //Create variables
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

    
    if (!al_init())
        return -1;
    
    display = al_create_display(width, height);
    
    if (!display)
        return -1;
    
    //Initialize all addons
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    
    ALLEGRO_FONT *font18 = al_load_font("/Library/Fonts/Arial.ttf", 18, 0);
    ALLEGRO_FONT *font36 = al_load_font("/Library/Fonts/Arial.ttf", 36, 0);
    
    event_queue = al_create_event_queue();
    //Timer set to lock at 60 FPS
    timer = al_create_timer(1.0/FPS);

    //Register event sources
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
    al_start_timer(timer);
    
    while (!done){
        
        //If rectangle reaches end location at (30, 40)
        if ((pos_x == 30) && (pos_y == 40)){
            al_draw_text(font36, al_map_rgb(255, 0, 255), 640/2, 480/2, ALLEGRO_ALIGN_CENTRE, "YOU'VE WON!");
            al_draw_textf(font36, al_map_rgb(255, 0, 255), 380, 300, ALLEGRO_ALIGN_RIGHT, "TIME: %i seconds", count/60);
            done = true;
        }
        
        //Draw texts for marked start and end locations
        al_draw_text(font18, al_map_rgb(255, 255, 255), 30, 40, 0, "ED");
        al_draw_text(font18, al_map_rgb(255, 255, 255), (width/2)-10, (height/2)-10, 0, "ST");
        
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        
        count++;
        
        //For keys pressed down
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    keys[UP] = true;
                    break;
                    
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = true;
                    break;
                    
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = true;
                    break;
                    
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = true;
                    break;
            }
        }
        
        //For keys lifted
        else if (ev.type == ALLEGRO_EVENT_KEY_UP){
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    keys[UP] = false;
                    break;
                    
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = false;
                    break;
                    
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = false;
                    break;
                    
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = false;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
            }
            
        }
        
        //Allow display to close
        else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            done = true;
        }
        
        //Updating cube every 60th of a second
        else if (ev.type == ALLEGRO_EVENT_TIMER){
            pos_y -= keys[UP] * 10;
            pos_y += keys[DOWN] * 10;
            pos_x -= keys[LEFT] * 10;
            pos_x += keys[RIGHT] * 10;
            
            redraw = true;
            
        }
        
        if (redraw && al_is_event_queue_empty(event_queue)){
            
            redraw = false;
        
            al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255, 0, 255));
            al_flip_display();
            al_clear_to_color(al_map_rgb(0, 0, 0));
        }
    }
    
    al_rest(5.0);
    al_destroy_display(display);
    
    return 0;
}
