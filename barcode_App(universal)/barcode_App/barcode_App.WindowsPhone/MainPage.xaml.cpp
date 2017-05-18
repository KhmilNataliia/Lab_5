//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <robuffer.h>
#include <opencv2\imgproc.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\core.hpp>

using namespace barcode_App;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation; 

using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Storage::Streams;
using namespace Microsoft::WRL;


using namespace cv;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
	InitializeComponent();
	cv::Mat bmp1 = cv::imread("demo.jpg");
	cv::Mat bmp2 = cv::Mat(bmp1.rows, bmp1.cols, CV_8UC4);
	cv::cvtColor(bmp1, bmp2, CV_BGR2BGRA);
	WriteableBitmap^ wbmp = ref new WriteableBitmap(bmp2.cols, bmp2.rows);
	IBuffer^ buffer = wbmp->PixelBuffer;
	unsigned char* dstPixels;
	ComPtr<IBufferByteAccess> pBufferByteAccess;
	ComPtr<IInspectable> pBuffer((IInspectable*)buffer);
	pBuffer.As(&pBufferByteAccess);
	pBufferByteAccess->Buffer(&dstPixels);
	memcpy(dstPixels, bmp2.data, bmp2.step.buf[1] * bmp2.cols * bmp2.rows);
}


/*void redact_img(Mat source, bool by_x)
{
	Mat gray_img;
	cvtColor(source, gray_img, CV_BGR2GRAY);
	Mat grad_by_x;
	Mat grad_by_y;
	Sobel(gray_img, grad_by_x, 1, 0, 3);
	Sobel(gray_img, grad_by_y, 0, 1, 3);

	abs(grad_by_x);
	abs(grad_by_y);

	Mat res_gradient;
	if (by_x)
	{
		subtract(grad_by_x, grad_by_y, res_gradient);
	}
	else
	{
		subtract(grad_by_y, grad_by_x, res_gradient);
	}
	convertScaleAbs(res_gradient, res_gradient);

	GaussianBlur(res_gradient, res_gradient, cv::Size(7, 7), 0);
	threshold(res_gradient, res_gradient, 100, 255, CV_THRESH_BINARY);


}*/

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter

	// TODO: Prepare page for display here.

	// TODO: If your application contains multiple pages, ensure that you are
	// handling the hardware Back button by registering for the
	// Windows::Phone::UI::Input::HardwareButtons.BackPressed event.
	// If you are using the NavigationHelper provided by some templates,
	// this event is handled for you.
}
