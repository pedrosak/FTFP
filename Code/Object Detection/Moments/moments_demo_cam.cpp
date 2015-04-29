#define IN_PER_PIXEL 0.0078125 // the number of inches in the FOV of the camera divided by the number of pixels horizontally
#define ENC_PER_INCH 0.00806452 //how many inches are in one turn of the encoder  
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace cv;
using namespace std;

//global variables
Point2f midPoint;
Mat src; Mat src_gray;
int thresh = 20;
int max_thresh = 255;
RNG rng(12345);
int *rubiks, *simon, *etch;
int iRubiks = 0;
int iSimon = 0;
int iEtch = 0;
int threshHold = 10000;
VideoCapture capture;
FILE *file;
int USB;
struct termios tty;
struct termios tty_old;
struct termios cam_tty;
//function headers
void capImage();
void thresh_callback(int, void*);
vector<int> whatObj(vector<double> area, vector<double> arcs, int* rubiks, int* etch, int* simon);
void printObject(vector<int> needDrawing, vector<Point2f> mc);
void printShuffle(float Diff);

int main(int, char** argv)
{
	//variables for signaling what object we saw
	rubiks = &iRubiks;
	simon = &iSimon;
	etch = &iEtch;

	USB = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
	memset(&tty, 0, sizeof tty);
	tty_old = tty;
	cfsetospeed(&tty, (speed_t)9600);
	cfsetispeed(&tty, (speed_t)9600);
	/* Setting other Port Stuff */
	tty.c_cflag &= ~PARENB;        // Make 8n1
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CSIZE;
	tty.c_cflag |= CS8;

	tty.c_cflag &= ~CRTSCTS;       // no flow control
	tty.c_cc[VMIN] = 1;                  // read doesn't block
	tty.c_cc[VTIME] = 0;                  // 0.5 seconds read timeout
	tty.c_cflag |= CREAD;     // turn on READ & ignore ctrl lines



	/* Make raw */
	cfmakeraw(&tty);

	/* Flush Port, then applies attributes */
	tcflush(USB, TCIFLUSH);
	while (true)
	{
		char buf = '\0';
		/* Whole response*/
		do
		{
			read(USB, &buf, 1);

		} while (buf != 'C');//while we haven't read a C from the serial line

		cout << "Camera on!: " << buf << endl;
		tcflush(USB, TCIFLUSH);
		if(buf == 'C')
			capImage();
	}

}

void capImage()
{
	capture.open(-1);//open up USB on port (-1)
	char cam_buf = '\0';
	cout << "Capturing image" << endl;
	if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return; }
	while (capture.read(src)) //while we are getting valid readings form the camera
	{

		if (src.empty()) //if we did not capture anything
		{
			printf(" --(!) No captured frame -- Break!");
			return;
		}
		/// Convert image to gray and blur it
		Size s = src.size();
		midPoint = Point2f(static_cast<float>(s.width / 2.0), static_cast<float>(s.height / 2.0));
		cvtColor(src, src_gray, COLOR_BGR2GRAY);
		blur(src_gray, src_gray, Size(3, 3));

		thresh_callback(0, 0);
		read(USB, &cam_buf, 1); //check to see if we've been signaled to turn off
		if (cam_buf == 'C') 
		{
			cout << "Camera off!: " << cam_buf << endl;
			return;
		}
	}

}

void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	/// Detect edges using canny
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Get the moments
	vector<Moments> mu(contours.size());
	vector<double> area(contours.size());

	for (size_t i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
		area[i] = contourArea(contours[i]);
	}

	if (area.size() == 0 || arcs.size() == 0) //if we have no valid areas of interest, return
		return;
	
	///  Get the mass centers:
	vector<Point2f> mc(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));
	}

	/// Draw contours
	vector<int> needDrawing = whatObj(area, arcs, rubiks, etch, simon);
	if (needDrawing.size() == 0)
		return;

	if (*rubiks == 5 || *simon == 5 || *etch == 5) //if we have a hit, lets tell the Arduino what we have
		printObject(needDrawing, mc);




}

