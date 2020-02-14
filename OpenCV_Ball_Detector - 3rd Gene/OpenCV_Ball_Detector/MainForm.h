/*
OpenCV  Image processing tutorial & tip ft trick
Youtube channel: youtube.com/jackyltle
All source codes are free for the education purpose. 
*/


#pragma once
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "jackylib.h"		// This lib use for the convert string2char, int2string & Mat2Bmp
#include <stdio.h>
#include <iostream>
#include <conio.h> 
namespace OpenCV_Ball_Detector {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	using namespace cv;
	using namespace jacky_lib;


	const int FRAME_WIDTH = 640;	// Video frame
	const int FRAME_HEIGHT = 480;	// Video fram size
	const int MIN_OBJECT_AREA = 20 * 20;	// Min object need to tracking area spec
	const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5; // Max object need to tracking area spec
	Mat cameraframe;
	mat2picture mat2bmp;
	Mat inrImg;
	Mat hvsImg;
	Mat srcImg;		// All the Mat variables need to use for the image process in main
	int Hmax, Hmin, Vmax, Vmin, Smax, Smin;	// HVS max,min value
	int Max_obj = 50;	// Max number of object we can found in contourn
	int xm, ym;			// x,y ROI
	num2str n2str;		// define variables to get str convertion

						/// <summary>
						/// Summary for MainForm
						/// </summary>


	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
#pragma region Install Window Form Component


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnBrowser;
	private: System::Windows::Forms::PictureBox^  ptbVideo;

