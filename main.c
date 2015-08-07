//including the SDK, OF COURSE! 
#include <pebble.h>

//declaring the window and text object pointers. 
static Window *window;
static TextLayer *text_layer;

//this function is run when the app detects a middle button press
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "You Are Selecting Stuff!");
}
//this function is run when the app detects an up button press
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "You Pressed Up!!");
}

//this function is run when the app detects a down button press
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "You Pressed Down!");
}

// assigns the different buttons to be listening for actions on the respective buttons
static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

// initializes the window, and creates the graphic elements, and places the text
static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(text_layer, "Press a button");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

// the unload function for the window, in turn destorys the text layer. 
static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

//initializes the window and loads it, then pushes it to the stack. 
static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
	.load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

//cleans up the pointers and other variable... Really just destroys the window.. 
// By doing that... It calls all the other destructors
static void deinit(void) {
  window_destroy(window);
}

//the main function
int main(void) {
  init();
  app_event_loop();
  deinit();
}
