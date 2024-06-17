# open_cv_image_data_processing

This project involves use of many of OpenCV's capabilities, which is a popular image processing library.
Implications of edge detection and overall image processing involve furthering generative image AI by preprocessing images for training as well as medical detection of anomolies on scans.


*** INITIAL STEPS ***
Enter the project directory in terminal and run make.
As a result you should get iptool in project/bin directory.

Please see bottom of file for Troubleshooting Errors section if you run into a problem at this stage or later stages.


*** FUNCTIONS ***
1. Sobel Edge Detection (ksize = 3): sobel3
Produces sobel edge detected image with ksize = 3 within ROI(s).
Parameters: None

2. Sobel Edge Detection (ksize = 5): sobel5
Produces sobel edge detected image with ksize = 5 within ROI(s).
Parameters: None

3. Color Edge Detection: coloredge
Produces Sobel edge image given V channel of RGB to HSV image within ROI(s).
Parameters: ksize for Sobel

4. Binary Edge Detection with Threshold and Angle: binaryedge
Produces image with edges that are at +- 10 degrees when inputted angle value within ROI(s).
Parameters: threshold angle
[Note: Angle should be within 0 to 180.]

5. Canny Edge Detection: cannycv
Produces edge image utilizing Canny edge detection function within ROI(s).
Parameters: None

6. Histogram Equalization: histoeq
Produces histogram equalizes image within ROI(s).
Parameters: None

7. Canny on Histogram Equalization: cannyhisto
Produces Canny edge image after applying histogram equailization within ROI(s).
Parameters: None

8. Otsu Thresholding: otsucv
Produces thresholding via Otsu's algorithm within ROI(s).
Parameters: None

9. QR Code Detection: QRcode
Outputs simplified detected QR code within ROI(s).
Parameters: None

10. QR Code Detection with Histogram Equalization: QRcodqul
Applies histogram equalization and then detects QR code within ROI(s).
Parameters: None


*** PARAMETERS FILE ***
There are for parameters:
1. the input file name;
2. the output file name;
3. the number of regions of interest;
4. x: starting leftmost pixel
5. y: starting topmost pixel
6. sx: distance to cover in x direction (left to right)
7. sy: distance to cover in y direction (top to bottom)
8. the name of the function operation
9. parameter(s) for function - specified in FUNCTIONS section above
10. Repeat #4-9 for each remaining ROI.


*** RUNNING THE PROGRAM ***
./iptool parameters.txt
(Be sure to run inside the bin folder.)


*** TROUBLESHOOTING ERRORS ***
If you run into a problem, try these steps. Firstly, delete .o files from iptools/image and iptools/utility folders. Second, delete everything inside the lib folder (it should be empty). Lastly, remove the iptool executable within project/bin if it is in there and start over again with the "make" command inside project folder. 
