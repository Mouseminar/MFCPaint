#pragma once

extern int Shape_Type;   //形状 1：直线 2：矩形 3：正圆 4：椭圆 5：曲线 6：画笔
extern bool isfill;      //填充 true：填充 false：不填充
extern int Line_Type;    //线型 0：实线 1：虚线
extern int Line_Width;   //线宽
extern COLORREF Line_Color; //线条颜色
extern COLORREF Fill_Color;	//填充颜色
extern CString Text;	//文字