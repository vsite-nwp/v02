#include "nwpwin.h"
#include "res.h"
#include "Header.h"
#include <sstream>
#include <Windows.h>
#include <map>
#include <vector>
#include <Commctrl.h>
#include <functional>

//const strings
#define ENUM_OUT_OF_RANGE_MESSAGE "Index is out of range!";
#define GRID_LENGTH_GREATER_THAN_ZERO_MESSAGE "Length must be greater than zero!"
#define COLUMNSPAN_INVALID_VALUE_MESSAGE "Columnspan needs to be equal or greater than 1"
#define ROWSPAN_INVALID_VALUE_MESSAGE "Rowspan needs to be equal or greater than 1"

using namespace std;

//types of windows
enum class WindowTypes
{
	Main,
	Parent,
	Grid,
	Edit,
	Button,
	Listbox
};

//Grid length type can be Pixels or a Star which represents ratio
enum class GridLengthType 
{
	Pixel,
	Star

};

//Window vertical alignment
enum class VerticalAlignments 
{
	Top,
	Center,
	Bottom,
	Stretch

};

enum class HorizontalAlignments 
{
	Left,
	Center,
	Right,
	Stretch

};

//General classes

template <class TypeToBeEnumerated>
class Enumerable {

public:

	//add at the back
	void Add(TypeToBeEnumerated* item) 
	{
		enumerableVektor.push_back(item);

	}

	//remove item
	bool Remove(const TypeToBeEnumerated* item) 
	{
		for (unsigned int i = 0; i < enumerableVektor.size(); ++i) {
			if (vektor[i] == item) {
				enumerableVektor.erase(enumerableVektor.begin() + i);
				return true;
			}
		}

		return false;

	}

	//remove at index
	bool RemoveAt(int elementIndex) 
	{
		if (elementIndex >= enumerableVektor.size()) 
		{
			return false;

		}

		enumerableVektor.erase(enumerableVektor.begin() + elementIndex);
		return true;
		
	}

	//return count
	int Count() const 
	{
		return enumerableVektor.size();

	}

	//return item
	TypeToBeEnumerated* operator[](unsigned int i) const 
	{
		if (i >= enumerableVektor.size()) {

			throw out_of_range(ENUM_OUT_OF_RANGE_MESSAGE);

		}

		return enumerableVektor[i];

	}

	~Enumerable() {
	enumerableVektor.clear();
	}

protected:

	vector<TypeToBeEnumerated*> enumerableVektor;

};
//Position structs

//struct representing thickness or margin
struct Thickness {

	int Top = 0;
	int Left = 0;
	int Right = 0;
	int Bottom = 0;

	Thickness(int uniformThickness) 
	{
		Top = uniformThickness;
		Left = uniformThickness;
		Right = uniformThickness;
		Bottom = uniformThickness;

	}

	Thickness() 
	{
		Top = 0;
		Left = 0;
		Right = 0;
		Bottom = 0;

	}

	Thickness(int left,int top,int right,int bottom) 
	{
		Top = top;
		Left = left;
		Right = right;
		Bottom = bottom;

	}
};

//Window position
struct WindowPosition {

	int x;
	int y;
	int Width;
	int Height;

	WindowPosition(int x, int y, int Width, int Height)
	{
		this->x = x;
		this->y = y;
		this->Width = Width;
		this->Height = Height;

	}
	WindowPosition()
	{
		this->x = 0;
		this->y = 0;
		this->Width = 0;
		this->Height = 0;

	}
	WindowPosition(HWND hw) 
	{
		if (hw == nullptr)
			hw = GetDesktopWindow();
		
		LPRECT r = new RECT();
		GetClientRect(hw, r);
		this->x = r->left;
		this->y = r->top;
		this->Width = r->right - r->left;
		this->Height = r->bottom - r->top;

	}

};

//Grid length represented in pixels or stars
class GridLength {

public:
	GridLengthType Type;

	GridLength() {

		Length = 0;
		Type = GridLengthType::Pixel;

	}

	GridLength(double Length, GridLengthType Type) {

		this->SetLength(Length);
		this->Type = Type;

	}

	double GetLength() const {

		return Length;

	}

	void SetLength(double Length) {

		if (Length <= 0) {
			throw invalid_argument(GRID_LENGTH_GREATER_THAN_ZERO_MESSAGE);
		}

		this->Length = Length;

	}

private:

