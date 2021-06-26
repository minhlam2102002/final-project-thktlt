# final_project_ktlt

Yêu cầu:
- Tạo ra tập tin siêu dữ liệu (metadata) (???????): 
  + Thông tin về các văn bản đã tiền xử lý (đã được rút trích) và nội dung chính của từng văn bản theo cấu trúc tự định nghĩa.
  + Khi thêm/xóa tập tin văn bản, chương trình tự động cập nhật dữ liệu của tập tin siêu dữ liệu.

- Rút trích đơn giản nội dung chính
  + Stopword:https://github.com/stopwords/vietnamese-stopwords/blob/master/vietnamese-stopwords.txt
- Tìm kiếm văn bản
- Xếp hạng kết quả tìm kiếm theo mức độ liên quan

Gợi ý làm bài:
- Danh sách văn bản:
  + Tập tin index.txt chứa danh sách các tập tin văn bản có trong thư mục
  + Mục đích để biết được trong thư mục có những tệp tin nào, thuận tiện cho việc đọc tệp tin
  + Chương trình nhận được đường dẫn đến thư mục chứa chỉ mục và các văn bản (????) bằng nhập chuẩn hoặc tham số hàm main.
- Rút trích nội dung chính:
  + Các văn bản được rút trích nội dung chính để lưu lại vào metadata.
  + Nội dung chính được xác định dựa trên các từ quan trọng xuất hiện trong văn bản.
  + Tính bằng tần suất xuất hiện của từ đó trong văn bản, chia cho tổng số từ có trong văn bản.
  + Tỷ lệ này nằm trong khoảng (0, 1)
  + Tự chọn tỉ lệ a, b tức là độ quan trọng nằm trong đoạn [a, b]. Giải thích lý do chọn giá trị a, b trong báo cáo (???????)
  + stopword sẽ bị loại bỏ khỏi danh sách từ quan trọng
- Tổ chức siêu dữ liệu (metadata):
  + Sinh metadata dựa vào các văn bản có trong index.txt
  + Khi thêm/xóa (linkedlist, array) văn bản trong index.txt, tự động cập nhật metadata, tính thời gian cập nhật metadata. 
  + Sinh viên tự xây dựng cấu trúc  siêu dữ liệu (skip list???) sao cho các thao tác thêm/xóa các văn bản, siêu dữ liệu được cập nhật nhanh chóng.
- Truy vấn thông tin:
  + Người dùng nhập vào một chuỗi từ khóa. Kết quả trả về các văn bản liên quan (???) xếp hạng giảm dần theo mức độ liên quan.
  + Dựa trên độ tương tự của văn bản với các từ khóa nhập vào.
  + Độ tương tự của văn bản với từ khóa được tính bằng cách:
    ++ Tìm tập giao tập từ quan trọng, của văn bản với tập từ khóa, nếu có thì văn bản được xem là có liên quan -> Tìm từ qtrong của văn bản, so sánh với từ qtrọng của từ khóa, ra được tập giao.
    ++ Số lượng từ giao càng nhiều thì độ liên quan càng cao, văn bản trong kết quả được xếp hạng càng cao
  + Kết quả trả về bao gồm:
    ++ Thứ hạng
    ++ Tựa đề văn bản
    ++ Tên tập tin văn bản
    ++ Mức độ liên
  + Số lượng văn bản có thể rất nhiều do đó các thao tác tìm kiếm (skiplist log(n)), sắp xếp (quicksort????) cần được tối ưu để tăng tốc việc truy vấn. 
  + So sánh với nhau thời gian truy vấn, các nhóm có kết quả truy vấn càng tốt và thời gian truy vấn càng ngắn sẽ được cộng điểm.

- Yêu cầu lập trình:
  + Hiển thị menu cho phép người dùng chọn các chức năng.
  + Tận dụng các cấu trúc dữ liệu đơn giản đã học.
  + Phải truy vấn dựa trên tập tin siêu văn bản, không truy vấn trực tiếp trên các văn bản.
  + Tự cài đặt thuật toán sắp xếp, tìm kiếm (không sử dụng thư viện có sẵn) với mảng hoặc danh sách liên kết. Tổng quát hóa bằng cách sử dụng con trỏ hàm (tùy chọn).
  + Chỉ sử dụng thư viện string.h của C để xử lý chuỗi.

Nhiệm vụ:
- Tạo file index.txt - done
- Tạo file metadata.txt - not done 
- Cách đọc file bằng tiếng việt - done - At: https://github.com/tntxtnt/VietnameseIO/blob/master/VietnameseIO/umain.cpp
- Xóa dấu tiếng việt http://tientrieu.net/4185-bo-dau-tieng-viet-trong-cpp.html
- Tạo hàm để rút trích văn bản, từ khóa (lấy ra những từ quan trọng) gồm tìm kiếm văn bản, loại bỏ stopword - not done
- Nghiên cứu cách lưu trữ tên văn bản trong index.txt (skip list?). Mục đích tối ưu cập nhập việc thêm, xóa. - not done
