/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 15:52:31 by soutchak          #+#    #+#             */
/*   Updated: 2024/07/31 15:55:05 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void playMP3(const char *filename) {
    mpg123_handle *mh;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;

    int driver;
    ao_device *dev;
    ao_sample_format format;
    int channels, encoding;
    long rate;

    // Initialize libao
    ao_initialize();
    driver = ao_default_driver_id();

    // Initialize mpg123
    mpg123_init();
    mh = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(mh);
    buffer = (unsigned char *) malloc(buffer_size * sizeof(unsigned char));

    // Open the MP3 file
    mpg123_open(mh, filename);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    // Set the output format
    format.bits = mpg123_encsize(encoding) * 8;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;

    // Open the output device
    dev = ao_open_live(driver, &format, NULL);
    if (dev == NULL) {
        fprintf(stderr, "Error opening device.\n");
        return;
    }

    // Play the MP3 file
    while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK) {
        ao_play(dev, (char *)buffer, done);
    }

    // Clean up
    free(buffer);
    ao_close(dev);
    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();
    ao_shutdown();
}