	double Length;

};

//Grid row definition defined by height represented as GridLength
class RowDefinition {
public:

	RowDefinition(GridLength* height) {

		Height = *height;

	}

	RowDefinition() {

		Height =*new GridLength();

	}

	GridLength Height;
};

//Column definition defined by width represented as GridLength
class ColumnDefinition {

public:

	ColumnDefinition(GridLength* width) {

		Width = *width;

	}

	ColumnDefinition() {

		Width = *new GridLength();

	}

	GridLength Width;

};

//Collection of row definitions
class RowDefinitionCollection :public Enumerable<RowDefinition> 
{
public:

	//Row heights need to be calculated because of star GridLengths which represent ratio
	vector<double> RowHeightsInPixels(const WindowPosition& position) const 
	{
		vector<double> rowHeights;

		double sumPixelRows = CalculateSumForType(GridLengthType::Pixel);
		double sumStarRows = CalculateSumForType(GridLengthType::Star);

		double pixelsForStars=0;
		if ((position.Height - sumPixelRows)> 0) {
			pixelsForStars = (position.Height - sumPixelRows);

		}

		RowDefinition* currentRowDefinition;
		const int START_ROW_COLLECTION_INDEX = 0;
		for (unsigned int rowDefinitionIndex = START_ROW_COLLECTION_INDEX;
			rowDefinitionIndex < Count();
			rowDefinitionIndex++) {

			currentRowDefinition = enumerableVektor[rowDefinitionIndex];
			GridLength currentRowHeight = currentRowDefinition->Height;
			if (currentRowHeight.Type == GridLengthType::Pixel)
			{
				rowHeights.push_back(currentRowHeight.GetLength());

			}
			else if (currentRowHeight.Type == GridLengthType::Star)
			{
				double starsToPixels = currentRowHeight.GetLength() / sumStarRows * pixelsForStars;
				rowHeights.push_back(starsToPixels);

			}
		}

		return rowHeights;

	}
private:

	double CalculateSumForType(GridLengthType typeForSumCalculation) const
	{
		double sum = 0;
		const int START_ROW_COLLECTION_INDEX = 0;
		RowDefinition* currentRowDefinition;
		for (unsigned int rowDefinitionIndex = START_ROW_COLLECTION_INDEX;
			rowDefinitionIndex < Count();
			rowDefinitionIndex++)
		{
			currentRowDefinition = enumerableVektor[rowDefinitionIndex];
			GridLength currentRowHeight = currentRowDefinition->Height;

			if (currentRowHeight.Type == typeForSumCalculation)
			{
				sum += currentRowHeight.GetLength();

			}

		}

		return sum;

	}
};

//Collection of column definitions
class ColumnDefinitionCollection :public Enumerable<ColumnDefinition>
{
public:

	vector<double> ColumnWidthsInPixels(const WindowPosition& position) const
	{
		vector<double> columnWidths;

		double sumPixelColumns = CalculateSumForType(GridLengthType::Pixel);
		double sumStarColumns = CalculateSumForType(GridLengthType::Star);

		double pixelsForStars = 0;
		if ((position.Width - sumPixelColumns) > 0) {
			pixelsForStars = (position.Width - sumPixelColumns);

		}

		const int START_COLUMN_COLLECTION_INDEX = 0;
		ColumnDefinition* currentColumnDefinition;
		for (unsigned int columnDefinitionIndex = START_COLUMN_COLLECTION_INDEX;
			columnDefinitionIndex < Count();
			columnDefinitionIndex++) {

			currentColumnDefinition = enumerableVektor[columnDefinitionIndex];
			GridLength currentColumnWidth = currentColumnDefinition->Width;

			if (currentColumnWidth.Type == GridLengthType::Pixel) {
				columnWidths.push_back(currentColumnWidth.GetLength());

			}
			else if (currentColumnWidth.Type == GridLengthType::Star) {
				double starsToPixels = currentColumnWidth.GetLength() / sumStarColumns * pixelsForStars;
				columnWidths.push_back(starsToPixels);

			}

		}

		return columnWidths;

	}

