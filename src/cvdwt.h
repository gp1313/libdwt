/**
 * @file
 * @author David Barina <ibarina@fit.vutbr.cz>
 * @brief OpenCV interface to libdwt.
 */
#ifndef CVDWT_H
#define CVDWT_H

#include <cv.h>

#include "libdwt.h"

/**
 * @defgroup cpp_ocv_interface C++ OpenCV interface
 * @{
 **/
#ifdef __cplusplus

/**
 * @namespace dwt
 * @brief Binding to OpenCV
 */
namespace dwt
{

/**
 * @brief Flags for @ref transform function.
 */
enum
{
	/**
	 * Perform forward transform.
	 */
	DWT_FORWARD = 1,

	/**
	 * Perform inverse transform.
	 */
	DWT_INVERSE = 2,

	/**
	 * Decompose one row or column.
	 */
	DWT_EXTREME = 4,

	/**
	 * Perform zero padding.
	 */
	DWT_PADDING = 8,

	/**
 	 * Simple image DWT.
	 * Size of image (outer frame) become a power of two. Size of nested
	 * image should be smaller or equal to outer frame. Outer frame is
	 * padded with zeros. Coefficients with large aplitude appear on inner
	 * image edges. Slowest variant.
	 */
	DWT_SIMPLE = 16,	

	/**
	 * Sparse image DWT.
	 * Size of image (outer frame) become a power of two. Size of nested
	 * image should be smaller or equal to outer frame. Coefficients with
	 * large aplitude do not appear on inner image edges. Undefined values
	 * remain in unused image area when you do not set @ref DWT_PADDING.
	 * Otherwise, unused image area is filled with zeros (slower than
	 * variant without zero padding).
	 */
	DWT_SPARSE = 32,

	/**
	 * Packed image DWT.
	 * Outer frame size is equal to inner image size. Inner image size can
	 * be of any size. Coefficients with large aplitude do not appear on
	 * inner image edges. Fastest variant.
	 */
	DWT_PACKED = 64
};

/**
 * @brief Perform forward or inverse discrete wavelet transform of given image.
 * 
 * @note This function operates IN-PLACE.
 * @note This function uses CDF 9/7 wavelet.
 */
void transform(
	cv::Mat &img,				///< image/transform (outer size)
	cv::Size size,				///< size of inner image (inside of input image)
	int &j,					///< target scale (get and set when performing forward transform, get when performing inverse transform)
	int flags = DWT_FORWARD|DWT_SIMPLE	///< flags
);

/**
 * @brief Perform forward or inverse discrete wavelet transform of given image.
 * 
 * @note This function can operate OUT-OF-PLACE (src != dst) or IN-PLACE (src == dst).
 * @note This function uses CDF 9/7 wavelet.
  */
void transform(
	const cv::Mat &src,			///< input image/transform (outer size)
	cv::Mat &dst,				///< place output image/transform here
	cv::Size size,				///< size of inner image (inside of input image)
	int &j,					///< target scale (get and set when performing forward transform, get when performing inverse transform)
	int flags = DWT_FORWARD|DWT_SIMPLE	///< type of transform
);

/**
 * @brief Resize image to power of two sizes.
 *
 * @note This function operates IN-PLACE.
 */
void resizePOT(
	cv::Mat &img,				///< image that can be resized if needed
	int borderType = cv::BORDER_CONSTANT	///< the border type
);

/**
 * @brief Resize image to power of two sizes.
 *
 * @note This function operates OUT-OF-PLACE.
 */
void resizePOT(
	const cv::Mat &src,			///< input image
	cv::Mat &dst,				///< place resized image here
	int borderType = cv::BORDER_CONSTANT	///< the border type
);

/**
 * @brief Check if image size equals to power of two size.
 */
int isPOT(
	const cv::Mat &img			///< tested image
);

/**
 * @brief Displays the discrete wavelet transform in the specified window.
 *
 * This function is similar to cv::imshow from OpenCV.
 */
void wtshow(
	const string &winname,			///< name of the window
	const cv::Mat &image			///< transform to be shown
);

}

#endif
/**
 * @}
 */

#endif
