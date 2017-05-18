//
// App.xaml.cpp
// Реализация класса приложения.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace barcode_wp;

using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Animation;
using namespace Windows::UI::Xaml::Navigation;

// Документацию по шаблону "Пустое приложение" см. по адресу http://go.microsoft.com/fwlink/?LinkID=391641

/// <summary>
/// Инициализирует одноэлементный объект приложения.  Это первая выполняемая строка разрабатываемого
/// кода; поэтому она является логическим эквивалентом main() или WinMain().
/// </summary>
App::App()
{
	InitializeComponent();
	Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
}

/// <summary>
/// Вызывается при обычном запуске приложения пользователем. Будут использоваться другие точки входа,
/// если приложение запускается для открытия конкретного файла, отображения
/// результатов поиска и т. д.
/// </summary>
/// <param name="e">Сведения о запросе и обработке запуска.</param>
void App::OnLaunched(LaunchActivatedEventArgs^ e)
{
#if _DEBUG
	if (IsDebuggerPresent())
	{
		DebugSettings->EnableFrameRateCounter = true;
	}
#endif

	auto rootFrame = dynamic_cast<Frame^>(Window::Current->Content);

	// Не повторяйте инициализацию приложения, если в окне уже имеется содержимое,
	// только обеспечьте активность окна.
	if (rootFrame == nullptr)
	{
		// Создайте фрейм, используемый в качестве контекста навигации, и свяжите его с
		// ключом SuspensionManager
		rootFrame = ref new Frame();

		// TODO: Измените это значение на размер кэша, подходящий для вашего приложения.
		rootFrame->CacheSize = 1;

		if (e->PreviousExecutionState == ApplicationExecutionState::Terminated)
		{
			// TODO: Восстановление сохраненного состояния сеанса только при необходимости и планирование
			// шаги по окончательному запуску только после завершения восстановления.
		}

		// Размещение фрейма в текущем окне
		Window::Current->Content = rootFrame;
	}

	if (rootFrame->Content == nullptr)
	{
		// Удаляет турникетную навигацию для запуска.
		if (rootFrame->ContentTransitions != nullptr)
		{
			_transitions = ref new TransitionCollection();
			for (auto transition : rootFrame->ContentTransitions)
			{
				_transitions->Append(transition);
			}
		}

		rootFrame->ContentTransitions = nullptr;
		_firstNavigatedToken = rootFrame->Navigated += ref new NavigatedEventHandler(this, &App::RootFrame_FirstNavigated);

		// Если стек навигации не восстанавливается для перехода к первой странице,
		// настройка новой страницы путем передачи необходимой информации в качестве параметра
		// навигации.
		if (!rootFrame->Navigate(MainPage::typeid, e->Arguments))
		{
			throw ref new FailureException("Failed to create initial page");
		}
	}

	// Обеспечение активности текущего окна
	Window::Current->Activate();
}

/// <summary>
/// Восстанавливает переходы содержимого после запуска приложения.
/// </summary>
void App::RootFrame_FirstNavigated(Object^ sender, NavigationEventArgs^ e)
{
	auto rootFrame = safe_cast<Frame^>(sender);

	TransitionCollection^ newTransitions;
	if (_transitions == nullptr)
	{
		newTransitions = ref new TransitionCollection();
		newTransitions->Append(ref new NavigationThemeTransition());
	}
	else
	{
		newTransitions = _transitions;
	}

	rootFrame->ContentTransitions = newTransitions;
	rootFrame->Navigated -= _firstNavigatedToken;
}

/// <summary>
/// Вызывается при приостановке выполнения приложения. Состояние приложения сохраняется
/// без учета информации о том, будет ли оно завершено или возобновлено с неизменным
/// содержимым памяти.
/// </summary>
void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
	(void) sender;	// Неиспользуемый параметр
	(void) e;		// Неиспользуемый параметр

	// TODO: Сохранить состояние приложения и остановить все фоновые операции
}