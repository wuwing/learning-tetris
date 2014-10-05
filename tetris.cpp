/******************************************************
 * File Name:   tetris.cpp
 * Author:      kojimai
 * Creater Time:2014年09月19日 星期五 20时51分40秒
******************************************************/

#include "wx/wx.h"
#include "wx/menu.h"
#include <cstdlib>
#include <algorithm>

enum allshape{
	NoShape,ZShape,SShape,LineShape,TShape,SquareShape,LShape,MLSape
};//枚举所有的形状

const int coords[8][4][2]={
	0,0, 0,0, 0,0, 0,0,
	0,-1, 0,0, -1,0, -1,1,
	0,-1, 0,0, 1,0, 1,1,
	0,-1, 0,0, 0,1, 0,2,
	-1,0, 0,0, 1,0, 0,1,
	0,0, 1,0, 0,1, 1,1,
	-1,-1, 0,-1, 0,0, 0,1,
	1,-1, 0,-1, 0,0, 0,1,
};//各种形状的坐标表示	

class Shape//建立一个形状类
{
	public:
		Shape(){
			SetShape(NoShape);//初始构造为无形状的情况
		}
		void SetShape(allshape shape);//赋给当前的形状值
		void RandomShape();//随机赋形状

		int x(int index) const{
			return coord[index][0];
		}
		int y(int index) const{
			return coord[index][1];
		}
		Shape Rotate();//旋转

	private:
		void SetX(int index,int x){
			coord[index][0]=x;
		}
		void SetY(int index,int y){
			coord[index][1]=y;
		}
		//改变形状

		int coord[4][2];//形状的坐标
		allshape curshape;//当前形状
};
void Shape::SetShape(allshape shape)
{
	for(int i=0;i<4;i++)
	{
		coord[i][0]=coords[shape][i][0];
		coord[i][1]=coords[shape][i][1];
	}
	curshape = shape;
	return;
}
void Shape::RandomShape()
{
	int ran = rand()%7 + 1;
	SetShape(ran);//(allshape(ran))
}
Shape Shape::Rotate()
{
	if(curshape == SquareShape)
		return *this;
	Shape ret;
	ret.curshape = curshpae;
	for(int i=0;i<4;i++)
	{
		ret.SetX(i,y(i));
		ret.SetY(i,-x(i));
	}
	return ret;
}

//游戏窗口
class LeftPanel:public wxPanel
{
	public:
		LeftPanel(wxPanel *parent);
		void Start();
		void Pause();

	protected:
		void OnPaint(wxPaintEvent &event);
		void OnKeyDown(wxKeyEvent &event);
		void OnTimer(wxCommandEvent &event);

	private:
		const int BoardWidth = 10,BoardHeight = 20;

		allshape & ShapeAt(int x,int y){
			return board[BoardWidth*y+x];
		}
		void ClearBoard();
		void DropDown();
		void OneLineDown();
		void Dropped();
		void RemoveFullLines();
		void NewShape();
		bool TryMove(const Shape& newshpae,int newX,int newY);
		void DrawSquare(wxPaintDC &dc,int x,int y,allshape nshape);
		//void LevelUp();

		wxTimer *timer;
		wxPanel *mp;
		bool Paused;
		bool Started;
		bool FallingFinished;
		Shape nowshape;
		int nowx;
		int nowy;
		int socre;
		int level;
		allshape board[BoardWidth][BoardHeight];
};
LeftPanel::LeftPanel(wxPanel *parent):wxPanel(parent,wxID_ANY,wxPoint(-1,-1),wxDefaultPosition,wxBORDER_NONE)
{
	timer = new wxTimer(this,1);
	Paused = false;
	Started = false;
	FallingFinished = false;
	level = 1;
	socre = 0;

	ClearBoard();

	Connect(wxEVT_PAINT,wxPaintEventHandler(LeftPanel::OnPaint));
	Connect(wxEVT_TIMER,wxCommandEventHandler(LeftPanel::OnTimer));
	Connect(wxEVT_KEY_DOWN,wxKeyEvnetHandler(LeftPanel::OnKeyDown));
}
void LeftPanel::Start()
{
	if(Paused)
		return;
	Started = true;
	FallingFinished = false;
	level = 1;
	socre = 0;
	ClearBoard();

	NewShape();
	timer->Start(300);
}
void LeftPanel::NewShape()  {
	nowshape.RandomShape();
	return;
}
void LeftPanel::Pause() {//暂停
	if(!Started) return;

	Paused = !Paused;
	if(!Paused)  {
		timer->Start(300);
	}
	else  {
		timer->Stop();
	}
}
void LeftPanel::ClearBoard()  {
	for(int i = 0; i < BoardWidth; i++)
		for(int j = 0; j < BoardHeight; j++)
			board[i][j] = NoShape;
}
bool LeftPanel::TryMove(const Shape& piece,int newX,int newY)  {
	for(int i = 0; i < 4; i++)  {
		int x = newX + newPiece.x(i);
		int y = newY + newPiect.y(i);
		if(x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
			return false;
		if(ShapeAt(x,y) != NoShape)
			return false;
	}
	nowshape = piece ;
	nowx = newX;
	nowy = newY;
	//Refresh();
	return true;
}
void LeftPanel::newshpae()  {
	nowshape.RandomShape();
	nowx = BoardWidth/2 + 1;
	nowy = BoardHeight - 1 ;//+miny();

	if(!TryMove(nowshape,nowx,nowy))  {
		nowshape.SetShape(NoShape);
		timer->Stop();
		Started = false;
	}
}

//状态栏
class RightPanel:public wxPanel
{
	public:
		RightPanel(wxPanel *parent);
		wxPanel *mp;
};
RightPanel::RightPanel(wxPanel *parent):wxPanel(parent,wxID_ANY,wxPoint(-1,-1),wxDefautlPositon)
{
	//
}

//总框架
class Tetris:public wxFrame
{
	public:
		Tetris(const wxString &title);

		LeftPanel *lp;
		RightPanel *rp;
		wxMenuBar *mb;
		wxPanel *mp;
	protected:
		void OnQuit(wxCommandEvent &event);
	private:
		wxMenubar *menubar;
		wxMenu *file;
};
Tetris::Tetris(const wxString &title):wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(400,200))//
{
	mp = new wxPanel(this,wxID_ANY);

	wxBoxSizer *hbox = new wxBoxSizer(wxHORITONTAL);

	lp = new LeftPanel(mp);
	rp = new RightPanel(rp);

	hbox->Add(lp,1,wxALL,5);/**/
	hbox->Add(rp,1,wxALL,5);/**/

	mp->SetSizer(hbox);

	Centre();

	//菜单栏
	const int wxNew = 101;
	menubar = new wxMenubar;
	file = new wxMenu;
	file->Append(wxNew,wxT("New Game"));
	file->Append(wxID_EXIT,wxT("&Quit"));
	menubar->Append(file,wxT("File"));
	Connect(wxNew,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(LeftPanel::Start));
	Connect(wxID_EXIT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(Tetris::OnQuit));
}

//运行端
class MyApp:public wxApp
{
	public:
		virtual bool OnInit();
};
IMPLEMENT_APP(MyApp)
bool MyApp::OnInit()
{
	Tetris *tetris = new Tetris(wxT("Tetris"));
	tetris->Show(true);
	return true;
}
