#include <pebble.h>

Window* window;
TextLayer *time_layer;
TextLayer *nearestStationLayer;
TextLayer *eastboundLayer;
TextLayer *westboundLayer;
TextLayer *station_label_layer;
TextLayer *eastbound_label_layer;
TextLayer *westbound_label_layer;

AppTimer *updateTimer;
//static GBitmap *background_img;
//static BitmapLayer* bg_layer;

char buffer[] = "00:00";

enum {
  NEAREST_STATION_STRING,
  NEAREST_STATION_CODE,
  EASTBOUND,
  WESTBOUND
};

// setting up the click handler for a center click
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  app_message_outbox_send();
}
static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}
static void out_sent_handler(DictionaryIterator *sent, void *context) {
	// outgoing message was delivered
}

void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Failed to send AppMessage to Pebble");
}

static void in_received_handler(DictionaryIterator *iter, void *context) {
	Tuple *nearestStationTuple = dict_find(iter, NEAREST_STATION_STRING);
	Tuple *eastboundTuple = dict_find(iter, EASTBOUND);
	Tuple *westboundTuple = dict_find(iter, WESTBOUND);

	if (nearestStationTuple) {
    text_layer_set_text(nearestStationLayer, nearestStationTuple->value->cstring);
  }
	if (eastboundTuple) {
		text_layer_set_text(eastboundLayer, eastboundTuple->value->cstring);
	}
	if (westboundTuple) {
		text_layer_set_text(westboundLayer, westboundTuple->value->cstring);
	}
}

void in_dropped_handler(AppMessageResult reason, void *context) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "incoming message from Pebble dropped");
}

void update() {
  // updating for aplite devices?
	//app_message_outbox_send();
  //updateTimer=app_timer_register(60000, (AppTimerCallback) update, NULL);
}
// handles all of the time changes
void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{
  if (clock_is_24h_style()) {
    strftime(buffer, sizeof("00:00"), "%k:%M", tick_time);
  } else {
    strftime(buffer, sizeof("00:00"), "%l:%M", tick_time);
  }
      text_layer_set_text(time_layer, buffer);
}


