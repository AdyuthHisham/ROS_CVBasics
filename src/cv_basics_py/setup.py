from setuptools import setup

package_name = 'cv_basics_py'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='sysenso',
    maintainer_email='sysenso@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
'img_publisher_py = cv_basics_py.webcam_pub_py:main',
'img_subscriber_py = cv_basics_py.webcam_sub_py:main',
        ],
    },
)
