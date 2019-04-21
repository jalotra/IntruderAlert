# IntruderAlert

Project Details :
1. This project is intended to use opencv and deep learning to tackle the problem of intruders entering a house.

---

How it Works:
1. Whenever a new object(a human) is seen in the premises of my house the rpi detects it and sends images of the intuder in two to three batches depending on the distance between the intuder and the camera location to a web server via a POST Request.</br>

2. On the webserver a cnn is deployed that runs a python script on the image and returns a response of the probability of different classes in json format.</br>

3.  The different classes are the different people's names that the cnn has been trained upon.


