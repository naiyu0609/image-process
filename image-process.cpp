#include<iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp> 
using namespace std;
using namespace cv;

Mat im3;
Mat im4;
Mat im5;
Mat ROI_LU;//Canny�B�z
Mat ROI_RU;//Blur�B�z
Mat ROI_LD;//�v���X���B�z
Mat ROI_RD;//�ϥ�
bool textflag = 0;//�P�_�O�_���W�B���L ���~�൲��
int blur_ksize = 3;//Blur�B�z��lKernel Size
int Beta = 50;//�v���X���B�z��l�v����50%
int lowThreshold = 40;//Canny�B�z��l�C�֭�
int negative=1;//�ϥ�Flag 

static void BlurImg(int, void*) {//Blur�B�z
	textflag = 0;//����N�|��B���L�α�
	if (blur_ksize < 1) blur_ksize = 1;//�O�@���ର0
	blur(im3, ROI_RU, Size(blur_ksize, blur_ksize));//Blur�B�z
	imshow("im5", im5);//���ᦨ��
}

static void AddWeight(int, void*) {//�v���X���B�z
	textflag = 0;//����N�|��B���L�α�
	addWeighted(im3, (double)Beta/100, im4, 1 - (double)Beta/100, 0.0, ROI_LD);//�v���X���B�z
	imshow("im5", im5);//���ᦨ��
}

static void Negative(int, void*) {//�ϥ�
	textflag = 0;//����N�|��B���L�α�
	if (negative)bitwise_not(im3, ROI_RD);//Flag�}�Ҭ��ϥռv��
	else im3.copyTo(ROI_RD);//Flag���������`�v��
	imshow("im5", im5);//���ᦨ��
}

static void CannyThreshold(int, void*)//Canny�B�z
{
	textflag = 0;//����N�|��B���L�α�
	Mat  detected_edges,im3_gray;
	cvtColor(im3, im3_gray, COLOR_BGR2GRAY);//�N�v���令�Ƕ�
	blur(im3_gray, detected_edges, Size(3, 3));//����
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * 3, 5);//Canny�˴�
	ROI_LU = Scalar::all(0);
	im3.copyTo(ROI_LU, detected_edges);//�Q���˴����G��B�n
	imshow("im5", im5);//���ᦨ��
}

static void onMouse(int event, int x, int y, int flags, void*)//�ƹ��ƥ�
{
	switch (event) {

	case EVENT_LBUTTONUP://������U
		Mat im5_temp;
		im5.copyTo(im5_temp);//�ƻsim5
		putText(im5_temp, "B10607044", Point(x, y), FONT_HERSHEY_COMPLEX | FONT_ITALIC, 1, CV_RGB(255, 0, 255), 1, LINE_AA);//�g�Ǹ�
		imshow("im5", im5_temp);//���Ǹ��v��
		imwrite("B10607044.jpg", im5_temp);//�g�J�ɮ�
		textflag = 1;//�T�{���g�Ǹ�
		break;
	}
}

int main(int, char** argv)
{
	Mat im1 = imread(argv[1], 1);//Ū�v��1
	Mat im2 = imread(argv[2], 1);//Ū�v��2
	
	resize(im1, im3, Size(), 0.5, 0.5);//�Nim3����im1���e�U�@�b�v��

	resize(im2, im4, im3.size(), 1, 1);//�Nim4����im2�����e����im3���v��

	im5.create(im1.size[0], im1.size[1], CV_8UC3);//�إ�im5���e��im1�@��

	ROI_LU = im5(Rect(0, 0, im1.cols / 2, im1.rows / 2));//im5���W����(Canny)
	ROI_RU = im5(Rect(im1.cols / 2, 0, im1.cols / 2, im1.rows / 2));//im5�k�W����(Blur)
	ROI_LD = im5(Rect(0, im1.rows / 2, im1.cols / 2, im1.rows / 2));//im5���U����(AddWeight)
	ROI_RD = im5(Rect(im1.cols / 2, im1.rows / 2, im1.cols / 2, im1.rows / 2));//im5�k�U����(Negative)

	namedWindow("im1");//�إߵ���
	moveWindow("im1", 100, 100);//���ʵ���
	imshow("im1", im1);//����
	namedWindow("im2");//�إߵ���
	moveWindow("im2", 120, 250);//���ʵ���
	imshow("im2", im2);//����
	namedWindow("im3");//�إߵ���
	moveWindow("im3", 420, 100);//���ʵ���
	imshow("im3", im3);//����
	namedWindow("im4");//�إߵ���
	moveWindow("im4", 500, 250);//���ʵ���
	imshow("im4", im4);//����
	namedWindow("im5");//�إߵ���(4�����)
	namedWindow("im6");//�إߵ���(�ѼƵ���)
	moveWindow("im5", 800, 200);//���ʵ���
	createTrackbar("Blur Kernel Size:", "im6", &blur_ksize, 15, BlurImg);//�إ�Blur Kernel Size��Trackbar
	createTrackbar("Beta:", "im6", &Beta, 100, AddWeight);//�إ�Beta��Trackbar
	createTrackbar("Min Threshold:", "im6", &lowThreshold, 100, CannyThreshold);//�إ�Min Threshold��Trackbar
	createTrackbar("Negative:", "im6", &negative, 1, Negative);//�إ�Negative Flag��Trackbar
	BlurImg(0, 0);//����Blur�B�z
	AddWeight(0, 0);//����AddWeight�B�z
	CannyThreshold(0, 0);//����Canny�B�z
	Negative(0, 0);//����Negative�B�z
	moveWindow("im5", 700, 150);//���ʵ���
	imshow("im5", im5);//����4��v��

	setMouseCallback("im5", onMouse);//Ū�ƹ��ƥ�

	cout << "im1 size = " << im1.size() << endl;//��Xim1�v���j�p
	cout << "im2 size = " << im2.size() << endl;//��Xim2�v���j�p
	cout << "im3 size = " << im3.size() << endl;//��Xim3�v���j�p
	cout << "im4 size = " << im4.size() << endl;//��Xim4�v���j�p
	cout << "im5 size = " << im5.size() << endl;//��Xim5�v���j�p
	while (1) {//�T�{����
		if (waitKey() == 27 && textflag == 1) break;//�T�w���B���L�H�Ϋ�ESC�����{��
	}

	destroyAllWindows();//�����Ҧ�����
	return 0;
}