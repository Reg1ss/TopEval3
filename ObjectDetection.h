#ifndef _TP_SSD_GPU_DETECTION_H__
#define _TP_SSD_GPU_DETECTION_H__

#include "CPUCore/TpErrorCode.h"
#include <memory>
#include "opencv2/opencv.hpp"
#include "TopObjectDetection/ObjectDetectionCommon.h"

namespace tpv
{
	class ObjectDetection
	{
	public:
		virtual ~ObjectDetection(){};

		virtual TpErrorCode Init(const ObjectDetectionInitParams &objectDetectionInitParams) = 0;
		virtual TpErrorCode Release() = 0;

		virtual TpErrorCode Detect(const cv::Mat &image, std::vector<ObjectDetectionResult> &result) = 0;
		virtual TpErrorCode Detect(const std::vector<cv::Mat> &imageVec, std::vector<std::vector<ObjectDetectionResult>> &resultVec) = 0;
		virtual TpErrorCode Detect(const cv::cuda::GpuMat &image, std::vector<ObjectDetectionResult> &result) = 0;
		virtual TpErrorCode Detect(const std::vector<cv::cuda::GpuMat> &imageVec, std::vector<std::vector<ObjectDetectionResult>> &resultVec) = 0;
	};
}


#endif