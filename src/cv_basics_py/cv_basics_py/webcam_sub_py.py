import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
import cv2
from cv_bridge import CvBridge


class ImageSubscriber(Node):
	def __init__(self):
		super().__init__('image_subscriber')
		self.subscription=self.create_subscription(
			Image,
			'video_frames',
			self.listener_callback,
			10
			)
		self.subscription #To ignore Unused variable warning(?)

		self.br = CvBridge()

	def listener_callback(self,data):
		self.get_logger().info('Receiving video frame')
		current_frame = self.br.imgmsg_to_cv2(data)
		cv2.imshow("Camera",current_frame)
		cv2.waitKey(1)


def main(args=None):
	rclpy.init(args=args)

	image_subscriber = ImageSubscriber()
	rclpy.spin(image_subscriber)

	image_subscriber.destroy_node()
	rclpy.shutdown()

if __name__ == '__main__':
	main()
