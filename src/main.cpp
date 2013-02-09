#include <stdio.h>
#include <gst/gst.h>
#include <glib.h>
#include "player.hpp"
#include "service.hpp"

using namespace ThriftyGramophone;
using namespace std;

static gboolean bus_call (
        GstBus     *bus,
        GstMessage *msg,
        gpointer    data)
{
  GMainLoop *loop = (GMainLoop *) data;

  switch (GST_MESSAGE_TYPE (msg)) {

    case GST_MESSAGE_EOS:
      g_print ("End of stream\n");
      g_main_loop_quit (loop);
      break;

    case GST_MESSAGE_ERROR: {
      gchar  *debug;
      GError *error;

      gst_message_parse_error (msg, &error, &debug);
      g_free (debug);

      g_printerr ("Error: %s\n", error->message);
      g_error_free (error);

      g_main_loop_quit (loop);
      break;
    }
    default:
      break;
  }

  return TRUE;
}

int main(int argc, char **argv)
{
  GMainLoop *loop;
  GstElement *pipeline, *source, *decoder, *sink;
  GstBus *bus;
  guint bus_watch_id;

  // Initialization
  gst_init(&argc, &argv);
  loop = g_main_loop_new(NULL, FALSE);

  // Check input arguments
  if(argc!=2)
  {
      g_printerr ("Usage: %s <MP3 filename>\n", argv[0]);
      return -1;
  }

  /* Create gstreamer elements */
   pipeline = gst_pipeline_new ("audio-player");
   source   = gst_element_factory_make ("filesrc","file-source");
   decoder  = gst_element_factory_make ("mad","mad");
   sink     = gst_element_factory_make ("autoaudiosink", "audio-output");

   if (!pipeline || !source || !decoder || !sink) {
      g_printerr ("One element could not be created. Exiting.\n");
      return -1;
    }

    /* Set up the pipeline */

   /* we set the input filename to the source element */
    g_object_set (G_OBJECT (source), "location", argv[1], NULL);

    /* we add a message handler */
    bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
    bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
    gst_object_unref (bus);

    /* we add all elements into the pipeline */
    /* file-source | mp3 decoder | alsa-output */
    gst_bin_add_many (GST_BIN (pipeline),
                      source, decoder, sink, NULL);

    /* we link the elements together */
    /* file-source -> mp3-decoder -> alsa-output */
    gst_element_link_many (source, decoder, sink);
    // g_signal_connect (demuxer, "pad-added", G_CALLBACK (on_pad_added), decoder);

    /* Set the pipeline to "playing" state*/
     g_print ("Now playing: %s\n", argv[1]);
     gst_element_set_state (pipeline, GST_STATE_PLAYING);

     /* Iterate */
     g_print ("Running...\n");
     g_main_loop_run (loop);

     /* Out of the main loop, clean up nicely */
     g_print ("Returned, stopping playback\n");
     gst_element_set_state (pipeline, GST_STATE_NULL);

     g_print ("Deleting pipeline\n");
     gst_object_unref (GST_OBJECT (pipeline));
     g_source_remove (bus_watch_id);
     g_main_loop_unref (loop);

     return 0;


  // Player player;
  // ThriftyGramophoneService service(player);
  
  // service.start();

//  boost::shared_ptr<apache::thrift::transport::TTransport> socket(new apache::thrift::transport::TSocket("localhost", 9090));
//  boost::shared_ptr<apache::thrift::transport::TTransport> transport(new apache::thrift::transport::TBufferedTransport(socket));
//  boost::shared_ptr<apache::thrift::protocol::TProtocol> protocol(new apache::thrift::protocol::TBinaryProtocol(transport));
//  ThriftyGramophone::ThriftyGramophoneClient client(protocol);

//  socket->open();
//  client.play(argv);
//  socket->close();
}