void window_load(Window *window)
{
    // changing placement of items based on the shape of the device
    #if defined(PBL_RECT)
      //bg_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
      time_layer = text_layer_create(GRect(0, 20, 144, 62));
      eastbound_label_layer = text_layer_create(GRect(0, 95, 24, 24));
      westbound_label_layer = text_layer_create(GRect(0, 120, 24, 24));
      nearestStationLayer = text_layer_create(GRect(0, 70, 144, 24));
      eastboundLayer = text_layer_create(GRect(25, 95, 119, 24));
      westboundLayer = text_layer_create(GRect(25, 120, 119, 24));
    #elif defined(PBL_ROUND)
      //bg_layer = bitmap_layer_create(GRect(0, 0, 180, 180));
      time_layer = text_layer_create(GRect(20, 20, 144, 62));
      eastbound_label_layer = text_layer_create(GRect(30, 95, 24, 24));
      westbound_label_layer = text_layer_create(GRect(30, 120, 24, 24));
      nearestStationLayer = text_layer_create(GRect(30, 70, 144, 24));
      eastboundLayer = text_layer_create(GRect(55, 95, 119, 24));
      westboundLayer = text_layer_create(GRect(55, 120, 119, 24));
    #endif
  
    //Background Layer
		//background_img = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG);
    //GRect bounds = bitmap_layer_get_bounds(bg_layer);
    //bg_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
    #ifdef PBL_COLOR
      //have a config file for choosing colors
      //window_set_background_color(window, GColorIslamicGreen);
      window_set_background_color(window, GColorBlack);
    #else
      window_set_background_color(window, GColorBlack);
    #endif
//     bitmap_layer_set_background_color(bg_layer, GColorBlack);
//     bitmap_layer_set_bitmap(bg_layer, background_img);
//     layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bg_layer));
    

		//Time layer
    //time_layer = text_layer_create(GRect(0, 20, 144, 62));
    text_layer_set_background_color(time_layer, GColorClear);
    text_layer_set_text_color(time_layer, GColorWhite);
    text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
    text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
    

	
    //text_layer_set_font(usdk_price_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_COMIC_SANS_20)));
    //text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_LECO_20_BOLD_NUMBERS));


    //layer for the station label
//     station_label_layer = text_layer_create(GRect(0, 70, 55, 24));
//     text_layer_set_background_color(station_label_layer, GColorClear);
//     text_layer_set_text_color(station_label_layer, GColorWhite);
//     text_layer_set_text_alignment(station_label_layer, GTextAlignmentLeft);
//     text_layer_set_font(station_label_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));


    // eastbound label
    //eastbound_label_layer = text_layer_create(GRect(0, 95, 24, 24));
    text_layer_set_background_color(eastbound_label_layer, GColorClear);
    text_layer_set_text_color(eastbound_label_layer, GColorWhite);
    text_layer_set_text_alignment(eastbound_label_layer, GTextAlignmentLeft);
    text_layer_set_font(eastbound_label_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
    

    // westbound label
    //westbound_label_layer = text_layer_create(GRect(0, 120, 24, 24));
    text_layer_set_background_color(westbound_label_layer, GColorClear);
    text_layer_set_text_color(westbound_label_layer, GColorWhite);
    text_layer_set_text_alignment(westbound_label_layer, GTextAlignmentLeft);
    text_layer_set_font(westbound_label_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
    
  
    //naerestStationLayer
		//nearestStationLayer = text_layer_create(GRect(0, 70, 144, 24));
		text_layer_set_text_color(nearestStationLayer, GColorWhite);
		text_layer_set_background_color(nearestStationLayer, GColorClear);
    text_layer_set_font(nearestStationLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
		text_layer_set_text_alignment(nearestStationLayer, GTextAlignmentLeft);
    
    
	  // eastboundLayer
		//eastboundLayer = text_layer_create(GRect(25, 95, 119, 24));
		text_layer_set_text_color(eastboundLayer, GColorWhite);
		text_layer_set_background_color(eastboundLayer, GColorClear);
    text_layer_set_font(eastboundLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
		text_layer_set_text_alignment(eastboundLayer, GTextAlignmentLeft);
    

		// westboundLayer
		//westboundLayer = text_layer_create(GRect(25, 120, 119, 24));
		text_layer_set_text_color(westboundLayer, GColorWhite);
		text_layer_set_background_color(westboundLayer, GColorClear);
    text_layer_set_font(westboundLayer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
		text_layer_set_text_alignment(westboundLayer, GTextAlignmentLeft);
    
    //adding all the layers
    layer_add_child(window_get_root_layer(window), (Layer*) time_layer);
		layer_add_child(window_get_root_layer(window), (Layer*) nearestStationLayer);
		layer_add_child(window_get_root_layer(window), (Layer*) eastboundLayer);
		layer_add_child(window_get_root_layer(window), (Layer*) westboundLayer);
    //layer_add_child(window_get_root_layer(window), (Layer*) station_label_layer);  
    layer_add_child(window_get_root_layer(window), (Layer*) eastbound_label_layer);
    layer_add_child(window_get_root_layer(window), (Layer*) westbound_label_layer);
    
    // setting the text for all the numbers
    text_layer_set_text(nearestStationLayer, "");
    text_layer_set_text(eastboundLayer, "");
    text_layer_set_text(westboundLayer, "");
    //setting the labels for the numbers.
    //text_layer_set_text(station_label_layer, "Station:");
    text_layer_set_text(eastbound_label_layer,"E:");
    text_layer_set_text(westbound_label_layer,"W:");
  
    

	  //Get a time structure so that the face doesn't start blank
    struct tm *t;
    time_t temp;
    temp = time(NULL);
    t = localtime(&temp);

    //Manually call the tick handler when the window is loading
    tick_handler(t, MINUTE_UNIT);
}

void window_unload(Window *window)
{
  //We will safely destroy the Window's elements here!
  text_layer_destroy(time_layer);
  text_layer_destroy(nearestStationLayer);
  text_layer_destroy(eastboundLayer);
  text_layer_destroy(westboundLayer);
//text_layer_destroy(station_label_layer);
  text_layer_destroy(eastbound_label_layer);
  text_layer_destroy(westbound_label_layer);
  //bitmap_layer_destroy(bg_layer);
}

static void app_message_init(void) {
	app_message_open(128 /* inbound_size */, 2 /* outbound_size */);
	app_message_register_inbox_received(in_received_handler);
	app_message_register_inbox_dropped(in_dropped_handler);
	app_message_register_outbox_sent(out_sent_handler);
	app_message_register_outbox_failed(out_failed_handler);
}

void init()
{
  app_message_init();
  //update();
  //Initialize the app elements here!
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
          .load = window_load,
          .unload = window_unload,
  });
  window_set_click_config_provider(window, click_config_provider);
  tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler) tick_handler);

	window_stack_push(window, true);

  //update the data
  //update();
  //updateTimer=app_timer_register(60000,(AppTimerCallback) update, NULL);
}

void deinit()
{
  //De-initialize elements here to save memory!
  tick_timer_service_unsubscribe();
  window_destroy(window);
  app_timer_cancel(updateTimer);
}

int main(void)
{
  init();
  app_event_loop();
  deinit();
}
