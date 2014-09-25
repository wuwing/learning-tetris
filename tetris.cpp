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
//游戏窗口
class LeftPanel:public wxPanel
{
	public:
		LeftPanel(wxPanel *parent);
		wxPanel *mp;
};
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

	hbox->Add(lp);/**/
	hbox->Add(rp);/**/

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
