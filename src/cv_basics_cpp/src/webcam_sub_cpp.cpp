#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "opencv2/opencv.hpp"
#include "cv_bridge/cv_bridge.h"

using std::placeholders::_1;

class ImgSubscriber : public rclcpp :: Node
{
	public:
	ImgSubscriber()
	: Node("img_subscriber")
	{
		subscription_ = this->create_subscription<sensor_msgs::msg::Image>("video_frames",10,
											std::bind(&ImgSubscriber::topic_callback,
											this,_1));
		cv::namedWindow("Video Stream",cv::WINDOW_AUTOSIZE);
	}

	private:
	void topic_callback(const sensor_msgs::msg::Image::SharedPtr msg)
	{
		current_frame = cv_bridge::toCvShare(msg,sensor_msgs::image_encodings::BGR8)->image;
		cv::imshow("Video Stream",current_frame);
		cv::waitKey(1);
		RCLCPP_INFO(this->get_logger(),"\nReceiving video frame");
	}

	cv::Mat current_frame;
	rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
	rclcpp::init(argc,argv);
	rclcpp::spin(std::make_shared<ImgSubscriber>());
	rclcpp::shutdown();
	return 0;
}
