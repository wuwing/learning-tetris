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

		void SetX(int index,int x){
			coord[index][0]=x;
		}
		void SetY(int index,int y){
			coord[index][1]=y;
		}
		//改变形状
		Shape Rotate();//旋转

	private:
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
void RandomShape()
{
	int x = rand()%7 + 1;
	SetShape(x);//(allshape(x))
}
Shape Shape::Rotate()
{
	if(curshape == SquareShape)
		return *this;
	Shape ret;
	ret.curshape = curshpae;
	for(int i=0;i<4;i++)
	{
		ret.SetX(i,coord[i][1]);
		ret.SetY(i,-coord[i][0]);
	}
	return ret;
}

//游戏窗口
class LeftPanel:public wxPanel
{
	public:
		LeftPanel(wxPanel *parent);
		wxPanel *mp;
};
LeftPanel::LeftPanel(wxPanel *parent):wxPanel(parent,-wxID_ANY,wxPoint(-1,-1))

//状态栏
class RightPanel:public wxPanel
{
	public:
		RightPanel(wxPanel *parent);
		wxPanel *mp;
};

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
	private:
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
