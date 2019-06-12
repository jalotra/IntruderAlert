// This program acts as client to receive images through zmq and Opencv
// To work as a different process at all times in the flask or django app. 
#include <zmq.hpp>
#include <cstdio>
#include <string>
#include "opencv2/opencv.hpp"

//some configuration parameters::
#define DISPLAY_WINDOW_NAME "Received image";
#define RASPBERRY_PI_SERVER "tcp://localhost:5555"


// Main Function starts
int main(int argc, char **argv)
{
    //Have to do with some showFrames Variable and argv


    //Initialize zmq socket
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);

    //Connect to the Raspberry PI SERver
    std::cout<< "Connecting to the image server that is running on Raspberry Pi" << std::endl;
    socket.connect(RASPBERRY_PI_SERVER);

    //Creating a REquest Object
    zmq::message_t request(5);
    memcpy(request.data(), "Hello", 5);


    //REquest New Frames while the user presses Esc key
    bool requestedFrames = true;
    while(requestedFrames){
        //SENDING REquests
        std::printf("Sending request to the %s ", RASPBERRY_PI_SERVER);
        socket.send(request);       //Sends the request object(Hello) to the SErver

        // Getting the Replies
        zmq::message_t reply;
        socket.receive(&reply);
        std::printf('Recieved bytes that are %d long', static_cast<int>(reply.size()))
        
        // Store the image into an image that is number_Rows X number_Columns X channels
        vector<int> availableDimensions = {3280 ,2464};  //For Noir Camera version2
        
        //cv::Mat can be used to make a n dimensional aXb matrix.
        cv::Mat image(availableDimensions[0], availableDimensions[1], CV_8UC3, reply.data());
        //here CV_8U(3) makes a 8Bit matrix with the rows and columns as availableDimensions[0] 
        //and availableDimensions[1] and (3) makes it a 3-Channel for bgr output.  



        //Displaying the resulting Image
        bool showFrames = true;

        if(showFrames)
        {
            cv::imshow(DISPLAY_WINDOW_NAME, image);

            //Check for program termination 
            //Program doesnot terminates as long as Esc key is pressed.
            if( cv::waitkey(1) == 27)
            {
                showFrames = false;
            }
        }


    }
    // closing the Socket
    socket.close();
    cv::destroyAllWindows();
    return 0;



}