	double CalculateSumForType(GridLengthType typeForSumCalculation) const
	{
		double sum = 0;
		const int START_COLUMN_COLLECTION_INDEX = 0;
		ColumnDefinition* currentColumnDefinition;
		for (unsigned int columnDefinitionIndex = START_COLUMN_COLLECTION_INDEX;
			columnDefinitionIndex < Count();
			columnDefinitionIndex++)
		{
			currentColumnDefinition = enumerableVektor[columnDefinitionIndex];
			GridLength currentColumnWidth = currentColumnDefinition->Width;

			if (currentColumnWidth.Type == typeForSumCalculation)
			{
				sum += currentColumnWidth.GetLength();

			}

		}

		return sum;

	};

};

class Window 
{
public:

	vector<WindowTypes> Types;
	//public static members
	static map<HWND, Window*> AllInstances;

	//public members
	string Name;
	HWND Handle = nullptr;
	WindowPosition* ParentBox = new WindowPosition();
	WindowPosition* Position = new WindowPosition();
	int ID;
	HMENU Menu;
	string Text;
	//virtual methods

	virtual void LoadWindow() = 0;

	//destructor
	~Window() 
	{
		AllInstances.erase(this->Handle);
		delete Handle;
		delete Position;
		delete ParentBox;
		delete Margin;
	}

	//static methods
	static Window* getInstanceByHandle(HWND hw)
	{
		return AllInstances[hw];

	}

	static Window* getInstanceById(int id) 
	{
		for (map< HWND, Window*>::iterator it = AllInstances.begin(); it != AllInstances.end(); ++it)
		{
			if (it->second->ID == id)
			{
				return it->second;

			}

		}

		return nullptr;

	}

	static Window* getInstanceByName(string name) 
	{
		const map< HWND, Window*>::iterator FIRST_POINTER = AllInstances.begin();
		const map< HWND, Window*>::iterator END_POINTER = AllInstances.end();


		for (map< HWND, Window*>::iterator currentPair = FIRST_POINTER;
			currentPair != END_POINTER;
			currentPair++)
		{

			Window* currentWindow = currentPair->second;
			if (currentWindow->Name == name)
			{
				return currentWindow;

			}

		}

		return nullptr;
	}
	//constructor
	Window(string className, string name = "",HWND parent = nullptr,
		double height = 0, double width = 0, Thickness* margin = new Thickness(),
		HorizontalAlignments horizontalAlignment = HorizontalAlignments::Left,
		VerticalAlignments verticalAlignment = VerticalAlignments::Top,
		string text = "", HMENU meni = nullptr)
	{
		ID = ++counter;
		
		this->Name = name;

		this->parent = parent;
		*this->ParentBox = *(new WindowPosition(parent));

		Height = height;
		Width = width;
		*Margin = *margin;

		HorizontalAlignment = horizontalAlignment;
		VerticalAlignment = verticalAlignment;

		CalculateObjectPosition();
		SetObjectPosition();

		this->Text = text;

		UINT flags = parent == nullptr ? WS_VISIBLE : WS_VISIBLE | WS_CHILD | WS_BORDER;
		
		if (meni == nullptr)
		{
			Menu = (HMENU)ID;

		}
			
		Handle = CreateWindow((LPCSTR)className.c_str(), (LPCSTR)text.c_str(), flags, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, parent, Menu, NULL, NULL);
		
		AllInstances.insert(pair<HWND, Window*>(Handle, this));
	}

	Window(string name = "", HWND parent = nullptr,
		double height = 0, double width = 0, Thickness* margin = new Thickness(),
		HorizontalAlignments horizontalAlignment = HorizontalAlignments::Left,
		VerticalAlignments verticalAlignment = VerticalAlignments::Top,
		string text = "", HMENU meni = nullptr) 
	{
		ID = ++counter;
		this->Name = name;

		this->parent = parent;
		*this->ParentBox = *(new WindowPosition(parent));

		Height = height;
		Width = width;
		*Margin = *margin;

		this->Text = text;

		HorizontalAlignment = horizontalAlignment;
		VerticalAlignment = verticalAlignment;

		this->Menu = meni == nullptr ? (HMENU)ID : meni;

	}
	void setIsEnabled(bool flag)
	{
		EnableWindow(this->Handle, (BOOL)flag);

	}

	//public methods

	void SetParentBox(const WindowPosition ParentBox)
	{
		*this->ParentBox = ParentBox;
		CalculateObjectPosition();
		SetObjectPosition();

	}

