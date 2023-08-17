#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "opencv2/opencv.hpp"
#include "cv_bridge/cv_bridge.h"
#include <chrono>

using namespace std::chrono_literals;

class ImgPublisher : public rclcpp :: Node
{
	public:
	ImgPublisher()
	: Node("img_publisher")
	{
		cap = cv::VideoCapture(0);
		publisher_ = this->create_publisher<sensor_msgs::msg::Image>("video_frames",10);
		timer_ = this->create_wall_timer(
		150ms, std::bind(&ImgPublisher::timer_callback,this));
	}

	private:
	void timer_callback()
	{
		if(!cap.isOpened())
		{
		RCLCPP_INFO(this->get_logger(), "\nCANT PARSE VIDEO");	
		}
		else
		{
			cap.read(frame);
			//std::unique_ptr<sensor_msgs::msg::Image> msg = cv_bridge::CvImage(
						//std_msgs::msg::Header(), "bgr8", frame).toImageMsg();	
			sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(
						std_msgs::msg::Header(), sensor_msgs::image_encodings::BGR8, frame).toImageMsg();
			publisher_->publish(*msg.get());
		}

		RCLCPP_INFO(this->get_logger(), "\nPublishing Video Frame");
	}


	cv::VideoCapture cap;
	cv::Mat frame;
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;

};

int main(int argc, char * argv[])
{
	rclcpp::init(argc,argv);
	rclcpp::spin(std::make_shared<ImgPublisher>());
	rclcpp::shutdown();
	return 0;
}
