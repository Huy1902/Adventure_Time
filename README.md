# Adventure Time - Huy1902

# Lời đầu

+ Họ và tên: Nguyễn Quốc Huy - K68CB

+ Mã sinh viên: 23020082

+ Bài tập lớn: Adventure Time 

# Giới thiệu game

- Video giới thiệu game:

- Adventure Time là một game thuộc thể loại RPG. Game thủ được nhập vai vào một chiến binh vô danh đang trên con đường đánh bại các Lord of Space, những người nắm giữ quyền năng to lớn của The First Crystal. Liên tục đối đầu với những chiến binh thiện chiến, giành lấy sức mạnh to lớn và bước lên đỉnh vinh quang từ tro tàn. 

# 0. Cách tải game

## a. Cách 1: Không bao gồm code.

- Tải file AdventureTime!!!.rar tại link sau: [AdventureTime!!!v1.0.0](https://github.com/Huy1902/Adventure_Time/releases/tag/v1.0.0) hoặc bạn có thể click vào link này để tải ngay: https://github.com/Huy1902/Adventure_Time/releases/download/v1.0.0/AdventureTime.rar
- Giải nén game vào một thư mục bất kỳ và click vào file Adventure_Time.exe để khởi động game.

## b. Cách 2: Bao gồm code và có thể biên dịch.

**Bước 1:** Tải file source code trong phần release tại link sau: [AdventureTime!!!v1.0.0](https://github.com/Huy1902/Adventure_Time/releases/tag/v1.0.0) hoặc bạn có thể click vào link này để tải ngay: https://github.com/Huy1902/Adventure_Time/archive/refs/tags/v1.0.0.zip.

- Tất cả code đều nằm trong thư mục Adventure_Time.

**Bước 2:** Cài Visual Studio. Khi xây dựng chương trình, mình dùng Visual Studio 2022. Bạn có thể tham khảo hướng dẫn cài tại: https://learn.microsoft.com/en-us/visualstudio/install/install-visual-studio?view=vs-2022 hoặc trên Youtube: https://www.youtube.com/watch?v=HS4c3kBEWr4.

**Bước 3:** Mở file Adventure_Time.sln. ![image](demo_resources/install.png)
- Bạn có thể nhấn `Ctrl + F5` để chạy game trong Visual Studio.

# 1. Tính năng game
- Có intro sinh động khi vào game.
- Màn hình menu cùng các nút bật tắt âm thanh cho người chơi.
- Bảng xếp hạng điểm cập nhật sau mỗi lần chơi và lưu lại kết quả trên máy, có thể truy cập lại.
- Màn hình đợi cùng các Tip hữu ích khi chơi game.
- Background chuyển động vô hạn cùng âm nhạc nhẹ nhàng.
- SFX khi bạn click các nút bấm.
- Nhân vật chính có các hành động cùng âm thanh đi kèm sinh động.
- Hệ thống quái sở hữu hành động cùng các tính chất riêng.
- Boss mạnh mẽ và thử thách.
- Những sự kiện khác nhau cùng màn hình thành tựu: lưu save point, hạ boss, hồi sinh, bị hạ gục, đặt chân lên map khác.
- Hỗ trợ dừng game và xem trạng thái của nhân vật.
- Cơ chế level up và tăng sức mạnh nhân vật
- Hệ thống skill hỗ trợ người chơi tiêu diệt kẻ địch.
- Cơ chế đỡ và làm choáng kẻ địch.
- Cơ chế crit và miss các đòn đánh.

# 2. Bắt đầu game:
- Khi khởi động game, chương trình sẽ hiện màn hình Intro. Nhấn phím hoặc nhấn chuột trái để tiếp tục.
![image](demo_resources/intro_demo.png)

- Game sẽ vào thẳng màn hình chính.
![image](demo_resources/main_menu.png)

- Chọn Play để vào game hoặc chọn Score để xem bảng xếp hạng ba điểm cao nhất.
![image](demo_resources/standing.png)

- Nhấn exit để thoát game.

# 3. Hướng dẫn chơi game:
- Sau khi nhấn Play tại màn hình chính, người chơi sẽ thấy màn hình đợi. Đây cũng sẽ là màn hình hiện mỗi khi người chơi chuyển map. Có vài tip khá hữu dụng được hiện tại đây.
![image](demo_resources/loading.png)

- Màn hình chơi game khá dễ làm quen. Điều bạn cần chú ý khi chơi là điểm số ![image](demo_resources/Score.png) và trạng thái máu và thể lực của nhân vật ![image](demo_resources/HP_STA.png).
![image](demo_resources/playing.png)

## a. Về nhân vật:

- Các phím điều khiển:

| Control |    Key   |
|---------|----------|
| LEFT    |     A    |
| RIGHT   |     D    |
| JUMP    |     K    |
| DASH    |     L    |
| ATTACK  |     J    |
| BASH    |     U    |
| SPELL 1 |     Q    |
| SPELL 2 |     E    |

- Lưu ý: Nếu nhân vật của bạn không di chuyển, hãy xem lại bạn có đang để ngôn ngữ khác ngoài tiếng Anh trên máy không. Với Window, chọn English tại Keyboard layout để nhân vật di chuyển mượt mà.

## b. Về cơ chế chơi:
- Nhân vật gây sát thương lên kẻ địch bằng đòn tần công thường hoặc sử dụng các phép.
![image](demo_resources/darkra.png)

- Nhân vật có thể làm choáng kẻ địch bằng các đòn bash. Khi bash nhân vật sẽ không nhận sát thương, và nếu sử dụng đúng lúc kẻ địch tấn công, kẻ địch sẽ bị choáng.
![image](demo_resources/bash_success.png)

- Khi kẻ địch bị choáng, nhấn phím `J` nhân vật sẽ thực hiện đòn crit. Đây là đòn đánh gây cực kỳ nhiều sát thương. Hãy tận dụng cơ chế để hạ gục quái nhanh hơn.
![image](demo_resources/crit.png)
  + Lưu ý: Cơ chế này chỉ áp dụng với kẻ địch mang vũ khí tầm gần. Kẻ địch là cung thủ sẽ miễn khống chế.

- Nhân vât có thể lưu điểm hồi sinh tại các cổng dịch chuyển hoặc trại lửa.
![image](demo_resources/bonfire.png)

- Di chuyển của các map khác nhau bằng cổng dịch chuyển màu xanh lá cây, khi đặt chân tới một vùng đất tên của nó sẽ hiện lên màn hình.
![image](demo_resources/portal.png)

- Nếu kẻ địch hạ gục bạn, thông báo "You died" sẽ hiện ra.
![image](demo_resources/died.png)

- Khi bị hạ gục, nhân vật sẽ hồi sinh tại điểm lưu gần nhất.
![image](demo_resources/revival.png)

- Khi hạ gục boss, thành tựu sẽ hiện ra. Bạn đã trở nên mạnh mẽ hơn rồi.
![image](demo_resources/boss_fallen.png)

- Sử dụng các đòn tấn công thường hay lướt sẽ tiêu tốn thể lực. Ngược lại, khi dùng skill, bạn không tiêu tốn thể lực nhưng sẽ có thời gian hồi và gây ít sát thương hơn. Đòn crit không tiêu hao gì cả.

## c. Kẻ địch

- Có ba loại kẻ địch thường trong game:

|                                         | Tên kẻ địch	       | Khả năng và sức mạnh                                                                                       |
|-----------------------------------------|--------------------|--------------------------------------------------------------------------------------------------|
| ![gif](demo_resources/Knight.gif) | Barrel Knight	  | Chiêu thức đa dạng, khánh phép cao.                                                                       |
| ![image](resources/images/Choose_level/flag.png)   | Flag Zombie	       | Báo hiệu một lượng lớn zombie đang chuẩn bị ra.                                                  |
| ![image](resources/images/Choose_level/cone.png)   | Conehead Zombie	   | Trâu gấp 3 lần zombie thường                                                                     |
| ![image](resources/images/Choose_level/bucket.png) | Buckethead Zombie	 | Trâu gấp 6.5 lần zombie thường                                                                   |
|