	bool IsTypeOf(WindowTypes type) 
	{
		const int START_INDEX = 0;
		for(int elementIndex=START_INDEX;
			elementIndex<Types.size();
			elementIndex++)
		{
			if (Types[elementIndex] == type)
			{
				return true;
			}
		}

		return false;

	}

	void SetObjectPosition()
	{
		SetWindowPos(Handle, parent, Position->x, Position->y, Position->Width, Position->Height, SWP_NOZORDER);

	}

	void SetHorizontalAlignment(HorizontalAlignments HorizontalAlignment) 
	{
		this->HorizontalAlignment = HorizontalAlignment;
		CalculateObjectPosition();
		SetObjectPosition();

	}
	void SetVerticalAlignment(VerticalAlignments VerticalAlignment) 
	{
		this->VerticalAlignment = VerticalAlignment;
		CalculateObjectPosition();
		SetObjectPosition();

	}
	void SetHeight(double height) 
	{
		this->Height = Height;
		CalculateObjectPosition();
		SetObjectPosition();

	}
	void SetWidth(double width) 
	{
		this->Height = Height;
		CalculateObjectPosition();
		SetObjectPosition();
	}
	bool operator<(Window* win) 
	{
		return true;

	}

	void CalculateObjectPosition() 
	{
		
		if (HorizontalAlignment == HorizontalAlignments::Left) 
		{
			Position->x = Margin->Left + ParentBox->x;
			Position->Width = Width;

		}
		else if (HorizontalAlignment == HorizontalAlignments::Center) 
		{
			Position->x = (ParentBox->Width - Width) / 2;
			Position->Width = Width;

		}
		else if (HorizontalAlignment == HorizontalAlignments::Right) 
		{
			Position->x = ParentBox->x + ParentBox->Width - Margin->Right - Position->Width;
			Position->Width = ParentBox->Width - Margin->Left - Margin->Right;

		}
		else if (HorizontalAlignment == HorizontalAlignments::Stretch) 
		{
			Position->x = Margin->Left + ParentBox->x;
			Position->Width = ParentBox->Width - Margin->Left - Margin->Right;

		}


		if (VerticalAlignment == VerticalAlignments::Top) 
		{
			Position->y = ParentBox->y + Margin->Top;
			Position->Height = Height;

		}
		else if (VerticalAlignment == VerticalAlignments::Center) 
		{
			Position->y = (ParentBox->Height - Height) / 2;
			Position->Height = Height;

		}
		else if (VerticalAlignment == VerticalAlignments::Bottom) 
		{
			Position->y = ParentBox->y + ParentBox->Height - Margin->Bottom - Position->Width;
			Position->Height = Height;

		}
		else if (VerticalAlignment == VerticalAlignments::Stretch) {
			Position->y = ParentBox->y + Margin->Top;
			Position->Height = ParentBox->Height - Margin->Top - Margin->Bottom;

		}
	}

protected:
	double Height = 0;
	double Width = 0;
	Thickness* Margin = new Thickness();
	HorizontalAlignments HorizontalAlignment = HorizontalAlignments::Left;
	VerticalAlignments VerticalAlignment = VerticalAlignments::Top;
	HWND parent = nullptr;
	static int counter;
};

class ParentWindow 
{
public:

	std::vector<Window*> Children;
	
	void LoadChildren() 
	{
		for (unsigned int i = 0; i < Children.size(); ++i) 
		{
			Children[i]->LoadWindow();

		}

	};

	ParentWindow() 
	{
		RegisterParentClass();

	};
	~ParentWindow() 
	{
		Children.clear();

	}
	virtual int OnCreate(CREATESTRUCT* pcs,HWND hw) = 0;

	bool OnCommand(int id, WORD childMessage, WPARAM wParam, LPARAM lParam); 

protected:
	static LRESULT CALLBACK EventHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	string RegisterParentClass() 
	{
		static int counter = 1;
		WNDCLASS wc; 
		stringstream ss;
		ss << "NWP" << counter++;
		ZeroMemory(&wc, sizeof wc);
		wc.lpfnWndProc = EventHandler;
		string pom = ss.str();
		wc.lpszClassName = pom.c_str();

		wc.cbWndExtra = sizeof(Window*);
		if(pom=="NWP2")
			wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = pom == "NWP2" ? (HBRUSH)GetStockObject(WHITE_BRUSH) : CreateSolidBrush(0x000000FF);
		bool dsad=RegisterClass(&wc);
		return ss.str();

	}
};