	private: System::Windows::Forms::TrackBar^  trbHmin;
	private: System::Windows::Forms::TrackBar^  trbHmax;
	private: System::Windows::Forms::TrackBar^  trbVmin;
	private: System::Windows::Forms::TrackBar^  trbVmax;
	private: System::Windows::Forms::TrackBar^  trbSmax;
	private: System::Windows::Forms::TrackBar^  trbSmin;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  txbHmax;
	private: System::Windows::Forms::TextBox^  txbHmin;
	private: System::Windows::Forms::TextBox^  txbVmax;
	private: System::Windows::Forms::TextBox^  txbVmin;
	private: System::Windows::Forms::TextBox^  txbSmax;
	private: System::Windows::Forms::TextBox^  txbSmin;

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnBrowser = (gcnew System::Windows::Forms::Button());
			this->ptbVideo = (gcnew System::Windows::Forms::PictureBox());
			this->trbHmin = (gcnew System::Windows::Forms::TrackBar());
			this->trbHmax = (gcnew System::Windows::Forms::TrackBar());
			this->trbVmin = (gcnew System::Windows::Forms::TrackBar());
			this->trbVmax = (gcnew System::Windows::Forms::TrackBar());
			this->trbSmax = (gcnew System::Windows::Forms::TrackBar());
			this->trbSmin = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->txbHmax = (gcnew System::Windows::Forms::TextBox());
			this->txbHmin = (gcnew System::Windows::Forms::TextBox());
			this->txbVmax = (gcnew System::Windows::Forms::TextBox());
			this->txbVmin = (gcnew System::Windows::Forms::TextBox());
			this->txbSmax = (gcnew System::Windows::Forms::TextBox());
			this->txbSmin = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ptbVideo))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbHmin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbHmax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbVmin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbVmax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSmax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSmin))->BeginInit();
			this->SuspendLayout();
			// 
			// btnBrowser
			// 
			this->btnBrowser->Location = System::Drawing::Point(12, 12);
			this->btnBrowser->Name = L"btnBrowser";
			this->btnBrowser->Size = System::Drawing::Size(75, 23);
			this->btnBrowser->TabIndex = 0;
			this->btnBrowser->Text = L"Video";
			this->btnBrowser->UseVisualStyleBackColor = true;
			this->btnBrowser->Click += gcnew System::EventHandler(this, &MainForm::btnBrowser_Click);
			// 
			// ptbVideo
			// 
			this->ptbVideo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->ptbVideo->Location = System::Drawing::Point(289, 50);
			this->ptbVideo->Name = L"ptbVideo";
			this->ptbVideo->Size = System::Drawing::Size(388, 284);
			this->ptbVideo->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->ptbVideo->TabIndex = 1;
			this->ptbVideo->TabStop = false;
			// 
			// trbHmin
			// 
			this->trbHmin->Location = System::Drawing::Point(49, 51);
			this->trbHmin->Maximum = 500;
			this->trbHmin->Name = L"trbHmin";
			this->trbHmin->Size = System::Drawing::Size(186, 45);
			this->trbHmin->TabIndex = 2;
			this->trbHmin->Value = 69;
			// 
			// trbHmax
			// 
			this->trbHmax->Location = System::Drawing::Point(49, 102);
			this->trbHmax->Maximum = 500;
			this->trbHmax->Name = L"trbHmax";
			this->trbHmax->Size = System::Drawing::Size(186, 45);
			this->trbHmax->TabIndex = 2;
			this->trbHmax->Value = 9;
			// 
			// trbVmin
			// 
			this->trbVmin->Location = System::Drawing::Point(49, 153);
			this->trbVmin->Maximum = 500;
			this->trbVmin->Name = L"trbVmin";
			this->trbVmin->Size = System::Drawing::Size(186, 45);
			this->trbVmin->TabIndex = 2;
			this->trbVmin->Value = 160;
			// 
			// trbVmax
			// 
			this->trbVmax->Location = System::Drawing::Point(49, 204);
			this->trbVmax->Maximum = 500;
			this->trbVmax->Name = L"trbVmax";
			this->trbVmax->Size = System::Drawing::Size(186, 45);
			this->trbVmax->TabIndex = 2;
			this->trbVmax->Value = 85;
			// 
			// trbSmax
			// 
			this->trbSmax->Location = System::Drawing::Point(49, 306);
			this->trbSmax->Maximum = 500;
			this->trbSmax->Name = L"trbSmax";
			this->trbSmax->Size = System::Drawing::Size(186, 45);
			this->trbSmax->TabIndex = 2;
			this->trbSmax->Value = 97;
			// 
			// trbSmin
			// 
			this->trbSmin->Location = System::Drawing::Point(49, 255);
			this->trbSmin->Maximum = 500;
			this->trbSmin->Name = L"trbSmin";
			this->trbSmin->Size = System::Drawing::Size(186, 45);
			this->trbSmin->TabIndex = 2;
			this->trbSmin->Value = 500;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(8, 51);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(34, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Hmax";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(8, 153);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(33, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Vmax";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(8, 255);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(33, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Smax";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(7, 102);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(31, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Hmin";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(8, 204);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(30, 13);
			this->label5->TabIndex = 3;
			this->label5->Text = L"Vmin";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(7, 306);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(30, 13);
			this->label6->TabIndex = 3;
			this->label6->Text = L"Smin";
			// 
			// txbHmax
			// 
			this->txbHmax->Location = System::Drawing::Point(241, 51);
			this->txbHmax->Name = L"txbHmax";
			this->txbHmax->Size = System::Drawing::Size(42, 20);
			this->txbHmax->TabIndex = 4;
			// 
			// txbHmin
			// 
			this->txbHmin->Location = System::Drawing::Point(241, 102);
			this->txbHmin->Name = L"txbHmin";
			this->txbHmin->Size = System::Drawing::Size(42, 20);
			this->txbHmin->TabIndex = 4;
			// 
			// txbVmax
			// 
			this->txbVmax->Location = System::Drawing::Point(241, 153);
			this->txbVmax->Name = L"txbVmax";
			this->txbVmax->Size = System::Drawing::Size(42, 20);
			this->txbVmax->TabIndex = 4;
			// 
			// txbVmin
			// 
			this->txbVmin->Location = System::Drawing::Point(241, 204);
			this->txbVmin->Name = L"txbVmin";
			this->txbVmin->Size = System::Drawing::Size(42, 20);
			this->txbVmin->TabIndex = 4;
			// 
			// txbSmax
			// 
			this->txbSmax->Location = System::Drawing::Point(241, 255);
			this->txbSmax->Name = L"txbSmax";
			this->txbSmax->Size = System::Drawing::Size(42, 20);
			this->txbSmax->TabIndex = 4;
			// 
			// txbSmin
			// 
			this->txbSmin->Location = System::Drawing::Point(241, 306);
			this->txbSmin->Name = L"txbSmin";
			this->txbSmin->Size = System::Drawing::Size(42, 20);
			this->txbSmin->TabIndex = 4;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(689, 346);
			this->Controls->Add(this->txbSmin);
			this->Controls->Add(this->txbSmax);
			this->Controls->Add(this->txbVmin);
			this->Controls->Add(this->txbVmax);
			this->Controls->Add(this->txbHmin);
			this->Controls->Add(this->txbHmax);
			this->Controls->Add(this->trbSmax);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->trbSmin);
			this->Controls->Add(this->trbVmax);
			this->Controls->Add(this->trbVmin);
			this->Controls->Add(this->trbHmax);
			this->Controls->Add(this->trbHmin);
			this->Controls->Add(this->ptbVideo);
			this->Controls->Add(this->btnBrowser);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ptbVideo))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbHmin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbHmax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbVmin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbVmax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSmax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSmin))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

