//
// MainPage.xaml.cpp
// Реализация класса MainPage.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2\highgui\highgui.hpp"

using namespace barcode_wp;

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


using namespace cv;
// Шаблон элемента пустой страницы задокументирован по адресу http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
	InitializeComponent();
}

void redact_img(Mat source ,bool by_x)
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


}

/// <summary>
/// Вызывается перед отображением этой страницы во фрейме.
/// </summary>
/// <param name="e">Данные о событиях, описывающие, каким образом была достигнута эта страница.  Свойство Parameter
/// обычно используется для настройки страницы.</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Неиспользуемый параметр

	// TODO: Подготовьте здесь страницу для отображения.

	// TODO: Если приложение содержит несколько страниц, обеспечьте
	// обработку нажатия аппаратной кнопки "Назад", выполнив регистрацию на
	// событие Windows::Phone::UI::Input::HardwareButtons.BackPressed.
	// Если вы используете NavigationHelper, предоставляемый некоторыми шаблонами,
	// данное событие обрабатывается для вас.
}
