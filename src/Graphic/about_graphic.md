- Ở folder này chứa các hàm và loader dành cho texture. Chương trình sử dụng hai phương thức load texture. Một là dành cho các object riêng lẻ không có nhiều animation khác nhau bằng [TextureLoader](./TextureLoader.h). Hai là dành cho các object có nhiều animation sẽ được load bằng [ObjectParser](../Parser/ObjectParser.h).

- Cả hai phương thức đều dùng đến [TextureManager](./TextureManager.h). Đây là lớp quản lý Texture có trong chương trình.

- Hình ảnh trong chương trình đều lấy từ nguồn mở, miễn phí, đa só từ: https://itch.io/game-assets. Hầu hết các hình ảnh không được sử dụng ngay mà được xử lý qua các phần mềm khác nhau. Ở đây, mình dùng `Adobe Photoshop` để edit hình ảnh, và `Aseprite` để edit sprites. Bạn có thể tải miễn phí `Aseprite` tại https://github.com/aseprite/aseprite, đây là một phần mềm mã nguồn mở.
  + Xem cụ thể các hình ảnh trong game tại folder [assets](../../Adventure_Time/assets/).

- Ngoài ra, các hình ảnh còn lại gồm có:
  + Hình ảnh thành tựu lấy từ Dark soul 3: https://rezuaq.be/new-area/image-creator/
  + Hình nền lấy từ: https://saga-of-a-new-world.com/gallery/
