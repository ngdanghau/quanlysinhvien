# Quản Lý Sinh Viên
ĐỀ TÀI MÔN CTDL & GT
KHÓA 2018 CNTT – 2017 PTUDĐPT
Quản lý điểm sinh viên theo hệ tín chỉ:  Ta tổ chức các danh sách sau: 
- Danh sách môn học: cây nhị phân tìm kiếm cân bằng (MAMH (C10) , TENMH (C50), STCLT (số tín chỉ lý thuyết – số nguyên), STCTH (số tín chỉ thực hành – số nguyên))
- Danh sách Lop Tín chỉ: danh sách tuyến tính là 1 mảng con trỏ có tối đa 10000 lớp (MALOPTC (số nguyên tự động tăng),  MAMH, Niên khóa, Học kỳ, Nhóm, số sv min, số sv max, hủy lớp (boolean), con trỏ dssv): con trỏ dssv sẻ trỏ đến danh sách sinh viên  đăng ký lớp tín chỉ.
- Danh sách sinh viên : danh sách liên kết đơn (MASV (C15), HO, TEN,  PHAI, SODT, MALOP (C15))
- Danh sách Đăng ký (danh sách liên kết đơn): ( MASV ,  DIEM)
Chương trình có các chức năng sau : 
a. Mở lớp tín chỉ : cho phép cập nhật (thêm / xóa / hiệu chỉnh ) thông tin của lớp tín chỉ
b. In danh sách sinh viên đã đăng ký lớp tín chỉ  theo các tham số : niên khóa, học kỳ, nhóm , mã môn học  
c. NhapSV : Cập nhập sinh viên của 1 lớp: nhập vào mã lớp trước, sau đó nhập các sinh viên vào lớp đó.  
    Lưu ý : Khi nhập liệu phải đủ 3 chức năng Thêm / Xóa / Hiệu chỉnh 
    Quá trình nhập SV mới sẽ dừng khi ta nhập vào  mã sv là chuỗi rỗng.

d. In DSSV của 1 lớp (dựa vào mã lớp) theo thứ tự alphabet tăng dần của tên+họ.

e. Nhập môn học: cho phép cập nhật (thêm / xóa / hiệu chỉnh ) thông tin của môn học .

f. In DS môn  học : tăng dần theo tên môn học. 
g. Đăng ký lớp tín chỉ: user nhập vào mã sinh viên của mình, chương trình tự động in ra các thông tin của sinh viên.  Kế tiếp, user nhập vào Niên khóa, Học kỳ, chương trình sẽ tự động lọc ra các lớp tín chỉ đã mở trong niên khóa , học kỳ đó để sinh viên đăng ký. Dữ liệu in ra gồm : MAMH, TENMH, NHOM, số sv đã đăng ký, số slot còn trống
h. Hủy lớp tín chỉ : tự động hủy các lớp tín chỉ có số sv đăng ký < số sv min trong 1 niên khóa, học kỳ. Trước khi hủy, cần sự xác nhận của user.
i. Nhập điểm: User nhập vào niên khóa, học kỳ, nhóm , môn học. Căn cứ vào các giá trị này, chương trình sẽ tự động lọc ra danh sách sv đã đăng ký , và in ra màn hình danh sách theo dạng sau : 
STT	MASV	HO	TEN	DIEM
99	XXXX	XXXXXXXXXXX	XXXXX	
99	XXXX	XXXXXXXXXXX	XXXXX	
				
Bốn cột đầu đã có sẵn dữ liệu, lúc này user chỉ việc nhập điểm hoặc hiệu chỉnh điểm trực tiếp vào khung trên cột điểm.
j. In bảng điểm môn học của 1 lớp tín chỉ: User nhập vào niên khóa, học kỳ, nhóm , môn học, chương trình sẽ in ra bảng điểm đã thi . Kết  quả trên màn hình:

BẢNG ĐIỂM MÔN HỌC <tenmon>
	Niên khóa  :  ....   Học kỳ : .....  Nhóm : ...	 
	 
STT	MASV	HO	TEN	DIEM
99	XXXX	XXXXXXXXXXX	XXXXX	99
99	XXXX	XXXXXXXXXXX	XXXXX	99

k. In điểm trung bình kết thúc khóa học của 1 lớp theo số tín chỉ. Kết xuất:
BẢNG THỐNG KÊ ĐIỂM TRUNG BÌNH KHÓA HỌC 
	Lớp 	 : <malop>	 
	 
STT	MASV	HO	TEN	Điểm TB 
99	XXXX	XXXXXXXXXXX	XXXXX	99.9
99	XXXX	XXXXXXXXXXX	XXXXX	99.9

l. Bãng điểm tổng kết các môn của các sinh viên thuộc 1 lớp (trong bảng điếm tổng kết chỉ hiện thị điểm thi lớn nhất từng môn của sinh viên). Kết xuất:
BẢNG ĐIỂM TỔNG KẾT
			Lớp  : <malop>    	 
	  
STT	Mã SV	Họ Tên	Mã MH1	Mã MH2	Mã MH3	Mã MH4	Mã MH5	……..	Mã MHn
1	XXXX	XXXXXXX	99	99	99	99	99	99	99
2	XXXX	XXXXXXX	99	99	99	99	99	99	99

Lưu ý: Chương trình cho phép lưu các danh sách vào file; Kiểm tra các điều kiện khi nhập làm dữ liệu bị sai.