#pragma endregion


	private: System::Void btnBrowser_Click(System::Object^  sender, System::EventArgs^  e) {

		
		VideoCapture videocap;
		videocap.open(0);						// Capture video from camera
												//videocap.open("objecttracking.mp4");	// Capture video from file (here i use video file)
		if (!videocap.isOpened()) {
			MessageBox::Show("Fail to open video");
			_getch();
			return;
		}
		videocap.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH); // Set video frame size
		videocap.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
		while (1) // The loop to get all video frame for processing
		{
			vector <vector<int>> objs; // Added
			// get H,V,S value from trackbar
			Hmin = trbHmax->Value;
			Hmax = trbHmin->Value;
			Vmin = trbVmax->Value;
			Vmax = trbVmin->Value;
			Smin = trbSmax->Value;
			Smax = trbSmin->Value;
			txbHmax->Text = Hmax.ToString();
			txbHmin->Text = Hmin.ToString();
			txbVmin->Text = Vmin.ToString();
			txbVmax->Text = Vmax.ToString();
			txbSmin->Text = Smin.ToString();
			txbSmax->Text = Smax.ToString();

			videocap.read(srcImg); // get the video frame

								   //Start to pre-image processing
			cvtColor(srcImg, hvsImg, COLOR_BGR2HSV);	// Convert Color image to HSV image ( 3 color: H,S and V)
														//imshow("HVS", hvsImg);
			inRange(hvsImg, Scalar(Hmin, Smin, Vmin), Scalar(Hmax, Smax, Vmax), inrImg); // Filter obj base on color.

			Mat erode_element = getStructuringElement(MORPH_RECT, cv::Size(4, 4));
			Mat dilate_element = getStructuringElement(MORPH_RECT, cv::Size(8, 8));
			erode(inrImg, inrImg, erode_element);
			erode(inrImg, inrImg, erode_element);
			//imshow("Erode", inrImg);
			dilate(inrImg, inrImg, dilate_element);
			dilate(inrImg, inrImg, dilate_element);
			//dilate(inrImg, inrImg, dilate_element);
			imshow("Dilate", inrImg);

			//Now we can start to find contours

			Mat temps;				// Get a temp Mat variable for image processing
			inrImg.copyTo(temps);	// Copy from inrImg to Temps image

			vector<vector<cv::Point>> conts;
			vector<Vec4i> hier;
			findContours(temps, conts, hier, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);	//Find contours

																						// After got contours & hier we can start to detect obj we need
			double arearef = 0;
			bool objFound = false;
			if (hier.size() > 0)	// hier: number of object detected after contours processing.
			{
				int obj_qty = hier.size();
				if (obj_qty < Max_obj)	//Only process when number of obj lower than define max obj.
				{
					for (int idx = 0; idx >= 0; idx = hier[idx][0]) {
						Moments moms = moments((cv::Mat)conts[idx]);	// You can find moments definition in OPENCV doc
						double area = moms.m00;
						if (area > MIN_OBJECT_AREA) // if area in range we defined -> obj found
						{
							vector <int> object;
							object.push_back(moms.m10 / area);
							object.push_back(moms.m01 / area);
							objs.push_back(object);
							objFound = true;
						}
						else
						{
							objFound = false;
						}
					}
				}
				if (objFound == true) // Ater got obj we will go to draw a circle on the object
				{
					for (int i = 0; i < objs.size(); i++) {

						cv::circle(srcImg, cv::Point(objs.at(i).at(0), objs.at(i).at(1)), 20, cv::Scalar(0, 255, 0), 2);
						cv::putText(srcImg, n2str.int2str(objs.at(i).at(0)) + " , " + n2str.int2str(objs.at(i).at(1)), cv::Point(objs.at(i).at(0), objs.at(i).at(1) + 45), 3, 1, Scalar(0, 255, 0));

					}
				}

			}
			// We need to show main video & obj found on picture box
			resize(srcImg, srcImg, cv::Size(320, 240));
			ptbVideo->Image = mat2bmp.Mat2Bimap(srcImg); // Mat convert to BMP we use from jackylib library
			ptbVideo->Refresh();
			//imshow("a", srcImg);
			if (waitKey(30) == 27)
				break;
		}

	}
	private: System::Void btnProcess_Click(System::Object^  sender, System::EventArgs^  e) {

	}
	
	
	};



}