class Edit : public Window 
{
public:

	Edit(string name = "", HWND parent = nullptr,
		double height = 0, double width = 0, Thickness* margin = new Thickness(),
		HorizontalAlignments horizontalAlignment = HorizontalAlignments::Left,
		VerticalAlignments verticalAlignment = VerticalAlignments::Top, string text = "") :
		Window("EDIT", name, parent, height, width, margin, horizontalAlignment, verticalAlignment, text) {
	}

	void SetText(string text) 
	{
		SetWindowText(Handle, (LPCSTR)text.c_str());

	}

	LPSTR GetText(int maxCount=25) 
	{
		LPSTR text =new TCHAR[maxCount];
		GetWindowText(Handle, text, maxCount);
		return text;
	}

	void LoadWindow() {
		SetWindowPos(Handle, parent, Position->x, Position->y, Position->Width, Position->Height, SWP_NOZORDER);

	}
};

class Button : public Window 
{
public:

	Button(string name = "", HWND parent = nullptr,
		double height = 0, double width = 0, Thickness* margin = new Thickness(),
		HorizontalAlignments horizontalAlignment = HorizontalAlignments::Left,
		VerticalAlignments verticalAlignment = VerticalAlignments::Top, string text = "") :
		Window("BUTTON", name, parent, height, width, margin, horizontalAlignment, verticalAlignment, text) {
		Types.push_back(WindowTypes::Button);
	}

	void LoadWindow() 
	{
		SetWindowPos(Handle, parent, Position->x, Position->y, Position->Width, Position->Height, SWP_NOZORDER);

	}
};

class ListBox : public Window 
{
public:

	ListBox(string name = "", HWND parent = nullptr,
		double height = 0, double width = 0, Thickness* margin = new Thickness(),
		HorizontalAlignments horizontalAlignment = HorizontalAlignments::Left,
		VerticalAlignments verticalAlignment = VerticalAlignments::Top, string text = "") :
		Window("LISTBOX", name, parent, height, width, margin, horizontalAlignment, verticalAlignment, text) {

		Types.push_back(WindowTypes::Listbox);

	}

	int Count() {
		return SendMessage(Handle, LB_GETCOUNT, 0, 0);

	}
	int GetSelectedIndex()
	{
		return SendMessage(Handle, LB_GETCURSEL, 0, 0);

	}
	bool RemoveAt(int i)
	{
		if (i >= 0 && i < Count()) 
		{
			SendMessage(Handle, LB_DELETESTRING, (WPARAM)i, 0);
			return true;

		}

		return false;
		
	}

	void Add(LPSTR text) 
	{
		SendMessage(Handle, LB_ADDSTRING, 0, (LPARAM)text);

	}

	void LoadWindow() 
	{
		SetWindowPos(Handle, parent, Position->x, Position->y, Position->Width, Position->Height, SWP_NOZORDER);

	}
};

class Grid :public Window, public ParentWindow {

public:

	RowDefinitionCollection RowDefinitions;
	ColumnDefinitionCollection ColumnDefinitions;

	static map<Window*, unsigned int> Rows;
	static map<Window*, unsigned int> Columns;

	static map<Window*, unsigned int> RowSpans;
	static map<Window*, unsigned int> ColumnSpans;

	static void SetRow(Window* window, const int row) {

		if (Rows.find(window) != Rows.end()) {
			Rows[window] = row;
			return;
		}

		Rows.insert(pair<Window*, unsigned int>(window, row));
		
	}

	static void SetColumn(Window* window, const int column) {

		if (Columns.find(window) != Columns.end()) {
			Columns[window] = column;
			return;
		}

		Columns.insert(pair<Window*, unsigned int>(window, column));
		
	}

	static unsigned int GetRow(Window* element) {

		if (Rows.find(element) != Rows.end()) {
			return Rows[element];
		}

		return 0;
		
	}
	static unsigned int GetColumn(Window* element) {
		if (Columns.find(element) != Columns.end()) {
			return Columns[element];
		}
		else {
			return 0;
		}
	}

	static unsigned int GetColumnSpan(Window* element) {

		if (ColumnSpans.find(element) != ColumnSpans.end())
		{
			return ColumnSpans[element];

		}

		return 1;
	}

