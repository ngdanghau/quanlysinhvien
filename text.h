#ifndef TEXT_H
#define TEXT_H
char FrameTitle[4][50]= {
	"CHUC NANG",
	"HUONG DAN CHUNG",
	"THONG BAO",
	"MAN HINH CHINH"
};

char MenuPhimTat[NUMBER_LINE_ITEM][50]= {
	"UP: Len",
	"DOWN: Xuong",
	"LEFT: Trai",
	"RIGHT: Phai",
	"PgUp: Keo Len",
	"PgDn: Keo Xuong",
	"Enter: Chon/ Xac Nhan",
	"ESC: Thoat"
};

char MenuText[NUMBER_MENU_ITEM][MENU_TEXT_LENGTH] = {
		"       LOP TIN CHI       ",
		"        SINH VIEN        ",
		"         MON HOC         ",
		"          DIEM           ",
		"          THOAT          "
};

char SubMenuText[NUMBER_MENU_ITEM-1][4][MENU_TEXT_LENGTH] = {
	{
		"Mo Lop TC",
		"Sua/Huy Lop Tin Chi",
		"Huy Lop TC",
		"In DS Lop TC"
	},
	{
		"Them Sinh Vien",
		"Sua/Xoa Sinh Vien",
		"In DSSV Theo Lop",
		"In DSSV Theo LopTC",
	},
	{
		"Them Mon Hoc",
		"Sua/Xoa Mon Hoc",
		"DK Mon Hoc/LopTC",
		"In DS Mon Hoc"
	},
	{
		"Nhap Diem",
		"In BD Lop TC",
		"In BD TB Lop",
		"In BD Tong Ket"
	}
};
#endif
