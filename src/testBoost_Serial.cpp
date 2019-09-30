#include<iostream>
#include<boost/asio.hpp>
#include<boost/bind.hpp>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace boost::asio;

int main(int argc,char** argv)
{
    io_service io;
    serial_port sp(io,"/dev/ttyS2");
    serial_port sp_1(io,"/dev/ttyS1");
    sp.set_option(serial_port::baud_rate(9600));
    sp.set_option(serial_port::flow_control(serial_port::flow_control::none));
    sp.set_option(serial_port::parity(serial_port::parity::none));
    sp.set_option(serial_port::stop_bits(serial_port::stop_bits::one));
    sp.set_option(serial_port::character_size(8));

    sp_1.set_option(serial_port::baud_rate(9600));
    sp_1.set_option(serial_port::flow_control(serial_port::flow_control::none));
    sp_1.set_option(serial_port::parity(serial_port::parity::none));
    sp_1.set_option(serial_port::stop_bits(serial_port::stop_bits::one));
    sp_1.set_option(serial_port::character_size(8));
    int counter=10;
    while (counter--)
    {
       string testData = cv::format("%-8.2f%-8.2f%-8.2f", 125.0 , 233.0, 777.0);
	   write(sp,buffer(testData.data(),testData.size()));
       cout<<"ttyS2 Sending data:"<<testData;
       char buf[24];
       read(sp_1,buffer(buf));
       //boost::system::error_code err;
       //sp_1.read_some(buffer(buf),err);
       cout<<"ttyS1 receved:"<<buf<<endl;
    }
    io.run();
    return 0;
}