	static unsigned int GetRowSpan(Window* element) 
	{
		if (RowSpans.find(element) != RowSpans.end())
		{
			return RowSpans[element];

		}

		return 1;

	}

	static int SetColumnSpan(Window* element, int i) 
	{
		if (i < 1) {
			throw out_of_range(COLUMNSPAN_INVALID_VALUE_MESSAGE);
		}

		ColumnSpans[element] = i;
		
	}

	static int SetRowSpan(Window* element, int i) 
	{
		if (i < 1) {
			throw out_of_range(ROWSPAN_INVALID_VALUE_MESSAGE);

		}

		RowSpans[element] = i;
		
	}

	Grid(string name = "", HWND parent = nullptr, 
		double height = 0, double width = 0, Thickness* margin = new Thickness(),
		HorizontalAlignments horizontalAlignment = HorizontalAlignments::Left,
		VerticalAlignments verticalAlignment = VerticalAlignments::Top) :
		Window(name, parent, height, width, margin, horizontalAlignment, verticalAlignment) 
	{
		
		CalculateObjectPosition();

		DWORD flags = parent == nullptr ? WS_VISIBLE : WS_VISIBLE | WS_CHILD;
		std::string className = RegisterParentClass();
		Handle = CreateWindow(className.c_str(), (LPCSTR)Text.c_str(), flags, Position->x, Position->y, Position->Width, Position->Height, parent, Menu, NULL, this);
		
		AllInstances.insert(pair<HWND, Window*>(Handle, this));

		Types.push_back(WindowTypes::Grid);
		Types.push_back(WindowTypes::Parent);

	}
	void LoadWindow() 
	{
		CalculateObjectPosition();
		SetWindowPos(Handle, parent, Position->x, Position->y, Position->Width, Position->Height, SWP_NOZORDER);
	}

	void LoadChildren() 
	{
		CalculateChildrenPositions();
	}

	//bool OnCommand(int id, WORD childMessage,WPARAM wParam,LPARAM lParam) 
	//{
	//	MainWindow* mainWindow = reinterpret_cast<MainWindow*>(getInstanceByName("Main"));

	//	tuple<int, WORD> handlerID = make_tuple(id, childMessage);
	//	bool result = mainWindow->allHandlers.ExecuteHandler(handlerID,wParam,lParam);
	//	
	//	return result;

	//}

protected:
	int OnCreate(CREATESTRUCT* pcs,HWND hw) 
	{
		return 0;
	}

private:
	void CalculateChildrenPositions() 
	{
		vector<double> rowHeights = RowDefinitions.RowHeightsInPixels(*Position);
		vector<double> columnWidths = ColumnDefinitions.ColumnWidthsInPixels(*Position);
		
		double passedColumnsSum = 0;
		double passedRowsSum = 0;
		
		const int START_INDEX = 0;
		for (unsigned int childIndex = START_INDEX; 
			childIndex < this->Children.size();
			childIndex++) 
		{

			double calculatedX=0;
			double calculatedY = 0;
			double calculatedHeight = 0;
			double calculatedWidth = 0;

			Window* currentWindow = Children[childIndex];
			
			unsigned int rowHeightsIndex = 0;
			while (rowHeightsIndex < rowHeights.size())
			{
				if (rowHeightsIndex < GetRow(currentWindow)
					&& rowHeightsIndex != (rowHeights.size() - 1))
				{
					calculatedY += rowHeights[rowHeightsIndex];

					rowHeightsIndex++;
					continue;

				}
				else if (rowHeightsIndex < (GetRow(currentWindow) + GetRowSpan(currentWindow)))
				{
					calculatedHeight += rowHeights[rowHeightsIndex];
					
					rowHeightsIndex++;
					continue;

				}

				break;
			}

			unsigned int columnWidthIndex = 0;
			while (columnWidthIndex < columnWidths.size())
			{
				if (columnWidthIndex < GetColumn(currentWindow) 
					&& columnWidthIndex != (columnWidths.size() - 1))
				{
					calculatedX += columnWidths[columnWidthIndex];
					
					columnWidthIndex++;
					continue;

				}
				else if (columnWidthIndex < (GetColumn(currentWindow) + GetColumnSpan(currentWindow)))
				{
					calculatedWidth += columnWidths[columnWidthIndex];
					
					columnWidthIndex++;
					continue;

				}
				
				break;
			}

			currentWindow->SetParentBox(*(new WindowPosition(calculatedX, calculatedY, calculatedWidth, calculatedHeight)));
			currentWindow->LoadWindow();

		}

	}

};

