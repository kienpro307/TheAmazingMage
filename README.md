# The Amazing Mage
- Họ và tên: Nguyễn Đức Kiên
- Mã sinh viên: 21020339
- Lớp môn học: INT2215 1, nhóm 8
## 1. Hướng dẫn cài đặt 
#### Mở Command Prompt bằng cách ấn tổ hợp phím Windows+R và gõ
```
cmd
```
#### Tạo một folder bất kỳ và copy lại địa chỉ của nó, sau đó gõ
```
cd địa-chỉ-folder
```
#### Gõ dòng lệnh sau
```
git clone https://github.com/kienpro307/TheAmazingMage.git
```
#### Mở file .sln lên

![2](https://user-images.githubusercontent.com/100121756/170998599-ba204f38-37cf-4ea5-aa60-84c179008634.png)

#### Chỉnh phần debug thành x86 và ấn Local Windows Debugger
![1](https://user-images.githubusercontent.com/100121756/170998554-c865fa17-ede3-49d9-aca7-2f5d49b3be2b.png)

## 2. Mô tả chung về trò chơi, các ý tưởng chính
- Người chơi vai nhân vật là phù thủy vượt qua hầm ngục và chiến đấu với quái vật để thoát ra ngoài
- Người chơi có 3 mạng, nếu số mạng trở về 0 và mất thêm mạng nữa thì trò chơi sẽ kết thúc và hiện ra bảng "Game Over"
- Có thể thu thập kim cương 
- Cố gắng né tránh đạn của kẻ thù, quái vật và bẫy hố

## 3. Mô tả các chức năng đã cài đặt
### Video minh họa:
- https://youtu.be/vVpKPWSLRF8

### Sinh ra và di chuyển
- Trượt bản đồ: Bản đồ sẽ di chuyển với nhân vật chính là trung tâm màn hình
- Quái vật sinh ra theo quy luật
### Xử lý va chạm
- Giữa người chơi và:
  - Quái vật
  - Đạn của quái vật
  - Hố bẫy
  - Kim cương
  - Mặt đất
- Giữa quái vật và:
  - Đạn của người chơi
  - Người chơi
  - Mặt đất
### Xử lý đối tượng: 
- Người chơi:
  - Có khả năng di chuyển theo ý người dùng (phím trái, phải, trên)
  - Có thể bắn cầu lửa tiêu diệt quái vật (click chuột trái)
  - Đi đến cổng dịch chuyển ở cuối bản đồ để hoàn thành trò chơi
- Quái vật
  - Có thể di chuyển trong một khoảng nhất định
  - Có thể bắn cầu lửa tiêu diệt người chơi
### Giao diện người dùng: 
- Màn hình Menu:
  - Nút `Start`: Bắt đầu chơi
  - Nút `Exit`: Thoát trò chơi
- Màn hình Game Over:
  - Click `OK`  nút tắt ở góc phải màn hình để thoát
- Chỉ số nhân vật
  - Số mạng của nhân vật 
  - Số kim cương ăn được
  - Thời gian
### Âm thanh:
- Nhạc nền
- Tiếng beep khi thao tác trên menu
- Tiếng đạn bắn của người chơi
### Xử lí FPS(Frames per second): Tùy chỉnh tùy ý

## 4. Các kỹ thuật lập trình được sử dụng trong chương trình
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
- Kĩ thuật design để thiết kế đồ họa Game
## 5. Kết luận, hướng phát triển và các điều tâm đắc rút ra được sau khi hoàn thành chương trình
### Kết luận
- Khi làm game nên làm cấu trúc game trước rồi mới bắt đầu tập trung xây dựng những mảng con
- Cần vạch ra 1 trình tự của game để xây dựng game không bị lỗi logic, không bị rời rạc và không khó sửa. Vừa làm vừa tách file kiểm tra lỗi liên tục
- Nên phân chia các object ra thành từng class và từng file riêng để tiện cho việc code và fix bug trong trường hợp chương trình có lỗi. Ngoài ra nó còn giúp người đọc code dễ dàng hình dung chương trình của mình làm gì. 
### Hướng phát triển của Game:
- Sẽ có thêm chức năng chọn nhân vật và nhân vật đa dạng hơn
- Có nhiều bản đồ hơn
- Đồ họa game sẽ đẹp hơn
- Có thêm các item phụ tăng sức mạnh cho nhân vật
- Bổ sung thêm nhiều loại đạn
- Quái vật sẽ mạnh hơn
- Sẽ có Boss ở mỗi màn chơi
- Có thời gian cho mỗi màn chơi và nhân vật sẽ phải hoàn thành màn chơi trước khi hết thời gian
- Cải thiện lại giao diện menu
- Tối ưu code hơn 
### Những điều tâm đắc sau khi hoàn thành chương trình:
- Biết cách đặt tên biến đúng với quy tắc chung và chia chương trình thành nhiều file để tiện cho việc lập trình
- Biết được cấu trúc vòng lặp của một game đơn giản và áp 
- Có thêm kinh nghiệm tìm tòi kiến thức mới trên mạng để sửa lỗi phát sinh khi chạy chương trình
- Biết liên kết thư viện với project
- Có kiến thức sâu hơn về kĩ thuật lập trình hướng đối tượng, class, tính kế thừa và cách áp dụng những kiến thức 
