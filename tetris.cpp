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

		Shape Rotate();//旋转

	private:
		int coord[4][2];//形状的坐标
		allshape curshape;//当前形状
};

class Board:public wxPanel
{
	public:
	protected:
	private:
}
class Tetris :public wxFrame
{
	public:
		Tetris(const wxString &title);
};

IMPLEMENT_APP(MyApp)
Tetris::Tetris(const wxString &title):wxFrame(NULL,wxID_ANY,title,wxDefaultPosition,wxSize(180,380))
{
	Board *board = new Board(this);
	board->SetFocus();
	board->Centre();
}
