#include <gst/gst.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    GstElement *pipeline;
    GstElement *source;
    GstElement *sink;
    GstBus *bus;
    GstMessage *message;
    int status = 0;

    gst_init(&argc, &argv);

    pipeline = gst_pipeline_new("test-pipeline");
    source = gst_element_factory_make("videotestsrc", "source");
    sink = gst_element_factory_make("fakesink", "sink");

    if (pipeline == NULL || source == NULL || sink == NULL) {
        fprintf(stderr, "Failed to create GStreamer elements.\n");
        status = 1;
        goto cleanup;
    }

    g_object_set(source, "num-buffers", 30, NULL);
    gst_bin_add_many(GST_BIN(pipeline), source, sink, NULL);

    if (!gst_element_link(source, sink)) {
        fprintf(stderr, "Failed to link GStreamer elements.\n");
        status = 1;
        goto cleanup;
    }

    if (gst_element_set_state(pipeline, GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE) {
        fprintf(stderr, "Failed to set pipeline to PLAYING.\n");
        status = 1;
        goto cleanup;
    }

    printf("Pipeline is playing.\n");
    bus = gst_element_get_bus(pipeline);
    message = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                         GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    if (message != NULL && GST_MESSAGE_TYPE(message) == GST_MESSAGE_ERROR) {
        GError *error = NULL;
        gchar *debug_info = NULL;

        gst_message_parse_error(message, &error, &debug_info);
        fprintf(stderr, "Pipeline error: %s\n", error->message);
        g_clear_error(&error);
        g_free(debug_info);
        status = 1;
    } else {
        printf("Pipeline completed successfully.\n");
    }

    if (message != NULL) {
        gst_message_unref(message);
    }
    gst_object_unref(bus);

cleanup:
    if (pipeline != NULL) {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
    } else {
        if (source != NULL) {
            gst_object_unref(source);
        }
        if (sink != NULL) {
            gst_object_unref(sink);
        }
    }

    return status;
}