class EventArgs
{
	//todo write event args
};

class MainWindowHandlers
{
	map <tuple<int, WORD>, function<void(Window*, WPARAM, LPARAM)>> commandHandlersDict;

	map <tuple<int, WORD>, function<void(Window*, WPARAM,LPARAM) >> customClassHandlersDict;

public:

	bool ExecuteHandler(tuple<int, WORD> idChildMessageTuple,WPARAM wParam,LPARAM lParam)
	{
		if (commandHandlersDict.find(idChildMessageTuple)!= commandHandlersDict.end())
		{
			int id = get<0>(idChildMessageTuple);
			WORD childMessage = get<1>(idChildMessageTuple);

			Window* senderWindow = Window::getInstanceById(id);
			commandHandlersDict[idChildMessageTuple](senderWindow,wParam,lParam);

			return true;

		} 
		
		return false;

	}

	void addCommandHandler(tuple<int, WORD> handlerID, function<void(Window*, WPARAM, LPARAM)> handlerFunction)
	{
		commandHandlersDict.insert(make_pair(handlerID, handlerFunction));
	}

};

class MainWindow : public Window,public ParentWindow
{
public:

	MainWindowHandlers allHandlers;

	MainWindow(string name, double height, double width,Thickness* margin) :
		Window(name, nullptr, height, width, margin, HorizontalAlignments::Left, VerticalAlignments::Top) {

		string className = RegisterParentClass();
		
		CalculateObjectPosition();
		
		Handle = CreateWindow(className.c_str(),(LPCSTR) "NWP", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
								Position->x, Position->y, Position->Width, Position->Height, nullptr, NULL, NULL, this);

		AllInstances.insert(pair<HWND, Window*>(Handle, this));

		Types.push_back(WindowTypes::Main);
		Types.push_back(WindowTypes::Parent);

	}

	void LoadWindow() 
	{
		LoadChildren();
	}

	//Handler methods

	function<void(Window*, WPARAM, LPARAM)> buttonAddClicked = [](Window* senderWindow, WPARAM wParam, LPARAM lParam)
	{
		Edit* edit = reinterpret_cast<Edit*>(Window::getInstanceByName("edit"));
		Button* remove = reinterpret_cast<Button*>(Window::getInstanceByName("remove"));
		ListBox* listBox = reinterpret_cast<ListBox*>(Window::getInstanceByName("listbox"));

		listBox->Add(edit->GetText());
		edit->SetText("");

		remove->setIsEnabled(true);
	};

	function<void(Window*, WPARAM, LPARAM)> buttonRemoveClicked = [](Window* senderWindow, WPARAM wParam, LPARAM lParam)
	{
		Button* remove = reinterpret_cast<Button*>(senderWindow);
		ListBox* listBox = reinterpret_cast<ListBox*>(Window::getInstanceByName("listbox"));

		listBox->RemoveAt(listBox->GetSelectedIndex());
		
		if (listBox->Count() == 0) 
		{
			remove->setIsEnabled(false);

		}
	};

