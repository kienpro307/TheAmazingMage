# Hướng dẫn cài đặt 
1. Mở Command Prompt bằng cách ấn tổ hợp phím Windows+R và gõ
```
cmd
```
2. Tạo một folder bất kỳ và copy lại địa chỉ của nó, sau đó gõ
```
cd địa-chỉ-folder
```
3. Gõ dòng lệnh sau
```
git clone https://github.com/kienpro307/TheAmazingMage.git
```
4. Mở file .sln lên

![2](https://user-images.githubusercontent.com/100121756/170998599-ba204f38-37cf-4ea5-aa60-84c179008634.png)

5. Chỉnh phần debug thành x86 và ấn Local Windows Debugger
![1](https://user-images.githubusercontent.com/100121756/170998554-c865fa17-ede3-49d9-aca7-2f5d49b3be2b.png)

# Mô tả chung về trò chơi, các ý tưởng chính
Game 2D Platformer cổ điển lấy cảm hứng từ Mario và có cách hoạt động tương tự, đồng thời được phát triển thêm một số tính năng mới

Ý tưởng game: Nhân vật sẽ vượt qua các hố bẫy, tránh quái vật, tiêu diệt quái vật để đi đến cuối bản đồ

# Mô tả các chức năng đã cài đặt

Menu mở đầu: Có 2 lựa chọn là Start và Exit, khi chọn sẽ phát ra tiếng beep

Hiển thị thời gian và số lượng kim cương đã ăn được

Đối với nhân vật: 
 - Có khả năng di chuyển theo ý người dùng (trái, phải, nhảy)

 - Có thể bắn cầu lửa tiêu diệt quái vật

 - Thu thập kim cương

Đối với quái:
 - Có thể di chuyển trong một khoảng nhất định

 - Có thể bắn cầu lửa tiêu diệt người chơi

Đi đến cổng dịch chuyển ở cuối bản đồ để hoàn thành trò chơi

- Video minh họa:

https://youtu.be/vVpKPWSLRF8

# Các kỹ thuật lập trình được sử dụng trong chương trình
- Kĩ thuật design để thiết kế đồ họa Game

- Kĩ thuật TileMap: Chia bản đồ thành lưới ô vuông gồm nhiều ô nhỏ, mỗi ô có một chỉ số nhất định. Việc này sẽ giúp xử lí di chuyển, va chạm dễ dàng hơn. 

- Struct và Class: Dùng để quản lí các đối tượng và thuộc tính của chúng. Cụ thể là: 
    - Nhân vật chính
    -  Quái vật
    -  Đạn 
    -  Bản đồ
    -  Texture
    -  Thời gian 
    -  Đạn
    -  Vật cản

- Vector: Dùng để tạo danh sách lưu trữ quái vật và đạn bắn

- Con trỏ: Quản lí object game, giảm gánh nặng xử lý memory

- Lập trình hướng đối tượng, vận dụng tính đóng gói, kế thừa, có thể dùng lại thuộc tính của một class cho các class con khác

- Sử dụng thư viện đồ họa 
  - SDL2
  - SDL2_Image để xử lí hình ảnh
  - SDL2_mixer để xử lí âm thanh
  - SDL2_ttf để xử lí chữ in lên màn hình


# Kết luận, hướng phát triển và các điều tâm đắc rút ra được sau khi hoàn thành chương trình
Kết luận
- Nên phân chia các object ra thành từng class và từng file riêng để tiện cho việc code và fix bug trong trường hợp chương trình có lỗi. Ngoài ra nó còn giúp người đọc code dễ dàng hình dung chương trình của mình làm gì. Khi làm game nên làm cấu trúc game trước rồi mới bắt đầu tập trung xây dựng những mảng con.
- Cần vạch ra 1 trình tự của game để xây dựng game không bị lỗi logic, không bị rời rạc và không khó sửa. Vừa làm vừa tách file kiểm tra lỗi liên tục

Hướng phát triển của Game:
- Sẽ có thêm chức năng chọn nhân vật
- Có nhiều bản đồ hơn
- Có thêm các item phụ tăng sức mạnh cho nhân vật
- Quái vật sẽ mạnh hơn
- Có thời gian cho mỗi màn chơi và nhân vật sẽ phải hoàn thành màn chơi trước khi hết thời gian

Những điều tâm đắc sau khi hoàn thành chương trình:
- Biết cách đặt tên biến đúng với quy tắc chung và chia chương trình thành nhiều file để tiện cho việc lập trình
- Biết được cấu trúc vòng lặp của một game đơn giản
- Có thêm kinh nghiệm tìm tòi kiến thức mới trên mạng để sửa lỗi phát sinh khi chạy chương trình
- Biết liên kết thư viện với project
- Có kiến thức sâu hơn về kĩ thuật lập trình hướng đối tượng, class, tính kế thừa và cách áp dụng những kiến thức 