//this function is used to determine what object we have by looking at the range on the areas
vector<int> whatObj(vector<double> area, vector<double> arcs, int* rubiks, int* etch, int* simon)
{
	int s = 0;
	int e = 0;
	int r = 0;
	vector<int> eIdx;
	vector<int> sIdx;
	vector<int> rIdx;

	//iterate over all the areas we found in the image
	for (size_t i = 0; i < area.size(); i++)
	{
		if(area[i]>6000 && area[i]<11000) //range for rubik's
		{
			r++;
			rIdx.push_back(i);
			continue;
		}

		if((area[i]>90000)&&(area[i]<110000)) //range for simon
		{
			s++;
			sIdx.push_back(i);
			continue;
		}
		if(area[i]>50&&area[i]<80) //range for etch
		{
			e++;
			eIdx.push_back(i);
			continue;
		}	
	}
	cout << "e: " << e << "\tr: " << r << "\ts: " << s << endl; //sanity check

	if (r == 9) // nine matches means rubik's cube
	{
		(*rubiks)++;
		*etch = 0;
		*simon = 0;
		printf("Rubik's cube! %d\n", *rubiks);
		return rIdx;

	}

	else if (s == 1) //one match means simon
	{
		(*simon)++;
		*etch = 0;
		*rubiks = 0;
		printf("Simon! %d\n", *simon);
		return sIdx;

	}
	else if (e == 1 && r<4) //one match means etch
	{
		(*etch)++;
		*simon = 0;
		*rubiks = 0;
		printf("Etch! %d\n", *etch);
		return eIdx;
	}
	vector<int> emptyVector;
	return emptyVector;
}

//this function is used to tell the arduino how far to shuffle
void printShuffle(float Diff)
{
		
	char buf = '\0';
	float inches = Diff*IN_PER_PIXEL;
	int encodes = inches/ENC_PER_INCH;
	static char float2str[50];
	int n =sprintf(float2str,"%d",encodes); //print number of encoder turns to a string
	cout<<"number of bytes written: "<<n<<endl;
	cout<<float2str<<endl;
	//need to write how many inches to shuffle (or cm)
	write(USB, float2str, n);

	/* Whole response*/
	std::string response;

	do
	{
		read(USB, &buf, 1);

	} while (buf != 'M'); //wait until Arduino has confirmed it moved
	cout << "Char from Arduino: " << buf << endl;

}

//used to print the object it saw to the arduino
void printObject(vector<int> needDrawing, vector<Point2f> mc)
{

	int index;

	if (*rubiks == 5)
	{
		*simon = 0;
		*etch = 0;
		*rubiks = 0;
		float average = 0;

		for (int i = 0; i < needDrawing.size(); i++)//determine how far out of alignment we are in the x direction
		{
			average += midPoint.x-mc[needDrawing[i]].x;
		}

		average = (float)(average /needDrawing.size());
		cout<<average<<endl;
		if (abs(average) > 30) //if the average is more than 30 pixels away from the center, we need to shuffle
		{
			write(USB, "X", 1);
			printShuffle(average);
		}
		else
		{
			write(USB, "2", 1); //tell arduino we saw a Rubik's cube
			int n = 0;
			char buf = '\0';
			/* Whole response*/
			do
			{
				read(USB, &buf, 1);
			} while (buf != 'R'); //wait for confirmation from the arduino
			cout << "Char from Arduino: " << buf << endl;
		}

	}
	if (*simon == 5)
	{

		*simon = 0;
		*etch = 0;
		*rubiks = 0;
		float average = 0;

		for (int i = 0; i < needDrawing.size(); i++)//determine how far out of alignment we are in the x direction
		{
			average += midPoint.x-mc[needDrawing[i]].x;
		}

		average = (float)(average /needDrawing.size());
		cout<<average<<endl;
		if (abs(average) > 30)//if the average is more than 30 pixels away from the center, we need to shuffle
		{
			write(USB, "X", 1);

			printShuffle(average);
		}
		else
		{
			write(USB, "3", 1); //tell the Arduino we saw a Simon
			int n = 0;
			char buf = '\0';
			/* Whole response*/
			std::string response;

			do
			{
				read(USB, &buf, 1);
			} while (buf != 'S'); //wait for response
			cout << "Char from Arduino: " << buf << endl;
		}

	}

	if (*etch == 5)
	{
		*simon = 0;
		*etch = 0;
		*rubiks = 0;

		index = distance(needDrawing.begin(), max_element(needDrawing.begin(), needDrawing.end())); //find the index of the largest area since this will be the screen
		Point2f offset = midPoint - mc[needDrawing[index]];

		cout<<offset.x<<endl;
		if (abs(offset.x) > 30) //if the offset is greater than 30 pixels
		{
			write(USB, "X", 1);
			printShuffle(offset.x);
		}
		else
		{

			write(USB, "1", 1); //tell the arduino we saw an etch a sketch
			int n = 0;
			char buf = '\0';

			/* Whole response*/
			std::string response;

			do
			{
				read(USB, &buf, 1);
			} while (buf != 'E'); //wait for confirmation from the arduino
			cout << "Char from Arduino: " << buf << endl;
		}

	}

}