	int OnCreate(CREATESTRUCT* pcs,HWND mainHandle) override
	{
		//Add Grid
		Grid* glavniGrid = new Grid("GlavniGrid", mainHandle, 0, 0, new Thickness(20), HorizontalAlignments::Stretch, VerticalAlignments::Stretch);
		//defining columns
		this->Children.push_back(glavniGrid);
		glavniGrid->ColumnDefinitions.Add(new ColumnDefinition(new GridLength(2, GridLengthType::Star)));
		glavniGrid->ColumnDefinitions.Add(new ColumnDefinition(new GridLength(1, GridLengthType::Star)));
		glavniGrid->ColumnDefinitions.Add(new ColumnDefinition(new GridLength(1, GridLengthType::Star)));

		//defining rows
		glavniGrid->RowDefinitions.Add(new RowDefinition(new GridLength(1, GridLengthType::Star)));
		glavniGrid->RowDefinitions.Add(new RowDefinition(new GridLength(1, GridLengthType::Star)));
		glavniGrid->RowDefinitions.Add(new RowDefinition(new GridLength(2, GridLengthType::Star)));


		//Add grid children windows
		ListBox* listBox = new ListBox("listbox", glavniGrid->Handle,
										0.0, 0.0, new Thickness(5),
										HorizontalAlignments::Stretch,
										VerticalAlignments::Stretch);

		Edit* edit = new Edit("edit", glavniGrid->Handle, 
								0.0, 0.0, new Thickness(5), 
								HorizontalAlignments::Stretch, 
								VerticalAlignments::Stretch);

		Button* buttonAdd = new Button("add", glavniGrid->Handle,
								0.0, 0.0, new Thickness(5),
								HorizontalAlignments::Stretch,
								VerticalAlignments::Stretch, "add");

		Button* buttonRemove = new Button("remove", glavniGrid->Handle,
											0.0, 0.0, new Thickness(5),
											HorizontalAlignments::Stretch,
											VerticalAlignments::Stretch, "remove");

		buttonRemove->setIsEnabled(false);

		//Set event handlers
		tuple<int, WORD> buttonAddClickID = make_tuple(buttonAdd->ID, BN_CLICKED);
		allHandlers.addCommandHandler(buttonAddClickID,buttonAddClicked);

		tuple<int, WORD> buttonRemoveClickID = make_tuple(buttonRemove->ID, BN_CLICKED);
		allHandlers.addCommandHandler(buttonRemoveClickID, buttonRemoveClicked);

		//set grid children in grid
		Grid::SetRow(listBox, 0);
		Grid::SetColumn(listBox, 0);
		Grid::SetRowSpan(listBox, 3);

		Grid::SetColumn(edit, 1);
		Grid::SetColumnSpan(edit, 2);

		Grid::SetRow(buttonAdd, 1);
		Grid::SetColumn(buttonAdd, 1);

		Grid::SetRow(buttonRemove, 1);
		Grid::SetColumn(buttonRemove, 2);
		
		//add children to grid
		glavniGrid->Children.push_back(listBox);
		glavniGrid->Children.push_back(edit);
		glavniGrid->Children.push_back(buttonAdd);
		glavniGrid->Children.push_back(buttonRemove);
		glavniGrid->LoadChildren();

		return 1;

	}



};

bool ParentWindow::OnCommand(int id,WORD childMessage,WPARAM wParam,LPARAM lParam)
{
	MainWindow* mainWindow = reinterpret_cast<MainWindow*>(Window::getInstanceByName("Main"));

	tuple<int, WORD> handlerID = make_tuple(id, childMessage);
	bool result = mainWindow->allHandlers.ExecuteHandler(handlerID, wParam, lParam);

	return result;

}

LRESULT CALLBACK ParentWindow::EventHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message == WM_CREATE)
	{
		CREATESTRUCT* pcs = reinterpret_cast<CREATESTRUCT*>(lParam);
		MainWindow* parentWindow = reinterpret_cast<MainWindow*>(pcs->lpCreateParams);
		parentWindow->OnCreate(pcs,hwnd);
		
		return 0;

	}

	else if (message == WM_COMMAND)
	{
		MainWindow* mainWindow = reinterpret_cast<MainWindow*>(Window::getInstanceByName("Main"));

		int id = LOWORD(wParam);

		WORD childMessage = HIWORD(wParam);

		mainWindow->OnCommand(id, childMessage, wParam, lParam);
		
	}
	else if (message == WM_DESTROY) 
	{
		PostQuitMessage(0);

	}

	return DefWindowProc(hwnd, message, wParam, lParam);

}

bool operator<(const GridLength& gr1, const GridLength& gr2) {

	if (gr1.Type == gr2.Type) 
	{
		return gr1.GetLength() < gr2.GetLength();

	}

    if (gr1.Type == GridLengthType::Pixel) 
	{
		return true;
	}

	return false;
	
}

bool operator<(const RowDefinition& row1, const RowDefinition& row2) 
{
	return row1.Height < row2.Height;

}

//static class members
int Window::counter = 0;
map<HWND, Window*> Window::AllInstances = {};
map<Window*, unsigned int> Grid::Rows = {};
map<Window*, unsigned int> Grid::Columns = {};
map<Window*, unsigned int> Grid::RowSpans = {};
map<Window*, unsigned int> Grid::ColumnSpans = {};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDM_V2));
	MainWindow* wnd = new MainWindow("Main", 300, 400, new Thickness(200, 200, 0, 0));
	
	Application app; 
	return app.Run();

}
