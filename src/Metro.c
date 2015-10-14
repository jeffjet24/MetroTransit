#include <pebble.h>

Window* window;
TextLayer *time_layer;
TextLayer *nearestStationLayer;
TextLayer *eastboundLayer;
TextLayer *westboundLayer;


AppTimer *updateTimer;
static GBitmap *background_img;
static BitmapLayer* bg_layer;

char buffer[] = "00:00";

enum {
  NEAREST_STATION_STRING,
  EASTBOUND,
  WESTBOUND
};

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
		text_layer_set_text(westboundLayer,westboundTuple->value->cstring);
	}
}

void in_dropped_handler(AppMessageResult reason, void *context) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "incoming message from Pebble dropped");
}

void update() {
	app_message_outbox_send();
  updateTimer=app_timer_register(300000, (AppTimerCallback) update, NULL);
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
    //Background Layer
		//background_img = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BG);
    bg_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
    bitmap_layer_set_background_color(bg_layer, GColorBlack);
    bitmap_layer_set_bitmap(bg_layer, background_img);
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bg_layer));

		//Time layer
    time_layer = text_layer_create(GRect(0, 20, 144, 62));
    text_layer_set_background_color(time_layer, GColorClear);
    text_layer_set_text_color(time_layer, GColorWhite);
    text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(window), (Layer*) time_layer);

		// naerestStationLayer
		nearestStationLayer = text_layer_create(GRect(75, 106, 67, 24));
		text_layer_set_text_color(nearestStationLayer, GColorWhite);
		text_layer_set_background_color(nearestStationLayer, GColorClear);
		text_layer_set_text_alignment(nearestStationLayer, GTextAlignmentCenter);

	  // eastboundLayer
		eastboundLayer = text_layer_create(GRect(71, 88, 71, 24));
		text_layer_set_text_color(eastboundLayer, GColorWhite);
		text_layer_set_background_color(eastboundLayer, GColorClear);
		text_layer_set_text_alignment(eastboundLayer, GTextAlignmentCenter);

		// westboundLayer
		westboundLayer = text_layer_create(GRect(65, 70, 77, 24));
		text_layer_set_text_color(westboundLayer, GColorWhite);
		text_layer_set_background_color(westboundLayer, GColorClear);
		text_layer_set_text_alignment(westboundLayer, GTextAlignmentCenter);

// 		text_layer_set_font(usdk_price_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_COMIC_SANS_20)));

    layer_add_child(window_get_root_layer(window), (Layer*) time_layer);
		layer_add_child(window_get_root_layer(window), (Layer*) nearestStationLayer);
		layer_add_child(window_get_root_layer(window), (Layer*) eastboundLayer);
		layer_add_child(window_get_root_layer(window), (Layer*) westboundLayer);


//     //layer for the block# label
//     block_label_layer = text_layer_create(GRect(0, 70, 77, 24));
//     text_layer_set_background_color(block_label_layer, GColorClear);
//     text_layer_set_text_color(block_label_layer, GColorWhite);
//     text_layer_set_text_alignment(block_label_layer, GTextAlignmentLeft);
//     layer_add_child(window_get_root_layer(window), (Layer*) block_label_layer);



//     diff_label_layer = text_layer_create(GRect(0, 88, 71, 24));
//     text_layer_set_background_color(diff_label_layer, GColorClear);
//     text_layer_set_text_color(diff_label_layer, GColorWhite);
//     text_layer_set_text_alignment(diff_label_layer, GTextAlignmentLeft);
//     layer_add_child(window_get_root_layer(window), (Layer*) diff_label_layer);



//     hash_label_layer = text_layer_create(GRect(0, 106, 67, 24));
//     text_layer_set_background_color(hash_label_layer, GColorClear);
//     text_layer_set_text_color(hash_label_layer, GColorWhite);
//     text_layer_set_text_alignment(hash_label_layer, GTextAlignmentLeft);
//     layer_add_child(window_get_root_layer(window), (Layer*) hash_label_layer);

//     //setting the labels for the numbers.
//     text_layer_set_text(block_label_layer, "Block:");
//     text_layer_set_text(diff_label_layer,"Diff:");
//     text_layer_set_text(hash_label_layer,"Hash:");




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
    bitmap_layer_destroy(bg_layer);
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
    update();
		//Initialize the app elements here!
        window = window_create();
        window_set_window_handlers(window, (WindowHandlers) {
                .load = window_load,
                .unload = window_unload,
        });

        tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler) tick_handler);

		window_stack_push(window, true);

  //update the data
  update();
  //psleep(2000);
  updateTimer=app_timer_register(300000,(AppTimerCallback) update, NULL);
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