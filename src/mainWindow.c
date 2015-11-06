#include <pebble.h>
#include "test.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_18_bold;
static GFont s_res_gothic_24_bold;
static TextLayer *StationLayer;
static TextLayer *EastLabelLayer;
static TextLayer *EastLayer;
static TextLayer *WestLayer;
static TextLayer *WestLabelLayer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  // StationLayer
  StationLayer = text_layer_create(GRect(0, 10, 144, 20));
  text_layer_set_background_color(StationLayer, GColorClear);
  text_layer_set_text_color(StationLayer, GColorWhite);
  text_layer_set_text(StationLayer, "Robert Street Station");
  text_layer_set_text_alignment(StationLayer, GTextAlignmentCenter);
  text_layer_set_font(StationLayer, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)StationLayer);
  
  // EastLabelLayer
  EastLabelLayer = text_layer_create(GRect(2, 36, 15, 28));
  text_layer_set_background_color(EastLabelLayer, GColorClear);
  text_layer_set_text_color(EastLabelLayer, GColorWhite);
  text_layer_set_text(EastLabelLayer, "E:");
  text_layer_set_font(EastLabelLayer, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)EastLabelLayer);
  
  // EastLayer
  EastLayer = text_layer_create(GRect(20, 36, 120, 28));
  text_layer_set_background_color(EastLayer, GColorClear);
  text_layer_set_text_color(EastLayer, GColorWhite);
  text_layer_set_font(EastLayer, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)EastLayer);
  
  // WestLayer
  WestLayer = text_layer_create(GRect(20, 64, 123, 28));
  text_layer_set_background_color(WestLayer, GColorClear);
  text_layer_set_text_color(WestLayer, GColorWhite);
  text_layer_set_font(WestLayer, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)WestLayer);
  
  // WestLabelLayer
  WestLabelLayer = text_layer_create(GRect(2, 64, 15, 28));
  text_layer_set_background_color(WestLabelLayer, GColorClear);
  text_layer_set_text_color(WestLabelLayer, GColorWhite);
  text_layer_set_text(WestLabelLayer, "W:");
  text_layer_set_font(WestLabelLayer, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)WestLabelLayer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(StationLayer);
  text_layer_destroy(EastLabelLayer);
  text_layer_destroy(EastLayer);
  text_layer_destroy(WestLayer);
  text_layer_destroy(WestLabelLayer);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_test(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_test(void) {
  window_stack_remove(s_window, true);
}
