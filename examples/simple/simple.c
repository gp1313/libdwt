/**
 * @file
 * @author David Barina <ibarina@fit.vutbr.cz>
 * @brief Simple example application showing usage of libdwt functions.
 */

#include "libdwt.h"

int main()
{
	// FIXME
	//dwt_util_test();

	dwt_util_init();

	dwt_util_log(LOG_INFO, "Library version is \"%s\".\n", dwt_util_version());
	dwt_util_log(LOG_INFO, "Using %i threads.\n", dwt_util_get_num_threads());
	dwt_util_log(LOG_INFO, "Using %i workers.\n", dwt_util_get_num_workers());

	// FIXME
	//const int x = 64, y = 64;
	const int x = 128, y = 128;
	//const int x = 256, y = 256;
	//const int x = 512, y = 512;
	//const int x = 768, y = 768;
	//const int x = 1024, y = 1024;
	//const int x = 1024, y = 10;
	//const int x = 1280, y = 10;
	//const int x = 2048, y = 10;
	//const int x = 4096, y = 10;
	const int stride_x = x*sizeof(float), stride_y = sizeof(float);
	void *data1, *data2;
	int j = -1;

	dwt_util_log(LOG_INFO, "generating test images...\n");

	// create test images
	dwt_util_alloc_image(&data1, stride_x, stride_y, x, y);
	dwt_util_test_image_fill_s(data1, stride_x, stride_y, x, y, 0);
	dwt_util_alloc_image(&data2, stride_x, stride_y, x, y);
	dwt_util_test_image_fill_s(data2, stride_x, stride_y, x, y, 0);

	// init timer
	dwt_clock_t time_start;
	dwt_clock_t time_stop;
	const int type = dwt_util_clock_autoselect();

	dwt_util_log(LOG_INFO, "forward transform...\n");

	// start timer
	time_start = dwt_util_get_clock(type);

	// forward transform
	dwt_util_set_accel(1); // FIXME
	dwt_util_set_num_threads(2); // FIXME
	dwt_util_set_num_workers(2); // FIXME
	dwt_cdf97_2f_s(data1, stride_x, stride_y, x, y, x, y, &j, 0, 0);

	// stop timer
	time_stop = dwt_util_get_clock(type);
	dwt_util_log(LOG_INFO, "elapsed time: %f secs\n", (double)(time_stop - time_start) / dwt_util_get_frequency(type));

	dwt_util_log(LOG_INFO, "inverse transform...\n");

	// start timer
	time_start = dwt_util_get_clock(type);

	// inverse transform
	dwt_util_set_accel(1); // FIXME
	dwt_util_set_num_threads(2); // FIXME
	dwt_util_set_num_workers(2); // FIXME
	dwt_cdf97_2i_s(data1, stride_x, stride_y, x, y, x, y, j, 0, 0);

	// stop timer
	time_stop = dwt_util_get_clock(type);
	dwt_util_log(LOG_INFO, "elapsed time: %f secs\n", (double)(time_stop - time_start) / dwt_util_get_frequency(type));

	// compare
	if( dwt_util_compare_s(data1, data2, stride_x, stride_y, x, y) )
		dwt_util_log(LOG_INFO, "images differs\n");
	else
		dwt_util_log(LOG_INFO, "success\n");

	dwt_util_finish();

	dwt_util_log(LOG_INFO, "saving...\n");
	dwt_util_save_to_pgm_s("data1.pgm", 1.0, data1, stride_x, stride_y, x, y);
	dwt_util_save_to_pgm_s("data2.pgm", 1.0, data2, stride_x, stride_y, x, y);

	return 0;
}
