//
// App.xaml.h
// Объявление класса приложения.
//

#pragma once

#include "App.g.h"

namespace barcode_wp
{
	/// <summary>
	/// Обеспечивает зависящее от конкретного приложения поведение, дополняющее класс Application по умолчанию.
	/// </summary>
	ref class App sealed
	{
	public:
		App();

		virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e) override;

	private:
		Windows::UI::Xaml::Media::Animation::TransitionCollection^ _transitions;
		Windows::Foundation::EventRegistrationToken _firstNavigatedToken;

		void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);
		void RootFrame_FirstNavigated(Platform::Object^ sender, Windows::UI::Xaml::Navigation::NavigationEventArgs^ e);
	};
}
